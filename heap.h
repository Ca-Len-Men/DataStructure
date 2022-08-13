#ifndef _FISH_HEAP_
#define _FISH_HEAP_

#include<iostream>
#include<initializer_list>

#ifndef _DEFINE_MACROS_
#define _DEFINE_MACROS_
#define FOR(i, start, end) for(int i = start; i < end; ++i)
#define RFOR(i, last, front) for(int i = last; i >= front; --i)
#define uFOR(i, start, end) for(size_t i = start; i < end; ++i)
#define uRFOR(i, last, front) for(size_t i = last; i >= front; --i)
#endif	// _DEFINE_MACROS_

/*===================================================
Author : Ca Len Men	(or Fish Climb Tree)			=
Max Heap : maxheap<typename>						=
Min Heap : minheap<typename>						=
===================================================*/

/*Heap is a dynamic array.
You must have constructor for your data type.*/

namespace dsa
{
	//##################################################
	//==========          Heap          ==========//
	template <class datatype>
	class abstractheap {
	protected:
		//=====     Protected Method     =====//
#pragma region Protected Methods
	// Change memory length
		void newCapacity(bool expand) {
			if (this->capacity == 1u && expand == false)
				return;
			datatype* res = this->ptr;

			//Expand is true than capacity * 2 else capacity / 2
			expand ? this->capacity <<= 1u : this->capacity >>= 1u;
			this->ptr = new datatype[this->capacity];
			uFOR(i, 0u, this->size)
				this->ptr[i] = res[i];
			delete[] res;
		}

		// Change memory length
		void newCapacity(size_t newCap, bool maintain_data = true)
		{
			if (maintain_data)
			{
				if (newCap < this->size) return;
				datatype* res = this->ptr;
				this->ptr = new datatype[this->capacity = newCap];
				uFOR(i, 0u, this->size)
					this->ptr[i] = res[i];
				delete[] res;
			}
			else {
				delete[] this->ptr;
				this->ptr = new datatype[this->capacity = newCap];
			}
		}

		// Compare function
		virtual bool compare(const datatype&, const datatype&) const = 0;

		// Push Heap
		void non_push(const datatype& item) {
			if (this->size == this->capacity)
				newCapacity(true);
			this->ptr[this->size++] = item;
		}

		// Bubble
		void bubble(int index) {
			int parentIdx;
			datatype item = this->ptr[index];

			for (;; index = parentIdx) {
				parentIdx = (index - 1) / 2;

				if (parentIdx != index && !compare(this->ptr[parentIdx], item))
					this->ptr[index] = this->ptr[parentIdx];
				else {
					this->ptr[index] = item;
					return;
				}
			}
		}

		// Heapify
		void heapify(int index) {
			datatype temp = this->ptr[index];
			size_t left, right;

			for (size_t i = index;; index = i) {
				left = index * 2 + 1;
				right = index * 2 + 2;

				if (left < this->size && !compare(temp, this->ptr[left]))
					i = left;
				if (right < this->size && !compare(temp, this->ptr[right])
					&& !compare(this->ptr[left], this->ptr[right]))
					i = right;

				if (i == index) {
					this->ptr[index] = temp;
					break;
				}
				else
					this->ptr[index] = this->ptr[i];
			}
		}

		// Build-heap
		void build_heap()
		{
			RFOR(i, this->size >> 1 - 1, 0)
				heapify(i);
		}
#pragma endregion

		//=====     Attributes     =====//
#pragma region Attributes
		datatype* ptr;
		size_t size;
		size_t capacity;
#pragma endregion

	public:
		//=====     Constructor     =====//
#pragma region Constructor
		abstractheap(bool callMemory = true) : size{ 0u }, capacity{ 1u }
		{
			if (callMemory)
				this->ptr = new datatype;
		}

		abstractheap(size_t setCapacity) : size{ setCapacity }, capacity{ setCapacity }
		{ this->ptr = new datatype[setCapacity]; }

		virtual ~abstractheap() {
			delete[] this->ptr;
		}
#pragma endregion

