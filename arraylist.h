#ifndef _ARRAY_LIST_
#define _ARRAY_LIST_

#pragma region Include
#include<iostream>
#include<initializer_list>
#include<conio.h>
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
Dynamic Array : dynamicarray<typename>				=
Array List : arraylist<typename>					=
===================================================*/

//##################################################
//==========          Abstract Array          ==========
template <class datatype>
class abstractarray {
protected:
	//=====     Protected Methods     =====//
#pragma region Protected Methods
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
#pragma endregion

	//=====     Attributes     =====//
#pragma region Attributes
	datatype* ptr;
	size_t size;
	size_t capacity;
#pragma endregion

	//=====     Consturctors and Destructor     =====//
#pragma region Constructors And Destructor
	abstractarray(size_t Capacity) : size(Capacity), capacity(Capacity)
	{ this->ptr = new datatype[this->capacity]; }
	
public:
	//Default Constructors
	abstractarray(bool callMemory = true) : size(0u), capacity(1u)
	{
		if(callMemory)
			this->ptr = new datatype[this->capacity];
	}

	//Destructor
	virtual ~abstractarray()
	{
		delete[] this->ptr;
	}
#pragma endregion

	//=====     Methods     =====//
#pragma region Methods
	//Add an item at the end
	virtual void pushBack(const datatype& item)
	{
		if (this->size == this->capacity)
			newCapacity(true);
		this->ptr[this->size++] = item;
	}

	//Add an item before the first item
	virtual void pushFront(const datatype& item)
	{
		if (this->size == this->capacity)
			newCapacity(true);
		uRFOR(i, this->size, 1u)
			this->ptr[i] = this->ptr[i - 1u];
		this->ptr[0u] = item;
		++this->size;
	}

	//Insert an item at any index
	virtual void pushAt(const datatype& item, size_t index)
	{
		if (index > this->size)
			return;

		if (this->size == this->capacity)
			newCapacity(true);
		for (size_t i = this->size; i > index; --i)
			this->ptr[i] = this->ptr[i - 1u];
		this->ptr[index] = item;
		++this->size;
	}

	//Delete last item
	virtual void popBack()
	{
		if (this->size == 0u)
			return;
		--this->size;
		if (this->size == this->capacity >> 1u)	//size == capacity / 2
			newCapacity(false);
	}

	//Delete first item
	virtual void popFront()
	{
		if (this->size == 0u)
			return;
		uFOR(i, 1u, this->size)
			this->ptr[i - 1u] = this->ptr[i];
		--this->size;
		if (this->size == this->capacity >> 1u)	//size == capacity / 2
			newCapacity(false);
	}

	//Delete an item at any index
	virtual void popAt(size_t index)
	{
		if (index >= this->size)
			return;
		uFOR(i, index + 1u, this->size)
			this->ptr[i - 1u] = this->ptr[i];
		--this->size;
		if (this->size == this->capacity >> 1u)	//size == capacity / 2
			newCapacity(false);
	}

	//Delete items in [left, right]
	virtual void popIn(size_t left, size_t right) {
		if (left > right || left >= this->size || right >= this->size)
			return;

		size_t count = right - left + 1u;
		uFOR(i, right + 1u, this->size)
			this->ptr[i - count] = this->ptr[i];
		this->size -= count;
		newCapacity(this->size);
	}

	//Reversing array
	virtual void reverse() {
		if (this->size <= 1u)
			return;
		for (size_t i = 0u, j = this->size - 1u; i < j; ++i, --j)
			std::swap(this->ptr[i], this->ptr[j]);
	}

	//Reversing in [left, right]
	virtual void reverse(size_t left, size_t right) {
		if (left > right || left >= this->size || right >= this->size)
			return;
		for (; left < right; ++left, --right)
			std::swap(this->ptr[left], this->ptr[right]);
	}

	//Array List is being empty
	virtual void clear() {
		this->size = 0u;
		newCapacity(1u, true);
	}

	//Writing on console
	virtual void out() const {
		std::cout << '[';
		uFOR(i, 0u, this->size) {
			std::cout << this->ptr[i];
			if (i + 1u < this->size)
				std::cout << ", ";
		}
		std::cout << "]\n";
	}

	//Check for empty array
	virtual bool empty() const final {
		return this->size == 0u;
	}

	//Length of array
	virtual size_t len() const final {
		return this->size;
	}
#pragma endregion

	//=====     Operators     =====//
#pragma region Operators
	//Check array is not empty
	virtual operator bool() const final
	{
		return this->size != 0u;
	}
#pragma endregion
};


//##################################################
//==========          Dynamic Array          ==========
template <class datatype>
class dynamicarray : public abstractarray<datatype> {
	using base = abstractarray<datatype>;

	//=====     Private Methods     =====//
#pragma region Private Methods
	static bool less_than_or_equal(const datatype& a, const datatype& b) {
		return a <= b;
	}

