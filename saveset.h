#ifndef _SAVE_SET_
#define _SAVE_SET_

#pragma region Include
#include<iostream>
#include<initializer_list>
#include<conio.h>
#include "queue.h"
#pragma endregion

#pragma region Syntax

#ifndef _DEFINE_SYNTAX_
#define _DEFINE_SYNTAX_
#define FOR(i, start, end) for(int i = start; i < end; ++i)
#define RFOR(i, last, front) for(int i = last; i >= front; --i)
#define uFOR(i, start, end) for(size_t i = start; i < end; ++i)
#define uRFOR(i, last, front) for(size_t i = last; i >= front; --i)
#define line putchar('\n')
#define wait _getch()
#define cls system("cls")
#endif

#pragma endregion

/*===================================================
Author : Ca Len Men									=
B Plus Tree : bplus<typekey, typevalue>				=
==================================================*/


//##################################################
//==========          B+ Tree          ==========
template <class data>
class saveset {
	//=====     Sub Class     =====//
#pragma region Sub Class
public:
	class node {
	public:
		data** ptr;
		node** ptrNode;
		char size;
		char sizeNode;
		bool leafnode;

		//=====     Constructor and Destructor     =====//
		node() = default;

		node(bool isLeaf) : leafnode{ isLeaf }
		{
			if (this->leafnode)
				this->ptrNode = new node * [this->sizeNode = '\2'];
			else {
				this->ptrNode = nullptr;
				this->sizeNode = '\0';
			}
			this->ptr = nullptr;
			this->size = '\0';
		}

		~node() {
			delete[] this->ptr;
			delete[] this->ptrNode;
		}
		//=====     Methods     =====//
		size_t find(const data& val)
		{//0 2 4 6 8
			size_t i = 0u;
			for (; i < this->size && !(val < *this->ptr[i]); ++i);
			return i;
		}

		void push(data* ptrItem, size_t idx)
		{
			data** res = this->ptr;
			this->ptr = new data * [this->size + 1];
			uFOR(i, 0u, idx)
				this->ptr[i] = res[i];
			uFOR(i, idx, this->size)
				this->ptr[i + 1u] = res[i];
			this->ptr[idx] = ptrItem;
			++this->size;
		}

		void pushNode(node* ptrSubNode, size_t idx)
		{
			node** res = this->ptrNode;
			this->ptrNode = new node * [this->sizeNode + 1];
			uFOR(i, 0u, idx)
				this->ptrNode[i] = res[i];
			uFOR(i, idx, this->sizeNode)
				this->ptrNode[i + 1u] = res[i];
			this->ptrNode[idx] = ptrSubNode;
			++this->sizeNode;
		}

		void pop(size_t index) {
			if(this->leafnode)
				delete this->ptr[index];
			if (this->size == '\1') {
				delete[] this->ptr;
				this->ptr = nullptr;
				--this->size;
				return;
			}

			data** res = this->ptr;
			--this->size;
			this->ptr = new data * [this->size];
			uFOR(i, 0u, index)
				this->ptr[i] = res[i];
			uFOR(i, index, this->size)
				this->ptr[i] = res[i + 1];
			delete[] res;
		}

		void popNode(size_t index)
		{
			delete this->ptrNode[index];
			node** res = this->ptrNode;
			--this->sizeNode;
			this->ptrNode = new node * [this->sizeNode];
			uFOR(i, 0u, index)
				this->ptrNode[i] = res[i];
			uFOR(i, index, this->sizeNode)
				this->ptrNode[i] = res[i + 1];
			delete[] res;
		}

		void share(node& source, size_t start)
		{
			source.size = this->size - start;
			source.ptr = new data * [source.size];
			data** res = this->ptr + start;
			uFOR(i, 0u, source.size)
				source.ptr[i] = res[i];
			
			res = this->ptr;
			this->ptr = new data * [this->size = start];
			uFOR(i, 0u, this->size)
				this->ptr[i] = res[i];
			delete[] res;
		}

		void shareNode(node& source, size_t start)
		{
			if (source.leafnode) {
				printf("Khong the chia se ptrNode cho nut la !\n");
				return;
			}

			source.sizeNode = this->sizeNode - start;
			source.ptrNode = new node * [source.sizeNode];
			node** res = this->ptrNode + start;
			uFOR(i, 0u, source.sizeNode)
				source.ptrNode[i] = res[i];

			res = this->ptrNode;
			this->ptrNode = new node * [this->sizeNode = start];
			uFOR(i, 0u, this->sizeNode)
				this->ptrNode[i] = res[i];
			delete[] res;
		}

