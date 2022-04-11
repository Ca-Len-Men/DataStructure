#ifndef _ARRAY_LIST_
#define _ARRAY_LIST_
#define _CRT_SECURE_NO_WARNINGS_
#include<iostream>
#include<initializer_list>
#include<conio.h>

#ifndef _DEFINE_SYNTAX_
#define _DEFINE_SYNTAX_
#define FOR(i, start, end) for(int i = start; i < end; ++i)
#define RFOR(i, last, front) for(int i = last; i >= front; --i)
#define uFOR(i, start, end) for(size_t i = start; i < end; ++i)
#define uRFOR(i, last, front) for(size_t i = last; i >= front; --i)
#define line putchar('\n')
#define wait _getch()
#endif

/*
*******************************************************
				ARRAY LIST LIBRARY					  *
- There have : ARRAY LIST							  *
Syntax :											  *
	arraylist<typename> arr;						  *
*******************************************************
*/

//**************************************************
//==========          ARRAY LIST          ==========

/*Arraylist is a dynamic array.
You must have constructor for your data type.*/
template <class data>
class arraylist {
	
	//=====     Private Methods     =====
	void changeCapacity(size_t newCapacity) {
		data** tempPtr = this->ptr;
		this->ptr = new data * [newCapacity];

		if (newCapacity < this->capacity) {
			uFOR(i, 0, newCapacity)
				this->ptr[i] = tempPtr[i];
		} else {
			uFOR(i, 0, this->capacity)
				this->ptr[i] = tempPtr[i];
			uFOR(i, this->capacity, newCapacity)
				this->ptr[i] = nullptr;
		}

		this->capacity = newCapacity;
		delete[] tempPtr;
	}
	size_t countCapacity(size_t numElement) const  {
		return (numElement / this->spaceMemory + 1) * this->spaceMemory;
	}
	void shellSort(data** arr, int n) {
		data* temp;
		int a[] = { 1, 2, 3, 5, 7, 11, 13, 17, 19, 23,
			29, 31, 37, 41, 43, 47, 53, 57, 61, 67}, space;

		for (int k = 19; k >= 0; --k) {
			space = a[k];

			for (int i = space; i < n; i += space)
			{
				int j = i - space;
				temp = arr[i];

				for (; j >= 0 && *temp < *arr[j]; j -= space)
					arr[j + space] = arr[j];
				arr[j + space] = temp;
			}
		}
	}
	void mergeSort(data** arr, size_t left, size_t right) {
		if (right - left < 100) {
			shellSort(arr + left, right - left + 1);
			return;
		}

		size_t mid = (left + right) / 2;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);
		if (*arr[mid] < *arr[mid + 1])
			return;

		data** ptrLeft, ** ptrRight(arr + mid + 1);
		size_t lengthLeft = mid - left + 1;
		size_t lengthRight = right - mid;
		size_t l = 0, r = 0, k = left;

		ptrLeft = new data * [lengthLeft];
		for (size_t i = left; i <= mid; ++i)
			ptrLeft[i - left] = arr[i];

		for (; l < lengthLeft && r < lengthRight; ++k)
			if (*ptrLeft[l] < *ptrRight[r])
				arr[k] = ptrLeft[l++];
			else
				arr[k] = ptrRight[r++];
		for(; l < lengthLeft; ++k, ++l)
			arr[k] = ptrLeft[l];
	}

	void shellSort(data** arr, int n,
		bool(&compareFunction)(const data& a, const data& b)) {
		data* temp;
		int a[] = { 1, 2, 3, 5, 7, 11, 13, 17, 19, 23,
			29, 31, 37, 41, 43, 47, 53, 57, 61, 67 }, space;

		for (int k = 19; k >= 0; --k) {
			space = a[k];

			for (int i = space; i < n; i += space)
			{
				int j = i - space;
				temp = arr[i];

				for (; j >= 0 && compareFunction(*temp, *arr[j]); j -= space)
					arr[j + space] = arr[j];
				arr[j + space] = temp;
			}
		}
	}
	void mergeSort(data** arr, size_t left, size_t right,
		bool(&compareFunction)(const data& a, const data& b)) {
		if (right - left < 100) {
			shellSort(arr + left, right - left + 1, compareFunction);
			return;
		}

		size_t mid = (left + right) / 2;
		mergeSort(arr, left, mid, compareFunction);
		mergeSort(arr, mid + 1, right, compareFunction);
		if (compareFunction(*arr[mid], *arr[mid + 1]))
			return;

		data** ptrLeft, ** ptrRight(arr + mid + 1);
		size_t lengthLeft = mid - left + 1;
		size_t lengthRight = right - mid;
		size_t l = 0, r = 0, k = left;

		ptrLeft = new data * [lengthLeft];
		for (size_t i = left; i <= mid; ++i)
			ptrLeft[i - left] = arr[i];

		for (; l < lengthLeft && r < lengthRight; ++k)
			if (compareFunction(*ptrLeft[l], *ptrRight[r]))
				arr[k] = ptrLeft[l++];
			else
				arr[k] = ptrRight[r++];
		for (; l < lengthLeft; ++k, ++l)
			arr[k] = ptrLeft[l];
	}

	//=====     Attributes     =====
	data** ptr;
	size_t size;
	size_t capacity;
	size_t spaceMemory;

