#ifndef _FISH_HEAP_
#define _FISH_HEAP_
#include "queue.h"
#include "arraylist.h"

/*
*******************************************************
					HEAP LIBRARY					  *
- There have : Min/Max Heap, Solid Heap.			  *
Syntax :											  *
	+ Min Heap : minheap<typename> heap;			  *
	+ Max Heap : maxheap<typename> heap;			  *
	+ Min Solid Heap : minheaparr<typename> heap;	  *
	+ Max Solid Heap : maxheaparr<typename> heap;	  *
*******************************************************
*/

//**************************************************
//==========          BINARY HEAP          ==========
template <class data>
class binaryheap {
protected:
	//=====     Sub Class     =====//
#pragma region Sub Class
	class heapnode {
	public:
		data info;
		heapnode* left, * right;

		heapnode(const data& item) :
			info{ item }, left{ nullptr }, right{ nullptr } {}
	};
#pragma endregion

	//=====     Protected Methods     =====//
#pragma region Protected Methods
	//Compare Function
	virtual bool compare(const data& item1, const data& item2) const = 0;

	//Heapify Function
	void heapify(heapnode* node) {
		if (node == nullptr)
			return;
		data temp = node->info;

		for (heapnode* i = node;; node = i) {
			if (node->left && !compare(temp, node->left->info))
				i = node->left;
			if (node->right && !compare(temp, node->right->info)
				&& !compare(node->left->info, node->right->info))
				i = node->right;

			if (i == node) {
				node->info = temp;
				break;
			} else
				node->info = i->info;
		}
	}
	
	//Push Binary Heap use recursive
	void pushRecursive(heapnode*& refNode, const data& item, dynamicarray<bool>& st) {
		if (refNode == nullptr) {
			refNode = new heapnode(item);
			return;
		}

		heapnode*& refChild(st[st.length() - 1u] ? refNode->right : refNode->left);
		st.popBack();
		pushRecursive(refChild, item, st);
		if (!compare(refNode->info, refChild->info))
			std::swap(refNode->info, refChild->info);
	}
	
	//Pop Binary Heap use recursive
	bool popSecur(data& get) {
		if (this->size == 0u)
			return false;

		get = root->info;
		dynamicarray<bool> st = getRoad(this->size);
		heapnode** refNode = &this->root;
		while (st) {
			refNode = st[st.length() - 1] ? &(*refNode)->right : &(*refNode)->left;
			st.popBack();
		}
		root->info = (*refNode)->info;
		delete (*refNode);
		*refNode = nullptr;
		heapify(this->root);
		--this->size;
		return true;
	}
	
	//Road move to leaf node
	dynamicarray<bool> getRoad(size_t length) const {
		dynamicarray<bool> arr;
		for (; length > 1u; length >>= 1)	//length / 2
			arr.pushBack(length % 2);
		return arr;
	}

	//Clear binary tree use recursive
	void clearRecursive(heapnode* node) {
		if (node == nullptr)
			return;
		clearRecursive(node->left);
		clearRecursive(node->right);
		delete node;
	}

	//Clopy binary tree use recursive
	void copyRecursive(heapnode*& refNode, heapnode* nodeSource) {
		if (nodeSource == nullptr)
			return;
		refNode = new heapnode(nodeSource->info);
		copyRecursive(refNode->left, nodeSource->left);
		copyRecursive(refNode->right, nodeSource->right);
	}
#pragma endregion

	//=====     Attributes     =====//
#pragma region Attributes
	heapnode* root;
	size_t size;
#pragma endregion

public:
	//=====     Constructors and Destructor     =====//
#pragma region Constructors and Destructor
	binaryheap() : root{ nullptr }, size{ 0u }{}

	virtual ~binaryheap() {
		clearRecursive(this->root);
	}
#pragma endregion

	//=====     Methods     =====//
#pragma region Methods
	//Push Binary Heap
	void push(const data& item) {
		dynamicarray<bool> st = this->getRoad(++this->size);
		this->pushRecursive(this->root, item, st);
	}

	//Push Binary Heap
	template <class anyIterator>
	void push(anyIterator begin, anyIterator end)
	{
		for (; begin != end; ++begin)
			push(*begin);
	}

	//Pop Binary Heap
	data pop() {
		data temp;
		this->popSecur(temp);
		return temp;
	}

	//Try pop Binary Heap
	bool tryPop(data& get) {
		return this->popSecur(get);
	}

	//Binary Heap being empty
	void clear() {
		clearRecursive(this->root);
		this->root = nullptr;
		this->size = 0u;
	}

	//Writting on Console
	void out() const {
		if (this->root == nullptr) {
			std::cout << "[]\n";
			return;
		}
		heapnode* node;
		queue<heapnode*> qu;
		qu.push(this->root);

		std::cout << '[';
		while (qu) {
			node = qu.pop();
			if (node->left)
				qu.push(node->left);
			if (node->right)
				qu.push(node->right);
			std::cout << node->info;
			if (qu)
				std::cout << ", ";
		}
		std::cout << "]\n";
	}
	
	//Check Heap is empty
	bool empty() const {
		return root == nullptr;
	}

	//Length of Heap
	size_t length() const {
		return size;
	}
#pragma endregion

	//=====     Operators     =====//
#pragma region Operators
	operator bool() const {
		return this->root != nullptr;
	}
#pragma endregion

