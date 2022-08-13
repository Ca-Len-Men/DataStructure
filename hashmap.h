#ifndef _FISH_HASHMAP_
#define _FISH_HASHMAP_

#include "pair.h"
#include<initializer_list>

#ifndef _DEFINE_SYNTAX_
#define _DEFINE_SYNTAX_
#define FOR(i, start, end) for(int i = start; i < end; ++i)
#define RFOR(i, last, front) for(int i = last; i >= front; --i)
#define uFOR(i, start, end) for(size_t i = start; i < end; ++i)
#define uRFOR(i, last, front) for(size_t i = last; i >= front; --i)
#endif

/*===================================================
Author : Ca Len Men	(or Fish Climb Tree)			=
Hash Map : hashmap<keytype, valuetype>				=
===================================================*/

/* Hash Map is a dynamic array and Singly Linked List.
You must have copy constructor, operator%(int), operator= for your keytype.*/

namespace dsa
{
	//==================================================//
	//==========          Hash Map          ==========//
	template <class keytype, class valuetype>
	class hashmap {
		using pairtype = pair<keytype, valuetype>;
		//=====     Sub Class     =====//
#pragma region Sub Class
		class node {
		public:
			pair<keytype, valuetype> info;
			node* next;
			node(const keytype& key, const valuetype& value) : info(key, value), next(nullptr) {}
			node(const pairtype& _pair) : info(_pair), next(nullptr) {}
		};
#pragma endregion

		//=====     Private Methods     =====//
#pragma region Private Methods
	// Hash Function : hash value to index of Hash Set
		int hash_function(const keytype& key) const {
			int mod = key % this->capacity;
			if (mod < 0)
				mod = -mod;
			return mod;
		}

		void resize(bool expand = true) {
			if (this->size == 0u) {
				delete[] this->ptr;
				this->capacity = expand ? this->capacity * 2 + 1 : this->capacity / 2;
				this->ptr = new node * [this->capacity];
				uFOR(i, 0u, this->capacity)
					this->ptr[i] = nullptr;
				return;
			}

			node* head(nullptr), * tail(nullptr);
			size_t i = 0u;
			for (; i < this->capacity; ++i)
				if (this->ptr[i] != nullptr) {
					head = tail = this->ptr[i];
					break;
				}

			for (++i; i < this->capacity; ++i)
				if (this->ptr[i])
				{
					while (tail->next) tail = tail->next;
					tail->next = this->ptr[i];
				}

			delete[] this->ptr;
			this->capacity = expand ? this->capacity * 2 + 1 : this->capacity / 2;
			this->ptr = new node * [this->capacity];
			for (i = 0u; i < this->capacity; ++i)
				this->ptr[i] = nullptr;

			int index;
			for (i = 0u; i < this->size; ++i) {
				tail = head;
				head = head->next;
				index = this->hash_function(tail->info.key);
				tail->next = this->ptr[index];
				this->ptr[index] = tail;
			}
		}

		void delete_function() {
			uFOR(i, 0u, this->capacity)
				if (this->ptr[i])
					for (node* pointer = this->ptr[i]; pointer;) {
						node* temp = pointer;
						pointer = pointer->next;
						delete temp;
					}

			delete[] this->ptr;
		}
#pragma endregion

		//=====     Attributes     =====//
#pragma region Attributes
		node** ptr;
		size_t size;
		size_t capacity;
#pragma endregion

	public:
		//=====     Constructors and Destructor     =====//
#pragma region Constructors and Destructor
		hashmap() : size(0u), capacity(1u)
		{
			this->ptr = new node * [this->capacity];
			uFOR(i, 0u, this->capacity)
				this->ptr[i] = nullptr;
		}

		hashmap(std::initializer_list<pairtype> list) : size(0u), capacity(1u)
		{
			this->ptr = new node * [1u];
			this->ptr[0] = nullptr;
			for (auto& i : list)
				this->push(i);
		}

		template <class anyIterator>
		hashmap(anyIterator begin, anyIterator end) : size(0u), capacity(1u)
		{
			this->ptr = new node * [1u];
			this->ptr[0] = nullptr;
			for (; begin != end; ++begin)
				this->push(*begin);
		}

