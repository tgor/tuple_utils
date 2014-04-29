#ifndef EXPLODE_TUPLE_H
#define EXPLODE_TUPLE_H

#include <tuple>
#include <type_traits>
#include "aux/sequence.hpp"
#include "aux/traits.hpp"

/**
 * @file
 * @author
 * @version
*/

//! Utilities for tuples manipulation
namespace tuple_utils
{

///@internal
namespace details
{

/**
 * @brief Helper function which calls function 'func' for 'tuple' elements
 * Use pack expansion to get each tuple element and forward those values into function 'func'
 */
template <
        typename Func,
        typename Tuple,
        std::size_t... Seq
        >
auto explode_det(Func&& func, Tuple&& tuple, sequence<Seq...>)
-> decltype(func(std::forward<typename std::tuple_element<Seq, Tuple>::type>(std::get<Seq>(tuple))...))
{
    return func(std::forward<typename std::tuple_element<Seq, Tuple>::type>(std::get<Seq>(tuple))...);
}

}//namespace details

/**
 * @brief Explode contents of std::tuple so they could be used as arguments by a function 'func'
 * Take function f with argument types X, Y, ..., Z and std::tuple<X, Y, ..., Z> and call f with
 * arguments values extracted from the given tuple.
 * @tparam Func - type of function which will be called for tuple elements
 * @tparam Tuple - std::tuple type passed as an argument
 * @return Result of function f called for values from inside argument tuple.
 *
 * Example:
 * @code
 * auto lambda = [](float i, int j){ return j * 2 + i; };
 * auto result = tuple_utils::explode(lambda, std::make_tuple(4.4, 5)); //result == 14.4f
 * @endcode
 */
template <
        typename Func,
        typename Tuple
        >
auto explode(Func&& func, Tuple&& tuple)
-> decltype(details::explode_det(
                std::forward<Func>(func),
                std::forward<typename std::decay<Tuple>::type>(tuple),
                typename make_sequence<size_bare<Tuple>::value>::type()
            ))
{
    return details::explode_det(
                std::forward<Func>(func),
                std::forward<typename std::decay<Tuple>::type>(tuple),
                typename make_sequence<size_bare<Tuple>::value>::type()
            );
}

}//namespace tuple_utils

#endif // EXPLODE_TUPLE_H
