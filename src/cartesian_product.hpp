#ifndef CARTESIAN_PRODUCT_H
#define CARTESIAN_PRODUCT_H

#include <cstdlib>
#include <type_traits>
#include <iostream>
#include <tuple>
#include "aux/sequence.hpp"
#include "merge_tuples.hpp"

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
 * @brief Glue value of arbitrary type T with std::tuple's passed as arguments.
 * Simply creates a std::tuple from 'value' and uses tuple_utils::merge to merge
 * all arguments into one std::tuple
 */
template <
        typename T,
        typename... Args,
        typename... Rest
        >
auto glue(const T& value, const std::tuple<Args...>& tuple, const Rest&... rest)
-> decltype(tuple_utils::merge(std::make_tuple(value), tuple, rest...))
{
    return tuple_utils::merge(std::make_tuple(value), tuple, rest...);
}

/**
 * @brief Glue two values together into std::tuple.
 * Behaves in exactly the same way as std::make_tuple, needed by the tuple_utils::c_product
 */
template <
        typename T,
        typename Y
        >
auto glue(const T& x, const Y& y)
-> decltype(std::make_tuple(x, y))
{
    return std::make_tuple(x, y);
}

/**
 * @brief Combine two values from two tuples together.
 * Combine the value at position I from the first argument with the value at position J from the
 * second argument. If first argument is std::tuple and second argument is std::tuple of std::tuples
 * then it glues value from the first argument to std::tuple at position J from the second argument.
 * Those two scenarios could be represented as follows (make_tuple from std):
 * @code
 * c_product_one<0,0>(make_tuple(1,2), make_tuple(3,4)); // results in std::tuple<int,int>(1,3)
 * c_product_one<0,0>(make_tuple(1,2), make_tuple(make_tuple(31, 41), make_tuple(32,42)); //results
 * //in std::tuple<int,int,int>(1,31,41)
 * @endcode
 */
template <
        int I,
        int J,
        typename... Args1,
        typename... Args2
        >
auto c_product_one(const std::tuple<Args1...>& x, const std::tuple<Args2...>& y)
-> decltype(glue(std::get<I>(x), std::get<J>(y)))
{
    return glue(std::get<I>(x), std::get<J>(y));
}

/**
 * @brief Combine value given at position I from the first tuple with each value from the second tuple.
 * Use sequence Seq2 equal to <0, 1,... , sizeof...(Args2)> to call c_product_one multiple times (with pack
 * expansion). On each time value at position I from the first tuple is combined with next value from the
 * second tuple. Whole operation creates sizeof...(Args2) tuples which are aggregated into one std::tuple,
 * so the type of returned value is equal to std::tuple of std::tuple's.
 *
 * Example:
 * @code
 * auto res = c_product_line<0>(std::make_tuple(1,2), std::make_tuple(3,4,5));
 * //res is equal to std::tuple<std::tuple<int, int>, std::tuple<int, int>, std::tuple<int, int>>
 * //with values ((1,3), (1,4), (1,5))
 * @endcode
 */
template <
        int I,
        int... Seq2,
        typename... Args1,
        typename... Args2
        >
auto c_product_line(const std::tuple<Args1...>& x, const std::tuple<Args2...>& y, sequence<Seq2...>)
-> decltype(std::make_tuple(c_product_one<I, Seq2>(x, y)...))
{
    return std::make_tuple(c_product_one<I, Seq2>(x, y)...);
}

/**
 * @brief Return Cartesian product of two std::tuples.
 * For each value from the first argument combine it with each value from the second argument and return
 * std::tuple with results. Use sequence Seq1 equal to <0, 1,... , sizeof...(Args1)> to call c_product_line
 * multiple times (with pack expansion). Each call to c_product_line will combine one value from the first
 * argument with each value from the second one.
 *
 * Example:
 * @code
 * auto res = c_product_bin(std::make_tuple(1,2), std::make_tuple(3,4));
 * //res is equal to tuple<tuple<int, int>, tuple<int, int>, tuple<int, int>, tuple<int, int>>
 * //with values ((1,3), (1,4), (2,3), (2,4))
 * @endcode
 */
