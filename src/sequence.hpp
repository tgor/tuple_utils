#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <cstdio>
#include "static.hpp"

namespace tuple_utils
{

//sequences provided to enchance SEQUENCE functionality
template <
        unsigned... N
        >
struct sequence
{ };

//forward declaration
template <
        unsigned... Args
        >
struct sequence_det;

template <
        unsigned Min,
        unsigned Max,
        unsigned Step,
        unsigned... Tail
        >
struct sequence_det<Min, Step, Max, Tail...> : sequence_det<Min, Step, Max-Step, Max-Step, Tail...>
{ };

template <
        unsigned Min,
        unsigned Step,
        unsigned... Tail
        >
struct sequence_det<Min, Step, Min, Tail...>
{
    using seq = sequence<Tail...>;
};

template <
        unsigned  Max,
        unsigned  Min = 0,
        unsigned  Step = 1
        >
using make_sequence = typename sequence_det<Min, Step, Max>::seq;


} //namespace tuple_utils

#endif // SEQUENCE_HPP
