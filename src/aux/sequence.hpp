#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <cstdio>
#include <type_traits>
#include <iostream>
#include "static.hpp"

/**
 * @file
 * @author
 * @version
*/

//! Utilities for tuples manipulation
namespace tuple_utils
{

//forward declaration
template <std::size_t...>
struct sequence;

/**
 *@brief Class parametrized with variable number of std::size_t's, used only to keep those values
 *Values used as template parameters will be used at compile time by other structs. Private method
 *static void print() is used for testing purposes.
 */
template <
        std::size_t I,
        std::size_t... N
        >
struct sequence<I, N...>
{
    static std::ostream& print(std::ostream& str)
    {
        str << I << " ";
        sequence<N...>::print(str);
        return str;
    }
};

/**
 *Class used by recursive call to print() method, used for testing purposes.
 */
template <
        std::size_t I
        >
struct sequence<I>
{
    static std::ostream& print(std::ostream& str)
    {
        str << I;
        return str;
    }
};

/**
 *@brief Empty sequence, useful when operating on empty tuples
 */
template <>
struct sequence<>
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
        typename,
        std::size_t... Args
        >
struct sequence_det;

/**
 *@brief Helper struct used by make_sequence, generates sequence by adding elements to a parameters pack
 *In each step it adds next element after the prevoius ones, starting with Min value and in each
 *step adding Step until it exceeds Max value. std::enable_if is used to check if next step is not greater
 *than Max, if so, special case of sequence_det is used and sequence is completed.
 */
template <
        std::size_t Min,
        std::size_t Step,
        std::size_t Max,
        std::size_t Curr,
        std::size_t... Tail
        >
struct sequence_det<Min, Step, Max, Curr, typename std::enable_if<(Curr + Step < Max)>::type, Tail...>
 : sequence_det<Min, Step, Max, Curr + Step, void, Tail..., Curr + Step>
{ };

/**
 *@brief Last recursive step of sequence_det, hit when iterating from Min to Max with Step interval
 *It is used when next step is greater than Max, it is time to collect values and put them into sequence
 *parameters.
 */
template <
        std::size_t Min,
        std::size_t Step,
        std::size_t Max,
        std::size_t Curr,
        std::size_t... Tail
        >
struct sequence_det<Min, Step, Max, Curr, typename std::enable_if<(Curr + Step >= Max)>::type, Tail...>
{
 static_assert(Min <= Max, "Min is greater than Max");
 using seq = sequence<Min, Tail...>;
};

} //namespace details
///@endinternal

/**
 *@brief Create seqence from Min to Max with Step interval (Min, Min + Step, Min + 2*Step,... Max)
 *Default values allow to use it with only Max template parameter value so it
 *generates seqence 0, 1, 2,... Max. If Max is not a multiple of Min + X * Step values, then last value
 *in series less than Max is added to the sequence
 */
template <
        int Max,
        int Min = 0,
        int Step = 1
        >
struct make_sequence
{
    using type = typename details::sequence_det<Min, Step, Max, Min, void>::seq;
};

/**
 *@brief Special case when Min == Max, generate empty sequence
 */
template <
        int Max,
        int Step
        >
struct make_sequence<Max, Max, Step>
{
    using type = sequence<>;
};

} //namespace tuple_utils

#endif // SEQUENCE_HPP
