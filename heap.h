#ifndef __FISH_HEAP_
#define __FISH_HEAP_

#include<iostream>
#include<initializer_list>

#pragma region Syntax

#ifndef _DEFINE_MACROS_
#define _DEFINE_MACROS_
#define FOR(i, start, end) for(int i = start; i < end; ++i)
#define RFOR(i, last, front) for(int i = last; i >= front; --i)
#define uFOR(i, start, end) for(size_t i = start; i < end; ++i)
#define uRFOR(i, last, front) for(size_t i = last; i >= front; --i)
#define line putchar('\n')
#define wait _getch()
#endif	// _DEFINE_MACROS_

#pragma endregion


/*Heap is a static array.
You must have constructor for your data type.*/

//##################################################
//==========          Heap          ==========
template <class datatype>
class heap {
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
	heap(bool callMemory = true) : size{ 0u }, capacity{ 1u }
	{
		if (callMemory)
			this->ptr = new datatype;
	}

	heap(size_t setCapacity) : size{ setCapacity }, capacity{ setCapacity }
	{ this->ptr = new datatype[setCapacity]; }

	virtual ~heap() {
		delete[] this->ptr;
	}
#pragma endregion

	//=====     Methods     =====
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

	//=====     Operators     =====
#pragma region Operators
	// Check Heap is not empty
	operator bool() const {
		return this->size != 0u;
	}
#pragma endregion

	//=====     Static Methods     =====
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

};

/* Max Heap is a static array.
You must have constructor, operator>= for your datatype.*/
//##################################################
//==========          Heap Array          ==========
template <class datatype>
class maxheap : public heap<datatype> {
	using base = heap<datatype>;

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

#pragma endregion
};

//**************************************************
//==========          MIN HEAP          ==========

/*Min Heap is a static array.
You must have constructor, operator<= for your datatype.*/
template <class datatype>
class minheap : public heap<datatype> {
	using base = heap<datatype>;

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

#pragma endregion
};

//==========          Overloading operator<< with std::cout           ==========
#pragma region Overloading Ostream
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

#pragma endregion
//**************************************************
#endif	// __FISH_HEAP_