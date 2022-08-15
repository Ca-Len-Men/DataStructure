#ifndef _FISH_SET_
#define _FISH_SET_

#include "limitlist.h"
#include<initializer_list>

/*===================================================
Author : Ca Len Men (or Fish Climb Tree)			=
Set : set<datatype>						            =
===================================================*/

/* Set is a B+ Tree.
You must have copy constructor, operator<, operator== for your datatype.*/

namespace dsa
{
	//##################################################
	//==========          SET          ==========//
	template <class datatype>
	class set {
		//=====     Sub Class     =====//
#pragma region Sub Class
		class node {
		public:
			//=====     Attributes     =====//
			datatype* values[2];			// List value
			node* ptrs[3];					// Branch
			int num;						// 

			//=====     Constructor     =====//
			node() : num(0)
			{
				values[0] = values[1] = nullptr;
				ptrs[0] = ptrs[1] = ptrs[2] = nullptr;
			}

			// Push an element at index into node
			void push_value(datatype*& pointer, size_t index) {
				if (index == 0u) {
					if (values[1] == nullptr)	// 1 0
						values[1] = values[0];
					else {	// 1 2 0
						datatype* temp(pointer);
						pointer = values[1];
						values[1] = values[0];
						values[0] = temp;
						return;
					}
					values[0] = pointer;
					pointer = nullptr;
				}
				else if (index == 1u)
					std::swap(values[1], pointer);
			}

			// Push an branch at index into 
			void push_node(node*& pointer, size_t index) {
				switch (index) {
				case 0u:
					if (ptrs[1] == nullptr)
						ptrs[1] = ptrs[0];
					else {
						if (ptrs[2] == nullptr) {
							ptrs[2] = ptrs[1];
							ptrs[1] = ptrs[0];
						}
						else {
							node* temp(pointer);
							pointer = ptrs[2];
							ptrs[2] = ptrs[1];
							ptrs[1] = ptrs[0];
							ptrs[0] = temp;
							return;
						}
					}
					ptrs[0] = pointer;
					pointer = nullptr;
					break;
				case 1u:
					if (ptrs[2] == nullptr)
						ptrs[2] = ptrs[1];
					else {
						node* temp(pointer);
						pointer = ptrs[2];
						ptrs[2] = ptrs[1];
						ptrs[1] = temp;
						return;
					}
					ptrs[1] = pointer;
					pointer = nullptr;
					break;
				case 2u:
					std::swap(ptrs[2], pointer);
				}
			}

			// Pop an element at index
			void pop_value(size_t index) {
				if (index == 0u)
					values[0] = values[1];
				values[1] = nullptr;
			}

			// Pop an branch at index
			void pop_node(size_t index) {
				if (index == 0u) {
					ptrs[0] = ptrs[1];
					ptrs[1] = ptrs[2];
				}
				else if (index == 1u)
					ptrs[1] = ptrs[2];
				ptrs[2] = nullptr;
			}

			// Find branch
			size_t find_branch(const datatype& value) {	// Node is not empty
				if (value < *values[0])
					return 0u;
				if (values[1] == nullptr || value < *values[1])
					return 1u;
				return 2u;
			}

			// Index of min value from this leaf node to next leaf node
			datatype* min_to_right() {
				if (values[0])
					return values[0];
				return ptrs[1]->values[0];
			}

			// Sum
			void sum() {
				num = ptrs[0]->num;
				if (ptrs[1])
					num += ptrs[1]->num;
				if (ptrs[2])
					num += ptrs[2]->num;
				if (num < 0)
					num = -num;
			}
		};
#pragma endregion

		//=====     Private Methods     =====//
#pragma region Private Methods
	// Default constructor
		void default_constructor() {
			head = new node;
			tail = new node;
			linked(head, tail);
		}

		// Linked
		void linked(node* prev, node* next) {
			prev->ptrs[1] = next;
			next->ptrs[0] = prev;
		}

		// Linked
		void linked(node* prev, node* mid, node* next) {
			prev->ptrs[1] = mid;
			mid->ptrs[0] = prev;
			mid->ptrs[1] = next;
			next->ptrs[0] = mid;
		}