public:
	//=====     Constructors, Destructor     =====
	
	template <int n>
	arraylist(data (&arr)[n], size_t spaceCapacity = 20);
	arraylist(std::initializer_list<data> list, size_t spaceCapacity = 20);
	arraylist(size_t spaceCapacity = 20);
	arraylist(const arraylist& source);
	arraylist(arraylist&& source) noexcept;
	~arraylist();

	//=====     Methods     =====

/*Thêm một phần tử vào cuối mảng
Độ phức tạp thời gian : O(1) hoặc O(n)*/
	void pushBack(const data& item) {
		this->ptr[this->size++] = new data(item);
		if (this->size == this->capacity)
			changeCapacity(this->capacity + this->spaceMemory);
	}

/*Thêm một phần tử vào đầu mảng
Độ phức tạp thời gian : O(n)*/
	void pushFront(const data& item) {
		uRFOR(i, this->size, 1)
			this->ptr[i] = this->ptr[i - 1];
		this->ptr[0] = new data(item);
		if (++this->size == this->capacity)
			changeCapacity(this->capacity + this->spaceMemory);
	}

/*Chèn một phần tử vào vị trí index
#Nếu index nằm ngoài phạm vi, phần tử được đưa vào cuối mảng
Độ phức tạp thời gian : O(1) hoặc O(n)*/
	void pushAt(const data& item, size_t index) {
		if (index >= this->size) {
			pushBack(item);
			return;
		}

		if (index == 0) {
			pushFront(item);
			return;
		}

		uRFOR(i, this->size - 1, index)
			this->ptr[i + 1] = this->ptr[i];
		this->ptr[index] = new data(item);
		++this->size;
		if (this->size == this->capacity)
			changeCapacity(this->capacity + this->spaceMemory);
	}

/*Xóa một phần tử ở cuối mảng
Độ phức tạp thời gian : O(1) hoặc O(n)*/
	void popBack() {
		delete this->ptr[this->size - 1];
		this->ptr[--this->size] = nullptr;

		if (this->size < this->capacity - spaceMemory)
			changeCapacity(this->capacity - spaceMemory);
	}

/*Xóa một phần tử ở đầu mảng
Độ phức tạp thời gian : O(n)*/
	void popFront() {
		delete this->ptr[0];
		uFOR(i, 1, this->size)
			this->ptr[i - 1] = this->ptr[i];
		this->ptr[--this->size] = nullptr;

		if (this->size < this->capacity - this->spaceMemory)
			changeCapacity(this->capacity - this->spaceMemory);
	}

/*Xóa một phần tử tại chỉ số index
#Nếu index nằm ngoài phạm vi, không phần tử nào bị xóa
Độ phức tạp thời gian : O(n)*/
	void popAt(size_t index) {
		if (index >= this->size)
			return;

		delete this->ptr[index];
		uFOR(i, index + 1, this->size)
			this->ptr[i - 1] = this->ptr[i];
		this->ptr[--this->size] = nullptr;

		if (this->size < this->capacity - this->spaceMemory)
			changeCapacity(this->capacity - this->spaceMemory);
	}

