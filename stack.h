#ifndef _STACK_
#define _STACK_

#include<iostream>
//==================================================
//==========          Stack          ==========
template <class data>
class stack {
	//=====     Sub Class     =====//
#pragma region Sub Class
	class node {
	public:
		data info;
		node* next;

		node(const data& var) :
			info{ var }, next{ nullptr } {};
	};
#pragma endregion

	//=====     Attributes     =====//
#pragma region Attributes
	node* top;
	size_t size;
#pragma endregion

public:
	//=====     Constructors and Destructor     =====//
#pragma region Constructors and Destructor
	stack() :
		top{ nullptr }, size{ 0 }{}

	stack(const stack& st)
	{
		if (st.top == nullptr)
		{
			this->top = nullptr;
			this->size = 0;
			return;
		}

		this->top = new node(st.top->info);
		this->size = st.size;
		for (node* i = this->top, *j = st.top->next; j; i = i->next, j = j->next)
			i->next = new node(j->info);
	}

	stack(stack&& source) noexcept :
		top{ source.top }, size{ source.size }
	{ source.top = nullptr; }

	~stack()
	{
		this->clear();
	}
#pragma endregion
	
	//=====     Methods     =====//
#pragma region Methods
	//If Stack contain value valthan return true
	bool contain(const data& val) const
	{
		for (node* i = this->top; i != nullptr; i = i->next)
			if (i->info == val)
				return true;
		return false;
	}

	//Pop the value on the top of Stack
	data pop()
	{
		data res(this->top->info);
		node* p = this->top;
		this->top = this->top->next;
		--this->size;

		delete p;
		return res;
	}

	//Push the value on the top of Stack
	void push(const data& val)
	{
		if (this->top == nullptr)
		{
			this->top = new node(val);
			this->size = 1u;
			return;
		}

		node* p = new node(val);
		p->next = this->top;
		this->top = p;
		++this->size;
	}

	//Stack is being empty
	void clear() {
		for (node* i = this->top; this->top != nullptr; i = this->top)
		{
			this->top = this->top->next;
			delete i;
		}
		this->size = 0u;
	}

	//Writting on the console
	void out() const
	{
		std::cout << '[';
		for (node* i = this->top; i; i = i->next)
		{
			std::cout << i->info;
			if (i->next != nullptr)
				std::cout << ", ";
		}
		std::cout << "]\n";
	}

	//Get const value at top of Stack
	const data& getTop() const {
		return top->info;
	}

	//Swapping two Stack
	void swap(stack& st) {
		std::swap(this->top, st.top);
		std::swap(this->size, st.size);
	}
	
	//Check Stack is empty
	bool empty() const {
		return this->top == nullptr;
	}

	//Length of Stack
	size_t length() const {
		return this->size;
	}
#pragma endregion
	
	//=====     Operators     =====//
#pragma region Operators
	//Check Stack is not empty
	operator bool() const {
		return top != nullptr;
	}

	//Copy data from other Stack
	stack& operator=(const stack& source)
	{
		if (this == &source)
			return *this;
		this->clear();

		if (source.top != nullptr)
		{
			this->top = new node(source.top->info);
			this->size = source.size;
			for (node* i = top, *j = source.top->next; j != nullptr; i = i->next, j = j->next)
				i->next = new node(j->info);
		}
		return *this;
	}

	//Copy data from other Stack
	stack& operator=(stack&& source) noexcept {
		this->clear();
		this->top = source.top;
		this->size = source.size;
		source.top = nullptr;
	}
#pragma endregion

	//=====     Iterator     =====//
#pragma region Iterator
	class iterator {
		//=====     Attributes     =====//
		node* pointer;
		friend stack;
		//=====     Constructors     =====//
		iterator(node* _Pointer) : pointer{ _Pointer } {}

	public:
		iterator(const iterator& source) : pointer{ source.pointer } {}
		
		//=====     Operators     =====//
		
		//Check iterator not null
		operator bool() const {
			return this->pointer != nullptr;
		}

		//Get value of item
		data& operator*() {
			return this->pointer->info;
		}

		//Get index ( type data* ) of item
		data* operator->() {
			return &this->pointer->info;
		}

		//Iterator move to the next item
		iterator& operator++() {
			if(this->pointer != nullptr)
				this->pointer = this->pointer->next;
			return *this;
		}

		//Iterator move to the next item
		iterator operator++(int) {
			iterator res(*this);
			if (this->pointer != nullptr)
				this->pointer = this->pointer->next;
			return res;
		}

		//Copy data from other iterator
		iterator& operator=(const iterator& source) {
			this->pointer = source.pointer;
			return *this;
		}

		//Compare two iterators
		bool operator==(const iterator& source) {
			return this->pointer == source.pointer;
		}

		//Compare two iterators
		bool operator!=(const iterator& source) {
			return this->pointer != source.pointer;
		}
	};
#pragma endregion

	//=====     Const Iterator     =====//
#pragma region Const Iterator
	class const_iterator {
		//=====     Attributes     =====//
		const node* pointer;
		friend stack;

		//=====     Constructors     =====//
		const_iterator(const node* _Pointer) : pointer{ _Pointer } {}

	public:
		const_iterator(const const_iterator& source) :
			pointer{ source.pointer } {}

		//=====     Operators     =====//

		//Check const_iterator not null
		operator bool() const {
			return this->pointer != nullptr;
		}

		//Get const value of item
		const data& operator*() {
			return this->pointer->info;
		}

		//Get index ( type const data* ) of item
		const data* operator->() {
			return &this->pointer->info;
		}

		//Const iterator move to the next item
		const_iterator& operator++() {
			if (this->pointer != nullptr)
				this->pointer = this->pointer->next;
			return *this;
		}

		//Const Iterator move to the next item
		const_iterator operator++(int) {
			const_iterator res(*this);
			if (this->pointer != nullptr)
				this->pointer = this->pointer->next;
			return res;
		}

		//Copy data from other const_iterator
		const_iterator& operator=(const const_iterator& source) {
			this->pointer = source.pointer;
			return *this;
		}

		//Compare two const_iterators
		bool operator==(const const_iterator& source) {
			return this->pointer == source.pointer;
		}

		//Compare two const_iterators
		bool operator!=(const const_iterator& source) {
			return this->pointer != source.pointer;
		}
	};
#pragma endregion

	//=====     Methods of Iterator, Const Iterator     =====//
#pragma region Methods of Iterator
	//Iterator at top of Stack
	iterator begin() {
		return iterator(this->top);
	}

	//Const Iterator at top of Stack
	const_iterator begin() const {
		return const_iterator(this->top);
	}

	//Iterator at bottom of Stack
	iterator end() {
		return iterator(nullptr);
	}

	//Const Iterator at bottom of Stack
	const_iterator end() const {
		return const_iterator(nullptr);
	}
#pragma endregion
};

//==================================================
//=====     Overloading Operator STD::COUT     =====//
template <class datatype>
std::ostream& operator<<(std::ostream& os, const stack<datatype>& source)
{
	source.out();
	return os;
}

//==================================================
#endif	//_FISH_STACK_
