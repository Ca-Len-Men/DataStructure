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
==================================================*/

//##################################################
//==========          Dynamic Array          ==========
template <class data>
class dynamicarray {
protected:
#pragma region Protected Area
	void newCapacity(bool expand) {
		if (this->capacity == 1 && expand == false)
			return;
		data* res = this->ptr;
		//expand is true -> capacity x 2, else capacity / 2
		expand ? this->capacity <<= 1 : this->capacity >>= 1;
		this->ptr = new data[this->capacity];
		uFOR(i, 0, this->size)
			this->ptr[i] = res[i];
		delete[] res;
	}

	void newCapacity(size_t newCap, bool maintain_data = true)
	{
		if (maintain_data)
		{
			if (newCap < this->size) return;
			data* res = this->ptr;
			this->ptr = new data[this->capacity = newCap];
			uFOR(i, 0, this->size)
				this->ptr[i] = res[i];
			delete[] res;
		}else {
			delete[] this->ptr;
			this->ptr = new data[this->capacity = newCap];
		}
		
	}
#pragma endregion

#pragma region Attributes
public:
	data* ptr;
	size_t size;
	size_t capacity;
#pragma endregion

#pragma region Constructors And Destructor
protected:
	dynamicarray(size_t Capacity) : size{ 0 }, capacity{ Capacity }
	{ this->ptr = new data[this->capacity]; }

public:
	//Default Constructors
	dynamicarray() : size{ 0 }, capacity{ 1 }
	{ this->ptr = new data[this->capacity]; }

	dynamicarray(std::initializer_list<data> list) :
		size{ list.size() }, capacity{ list.size() }
	{
		this->ptr = new data[this->capacity];
		const data* pointer = list.begin();
		uFOR(i, 0, this->size)
			this->ptr[i] = pointer[i];
	}

	dynamicarray(const dynamicarray& source) :
		size{ source.size }, capacity{ source.capacity }
	{
		this->ptr = new data[this->capacity];
		uFOR(i, 0, this->size)
			this->ptr[i] = source.ptr[i];
	}

	dynamicarray(dynamicarray&& source) noexcept :
		size{ source.size }, capacity{ source.capacity }
	{
		this->ptr = source.ptr;
		source.ptr = nullptr;
	}

	//Destructor
	virtual ~dynamicarray()
	{
		delete[] this->ptr;
	}
#pragma endregion

#pragma region Methods
	//Add an item at the end
	void pushBack(const data& item)
	{
		if (this->size == this->capacity)
			newCapacity(true);
		this->ptr[this->size++] = item;
	}

	//Add an item before the first item
	void pushFront(const data& item)
	{
		if (this->size == this->capacity)
			newCapacity(true);
		uRFOR(i, this->size, 1)
			this->ptr[i] = this->ptr[i - 1];
		this->ptr[0] = item;
		++this->size;
	}

	//Insert an item at any index
	void pushAt(const data& item, size_t index)
	{
		if (index > this->size)
			return;
		if (this->size == this->capacity)
			newCapacity(true);

		for (size_t i = this->size; i > index; --i)
			this->ptr[i] = this->ptr[i - 1];
		this->ptr[index] = item;
		++this->size;
	}

	//Delete last item
	void popBack()
	{
		if (this->size == 0)
			return;
		--this->size;
		if (this->size == this->capacity >> 1)	//size == capacity / 2
			newCapacity(false);
	}

	//Delete first item
	void popFront()
	{
		if (this->size == 0)
			return;
		uFOR(i, 1, this->size)
			this->ptr[i - 1] = this->ptr[i];
		--this->size;
		if (this->size == this->capacity >> 1)	//size == capacity / 2
			newCapacity(false);
	}

	//Delete an item at any index
	void popAt(size_t index)
	{
		if (this->size == 0)
			return;
		uFOR(i, index + 1, this->size)
			this->ptr[i - 1] = this->ptr[i];
		--this->size;
		if (this->size == this->capacity >> 1)	//size == capacity / 2
			newCapacity(false);
	}

