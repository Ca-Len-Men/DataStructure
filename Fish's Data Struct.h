#ifndef _FISH_BASIC_
#define _FISH_BASIC_
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdarg.h>

const int MAXSIZE_BEGIN_TRAIN = 100;
template <class data> class train;
class txt;
template <class data> class node;
template <class data> class stack;
//====================================================================================================
template <class data> void Ascending(data* arr, int left, int right);
template <class data> void Descending(data* arr, int left, int right);
template <class data> inline void swap(data& a, data& b);
//====================================================================================================
template <class data>
class train{
	private:
		int* array_byte, size_array_byte;
		int MAXSIZE, size_member;
		data* array_member;

	//Hàm bổ trợ
		void change_MAXSIZE(int new_MAXSIZE);

		template <class data_member> void asc(data* arr, int left, int right, int idx_member);
		template <class data_member> void des(data* arr, int left, int right, int idx_member);

		template <class data_member> inline data_member* get_member(data* element, int idx_member);
	public:
	//Khởi tạo
		train();
		train(const train& source);
		~train();

	//Phương thức
		void operator=(train& source);
		void operator+=(train& tail);
		bool operator==(train& source);
		inline data operator[](int index);
	//Hàm bổ trợ
		void set_byte(int length = 0, ...);
		void set(data member, int index);
		template <class data_member> void set_member(data_member value, int idx_member, int index);
		void push_back(data member);
		void push_at(data member, int index);
		void pop_back();
		void pop_at(int index);
		void pop(data value);
		void show();
		void free();
		void sort(bool ascending = true);
		void Symmetry();
		template <class data_member> void sort_member(int idx_member, bool ascending = true);
		template <class data_member> void show_member(int idx_member);


		bool isEmpty();
		bool isSetByte();
		bool isSymmetry();
		bool isFound(data value);
		template <class data_member> bool isFound_member(data_member value, int idx_member);

		int size();
		int maxsize();
		int find(data value);
		template <class data_member> int find(data_member value, int idx_member);

		data get(int index);

	//Hàm bạn
};

//Kiểm tra có phần tử có thành viên thứ idx_member bằng value
template <class data>
template <class data_member>
bool train<data>::isFound_member(data_member value, int idx_member)
{
	for (int i = 0; i < size_member; i++)
		if (*get_member<data_member>(array_member + i, idx_member) == value)
			return true;
	return false;
}

//Kiểm tra có tồn tại phần tử value trong mảng
template <class data>
bool train<data>::isFound(data value)
{
	for (int i = 0; i < size_member; i++)
		if (array_member[i] == value)
			return true;
	return false;
}

//Toán tử phạm vi
template <class data>
inline data train<data>::operator[](int index)
{
	return array_member[index];
}

//Xóa phần tử mang giá trị value trong mảng
template <class data>
void train<data>::pop(data value)
{
	//Nếu mảng rỗng thì hàm kết thúc
	if (size_member == 0)
		return;

	pop_at(find(value));
}

//So sánh hai mảng
template <class data>
bool train<data>::operator==(train& source)
{
	//Nếu mảng nguồn là chính nó thì trả về true
	if (this == &source)
		return true;
	//Nếu độ dài hai mảng khác nhau thì trả về false
	if (size_member != source.size_member)
		return false;

	//So sánh từng phần tử
	for (int i = 0; i < size_member; i++)
		if (array_member[i] != source.array_member[i])
			return false;
	return true;
}

//Nối mảng tail vào đuôi mảng đích
template <class data>
void train<data>::operator+=(train& tail)
{
	//Nếu mảng tail rỗng thì hàm kết thúc
	if (tail.size_member == 0)
		return;

	//Gán new_size là độ dài mảng mới
	int new_size = size_member + tail.size_member;

	//Nếu độ dài mảng mới lớn hơn vùng nhớ thực thì tiến hành tăng vùng nhớ thực
	if (new_size > MAXSIZE)
	{
		int x_size = new_size / MAXSIZE_BEGIN_TRAIN;
		if (new_size % 100 != 0)
			x_size++;

		change_MAXSIZE(x_size * MAXSIZE_BEGIN_TRAIN);
	}

	//Trỏ đến phần tử cần nối mảng vào
	data* pointer = array_member + size_member;
	//Sao chép mảng vào đuôi mảng đích
	for (int i = 0; i < tail.size_member; i++)
		pointer[i] = tail.array_member[i];
	//Tăng độ dài mảng
	size_member = new_size;
}

//Sao chép giá trị từ source qua đích
template <class data>
void train<data>::operator=(train& source)
{
	//Nếu mảng nguồn là chính nó thì hàm kết thúc
	if (this == &source)
		return;

	//Giải phóng mảng byte
	delete[] array_byte;
	//Gán độ dài mảng byte mới
	size_array_byte = source.size_array_byte;
	//Cấp phát vùng nhớ mới
	array_byte = new int[size_array_byte];
	//Sao chép giá trị của mảng byte mới
	for (int i = 0; i < size_array_byte; i++)
		array_byte[i] = source.array_byte[i];

	//Giải phóng mảng
	delete[] array_member;
	//Gán độ dài mảng mới
	size_member = source.size_member;
	//Gán độ dài thực của vùng nhớ mới
	MAXSIZE = source.MAXSIZE;
	//Cấp phát vùng nhớ mới
	array_member = new data[MAXSIZE];
	//Sao chép giá trị của mảng mới
	for (int i = 0; i < size_member; i++)
		array_member[i] = source.array_member[i];
}

//Kiểm tra mảng đối xứng
template <class data>
bool train<data>::isSymmetry()
{
	for (int i = 0, j = size_member - 1; i < j; i++, j--)
		if (array_member[i] != array_member[j])
			return false;
	return true;
}

//Đảo mảng
template <class data>
void train<data>::Symmetry()
{
	for (int i = 0, j = size_member - 1; i < j; i++, j--)
		swap(array_member[i], array_member[j]);
}

//Tìm phần tử có thuộc tính thứ idx_member mang giá trị là value
template <class data>
template <class data_member>
int train<data>::find(data_member value, int idx_member)
{
	for (int i = 0; i < size_member; i++)
		if (value == *get_member<data_member>(array_member + i, idx_member))
			return i;
	return -1;
}

//Tìm vị trí phần tử mang giá trị value
template <class data>
int train<data>::find(data value)
{
	for (int i = 0; i < size_member; i++)
		if (array_member[i] == value)
			return i;
	return -1;
}

//Sắp xếp mảng dựa theo thuộc tính
template <class data>
template <class data_member>
void train<data>::sort_member(int idx_member, bool ascending)
{
	if (ascending)
		asc<data_member>(array_member, 0, size_member - 1, idx_member);
	else
		des<data_member>(array_member, 0, size_member - 1, idx_member);
}

