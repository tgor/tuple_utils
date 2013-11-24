#ifndef ZIP_TUPLES_H
#define ZIP_TUPLES_H

#include <tuple>
#include <type_traits>
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
 * @brief Create std::tuple of std::tuples with elements equal to elements from tuples at given positions
 * Each std::tuple in resulting std::tuple contains elements from tuples given as parameters. They are
 * constructed in such a way that index of resulting std::tuples describes which values from passed tuples will
 * they contain (e.g. tuple at index zero in result will contain all values at index zero from tuples passed).
 * Each tuple is constructed recursively from index 0 to End, where End is equal to the size of the smallest
 * tuple from parameter pack.
 * @tparam Curr - current index which will be used to get values
 * @tparam End - size of the smallest tuple passed through Tuple... parameter pack
 * @tparam Tuple... - parameter pack containing types of std::tuple's passed to tuple_utils::zip
 */
template <
        std::size_t Curr,
        std::size_t End,
        typename... Tuple
        >
struct zip_det
{
    /**
     * @brief Fill resulting std::tuple with values at given index recursively
     * Create std::tuple and fill it using pack expansion so that in one step values from all arguments are
     * used. Increment index and call itself recursively until index hits end.
     * @param tuple - arbitrary number of tuples to be zipped
     * @return tuple<tuple<get<0>(args)...>, tuple<get<1>(args)>...>,... tuple<get<N>(args)...>>
     */
    static auto go(const Tuple&... tuple)
    -> decltype(std::tuple_cat(
                            std::make_tuple(std::make_tuple(std::get<Curr>(tuple)...)),
                            zip_det<Curr + 1, End, Tuple...>::go(tuple...)
                        ))
    {
        auto one_tuple = std::make_tuple(std::get<Curr>(tuple)...);
        auto result = std::tuple_cat(std::make_tuple(one_tuple), zip_det<Curr + 1, End, Tuple...>::go(tuple...));
        return result;
    }
};

/**
 * @brief Helper struct used to limit the recursion, used when index used for zipping hits last element
 * @tparam End - size of the smallest tuple passed, used to delimit recursion
 * @tparam Tuple... - parameter pack containing types of std::tuple's passed to tuple_utils::zip
 */
template <
        std::size_t End,
        typename... Tuple
        >
struct zip_det<End, End, Tuple...>
{
    /**
     * @brief Return nested std::tuple with values from End index taken from arguments
     * After getting values at End index it stops recursion and result could be passed to tuple_utils::zip.
     * Returned value is std::tuple of std::tuples so it could be concatenated later.
     */
    static auto go(const Tuple&... tuple)
    -> decltype(std::make_tuple(std::make_tuple(std::get<End>(tuple)...)))
    {
        return std::make_tuple(std::make_tuple(std::get<End>(tuple)...));
    }
};

/**
 * @brief Proxy function used as a tag dispatcher, performs actual zipping
 * Hit only when there are no empty tuples passed to tuple_utils::zip
 */
template <
        typename First,
        typename... Rest
        >
auto zip_proxy(std::false_type, First&& first, Rest&&... rest)
-> decltype(details::zip_det<
                0,
                tsize_min<typename std::decay<First>::type, typename std::decay<Rest>::type...>::value - 1,
                First,
                Rest...
            >::go(first, rest...))
{
    constexpr std::size_t size = tsize_min<
                typename std::decay<First>::type,
                typename std::decay<Rest>::type...
            >::value - 1;

    auto result = details::zip_det<0, size, First, Rest...>::go(
                std::forward<First>(first),
                std::forward<Rest>(rest)...
            );

    return result;
}

/**
 * @brief Proxy function used as a tag dispatcher, because one or more tuples were empty it returns empty tuple
 */
template <
        typename First,
        typename... Rest
        >
std::tuple<> zip_proxy(std::true_type, First&&, Rest&&...)
{
    return std::tuple<>();
}

}//namespace details

/**
 * @brief Zip together values at corresponding indexes of arbitrary number of std::tuples
 * For each index create one std::tuple with values taken from std::tuples passed as arguments. Result
 * will contain tuples created starting from index zero up to index equal to the size of the smalles tuple
 * passed as an argument. Use tag dispatch and details::zip_proxy to check if any std::tuple given as parameter
 * is empty, if so then tuple_utils::zip should return empty std::tuple<>
 * Example:
 * @code
 *   auto result = tuple_utils::zip(make_tuple(1, 4, 2.2, "test"), make_tuple(2, 2.2, 1), make_tuple(4, 6, 9));
 *   //result is equal to tuple<tuple<int, int, int>, tuple<double, double, int>, tuple<double, int, int>>
 *   //and contain values ((1, 2, 4), ((4, 2.2, 6), (2.2, 1, 9))). Notice that value "test" from the first
 *   //tuple is not used because other tuples have smaller size than the first one.
 * @endcode
 */
template <
        typename... Tuples
        >
auto zip(Tuples&&... tuples)
-> decltype(details::zip_proxy(
                        std::integral_constant<bool, contain_empty<Tuples...>::value>(),
                        std::forward<Tuples>(tuples)...
                    ))
{
    return details::zip_proxy(
                    std::integral_constant<bool, contain_empty<Tuples...>::value>(),
                    std::forward<Tuples>(tuples)...
                );
}

/**
 * @brief Special case when no arguments are given, simply return empty std::tuple
 * @return Empty std::tuple<>
 */
std::tuple<> zip()
{
    return std::tuple<>();
}

}//namespace tuple_utils

#endif // FOLD_TUPLES_H