		bool enough() const {
			return this->size >= (branch - 1) >> 1;	//(branch - 1) / 2
		}

		bool veryenough() const {
			return this->size > (branch - 1) >> 1;	//(branch - 1) / 2
		}

		data* minValue() const {	//This is leaf node
			if (this->size != 0)
				return this->ptr[0];
			return this->ptrNode[1]->ptr[0];
		}

		node*& next()
		{
			return this->ptrNode[0];
		}

		node*& prev()
		{
			return this->ptrNode[1];
		}

		void borrowNext(node& nodeNext)
		{
			push(nodeNext.ptr[0], this->size);
			nodeNext.ptr[0] = nullptr;
			nodeNext.pop(0u);
		}

		void borrowPrev(node& nodeNext)
		{
			size_t lastIndex = nodeNext.size - 1;
			push(nodeNext.ptr[lastIndex], 0u);
			nodeNext.ptr[lastIndex] = nullptr;
			nodeNext.pop(lastIndex);
		}

		void borrowNodeNext(node& nodeNext)
		{
			pushNode(nodeNext.ptrNode[0], this->sizeNode);
			nodeNext.ptrNode[0] = nullptr;
			nodeNext.popNode(0u);
		}

		void borrowNodePrev(node& nodeNext)
		{
			size_t lastIndex = nodeNext.sizeNode - 1;
			pushNode(nodeNext.ptrNode[lastIndex], 0u);
			nodeNext.ptrNode[lastIndex] = nullptr;
			nodeNext.popNode(lastIndex);
		}

		void mergeNext(node& nodeNext) {
			if (nodeNext.size == '\0')
				return;
			data** res = this->ptr;
			this->ptr = new data * [this->size + nodeNext.size];
			uFOR(i, 0u, this->size)
				this->ptr[i] = res[i];
			delete[] res;

			res = this->ptr + this->size;
			this->size += nodeNext.size;
			uFOR(i, 0u, nodeNext.size)
				res[i] = nodeNext.ptr[i];
		}

		void mergeNodeNext(node& nodeNext) {
			if (nodeNext.sizeNode == '\0')
				return;
			node** res = this->ptrNode;
			this->ptrNode = new node * [this->sizeNode + nodeNext.sizeNode];
			uFOR(i, 0u, this->sizeNode)
				this->ptrNode[i] = res[i];
			delete[] res;

			res = this->ptrNode + this->sizeNode;
			this->sizeNode += nodeNext.sizeNode;
			uFOR(i, 0u, nodeNext.sizeNode)
				res[i] = nodeNext.ptrNode[i];
		}

		node* createleafnode()
		{//If size == branch
			//Create new node
			if (this->size < branch)
			{
				printf("Nut la chua day !\n");
				return nullptr;
			}
			node* otherleafnode = new node(true);
			share(*otherleafnode, branch >> 1);	//branch / 2
			
			//Connect
			otherleafnode->next() = this->next();
			otherleafnode->prev() = this;
			this->next()->prev() = otherleafnode;
			this->next() = otherleafnode;
			return otherleafnode;
		}

		node* branching(data*& minofbranch)
		{	//If size == branch
			if (this->size < branch)
			{
				printf("Nut chua day !\n");
				return nullptr;
			}
			//Create node
			node* othernode = new node(false);
			othernode->size = (branch - 1u) >> 1u;	//(branch - 1) / 2
			othernode->sizeNode = othernode->size + 1;
			othernode->ptr = new data * [othernode->size];
			othernode->ptrNode = new node * [othernode->sizeNode];

			//Move data
			this->size -= othernode->sizeNode;
			this->sizeNode = this->size + 1;
			minofbranch = this->ptr[this->size];
			data** pointer = this->ptr + this->size + 1u;
			uFOR(i, 0u, othernode->size)
				othernode->ptr[i] = pointer[i];
			node** pointerNode = this->ptrNode + this->sizeNode;
			uFOR(i, 0u, othernode->sizeNode)
				othernode->ptrNode[i] = pointerNode[i];

			pointer = this->ptr;
			this->ptr = new data * [this->size];
			uFOR(i, 0u, this->size)
				this->ptr[i] = pointer[i];
			pointerNode = this->ptrNode;
			this->ptrNode = new node * [this->sizeNode];
			uFOR(i, 0u, this->sizeNode)
				this->ptrNode[i] = pointerNode[i];
			delete[] pointer;
			delete[] pointerNode;

			return othernode;
		}