	//Sort up ascending
	template <class Functor>
	void MergeSort(Functor functor, size_t left, size_t right)
	{
		if (left >= right) return;
		size_t mid = (left + right) / 2u;
		MergeSort(functor, left, mid);
		MergeSort(functor, mid + 1u, right);
		if (functor(this->ptr[mid], this->ptr[mid + 1u])) return;

		datatype* pointer = this->ptr + left;
		size_t i = 0u, j = 0u, k = 0u;
		left = mid - left + 1u;
		right = right - mid;
		datatype* ptrLeft = new datatype[left],
			* ptrRight = this->ptr + mid + 1u;

		for (; i < left; ++i)
			ptrLeft[i] = pointer[i];
		for (i = 0u; i < left && j < right; ++k)
			if (functor(ptrLeft[i], ptrRight[j]))
				pointer[k] = ptrLeft[i++];
			else
				pointer[k] = ptrRight[j++];
		for (; i < left; ++i, ++k)
			pointer[k] = ptrLeft[i];
		delete[] ptrLeft;
	}
#pragma endregion

public:
	//=====     Consturctors and Destructor     =====//
#pragma region Constructors And Destructor
	dynamicarray() : base() {}

	dynamicarray(std::initializer_list<datatype> list) : base(list.size())
	{
		const datatype* pointer = list.begin();
		uFOR(i, 0u, this->size)
			this->ptr[i] = pointer[i];
	}

	template <class anyIterator>
	dynamicarray(anyIterator begin, anyIterator end) : base()
	{
		for (; begin != end; ++begin)
			base::pushBack(*begin);
	}

	dynamicarray(const dynamicarray& source) : base(source.size)
	{
		uFOR(i, 0u, this->size)
			this->ptr[i] = source.ptr[i];
	}

	dynamicarray(dynamicarray&& source) noexcept : base(false)
	{
		this->ptr = source.ptr;
		this->size = source.size;
		this->capacity = source.capacity;
		source.ptr = nullptr;
	}

	~dynamicarray() {}
#pragma endregion

	//=====     Methods     =====//
#pragma region Methods
	//Add a list items at the end
	void push(std::initializer_list<datatype> list) {
		size_t newSize = this->size + list.size();
		base::newCapacity(newSize);

		const datatype* pointer = list.begin();
		uFOR(i, this->size, newSize)
			this->ptr[i] = pointer[i];
		this->size = newSize;
	}

	//Remove the first item with value equal to val
	void pop(const datatype& val) {
		uFOR(i, 0u, this->size)
			if (this->ptr[i] == val) {
				base::popAt(i);
				return;
			}
	}

	//Remove all items with value equal to val
	void popAll(const datatype& val) {
		size_t count = 0u;
		uFOR(i, 0u, this->size)
			if (this->ptr[i] == val) 
				++count;
			else
				this->ptr[i - count] = this->ptr[i];
		this->size -= count;
		base::newCapacity(this->size);
	}

	//Swapping two Array List
	void swap(dynamicarray& source) {
		std::swap(this->ptr, source.ptr);
		std::swap(this->size, source.size);
		std::swap(this->capacity, source.capacity);
	}

	//Search first item with value equal to val
	int indexOf(const datatype& val) {
		uFOR(i, 0u, this->size)
			if (this->ptr[i] == val)
				return i;
		return -1;
	}

	//Binary search item with value equal to val
	int binSearch(const datatype& val, bool ascending = true) {
		if (this->size == 0u)
			return -1;
		size_t left = 0u, right = this->size - 1u, mid;

		if (ascending) {
			while (left <= right) {
				mid = (left + right) / 2u;

				if (val == this->ptr[mid])
					return mid;
				else if (val < this->ptr[mid])
					right = mid - 1u;
				else
					left = mid + 1u;
			}
		}
		else {//Descending
			while (left <= right) {
				mid = (left + right) / 2u;

				if (val == this->ptr[mid])
					return mid;
				else if (val > this->ptr[mid])
					right = mid - 1u;
				else
					left = mid + 1u;
			}
		}
		//Not found
		return -1;
	}
	
	//Set Array List include length items with value equal to val
	void memset(const datatype& val, size_t length) {
		base::newCapacity(this->size = length, false);
		uFOR(i, 0u, this->size)
			this->ptr[i] = val;
	}

	//Set all items with value equal to val
	void memset(const datatype& val) {
		uFOR(i, 0u, this->size)
			this->ptr[i] = val;
	}

	//Count how many items with value equal to val
	size_t count(const datatype& val) const {
		size_t Count(0u);
		uFOR(i, 0u, this->size)
			if (val == this->ptr[i])
				++Count;
		return Count;
	}

