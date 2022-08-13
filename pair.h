#ifndef _FISH_PAIR_
#define _FISH_PAIR_

#include <iostream>

/*===================================================
Author : Ca Len Men	(or Fish Climb Tree)			=
Pair : pair<keytype, valuetype>			            =
===================================================*/

/* Pair is the object have 2 attributes, using for Map and Hash Map.*/

namespace dsa
{
	//==================================================//
	//==========          Pair          ==========//
	template <class keytype, class valuetype>
	class pair {
	public:
		//=====     Attributes     =====//
#pragma region Attributes
		keytype key;
		valuetype value;
#pragma endregion

		//=====     Constructors and Destructor     =====//
#pragma region Constructors and Destructor
		pair(const keytype& _key, const valuetype& _value) : key(_key), value(_value) {}

		pair(const pair& source) : key(source.key), value(source.value) {}
#pragma endregion

		//=====     Methods     =====//
#pragma region Methods
	// Swap two Pair
		void swap(pair& source) {
			std::swap(this->key, source.key);
			std::swap(this->value, source.value);
		}

		// Writting on Console
		void out() const {
			std::cout << '(' << this->key << ", " << this->value << ")\n";
		}
#pragma endregion

		//=====     Operators     =====//
#pragma region Operators
	// Copy data from other Pair
		pair& operator=(const pair& source) {
			if (this == &source)
				return *this;
			this->key = source.key;
			this->value = source.value;
			return *this;
		}
#pragma endregion
	};

	//==================================================//
	//=====     Overloading Operator STD::COUT     =====//
	template <class keytype, class valuetype>
	std::ostream& operator<<(std::ostream& os, const pair<keytype, valuetype>& source) {
		source.out();
		return os;
	}
}
//==================================================//
#endif	// _FISH_PAIR_