		// Push recursion
		bool push_recursion(node*& rootnode, const datatype& value, datatype*& ptr_value, node*& ptr_node) {
			size_t index = rootnode->find_branch(value);
			if (rootnode->num < 0) {	// rootnode is leaf
				if (index > 0 && value == *rootnode->values[index - 1u])		// Duplicated
					return false;

				// Don't duplicate
				ptr_value = new datatype(value);
				rootnode->push_value(ptr_value, index);
				++size;

				if (rootnode == root && ptr_value) {		// Rootnode is root
					// Create new node
					node* temp = new node;
					temp->values[0] = rootnode->values[1];
					temp->values[1] = ptr_value;
					temp->num = -2;
					rootnode->values[1] = nullptr;
					rootnode->num = -1;

					// Linked
					linked(rootnode, temp, tail);

					// Create top layer
					temp = new node;
					temp->num = 3;
					temp->ptrs[0] = rootnode;
					temp->ptrs[1] = rootnode->ptrs[1];
					temp->values[0] = rootnode->ptrs[1]->values[0];
					root = temp;
					return true;
				}

				--rootnode->num;
				return true;
			}

			// Rootnode is not leaf
			// Recursion
			bool result = push_recursion(rootnode->ptrs[index], value, ptr_value, ptr_node);
			if (result == false)
				return false;
			++rootnode->num;
			if (ptr_value == nullptr)		// Leaf node is not full
				return true;

			node* sub_node = rootnode->ptrs[index];
			// Sub node is full
			if (sub_node->num < 0) {	// The node closest to the leaf node
				// Create new node
				ptr_node = new node;
				ptr_node->values[0] = sub_node->values[1];
				ptr_node->values[1] = ptr_value;
				ptr_node->num = -2;
				sub_node->values[1] = nullptr;
				sub_node->num = -1;

				// Linked
				linked(sub_node, ptr_node, sub_node->ptrs[1]);

				// Push into rootnode
				ptr_value = ptr_node->values[0];
				rootnode->push_value(ptr_value, index);
				rootnode->push_node(ptr_node, index + 1u);
			}
			else {	// Node
				node* temp = new node;
				temp->values[0] = ptr_value;
				temp->ptrs[0] = sub_node->ptrs[2];
				temp->ptrs[1] = ptr_node;
				sub_node->ptrs[2] = nullptr;

				temp->sum();
				sub_node->sum();

				ptr_value = sub_node->values[1];
				sub_node->values[1] = nullptr;
				ptr_node = temp;

				// Push into rootnode
				rootnode->push_value(ptr_value, index);
				rootnode->push_node(ptr_node, index + 1u);
			}

			if (ptr_value && rootnode == root) {	// Rootnode is root
				node* temp = new node;
				temp->values[0] = ptr_value;
				temp->ptrs[0] = rootnode->ptrs[2];
				temp->ptrs[1] = ptr_node;
				rootnode->ptrs[2] = nullptr;

				temp->sum();
				rootnode->sum();

				node* newroot = new node;
				newroot->values[0] = rootnode->values[1];
				rootnode->values[1] = nullptr;
				newroot->ptrs[0] = rootnode;
				newroot->ptrs[1] = temp;
				newroot->sum();

				root = newroot;
			}

			return true;
		}