		void view() const
		{
			putchar('[');
			uFOR(i, 0u, this->size) {
				printf("%d", *this->ptr[i]);
				if (i + 1 < this->size)
					putchar(',');
			}
			printf("]\n");
		}
	};
#pragma endregion

	//=====     Private Methods     =====//
#pragma region Private Methods
	void viewRecur(node* rootnode, size_t layer = 0u) const
	{
		if (rootnode == nullptr)
			return;

		RFOR(i, rootnode->size, 0)
		{
			//Print node
			if (i < rootnode->size) {
				uFOR(k, 0u, layer)
					printf("%10s", " ");
				if (i == rootnode->size - 1)
					putchar('[');
				printf("%10d", *rootnode->ptr[i]);
				if (i == 0u)
					putchar(']');
				line;
			}
			if (!rootnode->leafnode)
				viewRecur(rootnode->ptrNode[i], layer + 1u);
		}
	}

	data* minBranch(node* rootnode) const {
		while (rootnode->leafnode == false)
			rootnode = rootnode->ptrNode[0];
		return rootnode->ptr[0];
	}

	bool pushRecursive(node*& rootnode, const data& item, bool& pushFinish)
	{
		if (rootnode->leafnode) {
			//Leaf node
			size_t index = rootnode->find(item);
			//Same value
			if (index > 0 && *rootnode->ptr[index - 1] == item) {
				pushFinish = false;
				return false;
			}
			//Add item
			rootnode->push(new data(item), index);
			pushFinish = true;
			
			bool isfull = rootnode->size == branch;
			if (this->root == rootnode && isfull) {
				node* newroot = new node(false);
				newroot->pushNode(rootnode, 0u);
				newroot->pushNode(rootnode->createleafnode(), 1u);
				newroot->push(newroot->ptrNode[1]->ptr[0], 0u);
				this->root = newroot;
			}
			return isfull;
		}
		
		size_t index = rootnode->find(item);
		//Child is full
		if (pushRecursive(rootnode->ptrNode[index], item, pushFinish))
		{	//ptr[index] and ptrNode[index + 1] is null
			//Branching leaf node
			if (rootnode->ptrNode[index]->leafnode)
			{	
				node* othernode = rootnode->ptrNode[index]->createleafnode();
				rootnode->pushNode(othernode, index + 1u);
				rootnode->push(othernode->ptr[0], index);
			} else {	//Branching node
				data* pointer;
				node* othernode = rootnode->ptrNode[index]->branching(pointer);
				rootnode->pushNode(othernode, index + 1u);
				rootnode->push(pointer, index);
			}

			bool isfull = rootnode->size == branch;
			if (this->root == rootnode && isfull) {
				node* newroot = new node(false);
				data* pointer;
				newroot->pushNode(rootnode, 0u);
				newroot->pushNode(rootnode->branching(pointer), 1u);
				newroot->push(pointer, 0u);
				this->root = newroot;
			}
			return isfull;
		}
		return false;
	}

