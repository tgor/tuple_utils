#ifndef MERGE_TUPLES_H
#define MERGE_TUPLES_H

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

//Forward declaration
template <typename...>
struct merge_tuples_type;

/**
 *@brief Obtain type of few std::tuples merged together
 *For example merge of std::tuple<int, float, double>, std::tuple<std::string> and std::tuple<long, short>
 *will yield type std::tuple<int, float, double, std::string, long, short>
 */
template <
        typename... Args1,
        typename... Args2,
        typename... Rest
        >
struct merge_tuples_type<std::tuple<Args1...>, std::tuple<Args2...>, Rest...>
{
    using type = typename merge_tuples_type<std::tuple<Args1..., Args2...>, Rest...>::type;
};

/**
 *@brief Get type of two std::tuples merged together
 *Last recursive step of merge_tuples_type<>::type where type member is std::tuple of types from
 *both tuples given as parameters
 */
template <
        typename... Args1,
        typename... Args2
        >
struct merge_tuples_type<std::tuple<Args1...>, std::tuple<Args2...>>
{
    using type = std::tuple<Args1..., Args2...>;
};

//forward declaration
template <typename...>
struct merge_tuples_det;


template <
        typename... Args1,
        typename... Args2,
        typename... RestArgs
        >
struct merge_tuples_det<std::tuple<Args1...>, std::tuple<Args2...>, RestArgs...>
{
    using Ret = typename merge_tuples_type<std::tuple<Args1...>, std::tuple<Args2...>, RestArgs...>::type;

    template <
            std::size_t ResultBegin,
            std::size_t ArgBegin,
            std::size_t ArgEnd
            >
    struct merge_unroll
    {
        template <
                typename... ResArgs,
                typename... VarArgs
                >
        static void go(std::tuple<ResArgs...>& result, const std::tuple<VarArgs...>& arg)
        {
            std::get<ResultBegin>(result) = std::get<ArgBegin>(arg);
            merge_unroll<ResultBegin + 1, ArgBegin + 1, ArgEnd>::go(result, arg);
        }
    };

    template <
            std::size_t ResultBegin,
            std::size_t ArgEnd
            >
    struct merge_unroll<ResultBegin, ArgEnd, ArgEnd>
    {
        template <
                typename... ResArgs,
                typename... VarArgs
                >
        static void go(std::tuple<ResArgs...>&, const std::tuple<VarArgs...>&)
        { }
    };

    template <
            typename T,
            std::size_t ResultBegin
            >
    struct merge_helper
    {
        template <
                typename... ResArgs
                >
        static void go(const std::tuple<ResArgs...>&)
        {}

        template <
                typename... ResArgs,
                typename... Args,
                typename... Rest
                >
        static void go(std::tuple<ResArgs...>& result, const std::tuple<Args...>& tuple1, const Rest&... rest)
        {
            merge_unroll<ResultBegin, 0, sizeof...(Args)>::go(result, tuple1);
            merge_helper<std::tuple<ResArgs...>, ResultBegin + sizeof...(Args)>::go(result, rest...);
        }

    };
};

} //namespace details
///@endinternal

template <
        typename... Args1,
        typename... Args2,
        typename... Rest
        >
auto merge(const std::tuple<Args1...>& tuple1, const std::tuple<Args2...>& tuple2, const Rest&... rest)
-> typename details::merge_tuples_det<std::tuple<Args1...>, std::tuple<Args2...>, Rest...>::Ret
{
    using Ret = typename details::merge_tuples_det<std::tuple<Args1...>, std::tuple<Args2...>, Rest...>::Ret;
    Ret result;
    
    details::merge_tuples_det<
        std::tuple<Args1...>, 
        std::tuple<Args2...>, 
        Rest...
    >::template merge_helper<Ret, 0>::go(result, tuple1, tuple2, rest...);
    
    return result;
}

/**
  *@brief Overload for calling tuple_utils::merge with only one argument
  *Special case which returns only a copy of the given argument
  */
template <
        typename... Args
        >
std::tuple<Args...> merge(std::tuple<Args...> arg)
{
    return arg;
}

} //namespace tuple_utils

#endif // MERGE_TUPLES_H