//Sắp xếp tăng theo thuộc tính
template <class data>
template <class data_member>
void train<data>::asc(data* arr, int left, int right, int idx_member)
{
	if (left >= right)
		return;

	int i = left, j = right;

	data_member x = *get_member<data_member>(arr + (left + right) / 2, idx_member);

	do {
		while (*get_member<data_member>(arr + i, idx_member) < x)
			i++;
		while (*get_member<data_member>(arr + j, idx_member) > x)
			j--;

		if (i <= j)
		{
			if (i != j)
				swap(arr[i], arr[j]);
			i++;
			j--;
		}
	} while (i < j);

	asc<data_member>(arr, left, j, idx_member);
	asc<data_member>(arr, i, right, idx_member);
}

//Sắp xếp giảm theo thuộc tính
template <class data>
template <class data_member>
void train<data>::des(data* arr, int left, int right, int idx_member)
{
	if (left >= right)
		return;

	int i = left, j = right;
	data_member x = *get_member<data_member>(arr + (left + right) / 2, idx_member);

	do {
		while (*get_member<data_member>(arr + i, idx_member) > x)
			i++;
		while (*get_member<data_member>(arr + j, idx_member) < x)
			j--;

		if (i <= j)
		{
			if (i != j)
				swap(arr[i], arr[j]);
			i++;
			j--;
		}
	} while (i < j);

	des<data_member>(arr, left, j, idx_member);
	des<data_member>(arr, i, right, idx_member);
}

//Sắp xếp mảng
template <class data>
void train<data>::sort(bool ascending)
{
	if (ascending)
		Ascending<data>(array_member, 0, size_member - 1);
	else
		Descending<data>(array_member, 0, size_member - 1);
}

//Trả về true nếu đã gán mảng byte, ngược lại trả về false
template <class data>
bool train<data>::isSetByte()
{
	return array_byte != NULL;
}

//Kiểm tra mảng rỗng
template <class data>
bool train<data>::isEmpty()
{
	return size_member == 0;
}

//Chuyển thành mảng rỗng
template <class data>
void train<data>::free()
{
	//Nếu mảng rỗng, hàm kết thúc
	if (size_member == 0)
		return;

	size_member = 0;
	change_MAXSIZE(MAXSIZE_BEGIN_TRAIN);
}

//Thay đổi thành viên thứ idx_member của phần tử thứ index
template <class data>
template <class data_member>
void train<data>::set_member(data_member value, int idx_member, int index)
{
	//Nếu index nằm ngoài phạm vi mảng, hàm kết thúc
	if (index < 0 || index >= size_member)
		return;

	data_member* pointer = get_member<data_member>(array_member + index, idx_member);
	*pointer = value;
}

//Thay đổi phần tử thứ index
template <class data>
void train<data>::set(data member, int index)
{
	if (index < 0 || index >= size_member)
		return;

	array_member[index] = member;
}

//Lấy ra phần tử thứ index
template <class data>
data train<data>::get(int index)
{
	return array_member[index];
}

//Xóa phần tử cuối
template <class data>
void train<data>::pop_back()
{
	//Nếu độ dài mảng bằng 0, hàm kết thúc
	if (size_member == 0)
		return;

	//Giảm độ dài mảng
	size_member--;

	//Nếu có thể thì thay đổi kích thước vùng nhớ
	if (MAXSIZE > MAXSIZE_BEGIN_TRAIN && size_member <= MAXSIZE - MAXSIZE_BEGIN_TRAIN)
		change_MAXSIZE(MAXSIZE - MAXSIZE_BEGIN_TRAIN);
}

//Xuất thành phần thứ idx_member của các phần tử trong mảng
template <class data>
template <class data_member>
void train<data>::show_member(int idx_member)
{
	for (int i = 0; i < size_member; i++)
		std::cout << *get_member<data_member>(array_member + i, idx_member) << " ";
	putchar('\n');
}

//Thêm một phần tử tại vị trí index
template <class data>
void train<data>::push_at(data member, int index)
{
	//Nếu index nằm ngoài mảng thì hàm kết thúc
	if (index < 0 || index > size_member)
		return;

	if (size_member == MAXSIZE)
		change_MAXSIZE(MAXSIZE + MAXSIZE_BEGIN_TRAIN);

	//Dời một dãy phần tử lùi 1 ô
	for (int i = size_member - 1; i >= index; i--)
		array_member[i + 1] = array_member[i];
	//Thêm phần tử vào ô trống
	array_member[index] = member;
	//Tăng độ dài mảng lên 1
	size_member++;
}

//Trả về độ dài mảng
template <class data>
int train<data>::size()
{
	return size_member;
}

//Trả về độ dài vùng nhớ thực MAXSIZE
template <class data>
int train<data>::maxsize()
{
	return MAXSIZE;
}

//Xóa phần tử tại vị trí index
template <class data>
void train<data>::pop_at(int index)
{
	//Nếu index nằm ngoài mảng thì hàm kết thúc
	if (index < 0 || index >= size_member)
		return;

	//Xóa phần tử tại vị trí index
	for (int i = index + 1; i < size_member; i++)
		array_member[i - 1] = array_member[i];
	//Giảm độ dài mảng
	size_member--;

	//Nếu có thể thì giảm vùng nhớ thực của mảng
	if (MAXSIZE > MAXSIZE_BEGIN_TRAIN && size_member <= MAXSIZE - MAXSIZE_BEGIN_TRAIN)
		change_MAXSIZE(MAXSIZE - MAXSIZE_BEGIN_TRAIN);
}

//Private : Truy xuất thành viên của kiểu dữ liệu data
template <class data>
template <class data_member>
inline data_member* train<data>::get_member(data* element, int idx_member)
{
	//Trỏ đến thành viên thứ idx_member của kiểu dữ liệu data
	bool* pointer = (bool*)element + array_byte[idx_member];

	//Trả về địa chỉ thuộc tính của phần tử đó
	return (data_member*)pointer;;
}

//Xuất mảng
template <class data>
void train<data>::show()
{
	for (int i = 0; i < size_member; i++)
		std::cout << array_member[i] << " ";
	putchar('\n');
}

//Thêm một phần tử vào cuối mảng
template <class data>
void train<data>::push_back(data member)
{
	//Nếu độ dài mảng size_member bằng độ dài thật của vùng nhớ MAXSIZE thì tăng MAXSIZE
	if (size_member == MAXSIZE)
		change_MAXSIZE(MAXSIZE + MAXSIZE_BEGIN_TRAIN);

	//Thêm một phần tử vào cuối mảng
	array_member[size_member] = member;

	//Tăng độ dài mảng lên 1
	size_member++;
}

