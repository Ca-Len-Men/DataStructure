#ifndef _FISH_NUM_
#define _FISH_NUM_

#include<iostream>
#include<conio.h>

#define SIZE_DEFAULT 8

class bigint;
//==================================================
//==========          Big Int          ==========
class bigint {
public:
	char* numText;
	short sizeData, sizeNum;
	bool isPositive;

	//Phương thức
	int countLength(long long value);
	int countSizeData(int sizeByte);
	void malloc(int sizeByte);
	void realloc(int sizeByte);
	void free();
	void clear();
	void x10(int exponential);
	static int Add(char* strAdd, char* str1, int length1, char* str2, int length2);
	static int Sub(char* strSub, char* str1, int length1, char* str2, int length2);
	static int Compare(char* str1, int length1, char* str2, int length2);
	static void Divide(const bigint& source, bigint& left, bigint& right, int length);
	static void Multi(bigint& destination, bigint& var1, bigint& var2);
	static void DivideAndConquer(bigint& destination, bigint& var1, bigint& var2, int n);
	static void Exponential(bigint& destination, bigint& var1, long long n);

public:
	//Khởi tạo
	bigint(long long value = 0);
	bigint(const bigint& var);
	~bigint();

	//Phương thức
	void output();
	void input(const char* title = NULL);

	int length();
	int byte();

	//Toán tử

	bigint& operator=(const bigint& var);
	bigint& operator=(long long value);

	bool operator==(const bigint& var);
	bool operator==(bool value);
	bool operator!=(bool value);
	bool operator<(const bigint& var);
	bool operator<=(const bigint& var);
	bool operator>(const bigint& var);
	bool operator>=(const bigint& var);

	bigint& operator+=(const bigint& var);
	bigint& operator-=(const bigint& var);
	bigint& operator*=(const bigint& var);
	bigint& operator^=(long long n);



	friend std::ostream& operator<<(std::ostream& out, bigint& var);
	friend std::istream& operator>>(std::istream& in, bigint& var);
	friend bigint operator+(const bigint& var1, const bigint& var2);
};

bigint operator+(const bigint& var1, const bigint& var2)
{
	bigint res = var1;
	res += var2;
	return res;
}

//Trả về độ dài mảng động
int bigint::byte()
{
	return sizeData;
}

//Trả về độ dài Big Int
int bigint::length()
{
	return sizeNum;
}

//Nhập Big Int
void bigint::input(const char* title)
{
	if (title)
		printf("%s", title);
	char text[100];
	fgets(text, 100, stdin);

	int i = sizeNum = 0, length;
	for (; text[i] != '\n'; i++)
		if (text[i] >= '0' && text[i] <= '9')
			sizeNum++;
	realloc(sizeNum);
	isPositive = *text != '-';

	for (length = i; i > 0; i--)
		numText[length - i] = text[i - 1];
}

//Xuất Big Int
void bigint::output()
{
	if (!isPositive)	putchar('-');
	//char* s = numText + sizeNum - 1;
	for (int i = sizeNum - 1; i >= 0; i--)
		putchar(numText[i]);
}

int count = 0;

//Giải phóng bộ nhớ
void bigint::free()
{
	printf("Lan %d\n", ++count);
	if (numText)
	{
		delete[] numText;
		numText = NULL;
	}
}

//Loại bỏ số 0 thừa. Ví dụ : 0036 -> 36
void bigint::clear()
{
	for (; sizeNum > 1 && numText[sizeNum - 1] == '0'; sizeNum--);
	realloc(sizeNum);
}

//Tăng, giảm kích thước bộ nhớ
void bigint::realloc(int sizeByte)
{
	int temp = countSizeData(sizeByte);
	if (temp == sizeData)
		return;

	sizeData = temp;
	char* p = numText;
	numText = new char[sizeData];

	int minLen = std::min<short>(sizeNum, sizeData);
	for (int i = 0; i < minLen; i++)
		numText[i] = p[i];

	delete[] p;
	if (sizeNum > sizeData)
		sizeNum = sizeData;
}