		//=====     Methods     =====//
#pragma region Methods
	// Push Heap
		void push(const datatype& item) {
			if (this->size == this->capacity)
				newCapacity(true);
			this->ptr[this->size] = item;
			bubble(this->size++);
		}

		// Pop Heap
		datatype pop() {
			datatype getRoot(this->ptr[0]);				// Warning
			this->ptr[0] = this->ptr[--this->size];
			if (this->size == this->capacity >> 1u)	// capacity / 2
				newCapacity(false);
			heapify(0u);
			return getRoot;
		}

		// Get value in top Heap
		const datatype& top() const {
			return this->ptr[0];
		}

		// Try pop Heap
		bool try_pop(datatype& get) {
			if (this->size == 0u)
				return false;
			get = pop();
			return true;
		}

		// Heap being empty
		void clear() {
			this->newCapacity(this->size = 1u, false);
		}

		// Writting on the console
		void out() const {
			std::cout << '[';
			uFOR(i, 0u, this->size) {
				std::cout << this->ptr[i];
				if (i + 1u < this->size)
					std::cout << ", ";
			}
			std::cout << "]\n";
		}

		// Length of Heap
		size_t len() const {
			return this->size;
		}

		// Check Heap is empty
		bool empty() const {
			return this->size == 0u;
		}
#pragma endregion

		//=====     Operators     =====//
#pragma region Operators
	// Check Heap is not empty
		operator bool() const {
			return this->size != 0u;
		}
#pragma endregion

		//=====     Iterator     =====//
#pragma region Iterator
		class iterator {
			friend abstractheap;
			abstractheap* ref;
			datatype* ptr;

			iterator(abstractheap* heap, datatype* idx) : ref(heap), ptr(idx) {}
		public:
			//=====     Constructor     =====//
			iterator(const iterator& source) : ref(source.ref), ptr(source.ptr) {}

			//=====     Methods     =====//

			// Iterator is null
			bool null() const {
				return this->ptr < this->ref->ptr ||
					this->ptr >= this->ref->ptr + this->ref->size;
			}

			// Get index
			int index() const {
				return this->ptr - this->ref->ptr;
			}

			//=====     Operators     =====

			// Get const value of item
			const datatype& operator*() const {
				return *this->ptr;
			}

			// Get index ( type const datatype* ) of item
			const datatype* operator->() const {
				return this->ptr;
			}

			// Iterator move to the next item
			iterator& operator++() {
				if (null() == false)
					++this->ptr;
				return *this;
			}

			// Iterator move to the next item
			iterator operator++(int) {
				iterator res(*this);
				if (null() == false)
					++this->ptr;
				return res;
			}

			// Iterator moves to the previous item
			iterator& operator--() {
				if (null() == false)
					--this->ptr;
				return *this;
			}

			// Iterator moves to the previous item
			iterator operator--(int) {
				iterator res(*this);
				if (null() == false)
					--this->ptr;
				return res;
			}

			// Copy data from other iterator
			iterator& operator=(const iterator& source) {
				this->ref = source.ref;
				this->ptr = source.ptr;
				return *this;
			}

			// Compare two iterators
			bool operator==(const iterator& source) const {
				return this->ptr == source.ptr;
			}

			// Compare two iterators
			bool operator!=(const iterator& source) const {
				return this->ptr != source.ptr;
			}

			// Compare two iterators
			bool operator<(const iterator& source) const {
				return this->ptr < source.ptr;
			}

			// Compare two iterators
			bool operator>(const iterator& source) const {
				return this->ptr > source.ptr;
			}

			// Compare two iterators
			bool operator<=(const iterator& source) const {
				return this->ptr <= source.ptr;
			}

			// Compare two iterators
			bool operator>=(const iterator& source) const {
				return this->ptr >= source.ptr;
			}

			// Iterator + int(...)
			iterator operator+(int i) {
				return iterator(*this) += i;
			}

			// Iterator - int(...)
			iterator operator-(int i) {
				return iterator(*this) -= i;
			}