//Private : Thay đổi độ dài thực của array_member, tăng hoặc giảm MAXSIZE bằng new_MAXSIZE, có thể thay đổi size_member
template <class data>
void train<data>::change_MAXSIZE(int new_MAXSIZE)
{
	//Nếu độ dài không phù hợp với kích thước ban đầu đưa ra, hàm kết thúc
	if (new_MAXSIZE < MAXSIZE_BEGIN_TRAIN)
		return;

	//Cấp phát một vùng nhớ mới cho mảng data
	data* pointer = new data[new_MAXSIZE];

	//Gán min_len bằng độ dài nhỏ nhất trong size_member và new_MAXSIZE
	int min_len = size_member <= new_MAXSIZE ? size_member : new_MAXSIZE;

	//Sao chép giá trị từ vùng nhớ array_member sang vùng nhớ pointer
	for (int i = 0; i < min_len; i++)
		pointer[i] = array_member[i];

	//Giải phóng vùng nhớ cũ array_member
	delete[] array_member;

	//Trỏ array_member vào vùng nhớ mới pointer
	array_member = pointer;

	//Thay đổi kích thước MAXSIZE
	MAXSIZE = new_MAXSIZE;

	//Nếu độ dài mảng mới new_MAXSIZE nhỏ hơn độ dài mảng size_member thì thay đổi size_member
	if (new_MAXSIZE < size_member)
		size_member = new_MAXSIZE;
}

//Lưu số byte của từng thành viên trong kiểu dữ liệt data
template <class data>
void train<data>::set_byte(int length, ...)
{
	//Giải phóng mảng byte cũ nếu có
	delete[] array_byte;

	//Cấp phát vùng nhớ mới cho mảng byte
	size_array_byte = length;
	array_byte = new int[size_array_byte];

	//Duyệt qua từng biến trong cú pháp '...'
	va_list list;
	va_start(list, length);

	//Phần tử đầu tiên của mảng byte mặc định là 0
	array_byte[0] = 0;
	//Phần tử array_byte[i] = array_byte[i - 1] + số byte của thành viên thứ i
	for (int i = 1; i < size_array_byte; i++)
		array_byte[i] = array_byte[i - 1] + va_arg(list, int);

	va_end(list);
}

//Hàm hủy
template <class data>
train<data>::~train()
{
	delete[] array_byte;
	delete[] array_member;
}

//Khởi tạo sao chép
template <class data>
train<data>::train(const train& source)
{
	//Khởi tạo giá trị cho các biến thành viên
	array_byte = NULL;
	size_array_byte = 0;

	MAXSIZE = MAXSIZE_BEGIN_TRAIN;
	array_member = new data[MAXSIZE];
	size_member = 0;

	*this = source;
}

//Khởi tạo
template <class data>
train<data>::train()
{
	//Gán mảng array_byte bằng rỗng
	array_byte = NULL;
	size_array_byte = 0;

	MAXSIZE = MAXSIZE_BEGIN_TRAIN;
	//Gán độ dài mảng bằng 0
	size_member = 0;
	//Cấp phát trước một mảng có độ dài MAXSIZE
	array_member = new data[MAXSIZE];
}
//====================================================================================================
//Sắp xếp mảng giảm
template <class data>
void Descending(data* arr, int left, int right)
{
	if (left >= right)
		return;

	int i = left, j = right;
	data x = arr[(left + right) / 2];

	do {
		while (arr[i] > x)
			i++;
		while (arr[j] < x)
			j--;

		if (i <= j)
		{
			if (i != j)
				swap(arr[i], arr[j]);
			i++;
			j--;
		}
	} while (i < j);

	Descending(arr, left, j);
	Descending(arr, i, right);
}

//Sắp xếp mảng tăng
template <class data>
void Ascending(data* arr, int left, int right)
{
	if (left >= right)
		return;

	int i = left, j = right;
	data x = arr[(left + right) / 2];

	do {
		while (arr[i] < x)
			i++;
		while (arr[j] > x)
			j--;

		if (i <= j)
		{
			if (i != j)
				swap<data>(arr[i], arr[j]);
			i++;
			j--;
		}
	} while (i < j);

	Ascending(arr, left, j);
	Ascending(arr, i, right);
}

//Hoán vị
template <class data>
inline void swap(data& a, data& b)
{
	data temp = a;
	a = b;
	b = temp;
}
//====================================================================================================
//====================================================================================================

#define MAX_SIZE_FILE 1000
#define MAX_STR 200


class txt;
//template <class data> class train;
//template <class data> class map;

int left(const txt& s, const char ch, unsigned int left);
void outleft(const txt& s, unsigned int length);
//====================================================================================================
class txt {
private:
	char* str;
	unsigned int size;
	unsigned int remember;

public:
	//Khởi tạo
	txt();
	txt(const char* const s);
	txt(const txt& s);
	~txt();

	//Hàm tĩnh
	static unsigned int strlen(const char* const s);
	static void swap(txt& s1, txt& s2);
	static void QuickSort_asc(txt* arr, int left, int right);
	static void QuickSort_des(txt* arr, int left, int right);
	static void sort(txt* arr, int length, bool ascending = true);

	static bool isLetter(const char ch);
	static bool isNumber(const char ch);
	static bool isSymmetry(const char* const s);
	static bool isUpper(const char ch);
	static bool isLower(const char ch);
	static bool isLetterNumber(const char ch);
	static bool isSpace(const char ch);
	static bool isEmpty(const char* const s);

	static char upper(const char ch);
	static char lower(const char ch);

	static txt toTxt(long value);
	//Phương thức kiểu dữ liệu
	void operator=(const char* const s);
	void operator=(const txt& s);
	void operator=(const char ch);
	bool operator==(const char* const s);
	friend bool operator==(const txt& s1, const txt& s2);

	friend bool operator<(const txt& s1, const txt& s2);
	friend bool operator>(const txt& s1, const txt& s2);

	void operator+=(const txt& s);
	void operator+=(const char* const s);
	void operator+=(const char ch);

	friend txt& operator+(txt& s1, txt& s2);
	friend txt& operator+(txt& s1, const char* const s2);
	friend txt& operator+(const char* const s1, txt& s2);

	void addition(const txt& s1, const char* const s2);
	void addition(txt& s1, txt& s2);
	void addition(const char* const s1, const char* const s2);

	//Hàm bổ trợ kiểu dữ liệu
	void free();
	void out(const char* const s = NULL, const char* const s1 = NULL, unsigned int length = 0, void (*function)(const txt&, unsigned int) = outleft);
	void in(const char* const s = NULL);

	void share(txt& s);
	void share(char* const s);
	void sub(unsigned int left, unsigned int right);
	void sub(txt& s, unsigned int left, unsigned int right);
	void rev();
	void rev(unsigned int left, unsigned int right);
	void swap(txt& s);
	void read(FILE* f, const char stop = '\n');
	void readall(const char* file_name);
	void writeall(const char* file_name);
	void lower();
	void upper();
	void name();
	void split(txt*& arr, int& n, const char* const pass = NULL, bool isMode = true, txt _pass2 = " \t\n");
	void readto(txt& s, txt char_stop, const char* const pass = NULL, bool isMode = true, txt _pass2 = " \t\n");
	void next(txt& s, const char* const pass = NULL, bool isMode = true, txt _pass2 = " \t\n");


	void start();

	int find(const char* const s, unsigned int start = 0);
	int find(const char ch, unsigned int sth = 1, int (*function)(const txt&, const char, unsigned int) = left);