		hashmap(const hashmap& source) : size(0u), capacity(1u)
		{
			this->ptr = new node * [1u];
			this->ptr[0] = nullptr;
			uFOR(i, 0u, source.capacity)
				if (source.ptr[i])
					for (node* pointer = source.ptr[i]; pointer; pointer = pointer->next)
						this->push(pointer->info);
		}

		hashmap(hashmap&& source) : size(source.size), capacity(source.capacity), ptr(source.ptr)
		{
			source.ptr = nullptr;
		}

		~hashmap() {
			if (this->ptr)
				this->delete_function();
		}
#pragma endregion

		//=====     Methods     =====//
#pragma region Methods
		bool push(const keytype& key, const valuetype& value) {
			size_t index = this->hash_function(key);
			for (node* pointer = this->ptr[index]; pointer; pointer = pointer->next)
				if (pointer->info.key == key)
					return false;

			if (this->size == this->capacity / 2) {
				this->resize();
				index = this->hash_function(key);
			}
			++this->size;

			if (this->ptr[index] == nullptr) {
				this->ptr[index] = new node(key, value);
				return true;
			}

			node* res = new node(key, value);
			res->next = this->ptr[index];
			this->ptr[index] = res;
			return true;
		}

		// Push an element into Hash Set
		bool push(const pairtype& item) {
			return this->push(item.key, item.value);
		}

		// Pop an element out of Hash Set
		bool pop(const keytype& key) {
			if (this->size == 0u)
				return false;

			int index = this->hash_function(key);
			if (this->ptr[index] == nullptr)
				return false;

			node* res = this->ptr[index];
			if (res->info.key == key) {
				this->ptr[index] = res->next;
				delete res;
				--this->size;
				if (this->size == this->capacity / 4)
					this->resize(false);
				return true;
			}

			for (; res->next; res = res->next)
				if (res->next->info.key == key) {
					node* temp = res->next;
					res->next = temp->next;
					delete temp;
					--this->size;
					if (this->size == this->capacity / 4)
						this->resize(false);
					return true;
				}

			return false;
		}

		// Hash Set contains the value
		bool contains(const keytype& key) const {
			if (this->size == 0u)
				return false;

			int index = this->hash_function(key);
			for (node* i = this->ptr[index]; i != nullptr; i = i->next)
				if (i->info.key == key)
					return true;
			return false;
		}

		// Swap two Hash Set
		void swap(hashmap& source) {
			std::swap(this->ptr, source.ptr);
			std::swap(this->size, source.size);
			std::swap(this->capacity, source.capacity);
		}

		// Hash Set being empty
		void clear() {
			this->delete_function();
			this->ptr = new node * [1u];
			this->ptr[0] = nullptr;
			this->size = 0u;
			this->capacity = 1u;
		}

		// Check Hash Set is empty
		bool empty() const {
			return this->size == 0u;
		}

		// Writting on console
		void out() const {
			size_t count(1u);

			std::cout << '[';
			uFOR(i, 0u, this->capacity)
				for (node* j = this->ptr[i]; j != nullptr; j = j->next, ++count) {
					std::cout << j->info.key << " : " << j->info.value;
					if (count < this->size)
						std::cout << ", ";
				}
			std::cout << "]\n";
		}

		// Length of Hash Set
		size_t len() const {
			return this->size;
		}
#pragma endregion

		//=====     Operators     =====//
#pragma region Operators
	// Hash Set contains the value
		valuetype& operator[](const keytype& key) {
			int index = this->hash_function(key);
			for (node* i = this->ptr[index]; i != nullptr; i = i->next)
				if (i->info.key == key)
					return i->info.value;
		}

		const valuetype& operator[](const keytype& key) const {
			int index = this->hash_function(key);
			for (node* i = this->ptr[index]; i != nullptr; i = i->next)
				if (i->info.key == key)
					return i->info.value;
		}

		// Copy data from other Hash Set
		hashmap& operator=(const hashmap& source) {
			if (this == &source)
				return *this;

			this->clear();
			uFOR(i, 0u, source.capacity)
				if (source.ptr[i])
					for (node* pointer = source.ptr[i]; pointer; pointer = pointer->next)
						this->push(pointer->info);
			return *this;
		}