	//Count how many items if its satisfy the condition
	template <class Functor>
	size_t count(Functor functor) const {
		size_t Count(0u);
		uFOR(i, 0u, this->size)
			if (functor((const datatype&)this->ptr[i]))
				++Count;
		return Count;
	}

	//Sort up ascending
	void sort(bool reverse = false)
	{
		this->MergeSort(this->less_than_or_equal, 0, this->size - 1u);
		if (reverse)
			base::reverse();
	}

	//Sort up ascending
	template <class Functor>
	void sort(Functor functor, bool reverse = false)
	{
		//mergeSort(functor, 0u, this->size - 1u);
		this->MergeSort(functor, 0, this->size - 1u);
		if (reverse)
			base::reverse();
	}

	//Loop through each item
	template <class Functor>
	void foreach(Functor functor) {
		uFOR(i, 0u, this->size)
			functor(this->ptr[i]);
	}

	//Return array include items satisfy
	template <class Functor>
	dynamicarray selectIf(Functor functor) const {
		dynamicarray res;
		uFOR(i, 0u, this->size)
			if (functor((const datatype&)this->ptr[i]))
				res.pushBack(this->ptr[i]);
		return res;
	}

	//Check all items satisfy the condition
	template <class Functor>
	bool all(Functor functor) const {
		uFOR(i, 0u, this->size)
			if (functor((const datatype&)this->ptr[i]) == false)
				return false;
		return true;
	}

	//Check any items satisfy the condition
	template <class Functor>
	bool any(Functor functor) const {
		uFOR(i, 0u, this->size)
			if (functor((const datatype&)this->ptr[i]))
				return true;
		return false;
	}

#pragma endregion

	//=====     Operators     =====//
#pragma region Operators
	//Access data at index
	datatype& operator[](size_t index) {
		return this->ptr[index];
	}

	//Copy data from other dynamic array
	dynamicarray& operator=(const dynamicarray& source)
	{
		if (this == &source)
			return *this;

		base::newCapacity(this->size = source.size);
		uFOR(i, 0u, this->size)
			this->ptr[i] = source.ptr[i];
		return *this;
	}

	//Copy data from other dynamic array
	dynamicarray& operator=(dynamicarray&& source) noexcept
	{
		delete[] this->ptr;
		this->size = source.size;
		this->capacity = source.capacity;
		this->ptr = source.ptr;
		source.ptr = nullptr;
		return *this;
	}

	//Copy data from std::initializer_list
	dynamicarray& operator=(std::initializer_list<datatype> list)
	{
		base::newCapacity(this->size = list.size(), false);
		const datatype* pointer = list.begin();
		uFOR(i, 0, this->size)
			this->ptr[i] = pointer[i];
		return *this;
	}

	//Concatenation two Array List
	dynamicarray operator+(const dynamicarray& source) {
		dynamicarray res(*this);
		return res += source;
	}

	//Concatenation other Array List
	dynamicarray& operator+=(const dynamicarray& source) {
		if (source.size == 0u)
			return *this;

		size_t newSize = this->size + source.size;
		if(newSize > this->capacity)
			base::newCapacity(newSize);
		datatype* pointer = this->ptr + this->size;
		uFOR(i, 0u, source.size)
			pointer[i] = source.ptr[i];
		this->size = newSize;
		return *this;
	}
#pragma endregion

	//=====     Child Class : Iterator     =====//
#pragma region Iterator
	class iterator {
		friend dynamicarray;
		dynamicarray* ref;
		datatype* ptr;

		iterator(dynamicarray* arr, datatype* idx) : ref(arr), ptr(idx){}
	public:
		//=====     Constructor     =====//
		iterator(const iterator& source) :
			ref(source.ref), ptr(source.ptr){}

		//=====     Methods     =====//

		//Iterator is null
		bool null() const {
			return this->ptr < this->ref->ptr ||
				this->ptr >= this->ref->ptr + this->ref->size;
		}

		/*Try set a value into item*/
		bool trySet(const datatype& val) {
			if (this->ptr >= this->ref->ptr &&
				this->ptr < this->ref->ptr + this->ref->size) {
				*ptr = val;
				return true;
			}
			return false;
		}

		/*Get index of iterator*/
		int index() const {
			return this->ptr - this->ref->ptr;
		}

		//=====     Operators     =====

		//Get value of item
		datatype& operator*() {
			return *this->ptr;
		}

		//Get index ( type data* ) of item
		datatype* operator->() {
			return this->ptr;
		}

		//Iterator move to the next item
		iterator& operator++() {
			if (null() == false)
				++this->ptr;
			return *this;
		}

		//Iterator move to the next item
		iterator operator++(int) {
			iterator res(*this);
			if (null() == false)
				++this->ptr;
			return res;
		}

		//The iterator moves to the previous item
		iterator& operator--() {
			if (null() == false)
				--this->ptr;
			return *this;
		}

