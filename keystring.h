#ifndef _TRIE_
#define _TRIE_

#pragma region Include
#include<iostream>
#include<conio.h>
#pragma endregion

#pragma region Syntax
#ifndef _DEFINE_SYNTAX_
#define _DEFINE_SYNTAX_
#define FOR(i, start, end) for(int i = start; i < end; ++i)
#define RFOR(i, last, front) for(int i = last; i >= front; --i)
#define uFOR(i, start, end) for(size_t i = start; i < end; ++i)
#define uRFOR(i, last, front) for(size_t i = last; i >= front; --i)
#define line putchar('\n')
#define wait _getch()
#endif
#pragma endregion

//**************************************************
//==========          TRIE          ==========
/*===================================================
Author : Ca Len Men									=
Trie : keystring<typename>							=
==================================================*/

template <class data>
class keystring {
	//=====     Subclass     =====
#pragma region Subclass
	class node {
	public:
	#pragma region Attributes
		char crt;
		data* info;
		node* listnode;
		unsigned short size;
	#pragma endregion

		//=====     Constructors     =====
	#pragma region Constructors

		node() :
			crt{ '\0' }, info{ nullptr }, listnode{ nullptr }, size{ 0u }{}

		node(char _crt) :
			crt{ _crt }, info{ nullptr }, listnode{ nullptr }, size{ 0u }{}

		node(const node& source) :
			crt{ source.crt }, info{ source.info },
			listnode{ source.listnode }, size{ source.size }{}

	#pragma endregion

		//=====     Methods     =====
	#pragma region Methods
		//Set value
		void setvalue(const data& item) {
			if (this->info == nullptr)
				this->info = new data(item);
		}

		//Check node have value
		bool isvalue() const{
			return this->info != nullptr;
		}

		//Push node
		void add(const node& source) {
			if (this->listnode == nullptr) {
				this->listnode = new node(source);
				++this->size;
				return;
			}

			node* res = this->listnode;
			this->listnode = new node[this->size + 1u];

			uFOR(i, 0u, this->size)
				this->listnode[i] = res[i];
			this->listnode[this->size++] = source;
			delete[] res;
		}

		//Find the character
		int find(char ch) const {
			if (this->listnode != nullptr) {
				uFOR(i, 0u, this->size)
					if (ch == this->listnode[i].crt)
						return i;
			}
			return -1;
		}

		//Delete node at index
		void remove(size_t index) {
			if (index >= this->size)
				return;
			clearRecursive(this->listnode[index]);
			node* res = this->listnode;
			this->listnode = new node[this->size - 1u];

			uFOR(i, 0u, index)
				this->listnode[i] = res[i];
			uFOR(i, index + 1u, this->size)
				this->listnode[i - 1u] = res[i];
			--this->size;
			delete[] res;
		}

		//Node is leaf
		bool empty() const {
			return this->listnode == nullptr;
		}

		//Length of sub node
		size_t length() const {
			return this->size;
		}

		//Last sub node
		node& last() const {
			return this->listnode[this->size - 1];
		}

		#pragma endregion

		//=====     Operators     =====
	#pragma region Operators
		//Check node is not empty
		operator bool() const {
			return this->listnode != nullptr;
		}

		//Copy data from other node
		node& operator=(const node& source) {
			this->crt = source.crt;
			this->info = source.info;
			this->listnode = source.listnode;
			this->size = source.size;

			return *this;
		}
	#pragma endregion
	};
#pragma endregion

	//=====     Private Methods     =====
#pragma region Private Methods
	//Clear the Keystring
	static void clearRecursive(node& rootnode) {
		if (rootnode) {
			uFOR(i, 0, rootnode.size)
				clearRecursive(rootnode.listnode[i]);
			delete[] rootnode.listnode;
			rootnode.listnode = nullptr;
			rootnode.size = 0u;
		}
	}

	//Pop the pair [key, value] use recursive
	bool popRecursive(node& rootnode, const char* ch, bool& delSubNode) {
		if (*ch == '\0') {
			delSubNode = rootnode.empty();
			if (rootnode.info == nullptr)
				return false;
			delete rootnode.info;
			rootnode.info = nullptr;
			--this->size;
			return true;
		}

		size_t index = rootnode.find(*ch);
		if (index == -1)
			return false;
		if (popRecursive(rootnode.listnode[index], ch + 1, delSubNode) == false)
			return false;
		if (delSubNode)
			rootnode.remove(index);
		delSubNode = rootnode.empty();
	}

