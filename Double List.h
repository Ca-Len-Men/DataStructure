#ifndef _FISH_DLIST_
#define _FISH_DLIST_

#include<iostream>
//==================================================
//=====     Nút     =====
template <class data>
class node {
public:
	data info;
	node* prev, * next;

public:
	node(const data& var) { info = var;		 prev = next = NULL; };
	node(const node& var) { info = var.info;  prev = next = NULL; };
	node(const node* var) { info = var->info;  prev = next = NULL; };

	//Hàm tĩnh

	static void connect(node* front, node* back) { front->next = back;  back->prev = front; };
};

//==================================================
//=====     Danh sách liên kết đôi     =====
template <class data>
class DList {
	node<data>* head, * tail;
	int size;

	void Ascending();
	void Descending();
public:
	DList() { head = tail = NULL;	size = 0; };

	//Phương thức
	void output(bool reverse = false);
	void sort(bool ascending = true);
	void reverse();
	void pushFront(const data& var);
	void pushBack(const data& var);
	data popFront();
	data popBack();

	bool isEmpty() { return head == NULL; };
	bool isFound(const data& var);

	int length() { return size; };

	data& operator[](int index);

	template <class Data> friend std::ostream& operator<<(std::ostream& out, const DList<Data>& list);
};

//Sắp xếp danh sách
template <class data>
void DList<data>::sort(bool ascending)
{
	if (ascending)
		Ascending();
	else
		Descending();
}

//Xuất danh sách
template <class data>
void DList<data>::output(bool reverse)
{
	if (!reverse)
		for (node<data>* i = head; i; i = i->next)
			std::cout << i->info << ' ';
	else
		for (node<data>* i = tail; i; i = i->prev)
			std::cout << i->info << ' ';
	printf("NULL\n");
}

//Có tồn tại một giá trị trong danh sách
template <class data>
bool DList<data>::isFound(const data& var)
{
	for (node<data>* i = head; i; i = i->next)
		if (i->info == var)
			return true;
	return false;
}

//Lấy ra phần tử cuối : danh sách không được rỗng
template <class data>
data DList<data>::popBack()
{
	data var = tail->info;
	node<data>* p = tail;
	tail = tail->prev;
	delete p;

	if (tail)
		tail->next = NULL;
	else
		head = NULL;
	size--;
	return var;
}

//Lấy ra phần tử đầu : danh sách không được rỗng
template <class data>
data DList<data>::popFront()
{
	data var = head->info;
	node<data>* p = head;
	head = head->next;
	delete p;

	if (head)
		head->prev = NULL;
	else
		tail = NULL;
	size--;
	return var;
}

//Đảo danh sách
template <class data>
void DList<data>::reverse()
{
	if (size <= 1)
		return;

	for (node<data>* i = head; i; i = i->prev)
		std::swap(i->prev, i->next);
	std::swap(head, tail);
}

//Thêm một phần tử vào cuối
template <class data>
void DList<data>::pushBack(const data& var)
{
	//Danh sách rỗng
	if (head == NULL)
		head = tail = new node<data>(var);
	else {
		node<data>::connect(tail, new node<data>(var));
		tail = tail->next;
	}

	size++;
}

//Thêm một phần tử vào đầu
template <class data>
void DList<data>::pushFront(const data& var)
{
	//Danh sách rỗng
	if (head == NULL)
		head = tail = new node<data>(var);
	else {
		node<data>::connect(new node<data>(var), head);
		head = head->prev;
	}

	size++;
}
//==================================================
//=====     Toán tử     =====

//Tham chiếu phần tử
template <class data>
data& DList<data>::operator[](int index)
{
	if (index == -1 || index >= size)
		return tail->info;
	node<data>* p = head;
	for (; index > 0; p = p->next, index--);
	return p->info;
}

//Xuất danh sách
template <class Data>
std::ostream& operator<<(std::ostream& out, const DList<Data>& list)
{
	for (node<Data>* i = list.head; i; i = i->next)
		std::cout << i->info << ' ';
	printf("NULL\n");
	return out;
}
//==================================================
//=====     Private Function     =====
template <class data>
void DList<data>::Ascending()
{
	if (size <= 1)
		return;

	node<data>* left = head, * right = tail, * k = left;
	while (left != right)
	{
		for(node<data>* i = left; i != right; i = i->next)
			if (i->info > i->next->info)
			{
				std::swap(i->info, i->next->info);
				k = i;
			}

		for (node<data>* i = right = k; i != left; i = i->prev)
			if (i->info < i->prev->info)
			{
				std::swap(i->info, i->prev->info);
				k = i;
			}
		left = k;
	}
}

template <class data>
void DList<data>::Descending()
{
	if (size <= 1)
		return;

	node<data>* left = head, * right = tail, * k = left;
	while (left != right)
	{
		for (node<data>* i = left; i != right; i = i->next)
			if (i->info < i->next->info)
			{
				std::swap(i->info, i->next->info);
				k = i;
			}

		for (node<data>* i = right = k; i != left; i = i->prev)
			if (i->info > i->prev->info)
			{
				std::swap(i->info, i->prev->info);
				k = i;
			}
		left = k;
	}
}
//==================================================
#endif	//_FISH_DLIST_
