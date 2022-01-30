#ifndef _FISH_STACK_
#define _FISH_STACK_

#include<iostream>
//==================================================
//==========          Stack          ==========
template <class data>
class stack {
	class node {
	public:
		data info;
		node* next{ nullptr };
		node(const data& var) : info{ var } {};
	};

	node* top = nullptr;
	size_t size = 0;

public:
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
	size_t length() const	{ return size; }

	//Toán tử
	stack& operator=(const stack& st);
	template <class Data> friend std::ostream& operator<<(std::ostream& out, const stack<Data>& st);
};

template <class Data>
std::ostream& operator<<(std::ostream& out, const stack<Data>& st)
{
	st.output();
	return out;
}

template <class data>
stack<data>& stack<data>::operator=(const stack& st)
{
	for (node* i = top; top; i = top)
	{
		top = top->next;
		delete i;
	}
	size = 0;

	if (st.top != nullptr)
	{
		top = new node(st.top->info);
		size = st.size;
		for (node* i = top, *j = st.top->next; j; i = i->next, j = j->next)
			i->next = new node(j->info);
	}
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
#endif	//_FISH_STACK_