/*Xóa một phần tử element đầu tiên trong mảng
Nếu không tồn tại, không phần tử nào bị xóa
Trả về true nếu xóa thành công, ngược lại trả về false
#Cần toán tử so sánh == hai kiểu data ( bool operator==(const data&) )
Độ phức tạp thời gian : O(n)*/
	bool pop(const data& element) {
		uFOR(i, 0, this->size)
			if (*this->ptr[i] == element) {
				popAt(i);
				return true;
			}
		return false;
	}

/*Xóa tất cả phần tử element trong mảng
#Cần toán tử so sánh == hai kiểu data ( bool operator==(const data&) )
Độ phức tạp thời gian : O(n)*/
	void popAll(const data& element) {
		size_t count = 0;
		uFOR(i, 0, this->size)
			if (*this->ptr[i] == element) {
				delete this->ptr[i];
				++count;
			} else this->ptr[i - count] = this->ptr[i];
		
		uFOR(i, this->size - count, this->size)
			this->ptr[i] = nullptr;
		this->size -= count;
		if (this->size < this->capacity - this->spaceMemory)
			changeCapacity(this->capacity - this->spaceMemory);
	}

/*Xóa các phần tử trong đoạn [left, right] hoặc [right, left]
#Nếu đoạn vượt ngoài phạm vi : đoạn con lớn nhất của nó sẽ bị đảo
Độ phức tạp thời gian : O(n)*/
	void popIn(size_t left, size_t right) {
		if (left == right && left == this->size)
			return;
		if (left > right)
			std::swap(left, right);
		if (right >= this->size)
			right = this->size - 1;

		int count = right - left + 1;
		int newCapacity = countCapacity(this->size - count);

		//Giải phóng trong đoạn [left, right]
		for (size_t i = left; i <= right; ++i)
			delete this->ptr[i];
		
		//Dời
		uFOR(i, right + 1, this->size)
			this->ptr[i - count] = this->ptr[i];
		uFOR(i, this->size - count, this->size)
			this->ptr[i] = nullptr;

		this->size -= count;

		if (newCapacity != this->capacity)
			changeCapacity(newCapacity);
	}

/*Đảo toàn bộ mảng
Độ phức tạp thời gian : O(n)*/
	void reverse() {
		for (size_t i = 0, j = this->size - 1; i < j; ++i, --j)
			std::swap(this->ptr[i], this->ptr[j]);
	}

/*Đảo trong một đoạn [left, right] hoặc [right, left]
#Nếu đoạn vượt ngoài phạm vi : đoạn con lớn nhất của nó sẽ bị đảo
Độ phức tạp thời gian : O(n)*/
	void reverse(size_t left, size_t right) {
		if (left == right && left == this->size)
			return;
		if (left > right)
			std::swap(left, right);
		if (right >= this->size)
			right = this->size - 1;

		for (; left < right; ++left, --right)
			std::swap(this->ptr[left], this->ptr[right]);
	}

/*Hoán vị hai mảng
Độ phức tạp thời gian : O(1)*/
	void swap(arraylist& source) {
		if (this == &source)
			return;

		std::swap(this->capacity, source.capacity);
		std::swap(this->size, source.size);
		std::swap(this->ptr, source.ptr);
		std::swap(this->spaceMemory, source.spaceMemory);
	}

/*Tìm kiếm tuyến tính
Tìm bắt đầu từ chỉ số 0, trả về chỉ số của phần tử đầu tiên tìm thấy
Nếu không tìm thấy, trả về -1
#Cần toán tử so sánh == hai kiểu data ( bool operator==(const data&) )
Độ phức tạp thời gian : O(n)*/
	int find(const data& element) const {
		for(size_t i = 0; i < this->size; ++i)
			if (*this->ptr[i] == element)
				return i;
		return -1;
	}

/*Tìm kiếm nhị phân 
Hãy cho biết mảng tăng hay giảm : true - mảng tăng , false - mảng giảm
Trả về chỉ số phần tử tìm thấy ( không chắc rằng đây là phần tử đầu tiên )
Nếu không tìm thấy, trả về -1
#Mảng cần phải được sắp xếp trước khi dùng phương thức này
#Cần toán tử so sánh ==, <, > hai kiểu data ( bool operator==(const data&) )
Độ phức tạp thời gian : O(log n)*/
	int binSearch(const data& element, bool ascending = true) {
		int left = 0, right = this->size - 1, mid;

		if (ascending) {
			while (left <= right) {
				mid = (left + right) / 2;

				if (element == *this->ptr[mid])
					return mid;
				else if (element < *this->ptr[mid])
					right = mid - 1;
				else
					left = mid + 1;
			}
		} else {//Descending
			while (left <= right) {
				mid = (left + right) / 2;

				if (element == *this->ptr[mid])
					return mid;
				else if (element > *this->ptr[mid])
					right = mid - 1;
				else
					left = mid + 1;
			}
		}
		//Not found
		return -1;
	}