		// Pop recursion
		bool pop_recursion(node*& rootnode, const datatype& value, datatype**& ref_value) {
			size_t index = rootnode->find_branch(value);
			// Rootnode is leaf
			if (rootnode->num < 0) {
				if (index == 0u)	return false;	// Does not contains value
				--index;
				if (value == *rootnode->values[index])	// Have contains value
					delete rootnode->values[index];
				else
					return false;
				rootnode->pop_value(index);
				++rootnode->num;
				--size;

				// Root is empty -> delete root
				if (rootnode == root && rootnode->values[0] == nullptr) {
					delete root;
					root = nullptr;
					linked(head, tail);
					return true;
				}

				if (ref_value)
					*ref_value = rootnode->min_to_right();
				return true;
			}

			bool isnode = rootnode->ptrs[0]->num > 0;
			// Rootnode is not leaf, nearest leaf node
			if (index > 0u && value == *rootnode->values[index - 1u])
				ref_value = rootnode->values + index - 1u;
			bool get = pop_recursion(rootnode->ptrs[index], value, ref_value);
			if (get == false)						// Does not contains value
				return false;
			--rootnode->num;
			if (rootnode->ptrs[index]->values[0])	// Sub node is still enough
				return true;

			// Have contains value
			node* sibling(nullptr);
			if (isnode == false) { // Nearest leaf node
				// Borrow value from left sibling
				if (index > 0u && rootnode->ptrs[index - 1u]->values[1]) {
					sibling = rootnode->ptrs[index - 1u];
					rootnode->ptrs[index]->values[0] = sibling->values[1];
					rootnode->values[index - 1u] = sibling->values[1];
					sibling->values[1] = nullptr;
					sibling->num = rootnode->ptrs[index]->num = -1;
					return true;
				}
				else if (index <= 1u && rootnode->ptrs[index + 1u] && rootnode->ptrs[index + 1u]->values[1]) {
					// Borrow value from right sibling
					sibling = rootnode->ptrs[index + 1u];
					rootnode->ptrs[index]->values[0] = sibling->values[0];
					if (index > 0u)
						rootnode->values[index - 1u] = sibling->values[0];
					rootnode->values[index] = sibling->values[1];
					sibling->values[0] = sibling->values[1];
					sibling->values[1] = nullptr;
					sibling->num = rootnode->ptrs[index]->num = -1;
					return true;
				}
				else {	// Merge
					int temp = index - 1;
					if (temp < 0) temp = 0;
					linked(rootnode->ptrs[index]->ptrs[0], rootnode->ptrs[index]->ptrs[1]);
					delete rootnode->ptrs[index];
					rootnode->pop_value(temp);
					rootnode->pop_node(index);
				}
			}
			else {	// Node
				if (index > 0u && rootnode->ptrs[index - 1u]->values[1]) {
					// Borrow value from left sibling
					sibling = rootnode->ptrs[index - 1u];
					rootnode->ptrs[index]->ptrs[1] = rootnode->ptrs[index]->ptrs[0];
					rootnode->ptrs[index]->ptrs[0] = sibling->ptrs[2];
					rootnode->ptrs[index]->values[0] = rootnode->values[index - 1u];
					rootnode->values[index - 1u] = sibling->values[1];
					sibling->ptrs[2] = nullptr;
					sibling->values[1] = nullptr;
					sibling->sum();
					rootnode->ptrs[index]->sum();
					return true;
				}
				else if (index <= 1u && rootnode->ptrs[index + 1u] && rootnode->ptrs[index + 1u]->values[1]) {
					// Borrow value from right sibling
					sibling = rootnode->ptrs[index + 1u];
					rootnode->ptrs[index]->ptrs[1] = sibling->ptrs[0];
					sibling->pop_node(0u);
					rootnode->ptrs[index]->values[0] = rootnode->values[index];
					rootnode->values[index] = sibling->values[0];
					sibling->values[0] = sibling->values[1];
					sibling->values[1] = nullptr;
					sibling->sum();
					rootnode->ptrs[index]->sum();
					return true;
				}
				else {	// Merge
					if (index == 0u) {	// Merge to right
						sibling = rootnode->ptrs[1];
						sibling->values[1] = sibling->values[0];
						sibling->values[0] = rootnode->values[0];
						sibling->push_node(rootnode->ptrs[0]->ptrs[0], 0u);
						delete rootnode->ptrs[0];
						rootnode->pop_value(0u);
						rootnode->pop_node(0u);
						rootnode->ptrs[0]->sum();
					}
					else {	// Merge to left
						sibling = rootnode->ptrs[index - 1u];
						sibling->ptrs[2] = rootnode->ptrs[index]->ptrs[0];
						sibling->values[1] = rootnode->values[index - 1u];
						delete rootnode->ptrs[index];
						rootnode->pop_value(index - 1u);
						rootnode->pop_node(index);
						sibling->sum();
					}
				}
			}

			// Delete top layer
			if (rootnode->values[0] == nullptr && rootnode == root) {
				node* temp = rootnode->ptrs[0];
				delete rootnode;
				root = temp;
			}
			return true;
		}

		// Clear recursion
		void clear_recursion(node* rootnode) {
			if (rootnode->num < 0) {
				delete rootnode->values[0];
				delete rootnode->values[1];
				delete rootnode;
				return;
			}

			clear_recursion(rootnode->ptrs[0]);
			clear_recursion(rootnode->ptrs[1]);
			if (rootnode->ptrs[2])
				clear_recursion(rootnode->ptrs[2]);
			delete rootnode;
		}

