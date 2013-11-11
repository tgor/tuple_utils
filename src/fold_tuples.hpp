#ifndef FOLD_TUPLES_H
#define FOLD_TUPLES_H

#include <tuple>
#include <type_traits>
#include "make_custom_tuple.hpp"
#include "traits.hpp"

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

//Forward declaration
template <
        typename Y,
        typename Z
        >
typename std::common_type<Y, Z>::type add_helper(const Y& beforelast, const Z& last);

/**
 *@brief Add unknown number of elements together
 *Helper function called with at least one element. Recursively calculates sum of all elements
 *@return sum of the first element with the result of a recursive add_helper call, type of the
 *returned value is recursively searched with std::common_type (with helper type of
 *common_type_var defined in traits.hpp
 */
template <
        typename F,
        typename... R
        >
typename common_type_var<F, R...>::type add_helper(const F& first, const R&... rest)
{
    return first + add_helper<R...>(rest...);
}

/**
 *@brief Last recursive call for add_helper function.
 *@return sum of two elements, type is deduced with std::common_type
 */
template <
        typename Y,
        typename Z
        >
typename std::common_type<Y, Z>::type add_helper(const Y& beforelast, const Z& last)
{
    return beforelast + last;
}

/**
 *@brief Special case when tuple_utils::fold is invoked with only one argument
 *@return return value of argument given
 */
template <
        typename T
        >
T add_helper(const T& arg)
{
    return arg;
}

/**
 *@brief Helper function used by the tuple_utils::fold
 *Assigns values in unrolled loop based on current index, used recursively
 *@tparam Begin - starting index, should be 0
 *@tparam End - value of the std::tuple_size<X>::value, ends loop unrolling
 *@tparam Args... - types of the elements stored by folded tuples
 */
template <
        std::size_t Begin,
        std::size_t End,
        typename... Args
        >
struct tuple_fold_det
{
    /**
     *Each call assigns sum of tuple elements given at the index Begin to the resulting tuple.
     *Then increment index value and recursively call fold_helper
     */
    template <
            template<typename...> class Res,
            template<typename...> class... T
            >
    static void fold_helper(Res<Args...>& result, const Res<Args...>& first, const T<Args...>&... rest)
    {
        tuple_utils::details::assign(std::get<Begin>(result), add_helper(std::get<Begin>(first), std::get<Begin>(rest)...));
        tuple_fold_det<Begin + 1, End, Args...>::fold_helper(result, first, rest...);
    }
};

/**
 *@brief Last call of unrolled tuple_fold_det struct
 *Partial template specialization used to call fold_helper for the one past last tuple element.
 */
template <
        std::size_t End,
        typename... Args
        >
struct tuple_fold_det<End, End, Args...>
{
    /**
     *@brief Called for the std::tuple_size<X>::value index, which is one past last tuple element, thus in this case fold_helper is no-op
     */
    template <
            template<typename...> class Res,
            template<typename...> class... T
            >
    static void fold_helper(Res<Args...>&, const Res<Args...>&, const T<Args...>&...)
    { }
};

} //namespace details
///@endinternal

/**
 *@brief Folds few tuples into one by adding elements on each position from those tuples.
 *Used to produce std::tuple in which each element is equal to the sum of corresponding elements from std::tuples given as an arguments
 *@tparam Tup - std::tuple type given as a first argument
 *@tparam Res... - unknown number of std::tuples types given as other arguments
 *@tparam Args... - types of the elements stored by each tuple
 *@param first - std::tuple given as a first argument
 *@param rest - unknown number of std::tuples, must be exactly the same type as in the 'first' argument
 *@return std::tuple in which each position is the sum of a values from the same positions from the tuples given as arguments
 *
 * Example Usage:
 * @code
 *    auto tuple_arg1 = std::make_tuple(2, 4.4, "hello ");
 *    auto tuple_arg2 = std::make_tuple(3, 0.1, "world");
 *    auto result = tuple_utils::fold(tuple_arg1, tuple_arg2); // result is equal to std::tuple<int, double, const char*> result {5, 4.5, "hello world}
 * @endcode
 */
template <
        template<typename...> class Tup,
        template<typename...> class... Res,
        typename... Args
        >
Tup<Args...> fold(Tup<Args...>& first, Res<Args...>&... rest)
{
    constexpr static auto range = std::tuple_size<Tup<Args...>>::value;
    Tup<Args...> result;
    details::tuple_fold_det<0, range, Args...>::fold_helper(result, first, rest...);
    return result;
}

} //namespace tuple_utils

#endif // FOLD_TUPLES_H