//Cấp phát
void bigint::malloc(int sizeByte)
{
	sizeData = countSizeData(sizeNum = sizeByte);
	numText = new char[sizeData];
}

//Hàm hủy
bigint::~bigint()
{
	if (numText)
	{
		delete[] numText;
		numText = NULL;
	}
}

//Khởi tạo sao chép
bigint::bigint(const bigint& var)
{
	*this = var;
}

//Khởi tạo
bigint::bigint(long long value)
{
	malloc(countLength(value));

	//Dấu của Big Int
	if (value < 0)
	{
		isPositive = false;
		value = -value;
	} else
		isPositive = true;
	//Sao chép giá trị value vào chuỗi
	for (int i = 0; i < sizeNum; i++, value /= 10)
		numText[i] = value % 10 + '0';
}
//==================================================
//=====     Toán tử     =====

bigint& bigint::operator^=(long long n)
{
	bigint temp = *this;
	Exponential(*this, temp, n);
	return *this;
}

bigint& bigint::operator*=(const bigint& var)
{
	bigint temp = var;
	DivideAndConquer(*this, *this, temp, 0);
	return *this;
}

bigint& bigint::operator-=(const bigint& var)
{
	//var == 0
	if (var.isPositive && var.sizeNum == 1 && *var.numText == '0')
		return *this;

	if (isPositive == var.isPositive)	//Cùng dấu
	{
		realloc(std::max(sizeNum, var.sizeNum));
		int compare = Compare(numText, sizeNum, var.numText, var.sizeNum);
		if (compare == 0)
			*this = 0;
		else if (compare > 0)
			sizeNum = Sub(numText, numText, sizeNum, var.numText, var.sizeNum);
		else {
			sizeNum = Sub(numText, var.numText, var.sizeNum, numText, sizeNum);
			isPositive = !isPositive;
		}

		realloc(sizeNum);
	} else {	//Trái dấu
		realloc(std::max(sizeNum, var.sizeNum) + 1);
		sizeNum = Add(numText, numText, sizeNum, var.numText, var.sizeNum);
	}

	return *this;
}

bigint& bigint::operator+=(const bigint& var)
{
	//var == 0
	if (var.isPositive && var.sizeNum == 1 && *var.numText == '0')
		return *this;

	if (isPositive == var.isPositive)	//Cùng dấu
	{
		realloc(std::max(sizeNum, var.sizeNum) + 1);
		sizeNum = Add(numText, numText, sizeNum, var.numText, var.sizeNum);
	} else {	//Trái dấu
		realloc(std::max(sizeNum, var.sizeNum));

		int compare = Compare(numText, sizeNum, var.numText, var.sizeNum);
		if (compare == 0)
			*this = 0;
		else if (compare > 0)
			sizeNum = Sub(numText, numText, sizeNum, var.numText, var.sizeNum);
		else {
			sizeNum = Sub(numText, var.numText, var.sizeNum, numText, sizeNum);
			isPositive = !isPositive;
		}
		realloc(sizeNum);
	}

	return *this;
}

bool bigint::operator<=(const bigint& var)
{
	if (isPositive != var.isPositive)	//Trái dấu
		return var.isPositive;

	//Cùng dấu
	int compare = Compare(numText, sizeNum, var.numText, var.sizeNum);
	if (isPositive)	//Dương
		return compare <= 0;
	else			//Âm
		return compare >= 0;
}

bool bigint::operator>=(const bigint& var)
{
	if (isPositive != var.isPositive)	//Trái dấu
		return isPositive;

	//Cùng dấu
	int compare = Compare(numText, sizeNum, var.numText, var.sizeNum);
	if (isPositive)	//Dương
		return compare >= 0;
	else			//Âm
		return compare <= 0;
}

bool bigint::operator>(const bigint& var)
{
	if (isPositive != var.isPositive)	//Trái dấu
		return isPositive;

	//Cùng dấu
	int compare = Compare(numText, sizeNum, var.numText, var.sizeNum);
	if (isPositive)	//Dương
		return compare > 0;
	else			//Âm
		return compare < 0;
}

