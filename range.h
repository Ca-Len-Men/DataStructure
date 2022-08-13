#ifndef _FISH_RANGE_
#define _FISH_RANGE_

#include<iostream>

/*===================================================
Author : Ca Len Men (or Fish Climb Tree)			=
Range : range							            =
===================================================*/

namespace dsa
{
	//##################################################
	//==========          RANGE          ==========//
	class range {
		int start, finish, step;
	public:
		//=====     Constructors     =====//
#pragma region Constructors
		range(int _end) : start(0), finish(_end), step(1) {}
		range(int _start, int _end) : start(_start), finish(_end), step(1) {}
		range(int _start, int _end, int _step) : start(_start), finish(_end), step(_step) {}
		range(const range& source) : start(source.start), finish(source.finish), step(source.step) {}
#pragma endregion

		//=====     Methods     =====//
#pragma region Methods
		void out() const {
			std::cout << '(' << this->start << ", "
				<< this->finish << ", " << this->step << ')';
		}
#pragma endregion

		//=====     Operators     =====//
#pragma region Operators
		range& operator=(const range& source) {
			this->start = source.start;
			this->finish = source.finish;
			this->step = source.step;
			return *this;
		}
#pragma endregion

		//=====     Iterator     =====//
#pragma region Iterator
		class iterator {
			int start, end, step;
		public:
			iterator(int _start, int _end, int _step) : start(_start), end(_end), step(_step) {}

			void out() const {
				std::cout << '(' << this->start << ", "
					<< this->end << ", " << this->step << ')';
			}

			int& operator*() {
				return this->start;
			}

			bool operator!=(const iterator& source) {
				return this->start != source.start;
			}

			iterator& operator++() {
				this->start += step;
				return *this;
			}

			iterator& operator=(const iterator& source) {
				this->start = source.start;
				this->end = source.end;
				this->step = source.step;
				return *this;
			}
		};
#pragma endregion

		//=====     Methods of Iterator     =====//
#pragma region Iterator
		iterator begin() {
			return iterator(this->start, this->finish, this->step);
		}

		iterator end() {
			int dist = this->finish - this->start;
			int val = this->step - (dist % this->step);
			if (dist % this->step == 0)
				val = 0;
			return iterator(this->start + dist + val, this->finish, this->step);
		}
#pragma endregion
	};

	//==========          Overloading operator<< with std::cout           ==========//
	std::ostream& operator<<(std::ostream& os, const range& source) {
		source.out();
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const range::iterator& iter) {
		iter.out();
		return os;
	}
}
//**************************************************
#endif	// _FISH_RANGE_