	friend int left(const txt& s, const char ch, unsigned int left);
	friend int right(const txt& s, const char ch, unsigned int right);
	friend void outleft(const txt& s, unsigned int length);
	friend void outright(const txt& s, unsigned int length);
	friend void outmid(const txt& s, unsigned int length);

	bool isFound(const char ch);
	bool isEmpty();
	bool isSymmetry();
	bool isEnd();

	char get(unsigned int idx);

	unsigned int len();

	long toNum();
	long next(const char* const pass = NULL, bool isMode = true, txt _pass2 = " \t\n");

	friend std::ostream& operator<<(std::ostream& output, txt s);
};

//Viết toàn bộ nội dung ra tệp
void txt::writeall(const char* file_name)
{
	if (txt::isEmpty(file_name))
		return;

	FILE* f = fopen(file_name, "w");

	for (unsigned int i = 0; i < size; i++)
		fputc(str[i], f);

	fclose(f);
}

//Kiểm tra chuỗi rỗng
bool txt::isEmpty(const char* const s)
{
	return s == NULL || *s == '\0';
}

//Chuyển từ số sang chuỗi
txt txt::toTxt(long value)
{
	txt convert;
	if (value == 0)
	{
		convert = '0';
		return convert;
	}

	bool check = false;

	if (value < 0)
	{
		check = true;
		value = -value;
	}

	for (; value != 0; value /= 10)
		convert += value % 10 + '0';

	if (convert.size > 1)
		convert.rev();

	if (check)
		convert = "-" + convert;
	return convert;
}

//Xuất chuỗi bằng cout
std::ostream& operator<<(std::ostream& output, txt s)
{
	s.out();
	return output;
}

//Sắp xếp mảng chuỗi
void txt::sort(txt* arr, int length, bool ascending)
{
	if (ascending)
		txt::QuickSort_asc(arr, 0, length - 1);
	else
		txt::QuickSort_des(arr, 0, length - 1);
}

//Sắp xếp mảng chuỗi tăng
void txt::QuickSort_des(txt* arr, int left, int right)
{
	if (left >= right)
		return;

	int i = left, j = right;
	txt x = arr[(left + right) / 2];

	do {
		while (arr[i] > x)
			i++;
		while (arr[j] < x)
			j--;

		if (i <= j)
		{
			if (i != j)
				txt::swap(arr[i], arr[j]);
			i++;
			j--;
		}
	} while (i < j);

	txt::QuickSort_des(arr, left, j);
	txt::QuickSort_des(arr, i, right);
}

//Sắp xếp mảng chuỗi tăng
void txt::QuickSort_asc(txt* arr, int left, int right)
{
	if (left >= right)
		return;

	int i = left, j = right;
	txt x = arr[(left + right) / 2];

	do {
		while (arr[i] < x)
			i++;
		while (arr[j] > x)
			j--;

		if (i <= j)
		{
			if (i != j)
				txt::swap(arr[i], arr[j]);
			i++;
			j--;
		}
	} while (i < j);

	txt::QuickSort_asc(arr, left, j);
	txt::QuickSort_asc(arr, i, right);
}

//Kiểm tra hết file
bool txt::isEnd()
{
	return remember >= size;
}

//Đọc một số
long txt::next(const char* const pass, bool isMode, txt _pass2)
{
	long num = 0;
	bool check = true;

	for (; remember < size; remember++)
		if (!_pass2.isFound(str[remember]))
			break;

	if (str[remember] == '-')
	{
		check = false;
		remember++;
	}

	for (; remember < size && !_pass2.isFound(str[remember]); remember++)
		if (txt::isNumber(str[remember]))
			num = num * 10 + str[remember] - '0';
	return check ? num : -num;
}

//Đọc một đoạn
void txt::next(txt& s, const char* const pass, bool isMode, txt _pass2)
{
	_pass2 += pass;
	s.free();
	char infor[MAX_STR];
	int len = 0;

	for (; remember < size; remember++)
		if (!_pass2.isFound(str[remember]))
			break;
	for (; remember < size && !_pass2.isFound(str[remember]); remember++)
		infor[len++] = str[remember];
	infor[len] = '\0';
	s = infor;
}

//Đọc đến những ký tự có trong chuỗi char_stop
void txt::readto(txt& s, txt char_stop, const char* const pass, bool isMode, txt _pass2)
{
	_pass2 += pass;
	s.free();
	char infor[MAX_STR];
	int len = 0;

	for (; remember < size && !char_stop.isFound(str[remember]); remember++)
		if (_pass2.isFound(str[remember]) != isMode)
			infor[len++] = str[remember];
	infor[len] = '\0';
	s = infor;
}

//Đọc hết file
void txt::readall(const char* file_name)
{
	free();
	FILE* f = fopen(file_name, "r");

	if (f == NULL)
		return;

	char infor[MAX_SIZE_FILE], ch;
	unsigned int len = 0;

	do {
		ch = fgetc(f);

		if (ch == EOF)
			infor[len] = '\0';
		else
			infor[len++] = ch;
	} while (ch != EOF);

	remember = 0;
	*this = infor;
	fclose(f);
}

//Bắt đầu chế độ lọc dữ liệu
void txt::start()
{
	remember = 0;
}

//Cắt chuỗi thành mảng chuỗi
void txt::split(txt*& arr, int& n, const char* const pass, bool isMode, txt _pass2)
{
	_pass2 += pass;
	n = 0;
	unsigned int i = 0, j, len;
	do {
		for (; i < size; i++)
			if (_pass2.isFound(str[i]) != isMode)
				break;
		if (i < size)
			n++;
		for (; i < size; i++)
			if (_pass2.isFound(str[i]) == isMode)
				break;
	} while (i < size);

	arr = new txt[n];
	for (len = 0, j = 0; len < n; len++)
	{
		for (i = j; i < size; i++)
			if (_pass2.isFound(str[i]) != isMode)
				break;
		for (j = i + 1; j < size; j++)
			if (_pass2.isFound(str[j]) == isMode)
				break;

		this->sub(arr[len], i, j - 1);
	}
}

//Chuyển chuỗi thành số
long txt::toNum()
{
	long num = 0;
	for (unsigned int i = 0; i < size; i++)
		if (txt::isNumber(str[i]))
			num = num * 10 + str[i] - '0';
	return str[0] == '-' ? -num : num;
}

//Chuyển thành tên : bỏ qua những ký tự không phải là chữ cái
void txt::name()
{
	char s[MAX_STR];
	unsigned int i = 0, len = 0;
	bool check;

	do {
		for (; i < size; i++)
			if (txt::isLetter(str[i]))
				break;

		if (i < size)
		{
			s[len++] = txt::upper(str[i++]);
			for (; i < size && txt::isLetter(str[i]); i++)
				s[len++] = txt::lower(str[i]);
			if (i < size)
				s[len++] = ' ';
		}
	} while (i < size);
	s[len] = '\0';
	*this = s;
}

