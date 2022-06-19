#ifndef _HEAP_ARRAY_
#define _HEAP_ARRAY_

#pragma region Include
#include<iostream>
#include<initializer_list>
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
#endif

#pragma endregion


/*Heap Array is a static array.
You must have constructor for your data type.*/

//##################################################
//==========          Heap Array          ==========
template <class data>
class heaparray {
protected:
	//=====     Protected Method     =====//
#pragma region Protected Methods
	//Change memory length
	void newCapacity(bool expand) {
		if (this->capacity == 1u && expand == false)
			return;
		data* res = this->ptr;

		//Expand is true than capacity * 2 else capacity / 2
		expand ? this->capacity <<= 1u : this->capacity >>= 1u;
		this->ptr = new data[this->capacity];
		uFOR(i, 0u, this->size)
			this->ptr[i] = res[i];
		delete[] res;
	}

	//Change memory length
	void newCapacity(size_t newCap, bool maintain_data = true)
	{
		if (maintain_data)
		{
			if (newCap < this->size) return;
			data* res = this->ptr;
			this->ptr = new data[this->capacity = newCap];
			uFOR(i, 0u, this->size)
				this->ptr[i] = res[i];
			delete[] res;
		}
		else {
			delete[] this->ptr;
			this->ptr = new data[this->capacity = newCap];
		}
	}

	//Compare function
	virtual bool compare(const data& item1, const data& item2) const = 0;