		//The iterator moves to the previous item
		iterator operator--(int) {
			iterator res(*this);
			if (null() == false)
				--this->ptr;
			return res;
		}

		//Copy data from other iterator
		iterator& operator=(const iterator& source) {
			this->ref = source.ref;
			this->ptr = source.ptr;
			return *this;
		}

		//Compare two iterators
		bool operator==(const iterator& source) const {
			return this->ptr == source.ptr;
		}

		//Compare two iterators
		bool operator!=(const iterator& source) const {
			return this->ptr != source.ptr;
		}

		//Compare two iterators
		bool operator<(const iterator& source) const {
			return this->ptr < source.ptr;
		}

		//Compare two iterators
		bool operator>(const iterator& source) const {
			return this->ptr > source.ptr;
		}

		//Compare two iterators
		bool operator<=(const iterator& source) const {
			return this->ptr <= source.ptr;
		}

		//Compare two iterators
		bool operator>=(const iterator& source) const {
			return this->ptr >= source.ptr;
		}

		//Iterator + int(...)
		iterator operator+(int i) {
			return iterator(*this) += i;
		}

		//Iterator - int(...)
		iterator operator-(int i) {
			return iterator(*this) -= i;
		}

		//Iterator += int(...)
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

		//Iterator -= int(...)
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

		//Check iterator not null
		operator bool() const {
			return this->ptr >= this->ref->ptr &&
				this->ptr < this->ref->ptr + this->ref->size;
		}
	};
#pragma endregion

	//=====     Child Class : Const Iterator     =====//
#pragma region ConstIterator
	class const_iterator {
		friend dynamicarray;
		const dynamicarray* ref;
		datatype* ptr;

		const_iterator(const dynamicarray* arr, datatype* idx) : ref{ arr }, ptr{ idx }{}
	public:
		//=====     Constructor     =====

		const_iterator(const const_iterator& source) :
			ref{ source.ref }, ptr{ source.ptr }{}
		//=====     Methods     =====

		//Const Iterator is null
		bool null() const {
			return this->ptr < this->ref->ptr ||
				this->ptr >= this->ref->ptr + this->ref->size;
		}

		//Get index of item
		int index() const {
			return this->ptr - this->ref->ptr;
		}
		//=====     Operators     =====

		//Get const item
		const datatype& operator*() {
			return *this->ptr;
		}

		//Get index ( type const data* ) of item
		const datatype* operator->() {
			return this->ptr;
		}

		//Operator++
		const_iterator& operator++() {
			if (null() == false)
				++this->ptr;
			return *this;
		}

		//Operator++
		const_iterator operator++(int) {
			const_iterator res(*this);
			if (null() == false)
				++this->ptr;
			return res;
		}

		//Operator--
		const_iterator& operator--() {
			if (null() == false)
				--this->ptr;
			return *this;
		}

		//Operator--
		const_iterator operator--(int) {
			const_iterator res(*this);
			if (null() == false)
				--this->ptr;
			return res;
		}

		//Copy data from other Const Iterator
		const_iterator& operator=(const const_iterator& source) {
			this->ref = source.ref;
			this->ptr = source.ptr;
			return *this;
		}

		//Compare two Const Iterators
		bool operator==(const const_iterator& source) const {
			return this->ptr == source.ptr;
		}

		//Compare two Const Iterators
		bool operator!=(const const_iterator& source) const {
			return this->ptr != source.ptr;
		}

		//Compare two Const Iterators
		bool operator<(const const_iterator& source) const {
			return this->ptr < source.ptr;
		}

		//Compare two Const Iterators
		bool operator>(const const_iterator& source) const {
			return this->ptr > source.ptr;
		}

		//Compare two Const Iterators
		bool operator<=(const const_iterator& source) const {
			return this->ptr <= source.ptr;
		}

		//Compare two Const Iterators
		bool operator>=(const const_iterator& source) const {
			return this->ptr >= source.ptr;
		}

		//Const Iterator + int(...)
		const_iterator operator+(int i)
		{
			return const_iterator(*this) + i;
		}

		//Const Iterator - int(...)
		const_iterator operator-(int i)
		{
			return const_iterator(*this) - i;
		}

		//Const Iterator += int(...)
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

		//Const Iterator -= int(...)
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

		//Check Const Iterator is not null
		operator bool() const {
			return this->ptr >= this->ref->ptr &&
				this->ptr < this->ref->ptr + this->ref->size;
		}
	};
#pragma endregion

	//=====     Methods of Iterator, Const Iterator     =====//
#pragma region Methods of Iterator
	//Iterator of first item
	iterator begin() {
		return iterator(this, this->ptr);
	}

	//Const Iterator of first item
	const_iterator begin() const {
		return const_iterator(this, this->ptr);
	}

	//Iterator of last item
	iterator rbegin() {
		return iterator(this, this->ptr + this->size - 1);
	}