		// Copy data from other tree with other root
		datatype* copy_recursion(node*& rootnode, node* othernode, queue<node*>& qu) {
			rootnode = new node;
			rootnode->num = othernode->num;

			// Node is leaf
			if (othernode->num < 0) {
				rootnode->values[0] = new datatype(*othernode->values[0]);
				if (othernode->values[1])
					rootnode->values[1] = new datatype(*othernode->values[1]);
				qu.push(rootnode);
				return rootnode->values[0];
			}

			datatype* min_value_of_branch = copy_recursion(rootnode->ptrs[0], othernode->ptrs[0], qu);
			rootnode->values[0] = copy_recursion(rootnode->ptrs[1], othernode->ptrs[1], qu);
			if (othernode->ptrs[2])
				rootnode->values[1] = copy_recursion(rootnode->ptrs[2], othernode->ptrs[2], qu);
			return min_value_of_branch;
		}

		void linked_leafnode(queue<node*>& qu) {
			qu.push(tail);
			node* prev_node = head, * next_node;
			for (; qu; prev_node = next_node) {
				next_node = qu.pop();
				linked(prev_node, next_node);
			}
		}
#pragma endregion

		//=====     Attributes     =====//
#pragma region Attributes
		node* root, * head, * tail;
		size_t size;
#pragma endregion

	public:
		//=====     Constructors and Destructor     =====//
#pragma region Constructors and Destructor
		set() : root(nullptr), size(0u)
		{
			default_constructor();
		}

		set(std::initializer_list<datatype> list) : root(nullptr), size(0u)
		{
			default_constructor();
			for (const datatype& item : list)
				push(item);
		}

		template <class anyIterator>
		set(anyIterator begin, anyIterator end) : root(nullptr), size(0u)
		{
			default_constructor();
			for (; begin != end; ++begin)
				push(*begin);
		}

		set(const set& source) : root(nullptr), size(source.size)
		{
			default_constructor();
			if (source.empty())
				return;

			queue<node*> qu;
			copy_recursion(root, source.root, qu);
			linked_leafnode(qu);
		}

		set(set&& source) noexcept :
			root(source.root), head(source.head), tail(source.tail), size(source.size)
		{
			source.root = source.head = source.tail = nullptr;
		}

		~set() {
			if (root != nullptr)
				clear_recursion(root);
			delete head;
			delete tail;
		}
#pragma endregion

		//=====     Methods     =====//
#pragma region Methods
	// Push an item into Set
		bool push(const datatype& value) {
			if (root == nullptr) {
				root = new node;
				root->values[0] = new datatype(value);
				root->num = -1;

				linked(head, root, tail);
				size = 1u;
				return true;
			}

			datatype* ptr_value(nullptr);
			node* ptr_node(nullptr);
			return push_recursion(root, value, ptr_value, ptr_node);
		}

		// Pop an item out of Set
		bool pop(const datatype& value) {
			datatype** res(nullptr);
			return pop_recursion(root, value, res);
		}

		// Set has contains the value
		bool contains(const datatype& value) const {
			if (root == nullptr)
				return false;

			node* res = root;
			while (res->num > 0)
				res = res->ptrs[res->find_branch(value)];
			size_t index = res->find_branch(value);

			if (index == 0u)
				return false;
			return value == *res->values[index - 1u];
		}

		// Clear Set
		void clear() {
			if (root == nullptr)
				return;
			clear_recursion(root);
			root = nullptr;
			size = 0u;
			linked(head, tail);
		}

		//Swap two Set
		void swap(set& source) {
			std::swap(this->root, source.root);
			std::swap(this->size, source.size);
			std::swap(this->head, source.head);
			std::swap(this->tail, source.tail);
		}

		//Writting on Console
		void out() const {
			std::cout << '[';
			for (auto i = begin(), j = end(); i != j; ++i)
			{
				std::cout << *i;
				if (i.next() != j)
					std::cout << ", ";
			}
			std::cout << "]\n";
		}

		// Set is empty
		bool empty() const {
			return root == nullptr;
		}

		// Length of Set
		size_t len() const {
			return size;
		}
#pragma endregion

		//=====     Operators     =====//
#pragma region Operators
	// Set is not empty
		operator bool() const {
			return root != nullptr;
		}