	//Writing on console
	virtual void out() const {
		if (this->size == 0) {
			std::cout << "Array List is empty !" << std::endl;
			return;
		}

		uFOR(i, 0, this->size)
			std::cout << this->ptr[i] << ' ';
		std::cout << std::endl;
	}

	//Check for empty array
	virtual bool empty() const {
		return this->size == 0;
	}

	//Length of array
	virtual size_t length() const {
		return this->size;
	}

	//Capacity of array
	virtual size_t limit() const {
		return this->capacity;
	}

#pragma endregion

#pragma region Operators
	//Check array is not empty
	virtual operator bool()
	{
		return this->size != 0;
	}

	//Access data at any index
	data& operator[](size_t index) {
		return this->ptr[index];
	}

	//Copy data from other dynamic array
	dynamicarray& operator=(const dynamicarray& source)
	{
		if (this == &source)
			return *this;

		delete[] this->ptr;
		this->size = source.size;
		this->capacity = source.capacity;
		this->ptr = new data[this->capacity];
		uFOR(i, 0, this->size)
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
	dynamicarray& operator=(std::initializer_list<data> source)
	{
		delete[] this->ptr;
		this->size = this->capacity = source.size();
		this->ptr = new data[this->capacity];
		const data* pointer = source.begin();
		uFOR(i, 0, this->size)
			this->ptr[i] = pointer[i];
		return *this;
	}
#pragma endregion
};
//==================================================

//##################################################
//==========          Array List          ==========
template <class data>
class arraylist : protected dynamicarray<data*> {
private:
	using base = dynamicarray<data*>;

#pragma region Private Methods
	//Sort up ascending
	void mergeSort(size_t left, size_t right)
	{
		if (left >= right) return;
		size_t mid = (left + right) / 2u;
		mergeSort(left, mid);
		mergeSort(mid + 1u, right);
		if (*this->ptr[mid] <= *this->ptr[mid + 1u]) return;

		data** pointer = this->ptr + left;
		size_t i = 0u, j = 0u, k = 0u;
		left = mid - left + 1u;
		right = right - mid;
		data** ptrLeft = new data * [left],
			** ptrRight = this->ptr + mid + 1u;
		
		for(; i < left; ++i)
			ptrLeft[i] = pointer[i];
		for (i = 0u; i < left && j < right; ++k)
			if (*ptrLeft[i] <= *ptrRight[j])
				pointer[k] = ptrLeft[i++];
			else
				pointer[k] = ptrRight[j++];
		for(; i < left; ++i, ++k)
			pointer[k] = ptrLeft[i];
		delete[] ptrLeft;
	}