bool bigint::operator<(const bigint& var)
{
	if (isPositive != var.isPositive)	//Trái dấu
		return var.isPositive;

	//Cùng dấu
	int compare = Compare(numText, sizeNum, var.numText, var.sizeNum);
	if (isPositive)	//Dương
		return compare < 0;
	else			//Âm
		return compare > 0;
}

//So sánh với Bool
bool bigint::operator!=(bool value)
{
	bool temp = *this == value;
	return !temp;
}

//So sánh với Bool
bool bigint::operator==(bool value)
{
	if (isPositive && sizeNum == 1 && *numText == '0' && !value)
		return true;
	return false;
}

//So sánh hai Big Int
bool bigint::operator==(const bigint& var)
{
	//Khác độ dài hoặc khác dấu
	if (sizeNum != var.sizeNum || isPositive != var.isPositive)
		return false;

	for (int i = 0; i < sizeNum; i++)
		if (numText[i] != var.numText[i])
			return false;
	return true;
}

//Gán bằng
bigint& bigint::operator=(long long value)
{
	free();
	malloc(countLength(value));

	//Dấu của Big Int
	if (value < 0)
	{
		isPositive = false;
		value = -value;
	}
	else
		isPositive = true;
	for (int i = 0; i < sizeNum; i++, value /= 10)
		numText[i] = value % 10 + '0';
	return *this;
}

//Gán bằng
bigint& bigint::operator=(const bigint& var)
{
	//Nếu là chính nó, hàm kết thúc
	if (this == &var)
		return *this;

	free();
	malloc(var.sizeNum);

	//Sao chép giá trị
	for (int i = 0; i < sizeNum; i++)
		numText[i] = var.numText[i];
	isPositive = var.isPositive;
	return *this;
}
//==================================================
//=====     Private Function     =====

//Hàm mũ
void bigint::Exponential(bigint& destination, bigint& var1, long long n)
{
	if (n == 0)
	{
		destination = 1;
		return;
	}

	Exponential(destination, var1, n / 2);
	destination *= destination;
	if (n % 2 != 0)
		destination *= var1;
}

//Nhân hai Big Int : Chia Để Trị
void bigint::DivideAndConquer(bigint& destination, bigint& var1, bigint& var2, int n)
{
	if (var1 == 0 || var2 == 0)
	{
		destination = 0;
		return;
	}

	if (var1.sizeNum == 1 && var2.sizeNum == 1)
	{
		Multi(destination, var1, var2);
		return;
	}

	bigint a, b, c, d, m1, m2, m3;
	int length = std::max(var1.sizeNum, var2.sizeNum);
	Divide(var1, a, b, length);
	Divide(var2, c, d, length);

	/*for (int i = 0; i < n; i++)
		std::cout << '\t';
	std::cout << a << " : " << b << " : " << c << " : " << d << '\n';*/

	DivideAndConquer(m1, a, c, n + 1);
	DivideAndConquer(m3, b, d, n + 1);
	a -= b;
	d -= c;
	DivideAndConquer(m2, a, d, n + 1);
	//std::cout << m1 << " - " << m2 << " - " << m3 << '\n';
	m2 += m1;	m2 += m3;
	m1.x10((length / 2) * 2);
	m2.x10(length / 2);

	destination = m1;
	destination += m2;
	destination += m3;
}

//Nhân hai Big Int có đúng 1 chữ số ( không tính số 0 )
void bigint::Multi(bigint& destination, bigint& var1, bigint& var2)
{
	if (var1.sizeNum != 1 || var2.sizeNum != 1)
		return;
	destination = (*var1.numText - '0') * (*var2.numText - '0');
	destination.isPositive = var1.isPositive == var2.isPositive;
}

