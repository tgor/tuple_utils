#ifndef FOLD_TUPLES_H
#define FOLD_TUPLES_H

#include <tuple>
#include <type_traits>
#include "make_custom_tuple.hpp"
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
 * @brief Determine type returned by the tuple_utils::fold
 * For each index in std::tuples taken as fold arguments set type in std::tuple type returned by fold.
 * Each type will be determined by the function used for folding and arguments types at given indexes
 * Example: fold(plus<>(), std::make_tuple(1, 2.1), std::make_tuple(3.3, 4)) will return value of type std::tuple<double, double>
 * @tparam Curr - current index which will be used for evaluation
 * @tparam Last - size of std::tuple returned by tuple_utils::fold (equal to the least size of fold arguments)
 * @tparam FuncType - function which determines the resoult type
 * @tparam Tuples... - types of tuple_utils::fold arguments
 */
template <
        std::size_t Curr,
        std::size_t Last,
        typename FuncType,
        typename... Tuples
        >
struct fold_result_type
{
    using type = decltype(std::tuple_cat(std::make_tuple(
        std::declval<typename result_of_rec<
            FuncType,
            typename std::tuple_element<Curr, typename std::decay<Tuples>::type>::type...>::type
        >()),
        std::declval<typename fold_result_type<Curr + 1, Last, FuncType, typename std::decay<Tuples>::type...>::type>()
    ));
};

/**
 * @brief Last recursive step of fold_result_type. Determine type at last postition in std::tuple returned from fold
 */
template <
        std::size_t Last,
        typename FuncType,
        typename... Tuples
        >
struct fold_result_type<Last, Last, FuncType, Tuples...>
{
    using type = decltype(std::make_tuple(std::declval<typename result_of_rec<
        FuncType,
        typename std::tuple_element<Last, Tuples>::type...>::type
    >()));
};

//Forward declaration
template <
        typename FuncType,
        typename Y,
        typename Z
        >
auto invoke_helper(FuncType f, Y& beforelast, Z& last)
-> typename result_of_rec<FuncType, Y, Z>::type;

/**
 * @brief Recursively fold arbitrary number of arguments
 * Helper function called with at least one element. For arguments x1, x2, x3..., x(N-1), xN it returns value of
 * f(x1, f(x2, f(x3, ... f(x(N-1), xN))))
 * @return fold the first element with the result of a recursive invoke_helper call using function f
 */
template <
        typename FuncType,
        typename F,
        typename... R
        >
auto invoke_helper(FuncType f, F& first, R&... rest)
-> typename result_of_rec<FuncType, F, R...>::type
{
    //without indirect x variable fold could not accept functions taking second argument by reference
    auto x = invoke_helper<FuncType, R...>(f, rest...);
    return f(first, x);
}

/**
 * @brief Last recursive call for invoke_helper function.
 * @return Result of binary function f invoked for last two arguments
 */
template <
        typename FuncType,
        typename Y,
        typename Z
        >
auto invoke_helper(FuncType f, Y& beforelast, Z& last)
-> typename result_of_rec<FuncType, Y, Z>::type
{
    return f(beforelast, last);
}

/**
 * @brief Special case when tuple_utils::fold is invoked with unary function
 * @return result of invocation of function f for the given argument
 */
template <
        typename FuncType,
        typename Y
        >
auto invoke_helper(FuncType f, Y& onlyOne)
-> typename result_of_rec<FuncType, Y>::type
{
    return f(onlyOne);
}

/**
 * @brief Helper function used by the tuple_utils::fold
 * Assigns values in unrolled loop based on current index, used recursively
 * @tparam Begin - starting index, should be 0
 * @tparam End - value of the std::tuple_size<X>::value, ends loop unrolling
 */
template <
        std::size_t Begin,
        std::size_t End
        >
struct tuple_fold_det
{
    /**
     * Each call assigns folded values of tuple elements given at the index Begin to the resulting tuple.
     * Then increment index value and recursively call fold_helper
     */
    template <
            typename FuncType,
            typename Result,
            typename... T
            >
    static void fold_helper(const FuncType& f, Result&& result, T&&... tuples)
    {
        tuple_utils::details::assign(std::get<Begin>(result), invoke_helper(f, std::get<Begin>(tuples)...));
        tuple_fold_det<Begin + 1, End>::fold_helper(
                    f,
                    std::forward<Result>(result),
                    std::forward<T>(tuples)...
        );
     }
};

/**
 * @brief Last call of unrolled tuple_fold_det struct
 * Partial template specialization used to call fold_helper for the one past last tuple element.
 */
template <
        std::size_t End
        >
struct tuple_fold_det<End, End>
{
    /**
     *@brief Called for the std::tuple_size<X>::value index, which is one past last tuple element, 
     *thus in this case fold_helper is no-op
     */
    template <
            typename FuncType,
            typename Res,
            typename... T
            >
    static void fold_helper(const FuncType&, Res&&, T&&...)
    { }
};

} //namespace details
///@endinternal

/**
 * @brief Folds few tuples into one by calling function f with arguments given on each position from those tuples.
 * Used to produce std::tuple in which each element is equal to the result of recursive invocation of function f
 * for each element from from std::tuples given as an arguments at each index
 * @tparam FuncType - type of function used for folding
 * @tparam Res... - unknown number of std::tuples types given as arguments
 * @param f - binary or unary function which will be used to fold one or more tuples
 * @param rest - unknown number of std::tuples
 * @return std::tuple in which each position is equal to the result of folding values from the same positions from
 * the tuples given as arguments
 *
 *  Example Usage:
 *  @code
 *    auto tuple_arg1 = std::make_tuple(2, 4.4, "hello ");
 *    auto tuple_arg2 = std::make_tuple(3, 1, "world");
 *    auto result = tuple_utils::fold(std::plus<>(), tuple_arg1, tuple_arg2); //std::plus<>() from C++14
 *    // result is equal to std::tuple<int, double, const char*> result {5, 5.4, "hello world}
 * @endcode
 */
template <
        typename FuncType,
        typename... Tuples
        >
auto fold(const FuncType& f, Tuples&&... args)
-> typename details::fold_result_type<0, tsize_min<Tuples...>::value - 1, FuncType, Tuples...>::type
{
    constexpr static auto range = tsize_min<Tuples...>::value;
    using ret_type = typename details::fold_result_type<0, range - 1, FuncType, Tuples...>::type;
    ret_type result;
    details::tuple_fold_det<0, range>::fold_helper(f, std::move(result), std::forward<Tuples>(args)...);
    return result;
}

} //namespace tuple_utils

#endif // FOLD_TUPLES_H
