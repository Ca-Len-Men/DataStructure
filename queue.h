#ifndef _FISH_QUEUE_
#define _FISH_QUEUE_

#include<iostream>
//==================================================
//==========          Queue          ==========
template <class data>
class queue {
	class node {
	public:
		data info;
		node* next{ nullptr };
		node(const data& var) : info{ var } {};
	};

	node* head = nullptr;
	node* tail = nullptr;
	size_t size = 0;

public:
	//Khởi tạo
	queue() = default;
	queue(const queue& qu);
	~queue();

	//Phương thức
	void output(const char* title = nullptr) const;
	void push(const data& var);
	data pop();
	bool isFound(const data& var) const;

	data get() const		{ return head->info; }
	data getBack() const	{ return tail->info; }
	void swap(queue& qu)	{ std::swap(head, qu.head); std::swap(tail, qu.tail); std::swap(size, qu.size); }
	bool isEmpty() const	{ return head == nullptr; }
	size_t length() const	{ return size; }

	//Toán tử
	queue& operator=(const queue& st);
	template <class Data> friend std::ostream& operator<<(std::ostream& out, const queue<Data>& qu);
};

template <class Data>
std::ostream& operator<<(std::ostream& out, const queue<Data>& qu)
{
	qu.output();
	return out;
}

template <class data>
queue<data>& queue<data>::operator=(const queue& qu)
{
	for (tail = head; head; tail = head)
	{
		head = head->next;
		delete tail;
	}
	size = 0;

	if (qu.head != nullptr)
	{
		head = tail = new node(qu.head->info);
		size = qu.size;
		for (node* i = qu.head->next; i; i = i->next, tail = tail->next)
			tail->next = new node(i->info);
	}
	return *this;
}

template <class data>
bool queue<data>::isFound(const data& var) const
{
	for (node* i = head; i; i = i->next)
		if (i->info == var)
			return true;
	return false;
}

template <class data>
data queue<data>::pop()
{
	data temp = head->info;
	node* p = head;

	head = head->next;
	if (head == nullptr)
		tail = nullptr;
	size--;

	delete p;
	return temp;
}

template <class data>
void queue<data>::push(const data& var)
{
	if (head == nullptr)
	{
		head = tail = new node(var);
		size = 1;
		return;
	}

	tail->next = new node(var);
	tail = tail->next;
	size++;
}

template <class data>
void queue<data>::output(const char* title) const
{
	if (title)
		printf(title);

	for (node* i = head; i; i = i->next)
		std::cout << i->info << ' ';
	std::cout << "NULL\n";
}

template <class data>
queue<data>::~queue()
{
	for (tail = head; head; tail = head)
	{
		head = head->next;
		delete tail;
	}
	size = 0;
}

template <class data>
queue<data>::queue(const queue& qu)
{
	if (qu.head == nullptr)
	{
		head = tail = nullptr;
		size = 0;
		return;
	}

	head = tail = new node(qu.head->info);
	size = qu.size;
	for (node* i = qu.head->next; i; i = i->next, tail = tail->next)
		tail->next = new node(i->info);
}
//==================================================
#endif	//_FISH_QUEUE_