			// Iterator += int(...)
			iterator& operator+=(int i) {
				if (null() == false) {
					this->ptr += i;
					if (this->ptr > this->ref->ptr + this->ref->size)
						this->ptr = this->ref->ptr + this->ref->size;
					else if (this->ptr < this->ref->ptr)
						this->ptr = this->ref->ptr - 1;
				}
				return *this;
			}

			// Iterator -= int(...)
			iterator& operator-=(int i) {
				if (null() == false) {
					this->ptr -= i;
					if (this->ptr > this->ref->ptr + this->ref->size)
						this->ptr = this->ref->ptr + this->ref->size;
					else if (this->ptr < this->ref->ptr)
						this->ptr = this->ref->ptr - 1;
				}
				return *this;
			}

			// Check iterator not null
			operator bool() const {
				return this->ptr >= this->ref->ptr &&
					this->ptr < this->ref->ptr + this->ref->size;
			}
		};
#pragma endregion

		//=====     Const Iterator     =====//
#pragma region Const Iterator
		class const_iterator {
			friend abstractheap;
			const abstractheap* ref;
			const datatype* ptr;

			const_iterator(const abstractheap* heap, const datatype* idx) : ref(heap), ptr(idx) {}
		public:
			//=====     Constructor     =====//
			const_iterator(const const_iterator& source) : ref(source.ref), ptr(source.ptr) {}

			//=====     Methods     =====//

			// Const Iterator is null
			bool null() const {
				return this->ptr < this->ref->ptr ||
					this->ptr >= this->ref->ptr + this->ref->size;
			}

			// Get index
			int index() const {
				return this->ptr - this->ref->ptr;
			}

			//=====     Operators     =====

			// Get const value of item
			const datatype& operator*() const {
				return *this->ptr;
			}

			// Get index ( type const datatype* ) of item
			const datatype* operator->() const {
				return this->ptr;
			}

			// Const Iterator move to the next item
			const_iterator& operator++() {
				if (null() == false)
					++this->ptr;
				return *this;
			}

			// Const Iterator move to the next item
			const_iterator operator++(int) {
				const_iterator res(*this);
				if (null() == false)
					++this->ptr;
				return res;
			}

			// Const Iterator moves to the previous item
			const_iterator& operator--() {
				if (null() == false)
					--this->ptr;
				return *this;
			}

			// Const Iterator moves to the previous item
			const_iterator operator--(int) {
				const_iterator res(*this);
				if (null() == false)
					--this->ptr;
				return res;
			}

			// Copy data from other Const Iterator
			const_iterator& operator=(const const_iterator& source) {
				this->ref = source.ref;
				this->ptr = source.ptr;
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

			// Compare two Const Iterators
			bool operator<(const const_iterator& source) const {
				return this->ptr < source.ptr;
			}

			// Compare two Const Iterators
			bool operator>(const const_iterator& source) const {
				return this->ptr > source.ptr;
			}

			// Compare two Const Iterators
			bool operator<=(const const_iterator& source) const {
				return this->ptr <= source.ptr;
			}

			// Compare two Const Iterators
			bool operator>=(const const_iterator& source) const {
				return this->ptr >= source.ptr;
			}

			// Const Iterator + int(...)
			const_iterator operator+(int i) {
				return const_iterator(*this) += i;
			}

			// Const Iterator - int(...)
			const_iterator operator-(int i) {
				return const_iterator(*this) -= i;
			}

			// Const Iterator += int(...)
			const_iterator& operator+=(int i) {
				if (null() == false) {
					this->ptr += i;
					if (this->ptr > this->ref->ptr + this->ref->size)
						this->ptr = this->ref->ptr + this->ref->size;
					else if (this->ptr < this->ref->ptr)
						this->ptr = this->ref->ptr - 1;
				}
				return *this;
			}

			// Const Iterator -= int(...)
			const_iterator& operator-=(int i) {
				if (null() == false) {
					this->ptr -= i;
					if (this->ptr > this->ref->ptr + this->ref->size)
						this->ptr = this->ref->ptr + this->ref->size;
					else if (this->ptr < this->ref->ptr)
						this->ptr = this->ref->ptr - 1;
				}
				return *this;
			}

			// Check Const Iterator not null
			operator bool() const {
				return this->ptr >= this->ref->ptr &&
					this->ptr < this->ref->ptr + this->ref->size;
			}
		};
#pragma endregion