//Cưa đôi Big Int cho 2 Big Int : Left và Right
void bigint::Divide(const bigint& source, bigint& left, bigint& right, int length)
{//(A - B)(D - C)
	if (source.sizeNum > length || length <= 1)
		return;

	int mid = length / 2;

	right.sizeNum = std::min<int>(source.sizeNum, mid);
	right.realloc(right.sizeNum);
	for (int i = 0; i < right.sizeNum; i++)
		right.numText[i] = source.numText[i];

	left.sizeNum = source.sizeNum - right.sizeNum;
	if (left.sizeNum <= 0)
	{
		left.sizeNum = 1;
		left.numText[0] = '0';
	}
	left.realloc(left.sizeNum);
	for (int i = right.sizeNum; i < source.sizeNum; i++)
		left.numText[i - right.sizeNum] = source.numText[i];

	if (!source.isPositive)
	{
		left.isPositive = left == 0;
		right.isPositive = right == 0;
	} else
		left.isPositive = right.isPositive = true;

	left.clear();
	right.clear();
}

//Thêm vài số 0 vào sau Big Int
void bigint::x10(int exponential)
{
	if (*this == 0 || exponential <= 0)
		return;

	realloc(sizeNum + exponential);
	for (int i = sizeNum - 1; i >= 0; i--)
		numText[i + exponential] = numText[i];
	for (int i = 0; i < exponential; i++)
		numText[i] = '0';
	sizeNum += exponential;
}

//So sánh 2 Big Int
int bigint::Compare(char* str1, int length1, char* str2, int length2)
{
	if (length1 != length2)
		return length1 - length2;
	for (int i = length1 - 1; i >= 0; i--)
		if (str1[i] != str2[i])
			return str1[i] - str2[i];
	return 0;
}

int bigint::Add(char* strAdd, char* str1, int length1, char* str2, int length2)
{	//Chỉ cộng, không so sánh dấu
	int remember = 0, i = 0, temp;

	for (int stop = std::min(length1, length2); i < stop; i++)
	{
		temp = str1[i] + str2[i] + remember - ('0' << 1);
		if (remember != 0)		//Cộng thêm nhớ
			remember = 0;
		if (temp >= 10)			//Lưu nhớ
			remember = 1;
		strAdd[i] = temp % 10 + '0';
	}

	char* next = length1 > length2 ? str1 : str2;
	for (int stop = std::max(length1, length2); remember == 1 || i < stop; i++)
		if (remember == 0)
			strAdd[i] = next[i];
		else {	//Remember = 1
			if (i < stop)
			{
				if (next[i] <= '8')
				{
					strAdd[i] = next[i] + 1;
					remember = 0;
				} else
					strAdd[i] = '0';
			} else {
				strAdd[i] = '1';
				remember = 0;
			}
		}
	return i;
}

int bigint::Sub(char* strSub, char* str1, int length1, char* str2, int length2)
{	//Chỉ trừ, không so sánh dấu ( length1 phải lớn hơn hoặc bằng length2 )
	int remember = 0, i = 0, temp;
	for (; i < length2; i++)
	{
		temp = str1[i] - str2[i] - remember;
		if (remember != 0)
			remember = 0;
		if (temp < 0)
		{
			temp += 10;
			remember = 1;
		}
		strSub[i] = temp + '0';
	}

	for (; i < length1; i++)
		if (remember == 0)
			strSub[i] = str1[i];
		else {
			if (str1[i] == '0')
				strSub[i] = '9';
			else {
				strSub[i] = str1[i] - 1;
				remember = 0;
			}
		}
	for (; i > 1 && strSub[i - 1] == '0'; i--);
	return i;
}

std::istream& operator>>(std::istream& in, bigint& var)
{
	var.input();
	return in;
}

std::ostream& operator<<(std::ostream& out, bigint& var)
{
	var.output();
	return out;
}

//Tính độ dài mảng cần cấp phát
int bigint::countSizeData(int sizeByte)
{	//Độ dài mảng phải là một số chia hết cho 8
	if (sizeByte <= 0)	return SIZE_DEFAULT;
	return (sizeByte / SIZE_DEFAULT + 1) * SIZE_DEFAULT;
}

//Tính độ dài Value
int bigint::countLength(long long value)
{
	if (value == 0)	return 1;
	int count = 0;
	for (; value != 0; value /= 10)	count++;
	return count;
}
//==================================================
#endif	//_FISH_NUM_