	//Iterator at back of Array List
	iterator end() {
		return iterator(this, this->ptr + this->size);
	}

	//Const Iterator at back of Array List
	const_iterator end() const {
		return const_iterator(this, this->ptr + this->size);
	}

	//Iterator at front of Array List
	iterator rend() {
		return iterator(this, this->ptr - 1);
	}

	//Const Iterator of first item
	const_iterator cbegin() const {
		return const_iterator(this, this->ptr);
	}

	//Const Iterator of last item
	const_iterator crbegin() const {
		return const_iterator(this, this->ptr + this->size - 1);
	}

	//Const Iterator at back of Array List
	const_iterator cend() const {
		return const_iterator(this, this->ptr + this->size);
	}

	//Const Iterator at front of Array List
	const_iterator crend() const {
		return const_iterator(this, this->ptr - 1);
	}
#pragma endregion
};
//==================================================

//##################################################
//==========          Array List          ==========
template <class datatype>
class arraylist : public abstractarray<datatype*> {
private:
	using base = abstractarray<datatype*>;

	//=====     Private Methods     =====//
#pragma region Private Methods
	static bool less_than_or_equal(const datatype& a, const datatype& b) {
		return a <= b;
	}

	//Sort up ascending
	template <class Functor>
	void MergeSort(Functor functor, size_t left, size_t right)
	{
		if (left >= right) return;
		size_t mid = (left + right) / 2u;
		MergeSort(functor, left, mid);
		MergeSort(functor, mid + 1u, right);
		if (functor(*this->ptr[mid], *this->ptr[mid + 1u])) return;

		datatype** pointer = this->ptr + left;
		size_t i = 0u, j = 0u, k = 0u;
		left = mid - left + 1u;
		right = right - mid;
		datatype** ptrLeft = new datatype * [left],
			** ptrRight = this->ptr + mid + 1u;

		for (; i < left; ++i)
			ptrLeft[i] = pointer[i];
		for (i = 0u; i < left && j < right; ++k)
			if (functor(*ptrLeft[i], *ptrRight[j]))
				pointer[k] = ptrLeft[i++];
			else
				pointer[k] = ptrRight[j++];
		for (; i < left; ++i, ++k)
			pointer[k] = ptrLeft[i];
		delete[] ptrLeft;
	}
#pragma endregion

public:
	//=====     Constructors And Destructor     =====//
#pragma region Constructors And Destructor
	arraylist() : base() {}

	arraylist(std::initializer_list<datatype> list) : base(list.size())
	{
		const datatype* pointer = list.begin();
		uFOR(i, 0, this->size)
			this->ptr[i] = new datatype(pointer[i]);
	}

	arraylist(const arraylist& source) :
		base(source.size)
	{
		uFOR(i, 0, this->size)
			this->ptr[i] = new datatype(*source.ptr[i]);
	}

	template <class anyIterator>
	arraylist(anyIterator begin, anyIterator end) : base()
	{
		for (; begin != end; ++begin)
			pushBack(*begin);
	}

	arraylist(arraylist&& source) noexcept : base(false)
	{
		this->size = source.size;
		this->capacity = source.capacity;
		this->ptr = source.ptr;
		source.ptr = nullptr;
	}

	~arraylist()
	{
		if (this->ptr == nullptr)
			return;
		uFOR(i, 0, this->size)
			delete this->ptr[i];
	}
#pragma endregion

	//=====     Methods     =====//
#pragma region Methods
	//Add a list items at the end
	void push(std::initializer_list<datatype> list)
	{
		size_t listSize = list.size();
		size_t newSize = this->size + listSize;
		if (this->capacity < newSize)
			base::newCapacity(newSize);

		const datatype* pointer = list.begin();
		datatype** res = this->ptr + this->size;
		uFOR(i, 0u, listSize)
			res[i] = new datatype(pointer[i]);
		this->size = newSize;
	}

	//Add an item at the end
	void pushBack(const datatype& item)
	{
		base::pushBack(new datatype(item));
	}

	//Add an item before the first item
	void pushFront(const datatype& item)
	{
		base::pushFront(new datatype(item));
	}

	//Insert an item at any index
	void pushAt(const datatype& item, size_t index)
	{
		if (index > this->size)
			return;
		base::pushAt(new datatype(item), index);
	}

	//Remove last item
	void popBack()
	{
		delete this->ptr[this->size - 1u];
		base::popBack();
	}

	//Remove first item
	void popFront()
	{
		delete this->ptr[0];
		base::popFront();
	}

	//Remove an item at any index
	void popAt(size_t index)
	{
		if (this->size == 0u || index >= this->size)
			return;
		delete this->ptr[index];
		base::popAt(index);
	}

	//Remove the first item with value equal to val
	bool pop(const datatype& val) {
		uFOR(i, 0u, this->size)
			if (*this->ptr[i] == val) {
				popAt(i);
				return true;
			}
		return false;
	}

