#ifndef MAKE_CUSTOM_TUPLE_H
#define MAKE_CUSTOM_TUPLE_H

#include "indices.hpp"
#include <tuple>

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
 *@brief Assign value of the second argument to the first one.
 *Templated helper function implementing simple assignment. It can be expanded with parameter packet expansion which is
 *impossible for assignment operator.
 *@param left - reference to assignee
 *@param right - const reference to assignor
 */
template <typename L, typename R>
void assign(L& left, const R& right)
{
    left = right;
}

/**
 *@brief Struct to extract std::tuple types based on indices.
 *Extract std::tuple types from type template parameter Tuple based on variadic non-type parameter Indices
 */
template <
        typename Tuple,
        std::size_t ...Indices
        >
struct tupleTypeFromIndices;

/**
 *@brief Recursive step of tupleTypeFromIndices.
 */
template <
        typename Tuple,
        std::size_t First,
        std::size_t ...Indices
        >
struct tupleTypeFromIndices<Tuple, First, Indices...>
{
    static_assert(First < std::tuple_size<Tuple>::value, "Too big indice");
    using type = decltype(std::tuple_cat(
    std::declval<std::tuple<typename std::tuple_element<First, Tuple>::type>>(),
    std::declval<typename tupleTypeFromIndices<Tuple, Indices...>::type>()
    ));
};

/**
 *@brief Last recursive instantiation of tupleTypeFromIndices struct.
 */
template <
        typename Tuple,
        std::size_t BeforeLast,
        std::size_t Last
        >
struct tupleTypeFromIndices<Tuple, BeforeLast, Last>
{
    static_assert(BeforeLast < std::tuple_size<Tuple>::value && Last < std::tuple_size<Tuple>::value, "Too big indice");
    using type = std::tuple<typename std::tuple_element<BeforeLast, Tuple>::type, typename std::tuple_element<Last, Tuple>::type>;
};

template <
        typename Tuple
        >
struct tupleTypeFromIndices<Tuple>
{
    using type = std::tuple<>;
};

/**
 *@brief Fill std::tuple created by tupleTypeFromIndices with values from the base tuple.
 */
template <
        typename Tuple,
        int... Indices
        >
struct partitionTuple
{
    /** std::tuple type set by tupleTypeFromIndices. */
    using PartitionType = typename tupleTypeFromIndices<Tuple, Indices...>::type;
    /** indices pack created based on non-type template parameter Indices. */
    static constexpr auto range = IndicesFor<std::tuple_size<PartitionType>::value>();

    /**
     *@brief Create and fill custom tuple.
     *Used by the helper function make_custom_tuple which wraps part of its internals so they are invisible to the user.
     *@param indices<Is...> - indices pack used for expansion, contains sequence 0, 1, 2... N where N is the
     * number of elements in the destination
     *@param source - base tuple
     *@return destination - std::tuple with values taken from base tuple based on indices
     */
    template<unsigned... Is>
    static PartitionType part(indices<Is...>, Tuple source)
    {
        PartitionType destination;

        /* unused[] - dummy type used for parameter pack expansion at compile time. Compiler tries to fill unused, but it must first
          evaluate first coma operator operand which performs assignment. Whole operation is repeated with parameter pack expansion
          up to the last value in the indices<Is> range */
        int unused[] = {0, (assign(std::get<Is>(destination), std::get<Indices>(source)), 1)...};
        (void)unused;

        return destination;
    }
};

} //namespace details
///@endinternal

/**
 *@brief Create tuple from existing tuple based on given indices.
 *Based on the type of tuple given as an argument and indices specified as a template parameters returns
 *a std::tuple with types and values corresponding to the base tuple. It is possible to use the same indices more than once.
 *@tparam Indices - integers indicating which base tuple values are to be used in constructing custom tuple
 *@param tuple - reference to constant std::tuple
 *@return custom std::tuple
 *
 * Example Usage:
 * @code
 *    auto base_tuple = std::make_tuple(2, 4.4, "string");
 *    auto custom_tuple = tuple_util::make_custom_tuple<0, 0, 1>(base_tuple); //create std::tuple<int, int, float> custom_tuple{2, 2, 4.4};
 * @endcode
 */
template <
        int... Indices,
        typename Tuple
        >
auto make_custom_tuple(const Tuple& tuple)
-> decltype( details::partitionTuple<Tuple, Indices...>::part(details::partitionTuple<Tuple, Indices...>::range, tuple) )
{
    return details::partitionTuple<Tuple, Indices...>::part(details::partitionTuple<Tuple, Indices...>::range, tuple);
}

} //namespace tuple_utils

#endif // MAKE_CUSTOM_TUPLE_H