		// True if Set has contains the value
		bool operator[](const datatype& value) const {
			return contains(value);
		}

		// Get item at index
		const datatype& operator()(int index) const {
			node* res = root;
			for (int i = 0; res->num > 0; res = res->ptrs[i], i = 0) {
				if (index >= std::abs(res->ptrs[0]->num)) {
					index -= std::abs(res->ptrs[0]->num);
					++i;
				}
				else
					continue;

				if (res->ptrs[1] && index >= std::abs(res->ptrs[1]->num)) {
					index -= std::abs(res->ptrs[1]->num);
					++i;
				}
			}
			return *res->values[index];
		}

		// Copy data from other Set
		set& operator=(const set& source)
		{
			if (this == &source)
				return *this;

			if (root != nullptr)
				clear_recursion(root);
			size = source.size;

			queue<node*> qu;
			copy_recursion(root, source.root, qu);
			linked_leafnode(qu);
			return *this;
		}

		// Copy data from other Set
		set& operator=(set&& source) noexcept
		{
			if (root != nullptr)
				clear_recursion(root);
			delete head;
			delete tail;
			size = source.size;
			root = source.root;
			head = source.head;
			tail = source.tail;
			source.root = source.head = source.tail = nullptr;
			return *this;
		}
#pragma endregion

		//=====     Iterator     =====//
#pragma region Iterator
		class iterator {
			friend set;

			//=====     Attributes     =====//
			const set* ref;
			const node* ptrNode;
			size_t idx;

			iterator(const set* _ref, const node* _ptrNode, size_t _idx) :
				ref(_ref), ptrNode(_ptrNode), idx(_idx) {}
		public:
			//=====     Constructors     =====//

			iterator(const iterator& source) : ref(source.ref),
				ptrNode(source.ptrNode), idx(source.idx) {}

			//=====     Methods     =====//

			// Iterator is null
			bool null() const {
				return this->ptrNode->num == 0;
			}

			// Iterator next
			iterator next() const {
				return ++iterator(*this);
			}

			// Iterator prev
			iterator prev() const {
				return --iterator(*this);
			}

			//=====     Operators     =====//

			// Get const value of item
			const datatype& operator*() const {
				return *this->ptrNode->values[this->idx];
			}

			// Get index ( type const data* ) of item
			const datatype* operator->() const {
				return this->ptrNode->values[this->idx];
			}

			// Iterator move to the next item
			iterator& operator++() {
				if (this->ptrNode->num == 0)
					return *this;
				++this->idx;
				if (this->idx == 2 || this->ptrNode->values[this->idx] == nullptr) {
					this->idx = 0u;
					this->ptrNode = this->ptrNode->ptrs[1];
				}
				return *this;
			}

			// Iterator move to the next item
			iterator operator++(int) {
				iterator res(*this);
				this->operator++();
				return res;
			}

			// The iterator moves to the previous item
			iterator& operator--() {
				if (this->ptrNode->num == 0)
					return *this;
				if (this->idx == 0u) {
					this->ptrNode = this->ptrNode->ptrs[0];
					this->idx = 0u;
					if (this->ptrNode->values[1])
						this->idx = 1u;
				}
				else
					--this->idx;
				return *this;
			}

			// The iterator moves to the previous item
			iterator operator--(int) {
				iterator res(*this);
				this->operator--();
				return res;
			}

			// Copy data from other iterator
			iterator& operator=(const iterator& source) {
				this->ref = source.ref;
				this->ptrNode = source.ptrNode;
				this->idx = source.idx;
				return *this;
			}

			// Compare two iterators
			bool operator==(const iterator& source) const {
				if (this->ptrNode == source.ptrNode) {
					if (this->ptrNode->num == 0)
						return true;
					return this->idx == source.idx;
				}
				return false;
			}

			// Compare two iterators
			bool operator!=(const iterator& source) const {
				return !this->operator==(source);
			}

			// Check iterator not null
			operator bool() const {
				return this->ptrNode->num != 0;
			}
		};
#pragma endregion

		//=====     Const Iterator     =====//
#pragma region Const Iterator
		class const_iterator {
			friend set;

			//=====     Attributes     =====//
			const set* ref;
			const node* ptrNode;
			size_t idx;

			const_iterator(const set* _ref, const node* _ptrNode, size_t _idx) :
				ref(_ref), ptrNode(_ptrNode), idx(_idx) {}
		public:
			//=====     Constructors     =====//