/*Trả về giá trị mới từ phần tử thứ index
#Chỉ số index phải nằm trong phạm vi của mảng
Độ phức tạp thời gian : O(1)*/
	const data& readOnly(size_t index) {
		return *this->ptr[index];
	}

/*Xuất mảng một chiều trên một dòng
#Cần xuất được kiểu data với std::cout
Độ phức tạp thời gian : O(n)*/
	void out() const {
		uFOR(i, 0, this->size)
			std::cout << *this->ptr[i] << ' ';
		std::cout << std::endl;
	}

/*Xem dung lượng
	Tham số là nullptr : Byte
	Tham số là "kb" : KB
	Tham số còn lại : MB*/
	void info(const char* typeMemory = nullptr) const {
		std::cout << "Length : " << this->size << " - Memory : ";
		size_t myMemory = 3 * sizeof(size_t) + (this->capacity + 1) *
			sizeof(data*) + this->size * sizeof(data);

		if(typeMemory == nullptr)
			std::cout << myMemory << " byte\n";
		else if(_strcmpi(typeMemory, "kb") == 0)
			std::cout << (myMemory * 1.0 / 1024) << " KB\n";
		else
			std::cout << (myMemory * 1.0 / 1048576) << " MB\n";
	}
	
/*Xóa toàn bộ phần tử
Độ phức tạp thời gian : O(n)*/
	void clear() {
		for (size_t i = 0; this->ptr[i]; ++i)
			delete this->ptr[i];
		delete[] this->ptr;

		this->size = 0;
		this->capacity = this->spaceMemory;
		this->ptr = new data * [this->spaceMemory];
		uFOR(i, 0, this->capacity)
			this->ptr[i] = nullptr;
	}

/*Trả về true nếu mảng rỗng*/
	bool empty() const {
		return this->size == 0;
	}

/*Trả về số lượng phần tử của mảng*/
	size_t length() const {
		return this->size;
	}
	
/*Sắp xếp mảng tăng dần
#Cần toán tử so sánh < cho kiểu data ( operator<(const data&) )
Độ phức tạp thời gian : O(n log n) hoặc O(n)
Độ phức tạp không gian : O(n) hoặc O(log n)*/
	void sort() {
		mergeSort(this->ptr, 0, this->size - 1);
	}

/*Sắp xếp mảng tăng dần theo một thuộc tính của đối tượng
#Cần hàm so sánh thứ tự cho kiểu data
bool (*)(const data& a, const data& b) : trả về true nếu a, b đứng đúng thứ tự
Độ phức tạp thời gian : O(n log n) hoặc O(n)
Độ phức tạp không gian : O(n) hoặc O(log n)*/
	void sort(bool (&compareFunction)(const data& a, const data& b)) {
		mergeSort(this->ptr, 0, this->size - 1, compareFunction);
	}

	//=====     Operators     =====

/*Trả về true nếu mảng không rỗng*/
	operator bool() const {
		return this->size != 0;
	}

/*Trả về tham chiếu phần tử thứ index
#Chỉ số index phải nằm trong phạm vi của mảng
Độ phức tạp thời gian : O(1)*/
	data& operator[](size_t index) {
		return *this->ptr[index];
	}

/*Nối mảng thứ hai vào cuối mảng
Độ phức tạp thời gian : O(n)*/
	arraylist& operator+=(const arraylist& source) {
		this->capacity = countCapacity(this->size + source.size);
		data** res = this->ptr;
		this->ptr = new data * [this->capacity];

		uFOR(i, 0, this->size)
			this->ptr[i] = res[i];
		uFOR(i, 0, source.size)
			this->ptr[i + this->size] = new data(*source.ptr[i]);

		delete[] res;
		this->size += source.size;
		uFOR(i, this->size, this->capacity)
			this->ptr[i] = nullptr;
		return *this;
	}

