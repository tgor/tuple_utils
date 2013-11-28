#ifndef REVERSE_TUPLE_H
#define REVERSE_TUPLE_H

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
 * @brief Helper function used by tuple_utils::reverse to reverse a tuple using given sequence.
 * Using given reverse sequence and variadic pack expansion create new std::tuple with elements in
 * reverse order comparing to the orginal tuple passed to tuple_utils::reverse.
 * @tparam Tuple - type of std::tuple passed to tuple_utils::reverse as an argument
 * @tparam RevSqe... - sequence N-1, N-2, N-3,..., 0 where N is equal to std::tuple_size<Tuple>::value
 */
template <
        typename Tuple,
        int... RevSeq
        >
auto reverse_det(Tuple&& tuple, sequence<RevSeq...>)
-> decltype(std::make_tuple(std::get<RevSeq>(std::forward<Tuple>(tuple))...))
{
    return std::make_tuple(std::get<RevSeq>(std::forward<Tuple>(tuple))...);
}

}//namespace details

/**
 * @brief Take one std::tuple as an argument and retun std::tuple with elements in reverse order.
 * Take std::tuple<A, B, C,... Z> and return std::tuple<Z,... , C, B, A>. Create sequence
 * N-1, N-2, N-3,..., 0 where N is equal to std::tuple_size<Tuple>::value. Using this sequence reserse
 * tuple in helper function details::reverse_det.
 *
 * Example:
 * @code
 *   auto result = tuple_utils::reverse(std::make_tuple(6, 3, "asd", 4.4));
 *   //result is std::tuple<double, const char*, int, int> with values (4.4, "asd", 3, 6)
 * @endcode
 */
template <
        typename Tuple
        >
auto reverse(Tuple&& tuple)
-> decltype(details::reverse_det(
                std::forward<Tuple>(tuple),
                typename make_sequence<-1, size_bare<Tuple>::value - 1, -1>::type()
            ))
{
    return details::reverse_det(
                    std::forward<Tuple>(tuple),
                    typename make_sequence<-1, size_bare<Tuple>::value - 1, -1>::type()
                );
}

}//namespace tuple_utils

#endif // REVERSE_TUPLE_H
