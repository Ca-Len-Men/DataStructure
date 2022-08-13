#ifndef _FISH_LIMITLIST_
#define _FISH_LIMITLIST_

#include<iostream>

/*===================================================
Author : Ca Len Men	(or Fish Climb Tree)			=
Stack : stack<typename>					            =
Queue : queue<typename>					            =
===================================================*/

/* Queue, Stack is a Singely Linked List.
You must have copy constructor for datatype.
You must have operator<, operator== for your keytype.*/

namespace dsa
{
	//##################################################
	//==========          Base List          ==========//
	template <class datatype>
	class baselist {
	protected:
		//=====     Sub Class     =====//
#pragma region Sub Class
		class node {
		public:
			datatype info;
			node* next;
			node(const datatype& var) : info{ var }, next{ nullptr } {};
		};
#pragma endregion

		//=====     Attributes     =====//
#pragma region Attributes
		node* head;
		size_t size;
#pragma endregion

		//=====     Constructors and Destructor     =====//
#pragma region Constructors and Destructor
		baselist() : head(nullptr), size(0u) {}

		baselist(node* pointer, size_t length) : head(pointer), size(length) {}

		baselist(node* pointer) : head(nullptr), size(0u)
		{
			if (pointer == nullptr)
				return;

			this->head = new node(pointer->info);
			this->size = 1u;
			pointer = pointer->next;
			for (node* i = this->head; pointer != nullptr; i = i->next, pointer = pointer->next)
				i->next = new node(pointer->info);
		}

		virtual ~baselist()
		{
			this->clear();
		}
#pragma endregion

	public:
		//=====     Methods     =====//
#pragma region Methods
	//True if Base List contains value
		virtual bool contains(const datatype& val) const final
		{
			for (node* i = this->head; i != nullptr; i = i->next)
				if (i->info == val)
					return true;
			return false;
		}

		//Push the value on the top of Base List
		virtual void push(const datatype& val) = 0;

		//Pop the value on the top of Base List
		virtual datatype pop() = 0;

		//Try pop the value on the top of Base List
		virtual bool try_pop(datatype& get) = 0;

		//Get const value at top of Base List
		virtual const datatype& top() const final {
			return this->head->info;
		}

		//Clear all element in Base List
		virtual void clear() {
			for (node* i = this->head; this->head != nullptr; i = this->head)
			{
				this->head = this->head->next;
				delete i;
			}
			this->size = 0u;
		}

		//Writting on the console
		virtual void out() const final
		{
			std::cout << '[';
			for (node* i = this->head; i; i = i->next)
			{
				std::cout << i->info;
				if (i->next != nullptr)
					std::cout << ", ";
			}
			std::cout << "]\n";
		}

		//Check Base List is empty
		virtual bool empty() const final {
			return this->head == nullptr;
		}

		//Length of Base List
		virtual size_t len() const final {
			return this->size;
		}
#pragma endregion

		//=====     Operators     =====//
#pragma region Operators
	//Check Stack is not empty
		virtual operator bool() const final {
			return this->head != nullptr;
		}
#pragma endregion

		//=====     Iterator     =====//
#pragma region Iterator
		class iterator {
			//=====     Attributes     =====//
			node* pointer;
			friend baselist;

			//=====     Constructors     =====//
			iterator(node* ptr) : pointer(ptr) {}

		public:
			iterator(const iterator& source) : pointer(source.pointer) {}

			//=====     Operators     =====//

			//Check iterator not null
			operator bool() const {
				return this->pointer != nullptr;
			}

			//Get value of item
			datatype& operator*() {
				return this->pointer->info;
			}

			//Get index ( type data* ) of item
			datatype* operator->() {
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
			bool operator==(const iterator& source) const {
				return this->pointer == source.pointer;
			}

			//Compare two iterators
			bool operator!=(const iterator& source) const {
				return this->pointer != source.pointer;
			}
		};
#pragma endregion

		//=====     Const Iterator     =====//
#pragma region Const Iterator
		class const_iterator {
			//=====     Attributes     =====//
			const node* pointer;
			friend baselist;

			//=====     Constructors     =====//
			const_iterator(const node* ptr) : pointer(ptr) {}

		public:
			const_iterator(const const_iterator& source) : pointer(source.pointer) {}

			//=====     Operators     =====//

			//Check const_iterator not null
			operator bool() const {
				return this->pointer != nullptr;
			}

			//Get const value of item
			const datatype& operator*() const {
				return this->pointer->info;
			}

			//Get index ( type const data* ) of item
			const datatype* operator->() const {
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
			bool operator==(const const_iterator& source) const {
				return this->pointer == source.pointer;
			}

			//Compare two const_iterators
			bool operator!=(const const_iterator& source) const {
				return this->pointer != source.pointer;
			}
		};
#pragma endregion

		//=====     Methods of Iterator, Const Iterator     =====//
#pragma region Methods of Iterator
	//Iterator at top of Base List
		iterator begin() {
			return iterator(this->head);
		}

		//Const Iterator at top of Base List
		const_iterator begin() const {
			return const_iterator(this->head);
		}

