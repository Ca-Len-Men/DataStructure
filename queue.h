#ifndef _FISH_QUEUE_
#define _FISH_QUEUE_

#include<iostream>
//==================================================
//==========          Queue          ==========
template <class data>
class queue {
	//=====     Sub Class     =====//
#pragma region Sub Class
	class node {
	public:
		data info;
		node* next;

		node(const data& var) : info{ var }, next{ nullptr } {}
	};
#pragma endregion

	//=====     Attributes     =====//
#pragma region Attributes
	node* head;
	node* tail;
	size_t size;
#pragma endregion

public:
	//=====     Constructors and Destructor     =====//
#pragma region Constructors and Destructor
	queue() : head{ nullptr }, tail{ nullptr }, size{ 0u } {}

	queue(const queue& qu)
	{
		if (qu.head == nullptr)
		{
			this->head = this->tail = nullptr;
			size = 0u;
			return;
		}

		this->head = this->tail = new node(qu.head->info);
		this->size = qu.size;
		for (node* i = qu.head->next; i != nullptr; i = i->next, this->tail = this->tail->next)
			this->tail->next = new node(i->info);
	}

	queue(queue&& source) noexcept :
		head{ source.head }, tail{ source.tail }, size{ source.size }
	{ source.head = source.tail = nullptr; }

	~queue()
	{
		this->clear();
	}
#pragma endregion

	//=====     Methods     =====//
#pragma region Methods
	//If Queue contain value valthan return true
	bool contain(const data& val) const
	{
		for (node* i = this->head; i; i = i->next)
			if (i->info == val)
				return true;
		return false;
	}

	//Pop the value on the top of Queue
	data pop()
	{
		data temp = this->head->info;
		node* p = this->head;

		this->head = this->head->next;
		if (this->head == nullptr)
			this->tail = nullptr;
		--this->size;

		delete p;
		return temp;
	}

	//Push the value on the top of Queue
	void push(const data& val)
	{
		if (this->head == nullptr)
		{
			this->head = this->tail = new node(val);
			this->size = 1u;
			return;
		}

		this->tail->next = new node(val);
		this->tail = this->tail->next;
		++this->size;
	}

	//Writting on the console
	void out() const
	{
		std::cout << '[';
		for (node* i = head; i; i = i->next) {
			std::cout << i->info;
			if (i->next != nullptr)
				std::cout << ", ";
		}
		std::cout << "]\n";
	}

	//Get const value at head of Queue
	const data& getHead() const {
		return this->head->info;
	}

	//Get const value at tail of Queue
	const data& getBack() const  {
		return this->tail->info;
	}

	//Swapping two Queue
	void swap(queue& qu) {
		std::swap(this->head, qu.head);
		std::swap(this->tail, qu.tail);
		std::swap(this->size, qu.size);
	}
	
	//Queue is being empty
	void clear() {
		for (this->tail = this->head; this->head != nullptr; this->tail = this->head)
		{
			this->head = this->head->next;
			delete this->tail;
		}
		this->size = 0u;
	}

	//Check Queue is empty
	bool empty() const {
		return this->head == nullptr;
	}

	//Length of Queue
	size_t length() const {
		return this->size;
	}
#pragma endregion

	//=====     Operators     =====//
#pragma region Operators
	//Check Queue is not empty
	operator bool() const {
		return this->head != nullptr;
	}

	//Copy data from other Queue
	queue& operator=(const queue& source)
	{
		if (this == &source)
			return *this;
		this->clear();

		if (source.head != nullptr)
		{
			this->head = this->tail = new node(source.head->info);
			this->size = source.size;
			for (node* i = source.head->next; i != nullptr; i = i->next, this->tail = this->tail->next)
				this->tail->next = new node(i->info);
		}
		return *this;
	}
#pragma endregion

	//=====     Iterator     =====//
#pragma region Iterator
	class iterator {
		//=====     Attributes     =====//
		node* pointer;
		friend queue;
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
			if (this->pointer != nullptr)
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
		friend queue;

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
	//Iterator at top of Queue
	iterator begin() {
		return iterator(this->head);
	}

	//Const Iterator at top of Queue
	const_iterator begin() const {
		return const_iterator(this->head);
	}

	//Iterator at bottom of Queue
	iterator end() {
		return iterator(nullptr);
	}

	//Const Iterator at bottom of Queue
	const_iterator end() const {
		return const_iterator(nullptr);
	}

	//Iterator at tail of Queue
	iterator rbegin() {
		return iterator(this->tail);
	}

	//Const Iterator at tail of Queue
	const_iterator rbegin() const {
		return const_iterator(this->tail);
	}
#pragma endregion
};

//==================================================
//=====     Overloading Operator STD::COUT     =====//
template <class datatype>
std::ostream& operator<<(std::ostream& os, const queue<datatype>& source)
{
	source.out();
	return os;
}

//==================================================
#endif	//_FISH_QUEUE_