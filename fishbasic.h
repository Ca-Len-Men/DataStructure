#ifndef _FISH_BASIC_
#define _FISH_BASIC_

#include<iostream>
#include<algorithm>

template <class data> class stack;
template <class data> class queue;
//==================================================
//==========          Stack          ==========
template <class data>
class stack {
	class node {
	public:
		data info;
		node* next = nullptr;
		node(const data& var) { info = var; }
	};
	
	node* top = nullptr;
	int size = 0;

public:
	static const stack Empty;

	//Khởi tạo
	stack() = default;
	stack(const stack& st);
	~stack();

	//Phương thức
	void output(const char* title = nullptr) const;
	void push(const data& var);
	data pop();
	bool isFound(const data& var) const;

	data get() const		{ return top->info; }
	void swap(stack& st)	{ std::swap(top, st.top); std::swap(size, st.size); }
	bool isEmpty() const	{ return top == nullptr; }
	int length() const		{ return size; }

	//Toán tử
	stack operator=(const stack& st);
	template <class Data> friend std::ostream& operator<<(std::ostream& out, const stack<Data> st);
};

template <class Data>
std::ostream& operator<<(std::ostream& out, const stack<Data> st)
{
	st.output();
	return out;
}

template <class data>
stack<data> stack<data>::operator=(const stack& st)
{
	for (node* i = top; top; i = top)
	{
		top = top->next;
		delete i;
	}
	size = 0;
	if(st.top == nullptr)
		return *this;

	top = new node(st.top->info);
	size = st.size;
	for (node* i = top, *j = st.top->next; j; i = i->next, j = j->next)
		i->next = new node(j->info);
	return *this;
}

template <class data>
bool stack<data>::isFound(const data& var) const
{
	for (node* i = top; i; i = i->next)
		if (i->info == var)
			return true;
	return false;
}

template <class data>
data stack<data>::pop()
{
	data temp = top->info;
	node* p = top;
	top = top->next;
	size--;

	delete p;
	return temp;
}

template <class data>
void stack<data>::push(const data& var)
{
	if (top == nullptr)
	{
		top = new node(var);
		size = 1;
		return;
	}

	node* p = new node(var);
	p->next = top;
	top = p;
	size++;
}

template <class data>
void stack<data>::output(const char* title) const
{
	if (title)
		printf(title);

	for (node* i = top; i; i = i->next)
		std::cout << i->info << ' ';
	std::cout << "NULL\n";
}

template <class data>
stack<data>::~stack()
{
	for (node* i = top; top; i = top)
	{
		top = top->next;
		delete i;
	}
	size = 0;
}

template <class data>
stack<data>::stack(const stack& st)
{
	if (st.top == nullptr)
	{
		top = nullptr;
		size = 0;
		return;
	}

	top = new node(st.top->info);
	size = st.size;
	for (node* i = top, *j = st.top->next; j; i = i->next, j = j->next)
		i->next = new node(j->info);
}
//==================================================
//==========          Queue          ==========
template <class data>
class queue {
	class node {
	public:
		data info;
		node* next = nullptr;
		node(const data& var) { info = var; }
	};

	node* head = nullptr;
	node* tail = nullptr;
	int size = 0;

public:
	static const queue Empty;

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
	void swap(queue& qu)	{ std::swap(head, qu.head); std::swap(tail, qu.tail); std::swap(size, qu.size); }
	bool isEmpty() const	{ return head == nullptr; }
	int length() const		{ return size; }

	//Toán tử
	queue operator=(const queue& st);
	template <class Data> friend std::ostream& operator<<(std::ostream& out, const queue<Data> qu);
};

template <class Data>
std::ostream& operator<<(std::ostream& out, const queue<Data> qu)
{
	qu.output();
	return out;
}

template <class data>
queue<data> queue<data>::operator=(const queue& qu)
{
	for (tail = head; head; tail = head)
	{
		head = head->next;
		delete tail;
	}
	size = 0;
	if (qu.head == nullptr)
		return *this;

	head = tail = new node(qu.head->info);
	size = qu.size;
	for (node* i = qu.head->next; i; i = i->next, tail = tail->next)
		tail->next = new node(i->info);
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
#endif	//_FISH_BASIC_
