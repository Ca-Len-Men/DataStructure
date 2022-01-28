#ifndef _FISH_BASIC_
#define _FISH_BASIC_

#include "painttree.h"
#include<iostream>
#include<algorithm>
#include<iomanip>

template <class data> class stack;
template <class data> class queue;
template <class data> class SList;
template <class key, class value> class bucket;
template <class key, class value> class AVLTree;
//==================================================
//==========          Stack          ==========
template <class data>
class stack {
	class node {
	public:
		data info;
		node* next = nullptr;
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
		node(const data& var) : info { var } {};
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
//==========          Bucket          ==========
enum class status {
	isEmpty,
	isFull,
	notValue,
	notFound
};
void testBucket(status Is)
{
	switch (Is)
	{
		case status::isEmpty: printf("Empty !");	break;
		case status::isFull: printf("Ton tai !");	break;
		case status::notValue: printf("Khong co gia tri !");	break;
		case status::notFound: printf("Khong ton tai !");	break;
	}
}

template <class key, class value>
class bucket {
	key code{};
	value info{};
	status valid{ status::isEmpty };

public:
	//Khởi tạo
	bucket(status Is = status::isEmpty) : valid { Is }
	{	//Empty or NotFound
		if (valid == status::isFull || valid == status::notValue)
			valid = status::isEmpty;
	};
	//Full
	bucket(const key& newCode, const value& newInfo) :
		code{ newCode },
		info{ newInfo },
		valid{ status::isFull }{};
	//Not Value
	bucket(const key& newCode) :
		code{ newCode },
		valid{ status::notValue },
		info{}{};
	//Copy
	bucket(const bucket& newBucket) :
		valid{ newBucket.valid },
		code{ newBucket.code },
		info{ newBucket.info }{};

	//Phương thức
	key getKey() const			{ return code; }
	value getValue() const		{ return info; }
	status getStatus() const	{ return valid; }
	//Full
	void change(const key& newCode, const value& newInfo)
	{
		code = newCode;
		info = newInfo;
		valid = status::isFull;
	}
	//Not Value
	void change(const key& newCode)
	{
		code = newCode;
		valid = status::notValue;
	}

	bool isEmpty() const	{ return valid == status::isEmpty; };
	bool isFull() const		{ return valid == status::isFull; };
	bool notValue() const	{ return valid == status::notValue; };
	bool notFound() const	{ return valid == status::notFound; };

	//Toán tử
	bucket& operator=(const bucket& newBucket) {
		code = newBucket.code;
		info = newBucket.info;
		valid = newBucket.valid;
		return *this;
	}

	bool operator==(const bucket& newBucket) const { return code == newBucket.code; };
	bool operator>(const bucket& newBucket) const { return code > newBucket.code; };
	bool operator<(const bucket& newBucket) const { return code < newBucket.code; };
};
//==================================================
//==========          AVL Tree          ==========
template <class key, class value>
class AVLTree {
	class node {
	public:	//+ : nghiêng trái			- : nghiêng phải
		node* left, * right;
		bucket<key, value> info;
		unsigned char height;

		//Khởi tạo
		node(const bucket<key, value>& newInfo) :
			info{ newInfo },
			left{ nullptr },
			right{ nullptr },
			height{ 1 }
			{};

		//Phương thức
		void countHeight() {	//Tính lại chiều cao
			unsigned char leftHeight = left == nullptr ? 0 : left->height;
			unsigned char rightHeight = right == nullptr ? 0 : right->height;
			height = std::max(leftHeight, rightHeight) + 1;
		}
		//Gán mới một bucket
		void copyBucket(const bucket<key, value>& newBucket) {
			info = newBucket;
		}
		//Tính độ lệch của hai cây con
		char countBalance() {
			char leftHeight = left == nullptr ? 0 : left->height;
			char rightHeight = right == nullptr ? 0 : right->height;
			return leftHeight - rightHeight;
		}

		//Hàm tĩnh
		//Quay trái
		static void rotateLeft(node*& root) {
			if (root == nullptr)
				return;

			if (root->right == nullptr)
				return;
			//Quay trái
			node* childLeft = root;
			root = root->right;
			childLeft->right = root->left;
			root->left = childLeft;
			//Tính lại chiều cao
			childLeft->countHeight();
			root->countHeight();
		}

		//Quay phải
		static void rotateRight(node*& root) {
			if (root == nullptr)
				return;

			if (root->left == nullptr)
				return;
			//Quay trái
			node* childRight = root;
			root = root->left;
			childRight->left = root->right;
			root->right = childRight;
			//Tính lại chiều cao
			childRight->countHeight();
			root->countHeight();
		}

		//Cân bằng tại root
		static void balanceRoot(node*& root) {
			if (root == nullptr)
				return;

			char tilt = root->countBalance();
			//Nghiêng phải -> quay trái
			if (tilt < -1) {
				if (root->right->countBalance() <= 0)	//Cây con phải lệch phải
					rotateLeft(root);
				else {	//Cây con phải lệch trái
					rotateRight(root->right);
					rotateLeft(root);
				}
			}
			else if (tilt > 1) {//Nghiêng trái -> quay phải
				if (root->left->countBalance() >= 0)	//Cây con trái lệch trái
					rotateRight(root);
				else {	//Cây con trái lệch phải
					rotateLeft(root->left);
					rotateRight(root);
				}
			}
		}

		//Tìm phần tử thế mạng ở cây con trái
		static void poorChildLeft(node*& root) {
			if (root == nullptr || root->left == nullptr)
				return;

			stack<node*&> st;
			st.push(root->left);
			while (st.get()->right != nullptr)
				st.push(st.get()->right);

			node*& temp = st.pop();
			root->info = temp->info;
			node* p = temp;
			temp = temp->left;
			delete p;

			while (!st.isEmpty())
				balanceRoot(st.pop());
		}