/*Gán bằng hai mảng
Độ phức tạp thời gian : O(n)*/
	arraylist& operator=(const arraylist& source) {
		if (this == &source)
			return *this;

		for (size_t i = 0; this->ptr[i]; ++i)
			delete this->ptr[i];
		delete[] this->ptr;

		this->capacity = countCapacity(source.size);
		this->ptr = new data * [this->capacity];
		this->size = source.size;

		uFOR(i, 0, this->size)
			this->ptr[i] = new data(*source.ptr[i]);
		uFOR(i, this->size, this->capacity)
			this->ptr[i] = nullptr;
		return *this;
	}

	//=====     Static Function     =====
	


	//=====     Child Class : Iterator     =====
	class iterator {
		friend arraylist;
		arraylist* ref;
		data** ptr;

		iterator(arraylist* arr, data** idx) : ref{ arr }, ptr{ idx }{}
	public:
		//=====     Constructor     =====
		iterator() : ref{ nullptr }, ptr{ nullptr }{}

		iterator(const iterator& source) : ref{ source.ref }, ptr{ source.ptr }{}
		
		//=====     Methods     =====

		/*Kiểm tra iterator rỗng
		Trả về true nếu nó rỗng*/
		bool null() const {
			return this->ptr < this->ref->ptr ||
				this->ptr >= this->ref->ptr + this->ref->size;
		}

		/*Thử gán giá trị cho phần tử mà nó trỏ tới
		Trả về true nếu phép gán thành công*/
		bool trySet(const data& val) {
			if (ptr >= ref->ptr && ptr < ref->ptr + size) {
				**ptr = val;
				return true;
			}

			return false;
		}

		/*Lấy ra vị trí tại iterator*/
		int getIndex() const {
			return this->ptr - this->ref->ptr;
		}
		//=====     Operators     =====

		/*#Tránh iterator là rỗng
		Trả về đối tượng mà nó trỏ tới*/
		data& operator*() {
			return **this->ptr;
		}

		/*#Tránh iterator là rỗng
		Trả về địa chỉ của đối tượng nó trỏ tới*/
		data* operator->() {
			return *this->ptr;
		}

		/*Nếu iterator là rỗng, toán tử ++ không thực hiện
		Trả về chính nó*/
		iterator& operator++() {
			if (null() == false)
				++this->ptr;
			return *this;
		}

		/*Nếu iterator là rỗng, toán tử ++ không thực hiện
		Trả về một iterator mới*/
		iterator operator++(int) {
			iterator res(*this);
			if (null() == false)
				++this->ptr;
			return res;
		}

		/*Nếu iterator là rỗng, toán tử -- không thực hiện
		Trả về chính nó*/
		iterator& operator--() {
			if (null() == false)
				--this->ptr;
			return *this;
		}

		/*Nếu iterator là rỗng, toán tử -- không thực hiện
		Trả về một iterator mới*/
		iterator operator--(int) {
			iterator res(*this);
			if (null() == false)
				--this->ptr;
			return res;
		}

		/*Gán bằng hai iterator*/
		iterator& operator=(const iterator& source) {
			this->ref = source.ref;
			this->ptr = source.ptr;
			return *this;
		}

		/*So sánh hai iterator
		Trả về true nếu chúng cùng trỏ vào một đối tượng*/
		bool operator==(const iterator& source) const {
			return this->ptr == source.ptr;
		}

		/*So sánh hai iterator
		Trả về true nếu chúng không cùng trỏ vào một đối tượng*/
		bool operator!=(const iterator& source) const {
			return this->ptr != source.ptr;
		}

		/*So sánh hai iterator
		Trả về true nếu chỉ số phần tử của nó nhỏ hơn chỉ số phần tử source
		#Hai iterator phải cùng một arraylist*/
		bool operator<(const iterator& source) const {
			return this->ptr < source.ptr;
		}

		/*So sánh hai iterator
		Trả về true nếu chỉ số phần tử của nó lớn hơn chỉ số phần tử source
		#Hai iterator phải cùng một arraylist*/
		bool operator>(const iterator& source) const {
			return this->ptr > source.ptr;
		}

		/*So sánh hai iterator
		Trả về true nếu chỉ số phần tử của nó nhỏ hơn bằng chỉ số phần tử source
		#Hai iterator phải cùng một arraylist*/
		bool operator<=(const iterator& source) const {
			return this->ptr <= source.ptr;
		}

		/*So sánh hai iterator
		Trả về true nếu chỉ số phần tử của nó lớn hơn bằng chỉ số phần tử source
		#Hai iterator phải cùng một arraylist*/
		bool operator>=(const iterator& source) const {
			return this->ptr >= source.ptr;
		}

		/*Nếu iterator rỗng, toán tử += không thực hiện
		Nếu chỉ số vượt quá phạm vi, iterator là end*/
		iterator& operator+=(int i) {
			if (null() == false)
				this->ptr += i;
			if (this->ptr > this->ref->ptr + this->ref->size)
				this->ptr = this->ref->ptr + this->ref->size;
			return *this;
		}

		/*Nếu iterator rỗng, toán tử -= không thực hiện
		Nếu chỉ số vượt quá phạm vi, iterator là rend*/
		iterator& operator-=(int i) {
			if (null() == false)
				this->ptr -= i;
			if (this->ptr < this->ref->ptr)
				this->ptr = this->ref->ptr - 1;
			return *this;
		}

		/*Kiểm tra iterator không rỗng
		Trả về true nếu nó không rỗng*/
		operator bool() const {
			return this->ptr >= this->ref->ptr &&
				this->ptr < this->ref->ptr + this->ref->size;
		}
	};

	//=====     Child Class : Const Iterator     =====
	class const_iterator {
		friend arraylist;
		const arraylist* ref;
		data** ptr;

		const_iterator(const arraylist* arr, data** idx) : ref{ arr }, ptr{ idx }{}

	public:
		//=====     Constructor     =====
		const_iterator() : ref{ nullptr }, ptr{ nullptr }{}

		const_iterator(const const_iterator& source) :
			ref{ source.ref }, ptr{ source.ptr }{}

		//=====     Methods     =====

		/*Kiểm tra iterator rỗng
		Trả về true nếu nó rỗng*/
		bool null() const {
			return this->ptr < this->ref->ptr ||
				this->ptr >= this->ref->ptr + this->ref->size;
		}

		/*Lấy ra vị trí tại const_iterator*/
		int getIndex() const {
			return this->ptr - this->ref->ptr;
		}
		//=====     Operators     =====

		/*#Tránh iterator là rỗng
		Trả về đối tượng hằng mà nó trỏ tới*/
		const data& operator*() {
			return **this->ptr;
		}

		/*#Tránh iterator là rỗng
		Trả về địa chỉ hằng của đối tượng nó trỏ tới*/
		const data* operator->() {
			return *this->ptr;
		}

		/*Nếu const_iterator là rỗng, toán tử ++ không thực hiện
		Trả về chính nó*/
		const_iterator& operator++() {
			if (null() == false)
				++this->ptr;
			return *this;
		}

		/*Nếu const_iterator là rỗng, toán tử ++ không thực hiện
		Trả về một const_iterator mới*/
		const_iterator operator++(int) {
			const_iterator res(*this);
			if (null() == false)
				++this->ptr;
			return res;
		}

		/*Nếu const_iterator là rỗng, toán tử -- không thực hiện
		Trả về chính nó*/
		const_iterator& operator--() {
			if (null() == false)
				--this->ptr;
			return *this;
		}

		/*Nếu const_iterator là rỗng, toán tử -- không thực hiện
		Trả về một const_iterator mới*/
		const_iterator operator--(int) {
			const_iterator res(*this);
			if (null() == false)
				--this->ptr;
			return res;
		}

		/*Gán bằng hai const_iterator*/
		const_iterator& operator=(const const_iterator& source) {
			this->ref = source.ref;
			this->ptr = source.ptr;
			return *this;
		}

		/*So sánh hai const_iterator
		Trả về true nếu chúng cùng trỏ vào một đối tượng*/
		bool operator==(const const_iterator& source) const {
			return this->ptr == source.ptr;
		}

		/*So sánh hai const_iterator
		Trả về true nếu chúng không cùng trỏ vào một đối tượng*/
		bool operator!=(const const_iterator& source) const {
			return this->ptr != source.ptr;
		}

		/*So sánh hai const_iterator
		Trả về true nếu chỉ số phần tử của nó nhỏ hơn chỉ số phần tử source
		#Hai const_iterator phải cùng một arraylist*/
		bool operator<(const const_iterator& source) const {
			return this->ptr < source.ptr;
		}

		/*So sánh hai const_iterator
		Trả về true nếu chỉ số phần tử của nó lớn hơn chỉ số phần tử source
		#Hai const_iterator phải cùng một arraylist*/
		bool operator>(const const_iterator& source) const {
			return this->ptr > source.ptr;
		}

		/*So sánh hai const_iterator
		Trả về true nếu chỉ số phần tử của nó nhỏ hơn bằng chỉ số phần tử source
		#Hai const_iterator phải cùng một arraylist*/
		bool operator<=(const const_iterator& source) const {
			return this->ptr <= source.ptr;
		}

		/*So sánh hai const_iterator
		Trả về true nếu chỉ số phần tử của nó lớn hơn bằng chỉ số phần tử source
		#Hai const_iterator phải cùng một arraylist*/
		bool operator>=(const const_iterator& source) const {
			return this->ptr >= source.ptr;
		}

		/*Nếu const_iterator rỗng, toán tử += không thực hiện
		Nếu chỉ số vượt quá phạm vi, const_iterator là cend*/
		iterator& operator+=(int i) {
			if (null() == false)
				this->ptr += i;
			if (this->ptr > this->ref->ptr + this->ref->size)
				this->ptr = this->ref->ptr + this->ref->size;
			return *this;
		}

		/*Nếu const_iterator rỗng, toán tử -= không thực hiện
		Nếu chỉ số vượt quá phạm vi, const_iterator là crend*/
		iterator& operator-=(int i) {
			if (null() == false)
				this->ptr -= i;
			if (this->ptr < this->ref->ptr)
				this->ptr = this->ref->ptr - 1;
			return *this;
		}

		/*Kiểm tra const_iterator không rỗng
		Trả về true nếu nó không rỗng*/
		operator bool() const {
			return this->ptr >= this->ref->ptr &&
				this->ptr < this->ref->ptr + this->ref->size;
		}
	};

	//=====     Iterator, Const Iterator     =====