	//Heapify
	void heapify(size_t index) {
		data temp = this->ptr[index];

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

	//Bubble
	void bubble(int index) {
		int parentIdx;
		data item = this->ptr[index];

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
#pragma endregion

	//=====     Attributes     =====//
#pragma region Attributes
	data* ptr;
	size_t size;
	size_t capacity;
#pragma endregion

public:
	//=====     Constructor     =====//
#pragma region Constructor
	heaparray(bool callMemory = true) : size{ 0u }, capacity{ 1u }
	{
		if(callMemory)
			this->ptr = new data;
	}

	heaparray(size_t setCapacity) : size{ setCapacity }, capacity{ setCapacity }
	{ this->ptr = new data[setCapacity]; }

	virtual ~heaparray() {
		delete[] this->ptr;
	}
#pragma endregion

	//=====     Methods     =====
#pragma region Methods
	//Push Heap Array
	void push(const data& item) {
		if (this->size == this->capacity)
			newCapacity(true);
		this->ptr[this->size] = item;
		bubble(this->size++);
	}

	//Pop Heap Array
	data pop() {
		data getRoot(this->ptr[0]);	//Warning
		this->ptr[0] = this->ptr[--this->size];
		if(this->size == this->capacity >> 1u)	//capacity / 2
			newCapacity(false);
		heapify(0u);
		return getRoot;
	}

	//Try pop Heap Array
	bool tryPop(data& get) {
		if (this->size == 0u)
			return false;
		get = pop();
		return true;
	}

	//Array Heap begin empty
	void clear() {
		this->newCapacity(this->size = 1u, false);
	}

	//Writting on the console
	void out() const {
		std::cout << '[';
		uFOR(i, 0u, this->size) {
			std::cout << this->ptr[i];
			if (i + 1u < this->size)
				std::cout << ", ";
		}
		std::cout << "]\n";
	}

	//Length of Heap Array
	size_t length() const {
		return this->size;
	}

	//Check Heap Array is empty
	bool empty() const {
		return this->size == 0u;
	}

	//Capacity of Heap Array
	size_t limit() const {
		return this->capacity;
	}
#pragma endregion
	
	//=====     Operators     =====
#pragma region Operators
	//Check Heap Array is not empty
	operator bool() const {
		return this->size != 0u;
	}

#pragma endregion
};

/*Max Heap is a static array.
You must have constructor, operator>= for your data type.*/
//##################################################
//==========          Heap Array          ==========
template <class data>
class maxheaparr : public heaparray<data> {
	using base = heaparray<data>;

	//=====     Private Methods     =====//
#pragma region Private Methods
	//Compare Function
	bool compare(const data& item1, const data& item2) const override {
		return item1 >= item2;
	}
#pragma endregion

public:
	//=====     Constructors and Destructor     =====//
#pragma region Constructors and Destructor
	maxheaparr() : base() {}

	maxheaparr(std::initializer_list<data> list) : base(list.size())
	{
		const data* pointer = list.begin();
		uFOR(i, 0u, this->size)
			this->ptr[i] = pointer[i];
		RFOR(i, (this->capacity - 1) >> 1, 0)
			this->heapify(i);
	}

	maxheaparr(const maxheaparr& source) : base(source.size)
	{
		uFOR(i, 0u, this->size)
			this->ptr[i] = source.ptr[i];
	}

	maxheaparr(maxheaparr&& source) noexcept : base(false)
	{
		this->size = source.size;
		this->capacity = source.capacity;
		this->ptr = source.ptr;
		source.ptr = nullptr;
	}

	~maxheaparr() {}
#pragma endregion

	//=====     Methods     =====//
#pragma region Methods
	//Swapping two Array Heap
	void swap(maxheaparr& source) {
		std::swap(this->ptr, source.ptr);
		std::swap(this->size, source.size);
		std::swap(this->capacity, source.capacity);
	}
#pragma endregion

	//=====     Operators     =====//
#pragma region Operators
	//Copy data from other Heap Array
	maxheaparr& operator=(const maxheaparr& source) {
		if (this == &source)
			return *this;

		base::newCapacity(this->size = source.size, false);
		uFOR(i, 0u, this->size)
			this->ptr[i] = source.ptr[i];
		return *this;
	}

	//Copy data from other Heap Array
	maxheaparr& operator=(maxheaparr&& source) noexcept {
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
You must have constructor, operator<= for your data type.*/

template <class data>
class minheaparr : public heaparray<data> {
	using base = heaparray<data>;

	//=====     Private Methods     =====//
#pragma region Private Methods
	//Compare Function
	bool compare(const data& item1, const data& item2) const override {
		return item1 <= item2;
	}
#pragma endregion

public:
	//=====     Constructors and Destructor     =====//
#pragma region Constructors and Destructor
	minheaparr() : base() {}

	minheaparr(std::initializer_list<data> list) : base(list.size())
	{
		const data* pointer = list.begin();
		uFOR(i, 0u, this->size)
			this->ptr[i] = pointer[i];
		RFOR(i, (this->capacity - 1) >> 1, 0)
			this->heapify(i);
	}

	minheaparr(const minheaparr& source) : base(source.size)
	{
		uFOR(i, 0u, this->size)
			this->ptr[i] = source.ptr[i];
	}

	minheaparr(minheaparr&& source) noexcept : base(false)
	{
		this->size = source.size;
		this->capacity = source.capacity;
		this->ptr = source.ptr;
		source.ptr = nullptr;
	}

	~minheaparr() {}
#pragma endregion

	//=====     Methods     =====//
#pragma region Methods
	//Swapping two Array Heap
	void swap(minheaparr& source) {
		std::swap(this->ptr, source.ptr);
		std::swap(this->size, source.size);
		std::swap(this->capacity, source.capacity);
	}
#pragma endregion


	//=====     Operators     =====//
#pragma region Operators
	//Copy data from other Heap Array
	minheaparr& operator=(const minheaparr& source) {
		if (this == &source)
			return *this;

		base::newCapacity(this->size = source.size, false);
		uFOR(i, 0u, this->size)
			this->ptr[i] = source.ptr[i];
		return *this;
	}

	//Copy data from other Heap Array
	minheaparr& operator=(minheaparr&& source) noexcept {
		this->size = source.size;
		this->capacity = source.capacity;
		this->ptr = source.ptr;
		source.ptr = nullptr;
		return *this;
	}

#pragma endregion
};

#pragma region Overloading Ostream

template <class data>
std::ostream& operator<<(std::ostream& os, const maxheaparr<data>& source) {
	source.out();
	return os;
}

template <class data>
std::ostream& operator<<(std::ostream& os, const minheaparr<data>& source) {
	source.out();
	return os;
}

#pragma endregion
//**************************************************
#endif	//_HEAP_ARRAY_