			const_iterator(const const_iterator& source) : ref(source.ref),
				ptrNode(source.ptrNode), idx(source.idx) {}

			//=====     Methods     =====//

			// Const Iterator is null
			bool null() const {
				return this->ptrNode->num == 0;
			}

			// Const Iterator next
			const_iterator next() const {
				return ++const_iterator(*this);
			}

			// Const Iterator prev
			const_iterator prev() const {
				return --const_iterator(*this);
			}

			//=====     Operators     =====//

			// Get const value of item
			const datatype& operator*() const {
				return *this->ptrNode->values[this->idx];
			}

			// Get index ( type const data* ) of item
			const datatype* operator->() const {
				return this->ptrNode->values[this->idx];
			}

			// Const Iterator move to the next item
			const_iterator& operator++() {
				if (this->ptrNode->num == 0)
					return *this;
				++this->idx;
				if (this->idx == 2 || this->ptrNode->values[this->idx] == nullptr) {
					this->idx = 0u;
					this->ptrNode = this->ptrNode->ptrs[1];
				}
				return *this;
			}

			// Const Iterator move to the next item
			const_iterator operator++(int) {
				const_iterator res(*this);
				this->operator++();
				return res;
			}

			// The Const Iterator moves to the previous item
			const_iterator& operator--() {
				if (this->ptrNode->num == 0)
					return *this;
				if (this->idx == 0u) {
					this->ptrNode = this->ptrNode->ptrs[0];
					this->idx = 0u;
					if (this->ptrNode->values[1])
						this->idx = 1u;
				}
				else
					--this->idx;
				return *this;
			}

			// The Const Iterator moves to the previous item
			const_iterator operator--(int) {
				const_iterator res(*this);
				this->operator--();
				return res;
			}

			// Copy data from other Const Iterator
			const_iterator& operator=(const const_iterator& source) {
				this->ref = source.ref;
				this->ptrNode = source.ptrNode;
				this->idx = source.idx;
				return *this;
			}

			// Compare two Const Iterator
			bool operator==(const const_iterator& source) const {
				if (this->ptrNode == source.ptrNode) {
					if (this->ptrNode->num == 0)
						return true;
					return this->idx == source.idx;
				}
				return false;
			}

			// Compare two Const Iterator
			bool operator!=(const const_iterator& source) const {
				return !this->operator==(source);
			}

			// Check Const Iterator not null
			operator bool() const {
				return this->ptrNode->num != 0;
			}
		};
#pragma endregion

		//=====     Methods of Iterator, Const Iterator     =====//
#pragma region Methods of Iterator, Const Iterator
	// Iterator of first item
		iterator begin() {
			return iterator(this, this->head->ptrs[1], 0u);
		}

		// Iterator of last item
		iterator rbegin() {
			node* res = this->tail->ptrs[0];
			return iterator(this, res, res->values[1] ? 1u : 0u);
		}

		// Iterator at back of Save Set
		iterator end() {
			return iterator(this, this->tail, 0u);
		}

		// Iterator at front of Save Set
		iterator rend() {
			return iterator(this, this->head, 0u);
		}

		// Const Iterator of first item
		const_iterator begin() const {
			return const_iterator(this, this->head->ptrs[1], 0u);
		}

		// Const Iterator of first item
		const_iterator cbegin() const {
			return const_iterator(this, this->head->ptrs[1], 0u);
		}

		//Const Iterator of last item
		const_iterator crbegin() const {
			node* res = this->tail->ptrs[0];
			return const_iterator(this, res, res->values[1] ? 1u : 0u);
		}

		//Const Iterator at back of Save Set
		const_iterator cend() const {
			return const_iterator(this, this->tail, 0u);
		}

		//Const Iterator at back of Save Set
		const_iterator end() const {
			return const_iterator(this, this->tail, 0u);
		}

		//Const Iterator at front of Save Set
		const_iterator crend() const {
			return const_iterator(this, this->head, 0u);
		}
#pragma endregion
	};

	//==========          Overloading operator<< with std::cout           ==========//
	template <class datatype>
	std::ostream& operator<<(std::ostream& os, const set<datatype>& set) {
		set.out();
		return os;
	}
}
//**************************************************
#endif	// _FISH_SET_
