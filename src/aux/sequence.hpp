#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <cstdio>
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
 *@brief Struct parametrized with variable number of std::size_t's, used only to keep those values
 *Values used as template parameters will be used at compile time by other structs
 */
template <
        std::size_t... N
        >
struct sequence
{ };

///@internal
namespace details
{

//forward declaration
template <
        std::size_t Min,
        std::size_t Step,
        std::size_t Max,
        std::size_t Curr,
        typename T = void,
        std::size_t... Args
        >
struct sequence_det;

/**
 *@brief Helper struct used by make_sequence, generates sequence by adding elements to a parameters pack
 *In each step it adds next element before the prevoius ones, starting with Max value and in each
 *step adding Last-Step until it hits Min value.
 */
template <
        std::size_t Min,
        std::size_t Step,
        std::size_t Max,
        std::size_t Curr,
        std::size_t... Tail
        >
struct sequence_det<Min, Step, Max, Curr, typename std::enable_if<(Curr <= Max)>::type, Tail...>
    : sequence_det<Min, Step, Max, Curr + Step, typename std::enable_if<(Curr <= Max)>::type, Curr + Step, Tail...>
{ };

/**
 *@brief Last recursive step of sequence_det, hit when iterating from Max to Min with Step interval
 */
template <
        std::size_t Min,
        std::size_t Step,
        std::size_t Max,
        std::size_t Curr,
        std::size_t... Tail
        >
struct sequence_det<Min, Step, Max, Curr, typename std::enable_if<not (Curr < Max)>::type, Tail...>
{
    using seq = sequence<Tail...>;
};

} //namespace details
///@endinternal

/**
 *@brief Create seqence from Min to Max with Step interval (Min, Min + Step, Min + 2*Step,... Max)
 *Default values allow to use it with only Max template parameter value so it
 *generates seqence 0, 1, 2,... Max. If there is no such X where Min + X * Step = Max then it ends
 *with an endless recursion (without 'static if'(N3613) it is impossible to check this at a compile time)
 *<- TODO: possible workaround using enable_if, check it later
 */
template <
        std::size_t Max,
        std::size_t Min = 0,
        std::size_t Step = 1
        >
using make_sequence = typename details::sequence_det<Min, Step, Max, Min, typename std::enable_if<(Min <= Max)>::type>::seq;


} //namespace tuple_utils

#endif // SEQUENCE_HPP