//Chuyển thành chuỗi hoa
void txt::upper()
{
	for (unsigned int i = 0; i < size; i++)
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
}

//Chuyển thành chuỗi thường
void txt::lower()
{
	for (unsigned int i = 0; i < size; i++)
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
}

//So sánh hai chuỗi
bool operator>(const txt& s1, const txt& s2)
{
	unsigned int min = s1.size <= s2.size ? s1.size : s2.size;

	for (unsigned int i = 0; i < min; i++)
	{
		if (s1.str[i] > s2.str[i])
			return true;
		if (s1.str[i] < s2.str[i])
			return false;
	}

	if (s1.size > s2.size)
		return true;
	return false;
}

//So sánh hai chuỗi
bool operator<(const txt& s1, const txt& s2)
{
	unsigned int min = s1.size <= s2.size ? s1.size : s2.size;

	for (unsigned int i = 0; i < min; i++)
	{
		if (s1.str[i] < s2.str[i])
			return true;
		if (s1.str[i] > s2.str[i])
			return false;
	}

	if (s1.size < s2.size)
		return true;
	return false;
}

//Vị trí chuỗi xuất hiện đầu tiên
int txt::find(const char* const s, unsigned int start)
{
	if (size == 0 || s == NULL || s[0] == '\0')
		return -1;

	int len = txt::strlen(s);
	if (len > size)
		return -1;

	unsigned int stop = len - size;
	bool check;
	for (unsigned int i = start; i <= stop; i++)
	{
		check = true;
		for (unsigned int j = 0; s[j]; j++)
			if (str[i + j] != s[j])
				check = false;

		if (check)
			return i;
	}
	return -1;
}

//Đọc đến ký tự stop
void txt::read(FILE* f, const char stop)
{
	free();
	char infor[MAX_STR], ch;
	int len = 0;

	do {
		ch = fgetc(f);

		if (ch == EOF || ch == stop)
		{
			infor[len] = '\0';
			break;
		}
		else
			infor[len++] = ch;
	} while (true);

	*this = infor;
}

//Hoán vị
void txt::swap(txt& s)
{
	txt::swap(*this, s);
}

//Hoán vị
void txt::swap(txt& s1, txt& s2)
{
	char* p = s1.str;
	s1.str = s2.str;
	s2.str = p;

	int len = s1.size;
	s1.size = s2.size;
	s2.size = len;
}

//Nối ký tự vào sau chuỗi
void txt::operator+=(const char ch)
{
	txt temp;
	temp = ch;
	*this += temp;
}

//Gán chuỗi bằng ký tự
void txt::operator=(const char ch)
{
	free();
	str = new char;
	str[0] = ch;
	size = 1;
}

//Tìm vị trí ký tự xuất hiện : trả về -1 nếu không tìm thấy
int txt::find(const char ch, unsigned int sth, int (*function)(const txt&, const char, unsigned int))
{
	unsigned int count = 0;
	int i = (function == &left) ? 0 : size - 1;
	int move = (function == &left) ? 1 : -1;

	do {
		i = function(*this, ch, i);

		if (i != -1)
			count++;
		else
			break;

		if (count == sth)
			return i;
		else
			i += move;
	} while (i >= 0);
	return -1;
}

//Đảo đoạn
void txt::rev(unsigned int left, unsigned int right)
{
	if (left >= size || right >= size)
		return;
	char temp;
	for (unsigned int i = left, j = right; i < j; i++, j--)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
}

//Đảo chuỗi
void txt::rev()
{
	char temp;
	for (unsigned int i = 0, j = size - 1; i < j; i++, j--)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
}

//Chia sẻ đoạn chuỗi
void txt::sub(txt& s, unsigned int left, unsigned int right)
{
	if (left >= size || left > right || right >= size)
		return;


	s.free();
	s.size = right - left + 1;
	s.str = new char[s.size];

	char* p = str + left;
	for (unsigned int i = 0; i < s.size; i++)
		s.str[i] = p[i];
}

//Cắt chuỗi
void txt::sub(unsigned int left, unsigned int right)
{
	if (left >= size || left > right || right >= size)
		return;

	unsigned int len = right - left + 1;
	char* p = new char[len];
	char* k = str + left;

	for (unsigned int i = 0; i < len; i++)
		p[i] = k[i];

	delete[] str;
	str = p;
	size = len;
}

//Trả về độ dài chuỗi
unsigned int txt::len()
{
	return size;
}

//Trả về phần tử tại vị trí idx
char txt::get(unsigned int idx)
{
	if (idx >= size)
		return '\0';
	return str[idx];
}

//Cộng hai chuỗi
txt& operator+(const char* const s1, txt& s2)
{
	static txt value;
	value = s1;
	value += s2;
	return value;
}

//Cộng hai chuỗi
txt& operator+(txt& s1, const char* const s2)
{
	static txt value;

	if (&value == &s1)
		value += s2;
	else
		value.addition(s1, s2);
	return value;
}

//Cộng hai chuỗi
txt& operator+(txt& s1, txt& s2)
{
	static txt value;

	if (&value == &s1)
		value += s2;
	else
		value.addition(s1, s2);
	return value;
}

//Nối hai chuỗi
void txt::addition(const txt& s1, const char* const s2)
{
	*this = s1;
	*this += s2;
}

//Nối hai chuỗi
void txt::addition(const char* const s1, const char* const s2)
{
	*this = s1;
	*this += s2;
}

//Nối hai chuỗi
void txt::addition(txt& s1, txt& s2)
{
	if (this == &s1)
	{
		s1 += s2;
		return;
	}

	if (this == &s2)
	{
		txt temp;
		s2.share(temp);
		s2 = s1;
		s2 += temp;
		return;
	}

	*this = s1;
	*this += s2;
}

//Giải phóng
void txt::free()
{
	if (size != 0)
	{
		delete[] str;
		size = 0;
	}
	str = NULL;
}

//Chia sẻ chuỗi
void txt::share(char* const s)
{
	if (s == NULL)
		return;

	s[size] = '\0';
	for (unsigned int i = 0; i < size; i++)
		s[i] = str[i];
}

//Chia sẻ chuỗi
void txt::share(txt& s)
{
	s.free();
	s = *this;
}

//Kiểm tra ký tự có tồn tại trong chuỗi
bool txt::isFound(const char ch)
{
	for (unsigned int i = 0; i < size; i++)
		if (str[i] == ch)
			return true;
	return false;
}

//Kiểm tra chuỗi đảo
bool txt::isSymmetry()
{
	for (unsigned int i = 0, j = size; i < j; i++, j--)
		if (str[i] != str[j])
			return false;
	return true;
}

//Kiểm tra chuỗi rỗng
bool txt::isEmpty()
{
	return size == 0;
}

//Nhập chuỗi txt
void txt::in(const char* const s)
{
	free();
	rewind(stdin);
	if (s != NULL)
		printf("%s", s);

	char title[MAX_STR];
	fgets(title, MAX_STR, stdin);

	size = txt::strlen(title) - 1;
	str = new char[size];

	for (unsigned int i = 0; i < size; i++)
		str[i] = title[i];
}