	//Sort up ascending
	template <class Functor>
	void mergeSort(Functor functor, size_t left, size_t right)
	{
		if (left >= right) return;
		size_t mid = (left + right) / 2u;
		mergeSort(functor, left, mid);
		mergeSort(functor, mid + 1u, right);
		if (functor(*this->ptr[mid], *this->ptr[mid + 1u])) return;

		data** pointer = this->ptr + left;
		size_t i = 0u, j = 0u, k = 0u;
		left = mid - left + 1u;
		right = right - mid;
		data** ptrLeft = new data * [left],
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

#pragma region Attributes
#pragma endregion

public:
	//=====     Constructors And Destructor     =====//
#pragma region Constructors And Destructor
	arraylist() : base()
	{ this->ptr[0] = nullptr; }

	arraylist(std::initializer_list<data> list) :
		base(list.size())
	{
		this->size = list.size();
		const data* pointer = list.begin();
		uFOR(i, 0, this->size)
			this->ptr[i] = new data(pointer[i]);
	}

	arraylist(const arraylist& source) :
		base(source.size)
	{
		this->size = source.size;
		uFOR(i, 0, this->size)
			this->ptr[i] = new data(*source.ptr[i]);
	}

	template <class anyIterator>
	arraylist(anyIterator begin, anyIterator end) : base()
	{
		for (; begin != end; ++begin)
			pushBack(*begin);
	}

	arraylist(arraylist&& source) noexcept
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
	void push(std::initializer_list<data> list)
	{
		size_t listSize = list.size();
		size_t newSize = this->size + listSize;
		if (this->capacity < newSize)
			base::newCapacity(newSize);

		const data* pointer = list.begin();
		data** res = this->ptr + this->size;
		uFOR(i, 0u, listSize)
			res[i] = new data(pointer[i]);
		this->size = newSize;
	}

	//Add an item at the end
	void pushBack(const data& item)
	{
		if (this->size == this->capacity)
			base::newCapacity(true);
		this->ptr[this->size++] = new data(item);
	}

	//Add an item before the first item
	void pushFront(const data& item)
	{
		if (this->size == this->capacity)
			base::newCapacity(true);
		uRFOR(i, this->size, 1u)
			this->ptr[i] = this->ptr[i - 1u];
		this->ptr[0u] = new data(item);
		++this->size;
	}

	//Insert an item at any index
	void pushAt(const data& item, size_t index)
	{
		if (index > this->size)
			return;
		if (this->size == this->capacity)
			base::newCapacity(true);

		for(size_t i = this->size; i > index; --i)
			this->ptr[i] = this->ptr[i - 1u];
		this->ptr[index] = new data(item);
		++this->size;
	}

	//Remove last item
	void popBack()
	{
		if (this->size == 0u)
			return;
		--this->size;
		delete this->ptr[this->size];
		if (this->size == this->capacity >> 1u)	//size == capacity / 2
			base::newCapacity(false);
	}

	//Remove first item
	void popFront()
	{
		if (this->size == 0u)
			return;
		delete this->ptr[0u];
		uFOR(i, 1u, this->size)
			this->ptr[i - 1u] = this->ptr[i];
		--this->size;
		if (this->size == this->capacity >> 1u)	//size == capacity / 2
			base::newCapacity(false);
	}

	//Remove an item at any index
	void popAt(size_t index)
	{
		if (this->size == 0u || index >= this->size)
			return;
		delete this->ptr[index];
		uFOR(i, index + 1u, this->size)
			this->ptr[i - 1u] = this->ptr[i];
		--this->size;
		if (this->size == this->capacity >> 1u)	//size == capacity / 2
			base::newCapacity(false);
	}

	//Remove the first item with value equal to val
	bool pop(const data& val) {
		uFOR(i, 0u, this->size)
			if (*this->ptr[i] == val) {
				popAt(i);
				return true;
			}
		return false;
	}

	//Remove all items with value equal to val
	void popAll(const data& val) {
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

	//Reversing Array List
	void reverse() {
		if (this->size == 0u)
			return;
		for (size_t i = 0u, j = this->size - 1u; i < j; ++i, --j)
			std::swap(this->ptr[i], this->ptr[j]);
	}

	//Reversing in [left, right]
	void reverse(size_t left, size_t right) {
		if (left > right || left >= this->size || right >= this->size)
			return;

		for (; left < right; ++left, --right)
			std::swap(this->ptr[left], this->ptr[right]);
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
	int indexOf(const data& val) const {
		uFOR(i, 0u, this->size)
			if (*this->ptr[i] == val)
				return i;
		return -1;
	}

	//Binary search item with value equal to val
	int binSearch(const data& val, bool ascending = true) {
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
		this->size = 0u;
		base::newCapacity(size_t(1u));
	}

	//Set Array List include length items with value equal to val
	void memset(const data& val, size_t length) {
		uFOR(i, 0u, this->size)
			delete this->ptr[i];

		base::newCapacity(length, false);
		this->size = length;
		uFOR(i, 0u, this->size)
			this->ptr[i] = new data(val);
	}

	//Set all items with value equal to val
	void memset(const data& item) {
		uFOR(i, 0u, this->size)
			delete this->ptr[i];
		uFOR(i, 0u, this->size)
			this->ptr[i] = new data(item);
	}

	//Count how many items with value equal to val
	size_t count(const data& val) const {
		size_t Count(0u);
		uFOR(i, 0u, this->size)
			if (val == *this->ptr[i])
				++Count;
		return Count;
	}

	//Sort up ascending
	void sort()
	{
		mergeSort(0u, this->size - 1u);
	}

	//Sort up ascending
	template <class Functor>
	void sort(Functor functor)
	{
		mergeSort(functor, 0, this->size - 1u);
	}

	//Count how many items if its satisfy the condition
	template <class Functor>
	size_t count(Functor functor) const {
		size_t Count(0u);
		uFOR(i, 0, this->size)
			if (functor((const data&)*this->ptr[i]))
				++Count;
		return Count;
	}

	//Loop through each item
	template <class Functor>
	void foreach(Functor functor) {
		uFOR(i, 0, this->size)
			functor(*this->ptr[i]);
	}

	template <class Functor>
	arraylist selectIf(Functor functor) const {
		arraylist res;
		uFOR(i, 0u, this->size)
			if (functor((const data&)*this->ptr[i]))
				res.pushBack(*this->ptr[i]);
		return res;
	}

	//Check all items satisfy the condition
	template <class Functor>
	bool all(Functor functor) const {
		uFOR(i, 0u, this->size)
			if (functor((const data)*this->ptr[i]) == false)
				return false;
		return true;
	}

	//Check any items satisfy the condition
	template <class Functor>
	bool any(Functor functor) const {
		uFOR(i, 0u, this->size)
			if (functor((const data)*this->ptr[i]))
				return true;
		return false;
	}

	//Writing on console
	void out() const override {
		if (this->size == 0u) {
			std::cout << "Array List is empty !" << std::endl;
			return;
		}

		uFOR(i, 0u, this->size)
			std::cout << *this->ptr[i] << ' ';
		std::cout << std::endl;
	}

	//Check for empty array
	bool empty() const override {
		return this->size == 0u;
	}

	//Length of array
	size_t length() const override {
		return this->size;
	}

	//Capacity of array
	size_t limit() const override {
		return this->capacity;
	}
#pragma endregion

	//=====     Operators     =====//
#pragma region Operators
	operator bool() override
	{
		return this->size != 0;
	}

	data& operator[](size_t index)
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
			this->ptr[i] = new data(*source.ptr[i]);
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
		if (source.size == 0)
			return *this;

		size_t newSize = this->size + source.size;
		if(newSize > this->capacity)
			base::newCapacity(newSize);

		data** res = this->ptr + this->size;
		uFOR(i, 0, source.size)
			res[i] = new data(*source.ptr[i]);
		this->size = newSize;
		return *this;
	}
#pragma endregion

	//=====     Child Class : Iterator     =====//
#pragma region Iterator
	class iterator {
		friend arraylist;
		arraylist* ref;
		data** ptr;

		iterator(arraylist* arr, data** idx) : ref{ arr }, ptr{ idx }{}
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
		bool trySet(const data& val) {
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
		data& operator*() {
			return **this->ptr;
		}

		//Get index ( type data* ) of item
		data* operator->() {
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
		data** ptr;

		const_iterator(const arraylist* arr, data** idx) : ref{ arr }, ptr{ idx }{}
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
		const data& operator*() {
			return **this->ptr;
		}

		//Get index ( type const data* ) of item
		const data* operator->() {
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
template <class data>
std::ostream& operator<<(std::ostream& os, const dynamicarray<data>& list) {
	list.out();
	return os;
}

template <class data>
std::ostream& operator<<(std::ostream& os, const arraylist<data>& list) {
	list.out();
	return os;
}
//==================================================
#endif	//_ARRAY_LIST_