	bool popRecursive(node*& rootnode, const data& item)
	{
		//Leaf node
		if (rootnode->leafnode){
			size_t index = rootnode->find(item);
			
			if (index == 0u || *rootnode->ptr[index - 1u] != item)
				return false;
			rootnode->pop(index - 1u);
			--this->size;
			
			if (this->root == rootnode && rootnode->size == '\0') {
				//B Plus only have one node
				delete this->root;
				this->root = nullptr;
				head->next() = tail;
				tail->prev() = head;
			}
			return true;
		}
		
		size_t index = rootnode->find(item);
		bool needRef = false;
		if (index > 0 && *rootnode->ptr[index - 1u] == item &&
			rootnode->ptrNode[0]->leafnode == false)
			needRef = true;

		//B Plus has been this item
		bool contain = popRecursive(rootnode->ptrNode[index], item);
		if (contain == false)
			return false;
		if (needRef)
			rootnode->ptr[index - 1u] = minBranch(rootnode->ptrNode[index]);

		node* childNode = rootnode->ptrNode[index];
		if (rootnode->ptrNode[0u]->leafnode) {	//Last node
			if (childNode->enough()) {
				if (index > 0u)
					rootnode->ptr[index - 1u] = rootnode->ptrNode[index]->ptr[0];
				return true;
			}

			//Not enough -> borrow or merge
			if (index > 0u && rootnode->ptrNode[index - 1u]->veryenough()) {
				//Borrow Prev
				childNode->borrowPrev(*rootnode->ptrNode[index - 1u]);
				rootnode->ptr[index - 1] = rootnode->ptrNode[index]->ptr[0];
			} else if(index < rootnode->size && rootnode->ptrNode[index + 1u]->veryenough()){
				//Borrow Next
				childNode->borrowNext(*rootnode->ptrNode[index + 1u]);
				rootnode->ptr[index] = rootnode->ptrNode[index + 1u]->ptr[0];
				if(index > 0u)
					rootnode->ptr[index - 1u] = rootnode->ptrNode[index]->ptr[0];
			} else {
				if (index == 0u) {
					//Merge Next
					childNode->mergeNext(*rootnode->ptrNode[1]);
					childNode->next() = rootnode->ptrNode[1]->next();
					childNode->next()->prev() = childNode;
					rootnode->pop(0u);
					rootnode->popNode(1u);
				} else{//Merge Prev
					rootnode->ptrNode[index - 1]->mergeNext(*childNode);
					rootnode->ptrNode[index - 1]->next() = childNode->next();
					childNode->next()->prev() = rootnode->ptrNode[index - 1];
					rootnode->pop(index - 1);
					rootnode->popNode(index);
				}

				if (rootnode->size == '\0' && this->root == rootnode) {
					node* temp = this->root;
					this->root = this->root->ptrNode[0];
					delete temp;
				}
			}
		}
		else {	//Node
			if (childNode->enough())
				return true;

			//Not enough -> borrow or merge
			if (index > 0u && rootnode->ptrNode[index - 1u]->veryenough()) {
				//Borrow Prev
				node* prevNode = rootnode->ptrNode[index - 1u];
				childNode->push(rootnode->ptr[index - 1u], 0u);
				rootnode->ptr[index - 1u] = prevNode->ptr[prevNode->size - 1];
				prevNode->pop(prevNode->size - 1);
				childNode->borrowNodePrev(*prevNode);
			} else if (index < rootnode->size && rootnode->ptrNode[index + 1u]->veryenough()) {
				//Borrow Next
				node* nextNode = rootnode->ptrNode[index + 1u];
				childNode->push(rootnode->ptr[index], childNode->size);
				rootnode->ptr[index] = nextNode->ptr[0];
				nextNode->pop(0u);
				childNode->borrowNodeNext(*nextNode);
				if (index > 0u)
					rootnode->ptr[index - 1u] = minBranch(rootnode->ptrNode[index]);
			} else {
				if (index == 0u) {
					//Merge Next
					childNode->push(rootnode->ptr[0], childNode->size);
					childNode->mergeNext(*rootnode->ptrNode[1]);
					childNode->mergeNodeNext(*rootnode->ptrNode[1]);
					rootnode->pop(0u);
					rootnode->popNode(1u);
				} else {
					//Merge Prev
					node* prevNode = rootnode->ptrNode[index - 1u];
					prevNode->push(rootnode->ptr[index - 1u], prevNode->size);
					prevNode->mergeNext(*childNode);
					prevNode->mergeNodeNext(*childNode);
					rootnode->pop(index - 1u);
					rootnode->popNode(index);
				}

				if (rootnode->size == '\0' && this->root == rootnode) {
					node* temp = this->root;
					this->root = this->root->ptrNode[0];
					delete temp;
				}
			}
		}
		
		return true;
	}

	void clearRecursive(node* rootnode) {
		if (rootnode->leafnode) {
			uFOR(i, 0u, rootnode->size)
				delete rootnode->ptr[i];
			delete rootnode;
			return;
		}

		uFOR(i, 0u, rootnode->sizeNode)
			clearRecursive(rootnode->ptrNode[i]);
		delete rootnode;
	}

	node* findIndex(size_t index, size_t& idxOfNode) const {
		node* pointer = this->head->next();
		size_t sum = pointer->size;
		for (; sum <= index; sum += pointer->size)
			pointer = pointer->next();
		idxOfNode = pointer->size - sum + index;
		return pointer;
	}