//Xuất chuỗi txt
void txt::out(const char* const s, const char* const s1, unsigned int length, void (*function)(const txt&, unsigned int))
{
	if (s != NULL)
		printf("%s", s);

	if (size == 0)
	{
		printf("(null)");
		return;
	}

	function(*this, length);
	if (s1 != NULL)
		printf("%s", s1);
}

//Nối chuỗi
void txt::operator+=(const char* const s)
{
	if (s == NULL)
		return;

	bool check = this->str == s;
	int len = check ? size : txt::strlen(s);
	int fullsize = size + len;

	char* p = new char[fullsize];
	for (unsigned int i = 0; i < size; i++)
		p[i] = str[i];

	if (size != 0)
		delete[] str;
	str = p;
	p = str + size;

	if (check)	//Trùng địa chỉ
		for (unsigned int i = 0; i < size; i++)
			p[i] = str[i];
	else
		for (unsigned int i = 0; i < len; i++)
			p[i] = s[i];

	size = fullsize;
}

//Nối chuỗi
void txt::operator+=(const txt& s)
{
	if (s.size == 0)
		return;

	int len = size + s.size;
	char* p = new char[len];
	for (unsigned int i = 0; i < size; i++)
		p[i] = str[i];

	bool check = this == &s;

	if (size != 0)
		delete[] str;
	str = p;
	p = str + size;

	if (check)	//Trùng địa chỉ
		for (unsigned int i = 0; i < size; i++)
			p[i] = str[i];
	else
		for (unsigned int i = 0; i < s.size; i++)
			p[i] = s.str[i];

	size = len;
}

//Gán bằng chuỗi
void txt::operator=(const txt& s)
{
	if (this == &s)
		return;

	free();
	if (s.size == 0)
		return;

	size = s.size;
	str = new char[size];

	for (unsigned int i = 0; i < size; i++)
		str[i] = s.str[i];
}

//Gán bằng chuỗi
void txt::operator=(const char* const s)
{
	if (this->str == s)
		return;

	free();
	if (s == NULL)
		return;

	size = txt::strlen(s);
	str = new char[size];
	for (unsigned int i = 0; s[i] != '\0'; i++)
		str[i] = s[i];
}

//Kiểm tra hai chuỗi bằng nhau
bool txt::operator==(const char* const s)
{
	if (str == s)
		return true;
	int len = txt::strlen(s);
	if (size != len)
		return false;

	for (unsigned int i = 0; i < size; i++)
		if (str[i] != s[i])
			return false;
	return true;
}

//Kiểm tra hai chuỗi bằng nhau
bool operator==(const txt& s1, const txt& s2)
{
	if (s1.size != s2.size)
		return false;
	if (&s1 == &s2)
		return true;

	for (unsigned int i = 0; i < s1.size; i++)
		if (s1.str[i] != s2.str[i])
			return false;
	return true;
}

//Hủy
txt::~txt()
{
	free();
}

//Khởi tạo
txt::txt(const txt& s)
{
	this->size = 0;
	*this = s;
}

//Khởi tạo
txt::txt(const char* const s)
{
	this->size = 0;
	*this = s;
}

//Khởi tạo rỗng
txt::txt()
{
	size = 0;
}

//Đưa về ký tự hoa
char txt::upper(const char ch)
{
	if (ch >= 'a' && ch <= 'z')
		return ch - 32;
	return ch;
}

//Đưa về ký tự thường
char txt::lower(const char ch)
{
	if (ch >= 'A' && ch <= 'Z')
		return ch + 32;
	return ch;
}

//Kiểm tra chuỗi đối xứng
bool txt::isSymmetry(const char* const s)
{
	for (unsigned int i = 0, j = txt::strlen(s); i < j; i++, j--)
		if (s[i] != s[j])
			return false;
	return true;
}

//Kiểm tra khoảng trắng, tab
bool txt::isSpace(const char ch)
{
	return ch == ' ' || ch == '\t';
}

//Kiểm tra chữ cái và chữ số
bool txt::isLetterNumber(const char ch)
{
	return ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z' || ch >= '0' && ch <= '9';
}

//Kiểm tra ký tự hoa
bool txt::isUpper(const char ch)
{
	return ch >= 'A' && ch <= 'Z';
}

//Kiểm tra ký tự thường
bool txt::isLower(const char ch)
{
	return ch >= 'a' && ch <= 'z';
}

//Kiểm tra chữ số
bool txt::isNumber(const char ch)
{
	return ch >= '0' && ch <= '9';
}

//Kiểm tra chữ cái
bool txt::isLetter(const char ch)
{
	return ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z';
}

//Trả về độ dài chuỗi
unsigned int txt::strlen(const char* const str)
{
	if (str == NULL)
		return 0;
	unsigned int i = 0;
	for (; str[i] != '\0'; i++);
	return i;
}
//====================================================================================================
//Duyệt từ bên trái
int left(const txt& s, const char ch, unsigned int left)
{
	for (unsigned int i = left; i < s.size; i++)
		if (s.str[i] == ch)
			return i;
	return -1;
}

//Duyệt từ bên phải
int right(const txt& s, const char ch, unsigned int right)
{
	for (int i = right; i >= 0; i--)
		if (s.str[i] == ch)
			return i;
	return -1;
}

void outleft(const txt& s, unsigned int length)
{
	for (unsigned int i = 0; i < s.size; i++)
		putchar(s.str[i]);
	for (unsigned int i = s.size; i < length; i++)
		putchar(' ');
}

void outright(const txt& s, unsigned int length)
{
	for (unsigned int i = s.size; i < length; i++)
		putchar(' ');
	for (unsigned int i = 0; i < s.size; i++)
		putchar(s.str[i]);
}

void outmid(const txt& s, unsigned int length)
{
	int _left = (length - s.size) / 2;
	for (unsigned int i = 0; i < _left; i++)
		putchar(' ');
	for (unsigned int i = 0; i < s.size; i++)
		putchar(s.str[i]);
	for (unsigned int i = _left + s.size; i < length; i++)
		putchar(' ');
}
//====================================================================================================
template <class data>
class node {
public:
	data info;
	node* next;

	//Khởi tạo
	node();
	node(data element);
};

//Khởi tạo nút có giá trị
template <class data>
node<data>::node(data element)
{
	info = element;
	next = NULL;
}

//Khởi tạo nút không giá trị
template <class data> node<data>::node() { next = NULL; }
//====================================================================================================
template <class data>
class stack {
private:
	int* array_byte, size_array_byte;
	node<data>* top;
	int size;

	//Hàm bổ trợ
	template <class data_member> inline data_member* get_member(data* element, int idx_member);
	
public:
	//Khởi tạo
	stack();
	stack(const stack& source);
	~stack();

	//Phương thức
	void operator=(stack& source);

