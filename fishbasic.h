#ifndef _FISH_BASIC_
#define _FISH_BASIC_

#include<iostream>
#include<algorithm>

template <class data> class stack;
template <class data> class queue;
template <class data> class SList;
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
	size_t length() const		{ return size; }

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
	size_t length() const		{ return size; }

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
//==========          Single List          ==========
template <class data>
class SList {
	class node {
	public:
		data info;
		node* next = nullptr;

		node(const data& var) : info{ var } {};

		static node* sort(node* head, int left, int right, int (*Compare)(const data&, const data&) = nullptr) {
			node* p = head, * j;
			int k, r;
			queue<data> quLeft;

			for (k = 0; p && k < left; k++, p = p->next)
				quLeft.push(p->info);

			for (j = p, k = 0; p && k < right; k++, p = p->next);
			if (quLeft.length() < left || k == 0)
				return p;
			right = k;

			if (Compare != nullptr) {
				if (Compare(quLeft.getBack(), j->info) <= 0)	return p;

				for (r = 0; !quLeft.isEmpty() && r < right; head = head->next)
					if (Compare(quLeft.get(), j->info) <= 0)
						head->info = quLeft.pop();
					else {
						head->info = j->info;
						r++;
						j = j->next;
					}
			} else {
				if (quLeft.getBack() <= j->info) return p;

				for (r = 0; !quLeft.isEmpty() && r < right; head = head->next)
					if (quLeft.get() <= j->info)
						head->info = quLeft.pop();
					else {
						head->info = j->info;
						r++;
						j = j->next;
					}
			}

			for (; !quLeft.isEmpty(); head = head->next)
				head->info = quLeft.pop();
			return p;
		}
	};

	node* head = nullptr;
	node* tail = nullptr;
	size_t size = 0;
public:
	//Khởi tạo
	SList() = default;
	SList(const SList& var);
	~SList();

	//Phương thức
	void output(const char* title = nullptr) const;
	void reverse();
	void sort(bool ascending = true, int (*Compare)(const data&, const data&) = nullptr);
	void rotate(int number);
	void memset(const data& var) const;
	void memset(const data& var, int length);
	void pushFront(const data& var);
	void pushBack(const data& var);
	data popFront();
	data popBack();
	bool popFrontSecurity(data& readOnly);
	bool popBackSecurity(data& readOnly);
	bool isFound(const data& var);

	void swap(SList& list)	{ std::swap(head, list.head); std::swap(tail, list.tail); std::swap(size, list.size); }
	data getFront() const	{ return head->info;		}
	data getBack() const	{ return tail->info;		}
	int length() const		{ return size;				}
	bool isEmpty() const	{ return head == nullptr;	}

	//Toán tử
	SList& operator=(const SList& list);
	SList& operator+=(const SList& list);

	template <class Data> friend SList<Data> operator+(const SList<Data>& list1, const SList<Data>& list2);
	template <class Data> friend std::ostream& operator<<(std::ostream& out, const SList<Data>& list);

	//==========          Iterator          ==========
	class iterator {
		node* pointer = nullptr;
		SList* symbiotic = nullptr;

	public:
		iterator() = default;
		iterator(const iterator& ptr) {
			pointer = ptr.pointer;
			symbiotic = ptr.symbiotic;
		}

		iterator(node* ptr, SList* list) {
			pointer = ptr;
			symbiotic = list;
		}

		data& operator*() const		{ return pointer->info; }
		data* operator->() const	{ return &(pointer->info); }

		iterator& operator=(const iterator& iter) {
			pointer = iter.pointer; 
			symbiotic = iter.symbiotic;
			return *this;
		}

		iterator& operator=(const data& var) {
			if(pointer != nullptr)
				pointer->info = var;
			return *this;
		}

		iterator& operator++() {
			if (pointer != nullptr)
				pointer = pointer->next;
			return *this;
		}