		// Copy data from other Hash Set
		hashmap& operator=(hashmap&& source) noexcept {
			this->delete_function();
			this->ptr = source.ptr;
			this->size = source.size;
			this->capacity = source.capacity;
			source.ptr = nullptr;
		}
#pragma endregion

		//=====     Iterator     =====//
#pragma region Iterator
		class iterator {
			friend hashmap;
			hashmap* ref;
			node* ptr;
			int index;

			iterator(hashmap* _ref, node* _ptr, int _index) : ref(_ref), ptr(_ptr), index(_index) {}
		public:
			iterator(const iterator& source) : ref(source.ref), ptr(source.ptr), index(source.index) {}

			//=====     Methods     =====//

			// Iterator is null
			bool null() const {
				return this->ptr == nullptr;
			}

			// Iterator move to the next item
			void next() {
				this->ptr = this->ptr->next;
				if (this->ptr == nullptr)
					for (++this->index; this->index < this->ref->capacity; ++this->index)
						if (this->ref->ptr[this->index]) {
							this->ptr = this->ref->ptr[this->index];
							break;
						}
			}

			// Iterator move to the previous item
			void prev() {
				if (this->ref->ptr[this->index] == this->ptr) {
					this->ptr = nullptr;
					for (--this->index; this->index >= 0; --this->index)
						if (this->ref->ptr[this->index]) {
							this->ptr = this->ref->ptr[this->index];
							while (this->ptr->next) this->ptr = this->ptr->next;
							break;
						}
				}
				else {
					node* res = this->ref->ptr[this->index];
					while (res->next != this->ptr)
						res = res->next;
					this->ptr = res;
				}
			}

			//=====     Operators     =====//

			// Iterator is not null
			operator bool() const {
				return this->ptr != nullptr;
			}

			// Access value in Hash Map
			const pairtype& operator*() const {
				return this->ptr->info;
			}

			// Access index of value in Hash Map
			const pairtype* operator->() const {
				return &this->ptr->info;
			}

			// Iterator move to the next item
			iterator& operator++() {
				if (this->ptr != nullptr)
					this->next();
				return *this;
			}

			// Iterator move to the next item
			iterator operator++(int) {
				iterator res(*this);
				if (this->ptr != nullptr)
					this->next();
				return res;
			}

			// Iterator move to the previous item
			iterator& operator--() {
				if (this->ptr != nullptr)
					this->prev();
				return *this;
			}

			// Iterator move to the previous item
			iterator operator--(int) {
				const_iterator res(*this);
				if (this->ptr != nullptr)
					this->prev();
				return res;
			}

			// Copy data from other Iterator
			iterator& operator=(const iterator& source) {
				this->ref = source.ref;
				this->ptr = source.ptr;
				this->index = source.index;
				return *this;
			}

			// Compare two Iterators
			bool operator==(const iterator& source) const {
				return this->ptr == source.ptr;
			}

			// Compare two Iterators
			bool operator!=(const iterator& source) const {
				return this->ptr != source.ptr;
			}
		};
#pragma endregion

		//=====     Const Iterator     =====//
#pragma region Const Iterator
		class const_iterator {
			friend hashmap;
			const hashmap* ref;
			const node* ptr;
			int index;

			const_iterator(const hashmap* _ref, const node* _ptr, int _index) : ref(_ref), ptr(_ptr), index(_index) {}
		public:
			const_iterator(const const_iterator& source) : ref(source.ref), ptr(source.ptr), index(source.index) {}

			//=====     Methods     =====//

			// Const Iterator is null
			bool null() const {
				return this->ptr == nullptr;
			}

			// Const Iterator move to the next item
			void next() {
				this->ptr = this->ptr->next;
				if (this->ptr == nullptr)
					for (++this->index; this->index < this->ref->capacity; ++this->index)
						if (this->ref->ptr[this->index]) {
							this->ptr = this->ref->ptr[this->index];
							break;
						}
			}