		//=====     Static Methods     =====//
#pragma region Static Methods
	// Heapify
		template <class Functor>
		static void heapify(datatype* arr, size_t length, size_t index, const Functor& cmp_func) {
			datatype temp = arr[index];
			size_t left, right;

			for (size_t i = index;; index = i) {
				left = index * 2 + 1;
				right = index * 2 + 2;

				if (left < length && !cmp_func(temp, arr[left]))
					i = left;
				if (right < length && !cmp_func(temp, arr[right])
					&& !cmp_func(arr[left], arr[right]))
					i = right;

				if (i == index) {
					arr[index] = temp;
					break;
				}
				else
					arr[index] = arr[i];
			}
		}

		// Build-heap
		template <class Functor>
		static void build_heap(datatype* arr, size_t length, const Functor& cmp_func)
		{
			RFOR(i, length >> 1 - 1, 0)
				heapify(arr, length, i, cmp_func);
		}
#pragma endregion

		//=====     Methods of Iterator, Const Iterator     =====//
#pragma region Methods of Iterator
	// Iterator of first item
		iterator begin() {
			return iterator(this, this->ptr);
		}

		// Const Iterator of first item
		const_iterator begin() const {
			return const_iterator(this, this->ptr);
		}

		// Iterator of last item
		iterator rbegin() {
			return iterator(this, this->ptr + this->size - 1);
		}

		// Iterator at back of Array List
		iterator end() {
			return iterator(this, this->ptr + this->size);
		}

		// Const Iterator at back of Array List
		const_iterator end() const {
			return const_iterator(this, this->ptr + this->size);
		}

		// Iterator at front of Array List
		iterator rend() {
			return iterator(this, this->ptr - 1);
		}

		// Const Iterator of first item
		const_iterator cbegin() const {
			return const_iterator(this, this->ptr);
		}

		// Const Iterator of last item
		const_iterator crbegin() const {
			return const_iterator(this, this->ptr + this->size - 1);
		}

		// Const Iterator at back of Array List
		const_iterator cend() const {
			return const_iterator(this, this->ptr + this->size);
		}

		// Const Iterator at front of Array List
		const_iterator crend() const {
			return const_iterator(this, this->ptr - 1);
		}
#pragma endregion
	};

	/* Max Heap is a dynamic array.
	You must have constructor, operator>= for your datatype.*/

	//##################################################
	//==========          MAX HEAP          ==========//
	template <class datatype>
	class maxheap : public abstractheap<datatype> {
		using base = abstractheap<datatype>;

		//=====     Private Methods     =====//
#pragma region Private Methods
	// Compare Function
		bool compare(const datatype& a, const datatype& b) const override {
			return a >= b;
		}
#pragma endregion

	public:
		//=====     Constructors and Destructor     =====//
#pragma region Constructors and Destructor
		maxheap() : base() {}

		maxheap(std::initializer_list<datatype> list) : base(list.size())
		{
			const datatype* pointer = list.begin();
			uFOR(i, 0u, this->size)
				this->ptr[i] = pointer[i];
			base::build_heap();
		}

		template <class anyIterator>
		maxheap(anyIterator begin, anyIterator end) : base()
		{
			for (; begin != end; ++begin)
				base::non_push(*begin);
			base::build_heap();
		}

		maxheap(const maxheap& source) : base(source.size)
		{
			uFOR(i, 0u, this->size)
				this->ptr[i] = source.ptr[i];
		}

		maxheap(maxheap&& source) noexcept : base(false)
		{
			this->size = source.size;
			this->capacity = source.capacity;
			this->ptr = source.ptr;
			source.ptr = nullptr;
		}

		~maxheap() {}
#pragma endregion