	//Remove all items with value equal to val
	void popAll(const datatype& val) {
		size_t count = 0u;
		uFOR(i, 0u, this->size)
			if (*this->ptr[i] == val) {
				delete this->ptr[i];
				++count;
			}
			else this->ptr[i - count] = this->ptr[i];

		this->size -= count;
		base::newCapacity(this->size);
	}

	//Delete items in [left, right]
	void popIn(size_t left, size_t right) {
		if (left > right || left >= this->size || right >= this->size)
			return;

		size_t count = right - left + 1u;
		//Free items in [left, right]
		for (size_t i = left; i <= right; ++i)
			delete this->ptr[i];
		uFOR(i, right + 1u, this->size)
			this->ptr[i - count] = this->ptr[i];
		this->size -= count;
		base::newCapacity(this->size);
	}

	//Swapping two Array List
	void swap(arraylist& source) {
		if (this == &source)
			return;

		std::swap(this->capacity, source.capacity);
		std::swap(this->size, source.size);
		std::swap(this->ptr, source.ptr);
	}

	//Search first item with value equal to val
	int indexOf(const datatype& val) const {
		uFOR(i, 0u, this->size)
			if (*this->ptr[i] == val)
				return i;
		return -1;
	}

	//Binary search item with value equal to val
	int binSearch(const datatype& val, bool ascending = true) {
		if (this->size == 0u)
			return -1;
		size_t left = 0u, right = this->size - 1u, mid;

		if (ascending) {
			while (left <= right) {
				mid = (left + right) / 2u;

				if (val == *this->ptr[mid])
					return mid;
				else if (val < *this->ptr[mid])
					right = mid - 1u;
				else
					left = mid + 1u;
			}
		}
		else {//Descending
			while (left <= right) {
				mid = (left + right) / 2u;

				if (val == *this->ptr[mid])
					return mid;
				else if (val > *this->ptr[mid])
					right = mid - 1u;
				else
					left = mid + 1u;
			}
		}
		//Not found
		return -1;
	}

	//Array List is being empty
	void clear() {
		uFOR(i, 0u, this->size)
			delete this->ptr[i];
		base::clear();
	}

	//Set Array List include length items with value equal to val
	void memset(const datatype& val, size_t length) {
		uFOR(i, 0u, this->size)
			delete this->ptr[i];

		base::newCapacity(length, false);
		this->size = length;
		uFOR(i, 0u, this->size)
			this->ptr[i] = new datatype(val);
	}

	//Set all items with value equal to val
	void memset(const datatype& item) {
		uFOR(i, 0u, this->size)
			delete this->ptr[i];
		uFOR(i, 0u, this->size)
			this->ptr[i] = new datatype(item);
	}

	//Count how many items with value equal to val
	size_t count(const datatype& val) const {
		size_t Count(0u);
		uFOR(i, 0u, this->size)
			if (val == *this->ptr[i])
				++Count;
		return Count;
	}

	//Sort up ascending
	void sort(bool reverse = false)
	{
		this->MergeSort(this->less_than_or_equal, 0u, this->size - 1u);
		if (reverse)
			base::reverse();
	}

	//Sort up ascending
	template <class Functor>
	void sort(Functor functor, bool reverse = false)
	{
		this->MergeSort(functor, 0u, this->size - 1u);
		if (reverse)
			base::reverse();
	}

	//Count how many items if its satisfy the condition
	template <class Functor>
	size_t count(Functor functor) const {
		size_t Count(0u);
		uFOR(i, 0, this->size)
			if (functor((const datatype&)*this->ptr[i]))
				++Count;
		return Count;
	}

	//Loop through each item
	template <class Functor>
	void foreach(Functor functor) {
		uFOR(i, 0u, this->size)
			functor(*this->ptr[i]);
	}

	//Return array include items satisfy
	template <class Functor>
	arraylist selectIf(Functor functor) const {
		arraylist res;
		uFOR(i, 0u, this->size)
			if (functor((const datatype&)*this->ptr[i]))
				res.pushBack(*this->ptr[i]);
		return res;
	}

	//Check all items satisfy the condition
	template <class Functor>
	bool all(Functor functor) const {
		uFOR(i, 0u, this->size)
			if (functor((const datatype)*this->ptr[i]) == false)
				return false;
		return true;
	}

	//Check any items satisfy the condition
	template <class Functor>
	bool any(Functor functor) const {
		uFOR(i, 0u, this->size)
			if (functor((const datatype)*this->ptr[i]))
				return true;
		return false;
	}

	//Writing on console
	void out() const override {
		std::cout << "[";
		uFOR(i, 0u, this->size) {
			std::cout << *this->ptr[i];
			if (i + 1u < this->size)
				std::cout << ", ";
		}
		std::cout << "]\n";
	}
#pragma endregion