	void copyRecursive(node*& rootnode, node* othernode, queue<node*>& quLeafNode) {
		rootnode = new node(othernode->leafnode);
		rootnode->ptr = new data * [rootnode->size = othernode->size];

		if (othernode->leafnode) {
			uFOR(i, 0u, rootnode->size)
				rootnode->ptr[i] = new data(*othernode->ptr[i]);
			quLeafNode.push(rootnode);
			return;
		}

		rootnode->ptrNode = new node * [rootnode->sizeNode = othernode->sizeNode];
		uFOR(i, 0u, rootnode->sizeNode)
			copyRecursive(rootnode->ptrNode[i], othernode->ptrNode[i], quLeafNode);
		uFOR(i, 0u, rootnode->size)
			rootnode->ptr[i] = minBranch(rootnode->ptrNode[i + 1u]);
	}

	void linkedLeafNode(queue<node*>& quLeafNode) {
		quLeafNode.push(this->tail);
		node* prevnode = this->head, * nextnode;
		for (; quLeafNode; prevnode = nextnode) {
			nextnode = quLeafNode.pop();
			prevnode->next() = nextnode;
			nextnode->prev() = prevnode;
		}
	}
#pragma endregion

	//=====     Attributes     =====//
#pragma region Attributes
	node* root, * head, * tail;
	size_t size;

	static const size_t branch = 7;
#pragma endregion

	//=====     Constructors and Destructor     =====//
public:
#pragma region Constructors and Destructor
	saveset() : root{ nullptr }, size{ 0u }
	{
		head = new node(true);
		tail = new node(true);
		head->next() = tail;
		tail->prev() = head;
	}

	saveset(std::initializer_list<data> list) : root{ nullptr }, size{ 0u }
	{
		this->head = new node(true);
		this->tail = new node(true);
		this->head->next() = this->tail;
		this->tail->prev() = this->head;

		const data* pointer = list.begin();
		size_t listSize = list.size();
		uFOR(i, 0u, listSize)
			push(pointer[i]);
	}

	template <class anyIterator>
	saveset(anyIterator begin, anyIterator end) : root{ nullptr }, size{ 0u }
	{
		this->head = new node(true);
		this->tail = new node(true);
		this->head->next() = this->tail;
		this->tail->prev() = this->head;

		for (; begin != end; ++begin)
			push(*begin);
	}

	saveset(const saveset& source) : root{ nullptr }, size { source.size }
	{
		this->head = new node(true);
		this->tail = new node(true);

		if (source.empty())
		{
			this->head->next() = this->tail;
			this->tail->prev() = this->head;
			return;
		}

		queue<node*> quLeafNode;
		copyRecursive(this->root, source.root, quLeafNode);
		linkedLeafNode(quLeafNode);
	}

	saveset(saveset&& source) : root{ source.root }, size{ source.size },
		head{ source.head }, tail{ source.tail }
	{ 
		source.root = source.head = source.tail = nullptr;
	}

	~saveset() {
		if (this->root != nullptr)
			clearRecursive(this->root);
		delete this->head;
		delete this->tail;
	}
#pragma endregion

	//=====     Methods     =====//
#pragma region Methods
	//Add an item
	bool push(const data& item)
	{
		if (root == nullptr)
		{
			this->root = new node(true);
			this->root->push(new data(item), 0u);

			this->head->next() = this->tail->prev() = this->root;
			this->root->next() = this->tail;
			this->root->prev() = this->head;
			++this->size;
			return true;
		}

		bool pushFinish;
		pushRecursive(this->root, item, pushFinish);
		if(pushFinish)
			++this->size;
		return pushFinish;
	}

	//Remove an item
	bool pop(const data& item) {
		return popRecursive(this->root, item);
	}

	//Check contains an item
	bool contains(const data& item) const {
		if (this->root == nullptr)
			return false;

		node* moveNode = this->root;
		size_t index;
		for (;;)
		{
			index = moveNode->find(item);
			if (index > 0u && *moveNode->ptr[index - 1u] == item)
				return true;
			if (moveNode->leafnode)
				return false;
			moveNode = moveNode->ptrNode[index];
		}
	}

	//Save Set being empty
	void clear() {
		if (this->root == nullptr)
			return;
		this->clearRecursive(this->root);
		this->root = nullptr;
		this->head->next() = this->tail;
		this->tail->prev() = this->head;
	}

