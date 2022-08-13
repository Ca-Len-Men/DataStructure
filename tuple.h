#ifndef _FISH_TUPLE_
#define _FISH_TUPLE_

#include <iostream>

/*===================================================
Author : Ca Len Men	(or Fish Climb Tree)			=
Tuple : tuple<typename ...>				            =
===================================================*/

/* Tuple is the struct object.
Attributes of Tuple is const value, can't change value of Tuple.*/

namespace dsa
{
    //##################################################
    //==========          TUPLE          ==========//
    template <typename... Rest>
    struct tuple {
        void convert() const {}
        void out() const {}
        bool empty() const {
            return true;
        }
    };
    
    //##################################################
    //==========          TUPLE          ==========//
    template<typename Type, typename... Rest>
    struct tuple<Type, Rest...> {               // Class parameter pack
        const Type first;
        const tuple<Rest...> rest;              // Parameter pack expansion

        tuple(const Type& first_value, const Rest& ... r) : first(first_value), rest(r...) {}

        bool empty() const {
            return false;
        }

        void out() const {
            std::cout << first;
            if (rest.empty() == false)
                std::cout << ", ";
            rest.out();
        }

        void convert(Type& ref, Rest& ... refs) const
        {
            ref = first;
            rest.convert(refs...);
        }

        size_t len() const
        {
            return sizeof...(Rest) + 1u;
        }
    };

    //==========          Access element in Tuple          ==========//

    template<size_t idx, typename Type>
    struct GetHelper;

    template<typename Type, typename... Rest>
    struct GetHelper<0u, tuple<Type, Rest...>> {
        static const Type& get(const tuple<Type, Rest...>& data) {
            return data.first;
        }
    };

    template<size_t idx, typename Type, typename... Rest>
    struct GetHelper<idx, tuple<Type, Rest...>> {
        static const auto& get(const tuple<Type, Rest...>& data) {
            return GetHelper<idx - 1, tuple<Rest...>>::get(data.rest);
        }
    };

    template<size_t idx, template <typename...> class tuple, typename... Rest>
    const auto& get(const tuple<Rest...>& t) {
        return GetHelper<idx, tuple<Rest...>>::get(t);
    }

    //==========          Overloading operator<< with std::cout           ==========//
    template <typename... Rest>
    std::ostream& operator<<(std::ostream& os, const tuple<Rest...>& tup)
    {
        std::cout << '(';
        tup.out();
        std::cout << ')';
        return os;
    }
}
//**************************************************
#endif  // _TUPLE_