	//Hàm bổ trợ
	void show();
	void push(data element);
	void pop(data& get);
	void free();
	void get(data& read_only);
	void set_byte(int length, ...);
	void swap(stack& source);

	inline bool isEmpty();
	bool isFound(data value);
	template <class data_member> bool isFound_member(data_member value, int idx_member);

	inline int length();

	data pop();
	inline data get();
};

//Hoán vị hai stack
template <class data>
void stack<data>::swap(stack& source)
{
	//Nếu là chính nó thì hàm kết thúc
	if (this == &source)
		return;
	//Hoán vị hai con trỏ top
	node<data>* p = top;
	top = source.top;
	source.top = p;

	//Hoán vị hai độ dài stack
	int temp = size;
	size = source.size;
	source.size = temp;
}

//Trả về độ dài stack
template <class data>
inline int stack<data>::length()
{
	return size;
}

//Gán bằng hai stack
template <class data>
void stack<data>::operator=(stack& source)
{
	//Nếu là chính nó, hàm kết thúc
	if (this == &source)
		return;

	//Giải phóng stack chính
	free();

	//Nếu source rỗng thì hàm kết thúc
	if (source.top == NULL)
		return;

	//Cấp phát một nút mang giá trị của đỉnh source
	top = new node<data>(source.get());

	//Duyệt qua stack source và cấp phát phần tử
	for (node<data>* i = top, *j = source.top;; i = i->next, j = j->next)
		if(j->next)
			i->next = new node<data>(j->next->info);
		else {
			i->next = NULL;
			break;
		}

	//Gán lại độ dài stack chính
	size = source.size;
}

//Kiểm tra trong stack có thuộc tính phần tử bằng value
template <class data>
template <class data_member>
bool stack<data>::isFound_member(data_member value, int idx_member)
{
	//Duyệt stack và kiểm tra
	for (node<data>* i = top; i; i = i->next)
		if (*get_member<data_member>(&i->info, idx_member) == value)
			return true;

	return false;
}

//Trả về thuộc tính thứ index của một phần tử trong stack : hãy chắc chắn rằng bạn đã gán thuộc tính ( sử dụng hàm set_byte )
template <class data>
template <class data_member>
inline data_member* stack<data>::get_member(data* element, int idx_member)
{
	//Trỏ vào thuộc tính của phần tử element
	bool* pointer = (bool*)element + array_byte[idx_member];

	//Trả về địa chỉ của thuộc tính phần tử đó
	return (data_member*)pointer;
}

//Kiểm tra stack có chứa phần tử mang giá trị value
template <class data>
bool stack<data>::isFound(data value)
{
	for (node<data>* i = top; i; i = i->next)
		if (i->info == value)
			return true;

	return false;
}

//Lưu số byte của từng thành viên trong kiểu dữ liệt data
template <class data>
void stack<data>::set_byte(int length, ...)
{
	//Giải phóng mảng byte cũ nếu có
	delete[] array_byte;

	//Cấp phát mảng byte mới
	size_array_byte = length;
	array_byte = new int[size_array_byte];

	//Phần tử đầu của mảng byte bằng 0
	array_byte[0] = 0;

	//Duyệt qua từng biến trong cú pháp '...'
	va_list list;
	va_start(list, length);

	//Gán giá trị cho mảng byte
	for (int i = 1; i < size_array_byte; i++)
		array_byte[i] = array_byte[i - 1] + va_arg(list, int);

	va_end(list);
}

//Xem giá trị ở đỉnh stack, không lấy ra : hãy chắc chắn rằng stack không rỗng
template <class data>
inline data stack<data>::get()
{
	if (top != NULL)
		return top->info;

	data value;
	return value;
}

//Xem giá trị ở đỉnh stack, không lấy ra
template <class data>
void stack<data>::get(data& read_only)
{
	//Nếu stack rỗng thì hàm kết thúc
	if (top == NULL)
		return;

	//Lấy ra giá trị ở đỉnh stack
	read_only = top->info;
}

//Chuyển thành stack rỗng : vẫn giữ nguyên mảng byte
template <class data>
void stack<data>::free()
{
	//Giải phóng từng nút trong stack
	for (node<data>* p = top; top != NULL; p = top)
	{
		top = top->next;
		delete p;
	}

	//Gán độ dài mảng bằng 0
	size = 0;
}

//Lấy ra phần tử ở đỉnh stack : nếu stack rỗng, giá trị trả về sẽ là rác
template <class data>
data stack<data>::pop()
{
	//Lưu giá trị ở đỉnh stack
	data value;
	
	//Nếu stack không rỗng, lưu giá trị ở đỉnh stack vào biến value
	if (top != NULL)
	{
		value = top->info;

		//Giải phóng đỉnh stack
		node<data>* p = top;
		top = top->next;
		delete p;
	}

	//Trả về giá trị
	return value;
}

//Lấy ra phần tử ở đỉnh stack
template <class data>
void stack<data>::pop(data& get)
{
	//Nếu stack rỗng thì hàm kết thúc
	if (top == NULL)
		return;

	//Lấy giá trị ở đỉnh stack
	get = top->info;

	//Giải phóng đỉnh stack
	node<data>* p = top;
	top = top->next;
	delete p;

	//Giảm độ dài stack
	size--;
}

//Thêm vào stack
template <class data>
void stack<data>::push(data element)
{
	node<data>* p = new node<data>(element);

	//Nối nút p vào đầu stack
	p->next = top;
	//Gán lại top
	top = p;
	//Tăng độ dài stack
	size++;
}

//Xuất stack
template <class data>
void stack<data>::show()
{
	for (node<data>* i = top; i; i = i->next)
		std::cout << i->info << " ";
	printf("NULL\n");
}

//Kiểm tra stack rỗng
template <class data>
inline bool stack<data>::isEmpty()
{
	return top == NULL;
}

//Giải phóng stack
template <class data>
stack<data>::~stack()
{
	//Giải phóng từng nút trong stack
	for (node<data>* p = top; top != NULL; p = top)
	{
		top = top->next;
		delete p;
	}

	//Giải phóng mảng byte
	delete[] array_byte;
}

//Khởi tạo sao chép
template <class data>
stack<data>::stack(const stack& source)
{
	//Khởi tạo stack rỗng
	array_byte = NULL;
	size_array_byte = 0;

	//Sao chép giá trị nguồn
	top = new node<data>(source.top->info);
	node<data>* p = top;

	for (node<data>* i = source.top;; i = i->next, p = p->next)
		if (i->next)
			p->next = new node<data>(i->next->info);
		else {
			p->next = NULL;
			break;
		}

	//Gán độ dài stack chính
	size = source.size;
}

//Khởi tạo stack rỗng
template <class data>
stack<data>::stack()
{
	top = NULL;
	size = 0;

	array_byte = NULL;
	size_array_byte = 0;
}
//====================================================================================================
//====================================================================================================
template <class data>
class queue {
private:
	int* array_byte, size_array_byte;
	node<data>* head, * tail;
	int size;
	
