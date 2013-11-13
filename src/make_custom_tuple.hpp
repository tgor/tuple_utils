#ifndef MAKE_CUSTOM_TUPLE_H
#define MAKE_CUSTOM_TUPLE_H

#include "aux/sequence.hpp"
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
 *@brief Struct to extract std::tuple types based on sequence.
 *Extract std::tuple types from type template parameter Tuple based on variadic non-type parameter Sequence
 */
template <
        typename Tuple,
        std::size_t... Sequence
        >
struct tupleTypeFromSequence;

/**
 *@brief Recursive step of tupleTypeFromSequence.
 */
template <
        typename Tuple,
        std::size_t First,
        std::size_t... Sequence
        >
struct tupleTypeFromSequence<Tuple, First, Sequence...>
{
    static_assert(First < std::tuple_size<Tuple>::value, "Too big indice");
    using type = decltype(std::tuple_cat(
    std::declval<std::tuple<typename std::tuple_element<First, Tuple>::type>>(),
    std::declval<typename tupleTypeFromSequence<Tuple, Sequence...>::type>()
    ));
};

/**
 *@brief Last recursive instantiation of tupleTypeFromSequence struct.
 */
template <
        typename Tuple,
        std::size_t BeforeLast,
        std::size_t Last
        >
struct tupleTypeFromSequence<Tuple, BeforeLast, Last>
{
    static_assert(BeforeLast < std::tuple_size<Tuple>::value && Last < std::tuple_size<Tuple>::value, "Too big indice");
    using type = std::tuple<typename std::tuple_element<BeforeLast, Tuple>::type, typename std::tuple_element<Last, Tuple>::type>;
};

/**
 *@brief Special case for calling make_custom_tuple without any indices (i.e. requesting empty tuple)
 */
template <
        typename Tuple
        >
struct tupleTypeFromSequence<Tuple>
{
    using type = std::tuple<>;
};

/**
 *@brief Fill std::tuple created by tupleTypeFromSequence with values from the base tuple.
 */
template <
        typename Tuple,
        int... Sequence
        >
struct partitionTuple
{
    /** std::tuple type set by tupleTypeFromSequence. */
    using PartitionType = typename tupleTypeFromSequence<Tuple, Sequence...>::type;
    /** sequence pack created based on non-type template parameter Sequence. */
    static constexpr auto range = typename make_sequence<std::tuple_size<PartitionType>::value>::type();

    /**
     *@brief Create and fill custom tuple.
     *Used by the helper function make_custom_tuple which wraps part of its internals so they are invisible to the user.
     *@param sequence<Is...> - sequence pack used for expansion, contains sequence 0, 1, 2... N where N is the
     * number of elements in the destination
     *@param source - base tuple
     *@return destination - std::tuple with values taken from base tuple based on sequence
     */
    template<unsigned... Is>
    static PartitionType part(sequence<Is...>, Tuple source)
    {
        PartitionType destination;

        /* unused[] - dummy type used for parameter pack expansion at compile time. Compiler tries to fill unused, but it must first
          evaluate first coma operator operand which performs assignment. Whole operation is repeated with parameter pack expansion
          up to the last value in the sequence<Is> range */
        int unused[] = {0, (assign(std::get<Is>(destination), std::get<Sequence>(source)), 1)...};
        (void)unused;

        return destination;
    }
};

} //namespace details
///@endinternal

/**
 *@brief Create tuple from existing tuple based on given sequence.
 *Based on the type of tuple given as an argument and sequence specified as a template parameters returns
 *a std::tuple with types and values corresponding to the base tuple. It is possible to use the same sequence more than once.
 *@tparam Sequence - integers indicating which base tuple values are to be used in constructing custom tuple
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
        int... Sequence,
        typename Tuple
        >
auto make_custom_tuple(const Tuple& tuple)
-> decltype( details::partitionTuple<Tuple, Sequence...>::part(details::partitionTuple<Tuple, Sequence...>::range, tuple) )
{
    return details::partitionTuple<Tuple, Sequence...>::part(details::partitionTuple<Tuple, Sequence...>::range, tuple);
}

} //namespace tuple_utils

#endif // MAKE_CUSTOM_TUPLE_H