	//=====     Operators     =====//
#pragma region Operators
	//Access data at index
	datatype& operator[](size_t index)
	{
		return *this->ptr[index];
	}

	//Copy data from other Array List
	arraylist& operator=(const arraylist& source)
	{
		if (this == &source)
			return *this;

		uFOR(i, 0, this->size)
			delete this->ptr[i];
		base::newCapacity(source.size, false);
		this->size = source.size;

		uFOR(i, 0, this->size)
			this->ptr[i] = new datatype(*source.ptr[i]);
		return *this;
	}

	//Get data from other Array List
	arraylist& operator=(arraylist&& source) noexcept
	{
		uFOR(i, 0, this->size)
			delete this->ptr[i];
		delete[] this->ptr;
		//Get data
		this->size = source.size;
		this->capacity = source.capacity;
		this->ptr = source.ptr;
		source.ptr = nullptr;
		return *this;
	}

	//Get data from initializer_list<data>
	arraylist& operator=(std::initializer_list<datatype> list)
	{
		uFOR(i, 0u, this->size)
			delete this->ptr[i];
		base::newCapacity(this->size = list.size(), false);
		const datatype* pointer = list.begin();
		uFOR(i, 0u, this->size)
			this->ptr[i] = new datatype(pointer[i]);
		return *this;
	}

	//Concatenation two Array List
	arraylist operator+(const arraylist& source)
	{
		arraylist res = *this;
		res += source;
		return res;
	}

	//Concatenation other Array List
	arraylist& operator+=(const arraylist& source)
	{
		if (source.size == 0u)
			return *this;

		size_t newSize = this->size + source.size;
		if(newSize > this->capacity)
			base::newCapacity(newSize);

		datatype** res = this->ptr + this->size;
		uFOR(i, 0, source.size)
			res[i] = new datatype(*source.ptr[i]);
		this->size = newSize;
		return *this;
	}
#pragma endregion

	//=====     Child Class : Iterator     =====//
#pragma region Iterator
	class iterator {
		friend arraylist;
		arraylist* ref;
		datatype** ptr;

		iterator(arraylist* arr, datatype** idx) : ref{ arr }, ptr{ idx }{}
	public:
		//=====     Constructor     =====//

		iterator(const iterator& source) :
			ref{ source.ref }, ptr{ source.ptr }{}
		//=====     Methods     =====//

		//Iterator is null
		bool null() const {
			return this->ptr < this->ref->ptr ||
				this->ptr >= this->ref->ptr + this->ref->size;
		}

		/*Try set a value into item*/
		bool trySet(const datatype& val) {
			if (this->ptr >= this->ref->ptr &&
				this->ptr < this->ref->ptr + this->ref->size) {
				**ptr = val;
				return true;
			}
			return false;
		}

		/*Get index of iterator*/
		int index() const {
			return this->ptr - this->ref->ptr;
		}

		//=====     Operators     =====
		
		//Get value of item
		datatype& operator*() {
			return **this->ptr;
		}

		//Get index ( type data* ) of item
		datatype* operator->() {
			return *this->ptr;
		}

		//Iterator move to the next item
		iterator& operator++() {
			if (null() == false)
				++this->ptr;
			return *this;
		}

		//Iterator move to the next item
		iterator operator++(int) {
			iterator res(*this);
			if (null() == false)
				++this->ptr;
			return res;
		}

		//The iterator moves to the previous item
		iterator& operator--() {
			if (null() == false)
				--this->ptr;
			return *this;
		}

		//The iterator moves to the previous item
		iterator operator--(int) {
			iterator res(*this);
			if (null() == false)
				--this->ptr;
			return res;
		}

		//Copy data from other iterator
		iterator& operator=(const iterator& source) {
			this->ref = source.ref;
			this->ptr = source.ptr;
			return *this;
		}

		//Compare two iterators
		bool operator==(const iterator& source) const {
			return this->ptr == source.ptr;
		}

		//Compare two iterators
		bool operator!=(const iterator& source) const {
			return this->ptr != source.ptr;
		}

		//Compare two iterators
		bool operator<(const iterator& source) const {
			return this->ptr < source.ptr;
		}

		//Compare two iterators
		bool operator>(const iterator& source) const {
			return this->ptr > source.ptr;
		}

		//Compare two iterators
		bool operator<=(const iterator& source) const {
			return this->ptr <= source.ptr;
		}

		//Compare two iterators
		bool operator>=(const iterator& source) const {
			return this->ptr >= source.ptr;
		}

		//Iterator + int(...)
		iterator operator+(int i) {
			return iterator(*this) += i;
		}

		//Iterator - int(...)
		iterator operator-(int i) {
			return iterator(*this) -= i;
		}

		//Iterator += int(...)
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

		//Iterator -= int(...)
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