		iterator operator++(int) {
			iterator temp = *this;
			++(*this);
			return temp;
		}

		bool operator==(const iterator& iter) const	{ return pointer == iter.pointer; }
		bool operator!=(const iterator& iter) const	{ return pointer != iter.pointer; }
		bool operator==(const node*& ptr) const		{ return pointer == ptr; }
		iterator next() const	{ return iterator(pointer->next, symbiotic); }

		friend std::ostream& operator<<(std::ostream& out, const iterator iter) {
			out << iter.pointer->info;
			return out;
		}

		friend SList;
	};

	iterator begin()	{ return iterator(head, this);		}
	iterator last()		{ return iterator(tail, this);		}
	iterator end()		{ return iterator(nullptr, this);	}

	void pop(iterator& iter);
	void popNext(const iterator& iter);
	void pushPrev(iterator& iter, const data& var);
	void pushNext(const iterator& iter, const data& var);
};

template <class data>
void SList<data>::sort(bool ascending, int (*Compare)(const data&, const data&))
{
	if (size <= 1)
		return;

	for (int length = 1;; length *= 2)
	{
		for (node* i = head; i;)
			i = node::sort(i, length, length, Compare);
		if (length * 2 > size)	break;
	}

	if (ascending == false)
		reverse();
}

template <class data>
void SList<data>::pushNext(const iterator& iter, const data& var)
{
	if (iter.symbiotic != this || iter.pointer == nullptr)
		return;

	node* p = new node(var);
	p->next = iter.pointer->next;
	iter.pointer->next = p;
	if (tail == iter.pointer)
		tail = tail->next;
	size++;
}

template <class data>
void SList<data>::pushPrev(iterator& iter, const data& var)
{
	if (iter.symbiotic != this || iter.pointer == nullptr)
		return;

	node* p = new node(iter.pointer->info);
	p->next = iter.pointer->next;
	iter.pointer->next = p;
	iter.pointer->info = var;
	if (tail == iter.pointer)
		tail = tail->next;
	size++;
	iter.pointer = p;
}

template <class data>
void SList<data>::popNext(const iterator& iter)
{
	if (iter.symbiotic != this || iter.pointer == nullptr || iter.pointer->next == nullptr)
		return;

	node* p = iter.pointer->next;
	if (tail == p)
		tail = iter.pointer;
	iter.pointer->next = p->next;
	delete p;
	size--;
}

template <class data>
void SList<data>::pop(iterator& iter)
{
	if (iter.symbiotic != this || iter.pointer == nullptr)
		return;

	if (size == 1)
	{
		iter = iterator(nullptr, this);
		delete head;
		head = tail = nullptr;
		size = 0;
		return;
	}

	if (iter.pointer == tail)
	{
		iter = iterator(nullptr, this);
		popBack();
		return;
	}

	node* p = iter.pointer->next;
	if (tail == p)
		tail = iter.pointer;
	iter.pointer->info = p->info;
	iter.pointer->next = p->next;
	delete p;
	size--;
}

template <class Data>
SList<Data> operator+(const SList<Data>& list1, const SList<Data>& list2)
{
	SList<Data> var = list1;
	return var += list2;
}

template <class Data>
std::ostream& operator<<(std::ostream& out, const SList<Data>& list)
{
	list.output();
	return out;
}

template <class data>
SList<data>& SList<data>::operator+=(const SList& list)
{
	if (list.head == nullptr)
		return *this;

	if (head == nullptr)
		return *this = list;

	size += list.size;
	for (node* i = list.head; i; i = i->next, tail = tail->next)
		tail->next = new node(i->info);
	return *this;
}

template <class data>
SList<data>& SList<data>::operator=(const SList& list)
{
	for (tail = head; head; tail = head)
	{
		head = head->next;
		delete tail;
	}
	size = 0;

	if (list.head != nullptr)
	{
		head = tail = new node(list.head->info);
		size = list.size;
		for (node* i = list.head->next; i; i = i->next, tail = tail->next)
			tail->next = new node(i->info);
	}
	return *this;
}