/*Trả về iterator trỏ vào phần tử đầu tiên
Nếu mảng rỗng, iterator sẽ là rỗng*/
	iterator begin()  {
		return iterator(this, this->ptr);
	}

/*Trả về iterator trỏ vào phần tử cuối cùng
Nếu mảng rỗng, iterator sẽ là rỗng*/
	iterator rbegin() {
		return iterator(this, this->ptr + this->size - 1);
	}

/*Trả về iterator rỗng ở cuối mảng*/
	iterator end()  {
		return iterator(this, this->ptr + this->size);
	}

/*Trả về iterator rỗng ở đầu mảng*/
	iterator rend()  {
		return iterator(this, this->ptr - 1);
	}

/*Trả về const_iterator trỏ vào phần tử đầu tiên
Nếu mảng rỗng, const_iterator sẽ là rỗng*/
	const_iterator cbegin() const  {
		return const_iterator(this, this->ptr);
	}

/*Trả về const_iterator trỏ vào phần tử cuối cùng
Nếu mảng rỗng, const_iterator sẽ là rỗng*/
	const_iterator crbegin() const {
		return const_iterator(this, this->ptr + this->size - 1);
	}

/*Trả về const_iterator rỗng ở cuối mảng*/
	const_iterator cend() const  {
		return const_iterator(this, this->ptr + this->size);
	}