	//Swapping two Save Set
	void swap(saveset& source) {
		std::swap(this->root, source.root);
		std::swap(this->size, source.size);
		std::swap(this->head, source.head);
		std::swap(this->tail, source.tail);
	}

	//View on Console
	void view() const
	{
		if (this->root == nullptr) {
			printf("B Plus is empty !\n");
			return;
		}
		viewRecur(this->root);
	}
	
	//Writting on Console
	void out() const {
		std::cout << '[';
		for (auto i = this->begin(), j = this->end(); i != j; ++i)
		{
			std::cout << *i;
			if (i.next() != j)
				std::cout << ", ";
		}
		std::cout << "]\n";
	}

	//Length of Save Set
	size_t length() const
	{
		return this->size;
	}

	//Check the Save Set is empty
	bool empty() const {
		return this->root == nullptr;
	}
#pragma endregion

	//=====     Operators     =====//
#pragma region Operators
	//Check the Save Set is not empty
	operator bool() const {
		return this->root != nullptr;
	}

	//Get const value item at index
	const data& operator[](size_t index) const {
		return *findIndex(index, index)->ptr[index];
	}

	//Copy data from other Save Set
	saveset& operator=(const saveset& source) {
		if (this == &source)
			return *this;

		clear();
		if (source) {
			queue<node*> quLeafNode;
			this->size = source.size;
			copyRecursive(this->root, source.root, quLeafNode);
			linkedLeafNode(quLeafNode);
		}
		return *this;
	}

	//Copy data from other Save Set
	saveset& operator=(saveset&& source) noexcept {
		this->root = source.root;
		this->size = source.size;
		this->head = source.head;
		this->tail = source.tail;
		source.root = nullptr;
		source.head = nullptr;
		source.tail = nullptr;
		return *this;
	}
#pragma endregion

	//=====     Iterator     =====//
#pragma region Iterator
	class iterator {
		friend saveset;

		//=====     Attributes     =====//
		const saveset* ref;
		node* ptrNode;
		size_t idx;

		iterator(const saveset* _ref, node* _ptrNode, size_t _idx) :
			ref { _ref }, ptrNode{ _ptrNode }, idx{ _idx }{}

	public:
		//=====     Constructors     =====//

		iterator(const iterator& source) : ref{ source.ref },
			ptrNode{ source.ptrNode }, idx{ source.idx }{}

		//=====     Methods     =====//
		
		//Iterator is null
		bool null() const {
			return this->ptrNode->size == '\0';
		}

		//Iterator next
		iterator next() const {
			return ++iterator(*this);
		}

		//Iterator prev
		iterator prev() const {
			return --iterator(*this);
		}

		//=====     Operators     =====//

		//Get const value of item
		const data& operator*() const {
			return *this->ptrNode->ptr[this->idx];
		}

		//Get index ( type data* const ) of item
		const data* operator->() const {
			return this->ptrNode->ptr[this->idx];
		}

		//Iterator move to the next item
		iterator& operator++() {
			if (null())
				return *this;
			++this->idx;
			if (this->idx == this->ptrNode->size) {
				this->idx = 0u;
				this->ptrNode = this->ptrNode->next();
			}
			return *this;
		}

		//Iterator move to the next item
		iterator operator++(int) {
			iterator res(*this);
			this->operator++();
			return res;
		}

		//The iterator moves to the previous item
		iterator& operator--() {
			if (null())
				return *this;
			if (this->idx == 0u) {
				this->ptrNode = this->ptrNode->prev();
				this->idx = this->ptrNode->size - '\1';
			} else
				--this->idx;
			return *this;
		}

		//The iterator moves to the previous item
		iterator operator--(int) {
			iterator res(*this);
			this->operator--();
			return res;
		}

		//Copy data from other iterator
		iterator& operator=(const iterator& source) {
			this->ref = source.ref;
			this->ptrNode = source.ptrNode;
			this->idx = source.idx;
			return *this;
		}

		//Compare two iterators
		bool operator==(const iterator& source) const {
			if (this->ptrNode == source.ptrNode) {
				if (null())
					return true;
				return this->idx == source.idx;
			}
			return false;
		}

		//Compare two iterators
		bool operator!=(const iterator& source) const {
			return !this->operator==(source);
		}