	//=====     Static Function     =====//
#pragma region Static Function

	static void binsort(data* arr, int n) {
		for (int i = n / 2 - 1; i >= 0; i--)
			binheapify(arr, n, i);

		for (int i = n - 1; i > 0; i--) {
			std::swap(arr[0], arr[i]);
			binheapify(arr, i, 0);
		}
	}
	static void binheapify(data* arr, int n, int idx) {
		int temp = arr[idx], l, r;
		for (int i = idx;; idx = i) {
			l = idx * 2 + 1;
			r = l + 1;
			
			if (l < n && temp < arr[l])
				i = l;
			if (r < n && temp < arr[r] && arr[l] < arr[r])
				i = r;

			if (i == idx) {
				arr[i] = temp;
				break;
			}else
				arr[idx] = arr[i];
		}
	}
	static void tersort(data* arr, int n) {
		for (int i = (n - 2) / 3; i >= 0; i--)
			terheapify(arr, n, i);

		for (int i = n - 1; i > 0; i--) {
			std::swap(arr[0], arr[i]);
			terheapify(arr, i, 0);
		}
	}
	static void terheapify(data* arr, int n, int idx) {
		data temp(arr[idx]), max;
		int l, r, m;

		for (int i = idx;; idx = i) {
			l = idx * 3 + 1;
			m = l + 1;
			r = l + 2;
			max = temp;

			if (l < n && max < arr[l]) {
				i = l;
				max = arr[l];
			}

			if (m < n && max < arr[m]) {
				i = m;
				max = arr[m];
			}

			if (r < n && max < arr[r])
				i = r;

			if (i == idx) {
				arr[i] = temp;
				break;
			} else
				arr[idx] = arr[i];
		}
	}

#pragma endregion

};

//**************************************************
//==========          MAX HEAP          ==========
template <class data>
class maxheap : public binaryheap<data> {
	using base = binaryheap<data>;

	//=====     Private Methods     =====//
#pragma region Private Methods
	bool compare(const data& item1, const data& item2) const override {
		return item1 >= item2;
	}
#pragma endregion

public:
	//=====     Constructors and Destructor     =====//
#pragma region Constructors and Destructor
	maxheap() : base() {}

	template <class anyIterator>
	maxheap(anyIterator begin, anyIterator end) : base()
	{ base::push(begin, end); }

	maxheap(const maxheap& source) : base()
	{
		this->size = source.size;
		base::copyRecursive(this->root, source.root);
	}

	maxheap(maxheap&& source) noexcept : base()
	{
		this->root = source.root;
		this->size = source.size;
		source.root = nullptr;
	}

	~maxheap() { }
#pragma endregion

	//=====     Methods     =====//
#pragma region Methods
	//Swapping two Binary Heap
	void swap(maxheap& source) {
		std::swap(this->root, source.root);
		std::swap(this->size, source.size);
	}
#pragma endregion

	//=====     Operators     =====//
#pragma region Operators
	//Copy data from other Binary Heap
	maxheap& operator=(const maxheap& source) {
		if (this == &source)
			return *this;

		base::clear();
		this->size = source.size;
		base::copyRecursive(this->root, source.root);
	}

	//Copy data from other Binary Heap
	maxheap& operator=(maxheap&& source) noexcept {
		base::clear();
		this->root = source.root;
		this->size = source.size;
		source.root = nullptr;
	}
#pragma endregion

};

//**************************************************
//==========          MIN HEAP          ==========
template <class data>
class minheap : public binaryheap<data> {
	using base = binaryheap<data>;

	//=====     Private Methods     =====//
#pragma region Private Methods
	bool compare(const data& item1, const data& item2) const override {
		return item1 <= item2;
	}
#pragma endregion

public:
	//=====     Constructors and Destructor     =====//
#pragma region Constructors and Destructor
	minheap() : base() {}

	template <class anyIterator>
	minheap(anyIterator begin, anyIterator end) : base()
	{
		base::push(begin, end);
	}

	minheap(const minheap& source) : base()
	{
		this->size = source.size;
		base::copyRecursive(this->root, source.root);
	}

	minheap(minheap&& source) noexcept : base()
	{
		this->root = source.root;
		this->size = source.size;
		source.root = nullptr;
	}

	~minheap() { }
#pragma endregion

	//=====     Methods     =====//
#pragma region Methods
	//Swapping two Binary Heap
	void swap(minheap& source) {
		std::swap(this->root, source.root);
		std::swap(this->size, source.size);
	}
#pragma endregion

	//=====     Operators     =====//
#pragma region Operators
	//Copy data from other Binary Heap
	minheap& operator=(const minheap& source) {
		if (this == &source)
			return *this;

		base::clear();
		this->size = source.size;
		base::copyRecursive(this->root, source.root);
	}

	//Copy data from other Binary Heap
	minheap& operator=(minheap&& source) noexcept {
		base::clear();
		this->root = source.root;
		this->size = source.size;
		source.root = nullptr;
	}
#pragma endregion
};

//==================================================
//=====     Overloading Operator STD::COUT     =====//
template <class data>
std::ostream& operator<<(std::ostream& os, const maxheap<data>& heap) {
	heap.out();
	return os;
}

template <class data>
std::ostream& operator<<(std::ostream& os, const minheap<data>& heap) {
	heap.out();
	return os;
}
//==================================================
#endif	//_FISH_HEAP_