/*Trả về const_iterator rỗng ở đầu mảng*/
	const_iterator crend() const  {
		return const_iterator(this, this->ptr - 1);
	} 

/*Trả về const_iterator ở vị trí index
#Nếu chỉ số index nằm ngoài phạm vi, const_iterator sẽ là cend hoặc crend*/
	const_iterator citerAt(int index) const {
		if (index < 0)
			return crend();
		if (index >= this->size)
			return cend();
		return const_iterator(this, this->ptr + index);
	}

/*Trả về iterator ở vị trí index
#Nếu chỉ số index nằm ngoài phạm vi, iterator sẽ là end hoặc rend*/
	iterator iterAt(int index) {
		if (index < 0)
			return rend();
		if (index >= this->size)
			return end();
		return iterator(this, this->ptr + index);
	}

/*Xóa một phần tử tại iterator
#Nếu iterator rỗng, không phần tử nào bị xóa
#Nhận vào rvalue
Độ phức tạp thời gian : O(n)*/
	void popAt(iterator&& iter) {
		popAt(iter.ptr - this->ptr);
	}

/*Xóa một phần tử tại iterator
#Nếu iterator rỗng, không phần tử nào bị xóa
#Nhận vào lvalue
#Sau khi xóa, iterator trỏ đến phần tử tiếp theo
Độ phức tạp thời gian : O(n)*/
	void popAt(iterator& iter) {
		if (iter.isNull())
			return;

		int oldIndex = iter.getIndex();
		popAt(iter.ptr - this->ptr);
		iter.ptr = this->ptr + oldIndex;
	}

