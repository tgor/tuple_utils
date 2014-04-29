#ifndef TRAITS_HPP
#define TRAITS_HPP

#include <type_traits>
#include "static.hpp"

/**
 * @file
 * @author
 * @version
*/

//! Utilities for tuples manipulation
namespace tuple_utils
{

/**
 * @brief Obtains smallest size for the number of given tuples
 */
template <typename T, typename... Args>
struct tsize_min : private static_
{
    using CT = typename std::decay<T>::type;
    static constexpr std::size_t value = std::tuple_size<CT>::value < tsize_min<Args...>::value
        ? std::tuple_size<CT>::value : tsize_min<Args...>::value;
};

/**
 * @brief Last step of recursive tsize_min<>::value, value is equal to the size of smaller tuple
 */
template <typename T, typename Y>
struct tsize_min<T, Y> : private static_
{
    using CT = typename std::decay<T>::type;
    using CY = typename std::decay<Y>::type;
    static constexpr std::size_t value = std::tuple_size<CT>::value < std::tuple_size<CY>::value
        ? std::tuple_size<CT>::value : std::tuple_size<CY>::value;
};

/**
 * @brief Special case when tsize_min is parameterized with only one type
 * Derives from std::integral_constant to get value member of type std::size_t with value equal
 * to std::tuple_size<>::value
 */
template <typename T>
struct tsize_min<T> :
        std::integral_constant<std::size_t, std::tuple_size<typename std::decay<T>::type>::value>,
        private static_
{ };

//Forward declaration
template <typename...>
struct result_of_rec;

/**
 * @brief Trait used to get return value of a recursive binary function call f(x, f(y, ...f(z1, fz2)))
 * Function f could take it's arguments by value, reference or both
 * @tparam FuncType - function type, could be function pointer, lambda or functor
 * @tparam F - first argument
 * @tparam R... - rest of the arguments, used in recursive call
 */
template <
        typename FuncType,
        typename F,
        typename... R
        >
struct result_of_rec<FuncType, F, R...> : private static_
{
    using type = decltype(std::declval<FuncType>()(
        std::declval<typename std::add_lvalue_reference<F>::type>(),
        std::declval<typename std::add_lvalue_reference<typename result_of_rec<FuncType, R...>::type>::type>()
    ));
};

/**
 * @brief Last step of result_of_rec<FuncType, F, R...>, type set to the return value of a binary function f(x,y)
 */
template <
        typename FuncType,
        typename T,
        typename Y
        >
struct result_of_rec<FuncType, T, Y> : private static_
{
    using type = decltype(std::declval<FuncType>()(
        std::declval<typename std::add_lvalue_reference<T>::type>(),
        std::declval<typename std::add_lvalue_reference<Y>::type>()
    ));
};

/**
 * @brief Get return value of unary function f(x)
 */
template <
        typename FuncType,
        typename T
        >
struct result_of_rec<FuncType, T> : private static_
{
    using type = decltype(std::declval<FuncType>()(std::declval<typename std::add_lvalue_reference<T>::type>()));
};

/**
 * @brief Check if any type passed as template parameter is empty
 */
template <
        typename T,
        typename... Rest
        >
struct contain_empty : private static_
{
    using CT = typename std::decay<T>::type;
    static constexpr bool value = !std::tuple_size<CT>::value || contain_empty<Rest...>::value;
};

/**
 * @ Check if type passed as template parameter is empty
 * Last step in recursive contain_empty check.
 */
template <
        typename T
        >
struct contain_empty<T> : private static_
{
    using CT = typename std::decay<T>::type;
    static constexpr bool value = !std::tuple_size<CT>::value;
};

/**
 * @brief Give size of bare Tuple type (stripped from cv qualifiers and references)
 */
template <
        typename Tuple
        >
struct size_bare
{
    static constexpr auto value = std::tuple_size<typename std::decay<Tuple>::type>::value;
};

} // namespace tuple_utils

#endif // TRAITS_HPP
