#ifndef _MY_STACK_
#define _MY_STACK_

#include<iostream>
//==================================================
template <class _data>
class node {
public:
	_data info;
	node* next;

	//Khoi tao
	node(_data enemy = 0);

	//Ham
	void change(_data enemy = 0);			//Khoi tao node co gia tri
};

template <class _data>
void node<_data>::change(_data enemy)
{
	info = enemy;
	next = NULL;
}

template <class _data>
node<_data>::node(_data enemy)
{
	info = enemy;
	next = NULL;
};
//==================================================

template <class _data> node<_data>* new_node(_data enemy);
//==================================================
template <class _data>
class stack {
public:
	node<_data>* head;
//public:
	//Khoi tao
	stack();

	//Phuong thuc


	//Ham
	void add(node<_data>* p);		//Them vao stack
	void add(_data value);			//Them vao stack
	void show();					//Show stack
	void push(_data& x);			//Lay ra stack

	bool isStack();					//Kiem tra stack rong

	void del();				//Giai phong stack
};

template <class _data>
void stack<_data>::del()
{
	node<_data>* p = head;

	for(; head;)
	{
		head = head->next;
		delete p;
		p = head;
	}
}

template <class _data>
void stack<_data>::push(_data& x)
{
	if (head == NULL)
		return;

	node<_data>* p = head;
	head = head->next;
	x = p->info;
	delete p;
}

template <class _data>
void stack<_data>::add(_data value)
{
	node<_data>* p = new_node<_data>(value);
	p->next = head;
	head = p;
}

template <class _data>
void stack<_data>::show()
{
	show_node(head);
}

template <class _data>
void stack<_data>::add(node<_data>* p)
{
	if (p == NULL)
		return;
	p->next = head;
	head = p;
}

template <class _data>
bool stack<_data>::isStack()
{
	return head == NULL;
}

template <class _data>
stack<_data>::stack()
{
	head = NULL;
}
//==================================================
template <class _data> void show_node(node<_data>* p);
//==================================================
template <class _data>
node<_data>* new_node(_data enemy)
{
	node<_data>* p = new node<_data>(enemy);
	return p;
}


template <class _data>
void show_node(node<_data>* p)
{
	for (; p; p = p->next)
		std::cout << p->info << " ";
	std::cout << "NULL\n";
}

#endif