template <
        int... Seq1,
        typename... Args1,
        typename... Args2
        >
auto c_product_bin(sequence<Seq1...>, const std::tuple<Args1...>& x, const std::tuple<Args2...>& y)
-> decltype(std::tuple_cat(c_product_line<Seq1>(x, y, typename make_sequence<sizeof...(Args2)>::type())...))
{
    return std::tuple_cat(c_product_line<Seq1>(x, y, typename make_sequence<sizeof...(Args2)>::type())...);
}

/**
 * @brief Obtain type of value returned by Cartesian product of N std::tuple's.
 * Recursively determine type of Cartesian product of type resulted by Cartesian product of the last
 * before-last arguments and third-to-last value. Stop when there are only two arguments.
 */
template <
        typename Tuple1,
        typename Tuple2,
        typename... Rest
        >
struct c_product_type
{
    using type = decltype(c_product_bin(
        std::declval<typename make_sequence<std::tuple_size<Tuple1>::value>::type>(),
        std::declval<Tuple1>(),
        std::declval<typename c_product_type<Tuple2, Rest...>::type>()
    ));
};

/**
 * @brief Obtain type of value returned by Cartesian product of two std::tuple's.
 * Used as a last recursive step in process of obtaining return type of Cartesian
 * product of N std::tuple's
 */
template <
        typename Tuple1,
        typename Tuple2
        >
struct c_product_type<Tuple1, Tuple2>
{
    using type = decltype(c_product_bin(
        std::declval<typename make_sequence<std::tuple_size<Tuple1>::value>::type>(),
        std::declval<Tuple1>(),
        std::declval<Tuple2>()
    ));
};

} //namespace details

/**
 * @brief Calculate value of Cartesian product of one std::tuple.
 * Simply returns value of the given argument. Used as a last step by tuple_utils::c_product
 * invoked for more than one std::tuple
 */
template <
        typename... Args1
        >
auto c_product(const std::tuple<Args1...>& x)
-> std::tuple<Args1...>
{
    return x;
}

/**
 * @brief Calculate n-ary Cartesian product over n std::tuple's.
 * Given n std::tuples T1, T2, T3, ..., Tn it calculates (T1 x (T2 x (T3 x (... x (T(n-1) x Tn)))))
 * where Ti x Tj is calculated by details::c_product_bin.
 *
 * Example:
 * @code
 *   auto x = std::make_tuple(6, 3);
 *   auto y = std::make_tuple("xxx", 5.3);
 *   auto z = std::make_tuple(7, -2);
 *   auto res = c_product(x, y, z); //res is std::tuple of std::tuples containing ((6, xxx, 7), (6, xxx, -2),
 *   // (6, 5.3, 7), (6, 5.3, -2), (3, xxx, 7), (3, xxx, -2), (3, 5.3, 7), (3, 5.3, -2))
 * @endcode
 */
template <
        typename... Args1,
        typename... Args2,
        typename... Rest
        >
auto c_product(const std::tuple<Args1...>& x, const std::tuple<Args2...>& y, const Rest&... rest)
//-> decltype(details::c_product_bin(typename make_sequence<sizeof...(Args1)>::type(), x, c_product(y, rest...)))
//decltype don't work with recursive function invocation, this issue has been addressed and will
//be fixed in upcoming C++ standards, therefore c_product_type had to be introduced
-> typename details::c_product_type<std::tuple<Args1...>, std::tuple<Args2...>, Rest...>::type
{
    return details::c_product_bin(typename make_sequence<sizeof...(Args1)>::type(), x, c_product(y, rest...));
}

} //namespace tuple_utils

#endif // CARTESIAN_PRODUCT_H