	//Copy data from other Keystring use Recursive
	void copyRecursive(node& rootnode, const node& sourcenode) {
		rootnode.crt = sourcenode.crt;
		if (sourcenode.isvalue())
			rootnode.setvalue(*sourcenode.info);
		else
			rootnode.info = nullptr;
		if (sourcenode.empty()) {
			rootnode.listnode = nullptr;
			return;
		}

		rootnode.listnode = new node[rootnode.size = sourcenode.size];
		uFOR(i, 0u, rootnode.size)
			copyRecursive(rootnode.listnode[i], sourcenode.listnode[i]);
	}

	//Writting Keystring use recursive
	void outRecursive(const node& rootnode, char* const ch, short len = 0) const{
		static size_t countItem = 0u;
		ch[len] = rootnode.crt;

		if (rootnode.isvalue())
		{
			ch[len + 1] = '\0';
			std::cout << ch << " : " << *rootnode.info;
			++countItem;
			if (countItem == this->size)
				countItem = 0u;
			else
				std::cout << ", ";
		}
		uFOR(i, 0u, rootnode.length())
			outRecursive(rootnode.listnode[i], ch, len + 1);
	}

	//Count node
	size_t countNode(const node& rootnode) const
	{
		if (rootnode.empty())
			return 1U;
		size_t sum = 0U;
		uFOR(i, 0, rootnode.size)
			sum += countNode(rootnode.listnode[i]);
		return sum + 1;
	}

#pragma endregion

	//=====     Attributes     =====
#pragma region Attributes

	node root;
	size_t size;

#pragma endregion
	
public:
	//=====     Constructors and Destructor     =====
#pragma region Constructors and Destructor
	keystring() : root{}, size { 0u } {}

	keystring(const keystring& source) : root{}, size{ source.size }
	{ copyRecursive(this->root, source.root); }

	~keystring() {
		clearRecursive(root);
	}
#pragma endregion

	//=====     Methods     =====
#pragma region Methods
	//Push the pair[key, value]
	bool push(const char* key, const data& item) {
		int len = 0, index;
		node* ptrnode = &this->root;
		for (; key[len] != '\0'; ++len) {
			index = ptrnode->find(key[len]);
			if (index == -1) {
				ptrnode->add(node(key[len]));
				index = ptrnode->size - 1u;
			}
			ptrnode = ptrnode->listnode + index;
		}

		if (ptrnode->isvalue())
			return false;
		ptrnode->setvalue(item);
		++this->size;
		return true;
	}

	//Pop the value with key
	bool pop(const char* key) {
		bool res;
		return popRecursive(this->root, key, res);
	}

	//Try set the value with key
	bool trySet(const char* key, const data& val) {
		int len = 0, index;
		node* ptrnode = &this->root;
		while (key[len] != '\0') {
			index = ptrnode->find(key[len++]);
			if (index == -1)
				return false;
			ptrnode = ptrnode->listnode + index;
		}
		*ptrnode->info = val;
		return true;
	}

	//If keystring contain this key than return true
	bool contains(const char* key) const {
		int len = 0, index;
		const node* ptrnode = &this->root;
		while (key[len] != '\0') {
			index = ptrnode->find(key[len++]);
			if (index == -1)
				return false;
			ptrnode = ptrnode->listnode + index;
		}
		return true;
	}

	//Swapping two Keystring
	void swap(keystring& source) {
		std::swap(this->size, source.size);
		std::swap(this->root.size, source.root.size);
		std::swap(this->root.listnode, source.root.listnode);
	}

	//Keystring begin empty
	void clear() {
		clearRecursive(this->root);
		this->size = 0u;
	}

	//Writting on the console
	void out() const {
		char res[100];
		std::cout << '[';
		uFOR(i, 0, this->root.length())
			outRecursive(this->root.listnode[i], res);
		std::cout << "]\n";
	}

	//Check the Kystring is empty
	bool empty() const {
		return this->size == 0u;
	}

	//Length of Keystring
	size_t length() const {
		return this->size;
	}

#pragma endregion

	//=====     Operators     =====
#pragma region Operators
	//Check Keystring is not empty
	operator bool() const {
		return this->size != 0u;
	}

	//Get value with key
	data& operator[](const char* key) {
		int len = 0;
		node* ptrnode = &this->root;
		while (key[len] != '\0')
			ptrnode = ptrnode->listnode + ptrnode->find(key[len++]);
		return *ptrnode->info;
	}

	//Copy data from other Keystring
	keystring& operator=(const keystring& source) {
		if (this == &source)
			return *this;

		this->clear();
		this->copyRecursive(this->root, source.root);
		this->size = source.size;
		return *this;
	}
#pragma endregion

};
//==================================================
//=====     Overloading Operator STD::COUT     =====//
template <class data>
std::ostream& operator<<(std::ostream& os, const keystring<data>& source) {
	source.out();
	return os;
}
//==================================================
#endif	//_TRIE_