		//Check iterator not null
		operator bool() const {
			return this->ptr >= this->ref->ptr &&
				this->ptr < this->ref->ptr + this->ref->size;
		}
	};
#pragma endregion

	//=====     Child Class : Const Iterator     =====//
#pragma region ConstIterator
	class const_iterator {
		friend arraylist;
		const arraylist* ref;
		datatype** ptr;

		const_iterator(const arraylist* arr, datatype** idx) : ref{ arr }, ptr{ idx }{}
	public:
		//=====     Constructor     =====

		const_iterator(const const_iterator& source) :
			ref{ source.ref }, ptr{ source.ptr }{}
		//=====     Methods     =====

		//Const Iterator is null
		bool null() const {
			return this->ptr < this->ref->ptr ||
				this->ptr >= this->ref->ptr + this->ref->size;
		}

		//Get index of item
		int index() const {
			return this->ptr - this->ref->ptr;
		}
		//=====     Operators     =====

		//Get const item
		const datatype& operator*() {
			return **this->ptr;
		}

		//Get index ( type const data* ) of item
		const datatype* operator->() {
			return *this->ptr;
		}

		//Operator++
		const_iterator& operator++() {
			if (null() == false)
				++this->ptr;
			return *this;
		}

		//Operator++
		const_iterator operator++(int) {
			const_iterator res(*this);
			if (null() == false)
				++this->ptr;
			return res;
		}

		//Operator--
		const_iterator& operator--() {
			if (null() == false)
				--this->ptr;
			return *this;
		}

		//Operator--
		const_iterator operator--(int) {
			const_iterator res(*this);
			if (null() == false)
				--this->ptr;
			return res;
		}

		//Copy data from other Const Iterator
		const_iterator& operator=(const const_iterator& source) {
			this->ref = source.ref;
			this->ptr = source.ptr;
			return *this;
		}

		//Compare two Const Iterators
		bool operator==(const const_iterator& source) const {
			return this->ptr == source.ptr;
		}

		//Compare two Const Iterators
		bool operator!=(const const_iterator& source) const {
			return this->ptr != source.ptr;
		}

		//Compare two Const Iterators
		bool operator<(const const_iterator& source) const {
			return this->ptr < source.ptr;
		}

		//Compare two Const Iterators
		bool operator>(const const_iterator& source) const {
			return this->ptr > source.ptr;
		}

		//Compare two Const Iterators
		bool operator<=(const const_iterator& source) const {
			return this->ptr <= source.ptr;
		}

		//Compare two Const Iterators
		bool operator>=(const const_iterator& source) const {
			return this->ptr >= source.ptr;
		}

		//Const Iterator + int(...)
		const_iterator operator+(int i)
		{
			return const_iterator(*this) + i;
		}

		//Const Iterator - int(...)
		const_iterator operator-(int i)
		{
			return const_iterator(*this) - i;
		}

		//Const Iterator += int(...)
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

		//Const Iterator -= int(...)
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

		//Check Const Iterator is not null
		operator bool() const {
			return this->ptr >= this->ref->ptr &&
				this->ptr < this->ref->ptr + this->ref->size;
		}
	};
#pragma endregion

	//=====     Methods of Iterator, Const Iterator     =====//
#pragma region Methods of Iterator
	//Iterator of first item
	iterator begin() {
		return iterator(this, this->ptr);
	}

	//Const Iterator of first item
	const_iterator begin() const {
		return const_iterator(this, this->ptr);
	}

	//Iterator of last item
	iterator rbegin() {
		return iterator(this, this->ptr + this->size - 1);
	}

	//Iterator at back of Array List
	iterator end() {
		return iterator(this, this->ptr + this->size);
	}

	//Const Iterator at back of Array List
	const_iterator end() const {
		return const_iterator(this, this->ptr + this->size);
	}

	//Iterator at front of Array List
	iterator rend() {
		return iterator(this, this->ptr - 1);
	}

	//Const Iterator of first item
	const_iterator cbegin() const {
		return const_iterator(this, this->ptr);
	}

	//Const Iterator of last item
	const_iterator crbegin() const {
		return const_iterator(this, this->ptr + this->size - 1);
	}

	//Const Iterator at back of Array List
	const_iterator cend() const {
		return const_iterator(this, this->ptr + this->size);
	}

	//Const Iterator at front of Array List
	const_iterator crend() const {
		return const_iterator(this, this->ptr - 1);
	}
#pragma endregion

};
//==================================================
//=====     Overloading Operator STD::COUT     =====//
template <class datatype>
std::ostream& operator<<(std::ostream& os, const dynamicarray<datatype>& list) {
	list.out();
	return os;
}

template <class datatype>
std::ostream& operator<<(std::ostream& os, const arraylist<datatype>& list) {
	list.out();
	return os;
}
//==================================================
#endif	//_ARRAY_LIST_
