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
 *@brief Traits for getting one common type from a list of types
 *Internally uses and works like std::common_type, but allows variable number of parameters
 */
template <
        typename T,
        typename... Args
        >
struct common_type_var : private static_
{
    using type = typename std::common_type<T, typename common_type_var<Args...>::type>::type;
};

/**
 *@brief Last step of recursive common_type_var<>::type, for two types gives simple std::common_type<>::type
 */
template <
        typename T,
        typename Y
        >
struct common_type_var<T, Y> : private static_
{
    using type = typename std::common_type<T, Y>::type;
};

/**
 *@brief Special case when common_type_var is parameterized with only one type
 */
template <
        typename T
        >
struct common_type_var<T> : private static_
{
    using type = T;
};

/**
 *@brief Obtains smallest size for the number of given tuples
 */
template <typename T, typename... Args>
struct tsize_min : private static_
{
    static constexpr std::size_t value = std::tuple_size<T>::value < tsize_min<Args...>::value
        ? std::tuple_size<T>::value : tsize_min<Args...>::value;
};

/**
 *@brief Last step of recursive tsize_min<>::value, value is equal to the size of smaller tuple
 */
template <typename T, typename Y>
struct tsize_min<T, Y> : private static_
{
    static constexpr std::size_t value = std::tuple_size<T>::value < std::tuple_size<Y>::value
        ? std::tuple_size<T>::value : std::tuple_size<Y>::value;
};

/**
 *@brief Special case when tsize_min is parameterized with only one type
 *Derives from std::integral_constant to get value member of type std::size_t with value equal to std::tuple_size<>::value
 */
template <typename T>
struct tsize_min<T> : std::integral_constant<std::size_t, std::tuple_size<T>::value>, private static_
{ };

} // namespace tuple_utils

#endif // TRAITS_HPP