/*Xóa các phần tử trong đoạn [left, right] hoặc [right, left]
#Nhận vào các rvalue
#Nếu có một iterator là rỗng, hàm sẽ kết thúc
Độ phức tạp thời gian : O(n)*/
	void popIn(iterator&& left, iterator&& right) {
		if (left.isNull() || right.isNull())
			return;

		int leftIndex = left.getIndex();
		int rightIndex = right.getIndex();
		popIn(leftIndex, rightIndex);
	}

/*Xóa các phần tử trong đoạn [left, right] hoặc [right, left]
#Nhận vào các lvalue
#Nếu có một iterator là rỗng, hàm sẽ kết thúc
#Sau khi xóa, left và right sẽ trỏ vào cùng một phần tử tại vị trí left
Độ phức tạp thời gian : O(n)*/
	void popIn(iterator& left, iterator& right) {
		if (left.isNull() || right.isNull())
			return;

		int leftIndex = left.getIndex();
		int rightIndex = right.getIndex();
		int minIndex = leftIndex < rightIndex ? leftIndex : rightIndex;

		popIn(leftIndex, rightIndex);
		left.ptr = right.ptr = this->ptr + minIndex;
	}

	//=====     Friend Function     =====
	template <class Data> friend std::ostream& operator<<(std::ostream& output, const arraylist<Data>& source) {
		source.out();
		return output;
	}
};

//=====     Constructors, Destructor of Arraylist     =====

template <class data>
arraylist<data>::arraylist(std::initializer_list<data> list, size_t spaceCapacity) :
	spaceMemory{ spaceCapacity }, size{ list.size() }
{
	this->capacity = countCapacity(this->size);
	this->ptr = new data * [this->capacity];

	const int* ptrList = list.begin();
	uFOR(i, 0, this->size)
		this->ptr[i] = new data(ptrList[i]);
	uFOR(i, this->size, this->capacity)
		this->ptr[i] = nullptr;
}

template <class data>
template <int n>
arraylist<data>::arraylist(data(&arr)[n], size_t spaceCapacity) :
	spaceMemory{ spaceCapacity }, size{ n }
{
	this->capacity = countCapacity(n);
	this->ptr = new data * [this->capacity];

	uFOR(i, 0, this->size)
		this->ptr[i] = new data(arr[i]);
	uFOR(i, this->size, this->capacity)
		this->ptr[i] = nullptr;
}

template <class data>
arraylist<data>::arraylist(size_t spaceCapacity) :
	spaceMemory{ spaceCapacity }, size{ 0 }, capacity { spaceCapacity }
{
	this->ptr = new data * [this->capacity];
	uFOR(i, 0, this->capacity)
		this->ptr[i] = nullptr;
}

template <class data>
arraylist<data>::arraylist(const arraylist& source) :
	spaceMemory{ source.spaceMemory },
	capacity{ source.capacity }, size{ source.size }
{
	this->ptr = new data * [this->capacity];
	uFOR(i, 0, this->size)
		this->ptr[i] = new data(*source.ptr[i]);
	uFOR(i, this->size, this->capacity)
		this->ptr[i] = nullptr;
}

template <class data>
arraylist<data>::arraylist(arraylist&& source) noexcept :
	capacity{ source.capacity }, ptr{ source.ptr },
	size{ source.size }, spaceMemory { source.spaceMemory }
{}

template <class data>
arraylist<data>::~arraylist()
{
	for (size_t i = 0; this->ptr[i]; i++)
		delete this->ptr[i];
	delete[] this->ptr;
}
//**************************************************
#endif	//_ARRAY_LIST_