	//Hàm bổ trợ
	template <class data_member> inline data_member* get_member(data* element, int idx_member);

public:
	//Khởi tạo
	queue();
	queue(const queue& source);
	~queue();

	//Phương thức
	void operator=(queue& source);
	
	//Hàm bổ trợ
	void show();
	void push(data element);
	void pop(data& get);
	void free();
	void get(data& read_only);
	void set_byte(int length, ...);
	void swap(queue& source);

	inline bool isEmpty();
	bool isFound(data value);
	template <class data_member> bool isFound_member(data_member value, int idx_member);

	inline int length();

	data pop();
	inline data get();
};

//Gán bằng hai queue
template <class data>
void queue<data>::operator=(queue& source)
{
	//Nếu là chính nó thì hàm kết thúc
	if (this == &source)
		return;

	//Giải phóng queue chính
	free();

	//Nếu source rỗng thì hàm kết thúc
	if (source.head == NULL)
		return;

	//Cấp phát nút đầu tiên cho queue chính
	tail = new node<data>(source.head->info);
	head = tail;

	for(node<data>* i = source.head;; i = i->next, tail = tail->next)
		if (i->next)
			tail->next = new node<data>(i->next->info);
		else {
			tail->next = NULL;
			break;
		}

	//Gán độ dài mảng chính
	size = source.size;
}

//Hoán vị hai queue
template <class data>
void queue<data>::swap(queue& source)
{
	//Nếu là chính nó thì hàm kết thúc
	if (this == &source)
		return;

	//Hoán vị hai con trỏ head
	node<data>* p = head;
	head = source.head;
	source.head = p;

	//Hoán vị hai con trỏ tail
	p = tail;
	tail = source.tail;
	source.tail = p;

	//Hoán vị hai độ dài queue
	int temp = size;
	size = source.size;
	source.size = temp;
}

//Kiểm tra trong queue có phần tử có thuộc tính thứ idx_member bằng value
template <class data>
template <class data_member>
bool queue<data>::isFound_member(data_member value, int idx_member)
{
	for (node<data>* i = head; i; i = i->next)
		if (*get_member<data_member>(&i->info, idx_member) == value)
			return true;
	return false;
}

//Chuyển thành queue rỗng
template <class data>
void queue<data>::free()
{
	//Nếu queue rỗng, hàm kết thúc
	if (head == NULL)
		return;

	for (tail = head; head; tail = head)
	{
		head = head->next;
		delete tail;
	}

	//Gán độ dài queue bằng 0
	size = 0;
}

//Trả về địa chỉ thành viên thứ idx_member trong data
template <class data>
template <class data_member>
inline data_member* queue<data>::get_member(data* element, int idx_member)
{
	bool* pointer = (bool*)element + array_byte[idx_member];
	return (data_member*)pointer;
}

//Gán mảng byte cho queue
template <class data>
void queue<data>::set_byte(int length, ...)
{
	//Giải phóng mảng array_byte
	delete[] array_byte;

	//Cấp phát mảng byte
	size_array_byte = length;
	array_byte = new int[size_array_byte];
	//Phần tử đầu tiên của mảng byte bằng 0
	array_byte[0] = 0;

	//Duyệt các biến trong cú pháp '...'
	va_list list;
	va_start(list, length);

	//Gán giá trị cho mảng byte
	for (int i = 1; i < size_array_byte; i++)
		array_byte[i] = array_byte[i - 1] + va_arg(list, int);

	va_end(list);
}

//Kiểm tra xem có tồn tại giá trị value trong queue
template <class data>
bool queue<data>::isFound(data value)
{
	for (node<data>* i = head; i; i = i->next)
		if (i->info == value)
			return true;
	return false;
}

//Chỉ xem giá trị đầu queue : nếu queue rỗng, giá trị trả về sẽ là rác
template <class data>
inline data queue<data>::get()
{
	if (head != NULL)
		return head->info;
	
	data value;
	return value;
}

//Lấy ra đầu queue : nếu queue rỗng, giá trị trả về sẽ là rác
template <class data>
data queue<data>::pop()
{
	data value;

	//Nếu queue rỗng, trả về giá trị value
	if (head == NULL)
		return value;

	value = head->info;

	//Giải phóng nút đầu queue
	node<data>* p = head;
	head = head->next;
	delete p;

	if (head == NULL)
		tail = NULL;

	//Giảm độ dài queue
	size--;

	return value;
}

//Chỉ xem giá trị ở đầu queue
template <class data>
void queue<data>::get(data& read_only)
{
	//Nếu queue rỗng, hàm kết thúc
	if (head == NULL)
		return;

	read_only = head->info;
}

//Lấy ra đầu queue
template <class data>
void queue<data>::pop(data& get)
{
	//Nếu queue rỗng, hàm kết thúc
	if (head == NULL)
		return;

	//Lưu giá trị ở đầu queue vào get
	get = head->info;

	//Giải phóng nút đầu queue
	node<data>* p = head;
	head = head->next;
	delete p;

	if (head == NULL)
		tail = NULL;

	//Giảm độ dài của queue
	size--;
}

//Thêm phần tử vào queue
template <class data>
void queue<data>::push(data element)
{
	//Nếu queue rỗng, trỏ head và tail vào cùng một nút
	if (head == NULL)
	{
		head = tail = new node<data>(element);
		size++;
		return;
	}

	//Cấp phát một nút, đưa vào cuối queue
	tail->next = new node<data>(element);
	tail = tail->next;
	size++;
}

//Xuất queue
template <class data>
void queue<data>::show()
{
	for (node<data>* i = head; i; i = i->next)
		std::cout << i->info << " ";
	printf("NULL\n");
}

//Trả về độ dài của queue
template <class data>
inline int queue<data>::length()
{
	return size;
}

//Kiểm tra queue rỗng
template <class data>
inline bool queue<data>::isEmpty()
{
	return head == NULL;
}

//Khởi tạo sao chép
template <class data>
queue<data>::queue(const queue& source)
{
	//Gán queue rỗng
	array_byte = NULL;
	size_array_byte = 0;

	//Sao chép giá trị từ nguồn
	head = tail = new node<data>(source.head->info);

	for (node<data>* i = source.head;; i = i->next, tail = tail->next)
		if (i->next)
			tail->next = new node<data>(i->next->info);
		else {
			tail->next = NULL;
			break;
		}

	//Gán độ dài queue
	size = source.size;
}

//Khởi tạo
template <class data>
queue<data>::queue()
{
	//Gán queue rỗng
	head = tail = NULL;
	size = 0;

	//Gán mảng byte rỗng
	array_byte = NULL;
	size_array_byte = 0;
}

//Hàm hủy
template <class data>
queue<data>::~queue()
{
	//Giải phóng lần lượt từng nút trong queue
	for (tail = head; head; tail = head)
	{
		head = head->next;
		delete tail;
	}
}
//====================================================================================================
#endif	//_FISH_BASIC_