template <class data>
bool SList<data>::isFound(const data& var)
{
	for (node* i = head; i; i = i->next)
		if (i->info == var)
			return true;
	return false;
}

template <class data>
bool SList<data>::popFrontSecurity(data& readOnly)
{
	if (head == nullptr)
		return false;

	readOnly = head->info;
	if (size == 1)
	{
		delete head;
		head = tail = nullptr;
		size = 0;
		return true;
	}

	node* p = head;
	head = head->next;
	size--;
	delete p;
	return true;
}

template <class data>
bool SList<data>::popBackSecurity(data& readOnly)
{
	if (head == nullptr)
		return false;

	readOnly = tail->info;
	if (size == 1)
	{
		delete tail;
		head = tail = nullptr;
		size = 0;
		return true;
	}

	node* i = head;
	for (; i->next != tail; i = i->next);
	i->next = nullptr;
	delete tail;
	tail = i;
	size--;
	return true;
}

template <class data>
data SList<data>::popBack()
{
	data temp = tail->info;

	if (size == 1)
	{
		delete head;
		head = tail = nullptr;
		size = 0;
		return temp;
	}

	node* i = head;
	for (; i->next != tail; i = i->next);
	i->next = nullptr;
	delete tail;
	tail = i;
	size--;
	return temp;
}

template <class data>
data SList<data>::popFront()
{
	data temp = head->info;
	if (size == 1)
	{
		delete head;
		head = tail = nullptr;
		size = 0;
		return temp;
	}

	node* p = head;
	head = head->next;
	size--;
	delete p;
	return temp;
}

template <class data>
void SList<data>::pushBack(const data& var)
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
void SList<data>::pushFront(const data& var)
{
	if (head == nullptr)
	{
		head = tail = new node(var);
		size = 1;
		return;
	}

	node* p = new node(var);
	p->next = head;
	head = p;
	size++;
}

template <class data>
void SList<data>::memset(const data& var, int length)
{
	for (tail = head; head; tail = head)
	{
		head = head->next;
		delete tail;
	}
	size = length;

	if (size <= 0)
	{
		size = 0;
		return;
	}

	head = tail = new node(var);
	for (; length > 1; length--, tail = tail->next)
		tail->next = new node(var);
}

template <class data>
void SList<data>::memset(const data& var) const
{
	for (node* i = head; i; i = i->next)
		i->info = var;
}

template <class data>
void SList<data>::rotate(int number)
{
	if (size <= 1 || number % size == 0)
		return;
	number %= size;
	
	//Rotate
	for (tail->next = head; number > 0; number--)
		tail = tail->next;
	head = tail->next;
	tail->next = nullptr;
}

template <class data>
void SList<data>::reverse()
{
	if (size <= 1)
		return;

	node* i = tail = head;
	i = i->next;
	head->next = nullptr;
	for (node* j = i; i; i = j)
	{
		j = i->next;
		i->next = head;
		head = i;
	}
}

template <class data>
void SList<data>::output(const char* title) const
{
	if (title)
		printf(title);
	for (node* i = head; i; i = i->next)
		std::cout << i->info << ' ';
	std::cout << "NULL\n";
}

template <class data>
SList<data>::~SList()
{
	for (tail = head; head; tail = head)
	{
		head = head->next;
		delete tail;
	}
	size = 0;
}

template <class data>
SList<data>::SList(const SList& var)
{
	if (var.head == nullptr)
	{
		head = tail = nullptr;
		size = 0;
		return;
	}

	head = tail = new node(var.head->info);
	size = var.size;
	for (node* i = var.head->next; i; i = i->next, tail = tail->next)
		tail->next = new node(i->info);
}
//==================================================
#endif	//_FISH_BASIC_