		//=====     Methods     =====//
#pragma region Methods
	// Swapping two Max Heap
		void swap(maxheap& source) {
			std::swap(this->ptr, source.ptr);
			std::swap(this->size, source.size);
			std::swap(this->capacity, source.capacity);
		}
#pragma endregion

		//=====     Operators     =====//
#pragma region Operators
	// Copy data from other Max Heap
		maxheap& operator=(const maxheap& source) {
			if (this == &source)
				return *this;

			base::newCapacity(this->size = source.size, false);
			uFOR(i, 0u, this->size)
				this->ptr[i] = source.ptr[i];
			return *this;
		}

		//Copy data from other Heap Array
		maxheap& operator=(maxheap&& source) noexcept {
			this->size = source.size;
			this->capacity = source.capacity;
			this->ptr = source.ptr;
			source.ptr = nullptr;
			return *this;
		}

		// Multiple push value
		maxheap& operator<<(const datatype& value) {
			base::push(value);
			return *this;
		}

		// Multiple pop value
		maxheap& operator>>(datatype& result) {
			result = base::pop();
			return *this;
		}
#pragma endregion
	};

	/* Min Heap is a dynamic array.
	You must have constructor, operator<= for your datatype.*/

	//##################################################
	//==========          MIN HEAP          ==========//
	template <class datatype>
	class minheap : public abstractheap<datatype> {
		using base = abstractheap<datatype>;

		//=====     Private Methods     =====//
#pragma region Private Methods
	//Compare Function
		bool compare(const datatype& a, const datatype& b) const override {
			return a <= b;
		}
#pragma endregion

	public:
		//=====     Constructors and Destructor     =====//
#pragma region Constructors and Destructor
		minheap() : base() {}

		minheap(std::initializer_list<datatype> list) : base(list.size())
		{
			const datatype* pointer = list.begin();
			uFOR(i, 0u, this->size)
				this->ptr[i] = pointer[i];
			base::build_heap();
		}

		template <class anyIterator>
		minheap(anyIterator begin, anyIterator end) : base()
		{
			for (; begin != end; ++begin)
				base::non_push(*begin);
			base::build_heap();
		}

		minheap(const minheap& source) : base(source.size)
		{
			uFOR(i, 0u, this->size)
				this->ptr[i] = source.ptr[i];
		}

		minheap(minheap&& source) noexcept : base(false)
		{
			this->size = source.size;
			this->capacity = source.capacity;
			this->ptr = source.ptr;
			source.ptr = nullptr;
		}

		~minheap() {}
#pragma endregion

		//=====     Methods     =====//
#pragma region Methods
	//Swapping two Array Heap
		void swap(minheap& source) {
			std::swap(this->ptr, source.ptr);
			std::swap(this->size, source.size);
			std::swap(this->capacity, source.capacity);
		}
#pragma endregion

		//=====     Operators     =====//
#pragma region Operators
	//Copy data from other Min Heap
		minheap& operator=(const minheap& source) {
			if (this == &source)
				return *this;

			base::newCapacity(this->size = source.size, false);
			uFOR(i, 0u, this->size)
				this->ptr[i] = source.ptr[i];
			return *this;
		}

		//Copy data from other Min Heap
		minheap& operator=(minheap&& source) noexcept {
			this->size = source.size;
			this->capacity = source.capacity;
			this->ptr = source.ptr;
			source.ptr = nullptr;
			return *this;
		}

		// Multiple push value
		minheap& operator<<(const datatype& value) {
			base::push(value);
			return *this;
		}

		// Multiple pop value
		minheap& operator>>(datatype& result) {
			result = base::pop();
			return *this;
		}
#pragma endregion
	};

	//==========          Overloading operator<< with std::cout           ==========//
	template <class datatype>
	std::ostream& operator<<(std::ostream& os, const maxheap<datatype>& source) {
		source.out();
		return os;
	}

	template <class datatype>
	std::ostream& operator<<(std::ostream& os, const minheap<datatype>& source) {
		source.out();
		return os;
	}
}
//**************************************************
#endif	// _FISH_HEAP_