			// Const Iterator move to the previous item
			void prev() {
				if (this->ref->ptr[this->index] == this->ptr) {
					this->ptr = nullptr;
					for (--this->index; this->index >= 0; --this->index)
						if (this->ref->ptr[this->index]) {
							this->ptr = this->ref->ptr[this->index];
							while (this->ptr->next) this->ptr = this->ptr->next;
							break;
						}
				}
				else {
					node* res = this->ref->ptr[this->index];
					while (res->next != this->ptr)
						res = res->next;
					this->ptr = res;
				}
			}

			//=====     Operators     =====//

			// Const Iterator is not null
			operator bool() const {
				return this->ptr != nullptr;
			}

			// Access value in Hash Map
			const pairtype& operator*() const {
				return this->ptr->info;
			}

			// Access index of value in Hash Map
			const pairtype* operator->() const {
				return &this->ptr->info;
			}

			// Const Iterator move to the next item
			const_iterator& operator++() {
				if (this->ptr != nullptr)
					this->next();
				return *this;
			}

			// Const Iterator move to the next item
			const_iterator operator++(int) {
				const_iterator res(*this);
				if (this->ptr != nullptr)
					this->next();
				return res;
			}

			// Const Iterator move to the previous item
			const_iterator& operator--() {
				if (this->ptr != nullptr)
					this->prev();
				return *this;
			}

			// Const Iterator move to the previous item
			const_iterator operator--(int) {
				const_iterator res(*this);
				if (this->ptr != nullptr)
					this->prev();
				return res;
			}

			// Copy data from other Const Iterator
			const_iterator& operator=(const const_iterator& source) {
				this->ref = source.ref;
				this->ptr = source.ptr;
				this->index = source.index;
				return *this;
			}

			// Compare two Const Iterators
			bool operator==(const const_iterator& source) const {
				return this->ptr == source.ptr;
			}

			// Compare two Const Iterators
			bool operator!=(const const_iterator& source) const {
				return this->ptr != source.ptr;
			}
		};
#pragma endregion

		//=====     Methods of Iterator, Const Iterator     =====//
#pragma region Methods of Iterator, Const Iterator
		iterator begin() {
			if (this->size == 0u)
				return iterator(this, nullptr, 0);
			uFOR(i, 0u, this->capacity)
				if (this->ptr[i])
					return iterator(this, this->ptr[i], i);
		}

		iterator end() {
			return iterator(this, nullptr, 0);
		}

		const_iterator begin() const {
			if (this->size == 0u)
				return const_iterator(this, nullptr, 0);
			uFOR(i, 0u, this->capacity)
				if (this->ptr[i])
					return const_iterator(this, this->ptr[i], i);
		}

		const_iterator end() const {
			return const_iterator(this, nullptr, 0);
		}

		iterator rbegin() {
			if (this->size == 0u)
				return iterator(this, nullptr, 0);
			RFOR(i, this->capacity - 1, 0)
				if (this->ptr[i]) {
					node* res = this->ptr[i];
					while (res->next) res = res->next;
					return iterator(this, res, i);
				}
		}

		iterator rend() {
			return iterator(this, nullptr, 0);
		}

		const_iterator cbegin() const {
			if (this->size == 0u)
				return const_iterator(this, nullptr, 0);
			uFOR(i, 0u, this->capacity)
				if (this->ptr[i])
					return const_iterator(this, this->ptr[i], i);
		}

		const_iterator cend() const {
			return const_iterator(this, nullptr, 0);
		}

		const_iterator crbegin() const {
			if (this->size == 0u)
				return const_iterator(this, nullptr, 0);
			RFOR(i, this->capacity - 1, 0)
				if (this->ptr[i]) {
					node* res = this->ptr[i];
					while (res->next) res = res->next;
					return const_iterator(this, res, i);
				}
		}

		const_iterator crend() const {
			return const_iterator(this, nullptr, 0);
		}
#pragma endregion
	};

	//==========          Overloading operator<< with std::ostream          ==========//
	template <class keytype, class valuetype>
	std::ostream& operator<<(std::ostream& os, const hashmap<keytype, valuetype>& source) {
		source.out();
		return os;
	}

	int operator%(const std::string& str, int mod) {
		int sum(0);
		for (auto i : str)
			sum += int(i);
		return sum % mod;
	}
}
//==================================================//
#endif	// _FISH_HASHMAP_