		//Tìm phần tử thế mạng ở cây con phải
		static void poorChildRight(node*& root) {
			if (root == nullptr || root->right == nullptr)
				return;

			stack<node*&> st;
			st.push(root->right);
			while (st.get()->left != nullptr)
				st.push(st.get()->left);

			node*& temp = st.pop();
			root->info = temp->info;
			node* p = temp;
			temp = temp->right;
			delete p;

			while (!st.isEmpty())
				balanceRoot(st.get());
		}
	};
	//=====     Tree     =====
	node* root;
	int size, weightOut;

	//Hàm tĩnh
	static void pushRecursive(node*& root, const bucket<key, value>& newBucket);
	static bool popRecursive(node*& root, bucket<key, value>& newBucket);
	static void outputRecursiveLNR(node*& root, const int& weight, int count, bool leftChild);

public:
	//Khởi tạo
	AVLTree(int setWeight = 10) :
		root{ nullptr }, size{ 0 }, weightOut{ setWeight }
	{
		if (weightOut <= 0)
			weightOut = 10;
	};

	//Phương thức
	void paint() const;
	void output() const;
	void push(const bucket<key, value>& newBucket);
	int length() const { return size; }
	bucket<key, value> pop(const key& code);
	bucket<key, value> find(const key& code) const;
};

template <class key, class value>
bucket<key, value> AVLTree<key, value>::find(const key& code) const
{
	node* p = root;
	while (p != nullptr)
	{
		if (p->info.getKey() == code)
			return p->info;
		else if (p->info.getKey() > code)	//Tìm sang cây con trái
			p = p->left;
		else
			p = p->right;
	}
	//Không tìm thấy
	return bucket<key, value>(status::notFound);
}

template <class key, class value>
void AVLTree<key, value>::paint() const
{
	print_ascii_tree<node>(root);
}

template <class key, class value>
bucket<key, value> AVLTree<key, value>::pop(const key& code)
{
	bucket<key, value> res{ code };
	if (popRecursive(root, res)) {	//Tồn tại
		size--;
		return res;
	}
	
	return bucket<key, value>(status::notFound);
}

template <class key, class value>
void AVLTree<key, value>::push(const bucket<key, value>& newBucket)
{
	if (!newBucket.isFull())
		return;
	pushRecursive(root, newBucket);
	size++;
}

template <class key, class value>
void AVLTree<key, value>::outputRecursiveLNR(node*& root, const int& weight, int count, bool leftChild)
{
	if (root == nullptr)
		return;

	outputRecursiveLNR(root->left, weight, count + 1, true);

	if (count)
		for (int i = weight * count; i > 0; i--)
			putchar(' ');
	std::cout << (leftChild ? '/' : '\\');
	std::cout << std::setw(weight - 2) << root->info.getKey() << "|\n";

	outputRecursiveLNR(root->right, weight, count + 1, false);
}

template <class key, class value>
bool AVLTree<key, value>::popRecursive(node*& root, bucket<key, value>& newBucket)
{
	if (root == nullptr)
		return false;

	bool getValue;
	if (root->info == newBucket)
	{
		newBucket = root->info;
		if (root->left == nullptr && root->right == nullptr)	//Nút lá
		{
			delete root;
			root = nullptr;
			return true;
		}

		//Tìm nút thế mạng
		if (root->countBalance() >= 0)	//Nghiêng trái : tìm nút thế mạng bên cây con trái
			node::poorChildLeft(root);
		else
			node::poorChildRight(root);
		return true;
	}
	else if (newBucket < root->info)	//Đệ quy sang cây con trái
		getValue = popRecursive(root->left, newBucket);
	else
		getValue = popRecursive(root->right, newBucket);//Đệ quy sang cây con phải

	node::balanceRoot(root);
	return getValue;
}

template <class key, class value>
void AVLTree<key, value>::pushRecursive(node*& root, const bucket<key, value>& newBucket)
{
	if (root == nullptr)
	{
		root = new node(newBucket);
		return;
	}

	if (root->info == newBucket)
	{
		root->info = newBucket;
		return;
	}
	else if (root->info < newBucket)//Đệ quy sang phải
		pushRecursive(root->right, newBucket);
	else//Đệ quy sang trái
		pushRecursive(root->left, newBucket);

	//Cân bằng nút
	root->countHeight();
	node::balanceRoot(root);
}

template <class key, class value>
void AVLTree<key, value>::output() const
{
	if (root == nullptr)
	{
		std::cout << "Tree is empty\n";
		return;
	}

	outputRecursiveLNR(root->left, weightOut, 1, true);
	std::cout << '|' << std::setw(weightOut - 2) << root->info.getKey() << "|\n";
	outputRecursiveLNR(root->right, weightOut, 1, false);
}
//==================================================
//==========          Red Black Tree          ==========
template <class key, class value>
class RBTree {
	enum class colors { RED, BLACK };

	class node {
	public:
		bucket<key, value> info;
		node* left, * right, * parent;
		colors color;

		//Constructor
		node(const bucket<key, value>& newBucket) {
			info = newBucket;
			left = right = parent = nullptr;
			color = colors::RED;
		}

		//Method
		void connectLeft(node* leftChild) {
			left = leftChild;
			leftChild->parent = this;
		}

		void connectRight(node* rightChild) {
			right = rightChild;
			rightChild->parent = this;
		}
	};
};
//==================================================
#endif	//_FISH_BASIC_