		//Check iterator not null
		operator bool() const {
			return !null();
		}
	};
#pragma endregion

	//=====    Const Iterator     =====//
#pragma region Const Iterators
	class const_iterator {
		friend saveset;

		//=====     Attributes     =====//
		const saveset* ref;
		node* ptrNode;
		size_t idx;

		const_iterator(const saveset* _ref, node* _ptrNode, size_t _idx) :
			ref{ _ref }, ptrNode{ _ptrNode }, idx{ _idx }{}

	public:
		//=====     Constructors     =====//

		const_iterator(const const_iterator& source) : ref{ source.ref },
			ptrNode{ source.ptrNode }, idx{ source.idx }{}

		//=====     Methods     =====//

		//Const Iterator is null
		bool null() const {
			return this->ptrNode->size == '\0';
		}

		//Const Iterator next
		const_iterator next() const {
			return ++const_iterator(*this);
		}

		//Const Iterator prev
		const_iterator prev() const {
			return --const_iterator(*this);
		}

		//=====     Operators     =====//

		//Get const value of item
		const data& operator*() const {
			return *this->ptrNode->ptr[this->idx];
		}

		//Get index ( type data* const ) of item
		const data* operator->() const {
			return this->ptrNode->ptr[this->idx];
		}

		//Iterator move to the next item
		const_iterator& operator++() {
			if (null())
				return *this;
			++this->idx;
			if (this->idx == this->ptrNode->size) {
				this->idx = 0u;
				this->ptrNode = this->ptrNode->next();
			}
			return *this;
		}

		//Iterator move to the next item
		const_iterator operator++(int) {
			const_iterator res(*this);
			this->operator++();
			return res;
		}

		//The iterator moves to the previous item
		const_iterator& operator--() {
			if (null())
				return *this;
			if (this->idx == 0u) {
				this->ptrNode = this->ptrNode->prev();
				this->idx = this->ptrNode->size - '\1';
			}
			else
				--this->idx;
			return *this;
		}

		//The iterator moves to the previous item
		const_iterator operator--(int) {
			const_iterator res(*this);
			this->operator--();
			return res;
		}

		//Copy data from other iterator
		const_iterator& operator=(const const_iterator& source) {
			this->ref = source.ref;
			this->ptrNode = source.ptrNode;
			this->idx = source.idx;
			return *this;
		}

		//Compare two iterators
		bool operator==(const const_iterator& source) const {
			if (this->ptrNode == source.ptrNode) {
				if (null())
					return true;
				return this->idx == source.idx;
			}
			return false;
		}

		//Compare two iterators
		bool operator!=(const const_iterator& source) const {
			return !this->operator==(source);
		}

		//Check iterator not null
		operator bool() const {
			return !null();
		}
	};
#pragma endregion

	//=====     Methods of Iterator, Const Iterator     =====//
#pragma region Methods of Iterator
	//Iterator of first item
	iterator begin() {
		return iterator(this, this->head->next(), 0u);
	}

	//Iterator of last item
	iterator rbegin() {
		node * res = this->tail->prev();
		return iterator(this, res, res->size - '\1');
	}

	//Iterator at back of Save Set
	iterator end() {
		return iterator(this, this->tail, 0u);
	}

	//Iterator at front of Save Set
	iterator rend() {
		return iterator(this, this->head, 0);
	}

	//Const Iterator of first item
	const_iterator begin() const {
		return const_iterator(this, this->head->next(), 0u);
	}

	//Const Iterator of first item
	const_iterator cbegin() const {
		return const_iterator(this, this->head->next(), 0u);
	}

	//Const Iterator of last item
	const_iterator crbegin() const {
		node* res = this->tail->prev();
		return const_iterator(this, res, res->size - '\1');
	}

	//Const Iterator at back of Save Set
	const_iterator cend() const {
		return const_iterator(this, this->tail, 0);
	}

	//Const Iterator at back of Save Set
	const_iterator end() const {
		return const_iterator(this, this->tail, 0);
	}

	//Const Iterator at front of Save Set
	const_iterator crend() const {
		return const_iterator(this, this->head, 0u);
	}
#pragma endregion
};

//==================================================
//=====     Overloading Operator STD::COUT     =====//
template <class data>
std::ostream& operator<<(std::ostream& os, const saveset<data>& set) {
	set.out();
	return os;
}
//==================================================
#endif	//_B_PLUS_