		//Iterator at bottom of Base List
		iterator end() {
			return iterator(nullptr);
		}

		//Const Iterator at bottom of Base List
		const_iterator end() const {
			return const_iterator(nullptr);
		}
#pragma endregion
	};

	//##################################################
	//==========          Stack          ==========//
	template <class datatype>
	class stack : public baselist<datatype> {
		using base = baselist<datatype>;
		using node = base::node;

	public:
		//=====     Constructors and Destructor     =====//
#pragma region Constructors and Destructor
		stack() : base() {}

		stack(const stack& st) : base(st.head) {}

		stack(stack&& source) noexcept : base(source.head, source.size)
		{
			source.top = nullptr;
		}

		~stack() {}
#pragma endregion

		//=====     Methods     =====//
#pragma region Methods
	//Push the value on the top of Stack
		void push(const datatype& val) override
		{
			if (this->head == nullptr)
			{
				this->head = new node(val);
				this->size = 1u;
				return;
			}

			node* p = new node(val);
			p->next = this->head;
			this->head = p;
			++this->size;
		}

		//Pop the value on the top of Stack
		datatype pop() override
		{
			datatype res(this->head->info);
			node* p = this->head;
			this->head = this->head->next;
			--this->size;
			delete p;
			return res;
		}

		//Try pop the value on the top of Stack
		virtual bool try_pop(datatype& get) override {
			if (this->head == nullptr)
				return false;

			get = pop();
			return true;
		}

		//Swapping two Stack
		void swap(stack& st) {
			std::swap(this->head, st.head);
			std::swap(this->size, st.size);
		}
#pragma endregion

		//=====     Operators     =====//
#pragma region Operators
	//Copy data from other Stack
		stack& operator=(const stack& source)
		{
			if (this == &source)
				return *this;
			base::clear();

			if (source.head != nullptr)
			{
				this->head = new node(source.head->info);
				this->size = source.size;
				for (node* i = this->head, *j = source.head->next; j != nullptr; i = i->next, j = j->next)
					i->next = new node(j->info);
			}
			return *this;
		}

		//Copy data from other Stack
		stack& operator=(stack&& source) noexcept {
			base::clear();
			this->head = source.head;
			this->size = source.size;
			source.head = nullptr;
		}

		// Multiple push value
		stack& operator<<(const datatype& value) {
			push(value);
			return *this;
		}

		// Multiple pop value
		stack& operator>>(datatype& result) {
			result = pop();
			return *this;
		}
#pragma endregion
	};

	//##################################################
	//==========          Queue          ==========//
	template <class datatype>
	class queue : public baselist<datatype> {
		using base = baselist<datatype>;
		using node = base::node;
		node* tail;

	public:
		//=====     Constructors and Destructor     =====//
#pragma region Constructors and Destructor
		queue() : base(), tail(nullptr) {}

		queue(const queue& qu) : base(qu.head), tail(nullptr)
		{
			if (qu.head == nullptr)
				return;

			for (this->tail = this->head; this->tail->next != nullptr; this->tail = this->tail->next);
		}

		queue(queue&& source) noexcept : base(source.head, source.size), tail(source.tail)
		{
			source.head = source.tail = nullptr;
		}

		~queue() {}
#pragma endregion

		//=====     Methods     =====//
#pragma region Methods
	//Push the value on the top of Queue
		void push(const datatype& val) override
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

		//Pop the value on the top of Queue
		datatype pop() override
		{
			datatype temp = this->head->info;
			node* p = this->head;
			this->head = this->head->next;
			if (this->head == nullptr)
				this->tail = nullptr;
			--this->size;
			delete p;
			return temp;
		}

		//Pop the value on the top of Queue
		bool try_pop(datatype& get) override
		{
			if (this->head == nullptr)
				return false;

			get = pop();
			return true;
		}

		//Get const value at tail of Queue
		const datatype& bottom() const {
			return this->tail->info;
		}

		//Swapping two Queue
		void swap(queue& qu) {
			std::swap(this->head, qu.head);
			std::swap(this->tail, qu.tail);
			std::swap(this->size, qu.size);
		}

		//Queue is being empty
		void clear() override {
			base::clear();
			this->tail = nullptr;
		}
#pragma endregion

		//=====     Operators     =====//
#pragma region Operators
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

		//Copy data from other Stack
		queue& operator=(queue&& source) noexcept {
			this->clear();
			this->head = source.head;
			this->tail = source.tail;
			this->size = source.size;
			source.head = source.tail = nullptr;
		}

		// Multiple push value
		queue& operator<<(const datatype& value) {
			push(value);
			return *this;
		}

		// Multiple pop value
		queue& operator>>(datatype& result) {
			result = pop();
			return *this;
		}
#pragma endregion
	};

	//==================================================//
	//=====     Overloading Operator STD::COUT     =====//
	template <class datatype>
	std::ostream& operator<<(std::ostream& os, const stack<datatype>& source)
	{
		source.out();
		return os;
	}

	template <class datatype>
	std::ostream& operator<<(std::ostream& os, const queue<datatype>& source)
	{
		source.out();
		return os;
	}
}
//==================================================
#endif	// _FISH_LIMITLIST_