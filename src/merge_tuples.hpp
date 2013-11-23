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
 * @brief Obtain type of few std::tuples merged together
 * For example merge of std::tuple<int, float, double>, std::tuple<std::string> and std::tuple<long, short>
 * will yield type std::tuple<int, float, double, std::string, long, short>
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
 * @brief Get type of two std::tuples merged together
 * Last recursive step of merge_tuples_type<>::type where type member is std::tuple of types from
 * both tuples given as parameters
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

/**
 *@brief Helper struct used by the tuple_utils::merge to fill std::tuple which is returned as a result.
 */
template <
        typename... Args1,
        typename... Args2,
        typename... RestArgs
        >
struct merge_tuples_det<std::tuple<Args1...>, std::tuple<Args2...>, RestArgs...>
{
    using Ret = typename merge_tuples_type<std::tuple<Args1...>, std::tuple<Args2...>, RestArgs...>::type;

    /**
    * @brief For each tuple from merge function arguments copy its content to the resulting std::tuple
    * Called recursively with the recursion depth equal to the size of currently processed std::tuple
    * (i.e. ArgEnd value). In each step copy one value from processed std::tuple to the result and call
    * merge_unroll for the next element, until the end of the currently processed std::tuple.
    * @tparam ResultCurr - current position in result-from-merge std::tuple, each time updated by 1
    * @tparam ArgBegin - current position in the current std::tuple given as merge argument
    * @tparam ArgEnd - size of one of current std::tuple given as merge argument, used to stop unrolling
    */
    template <
            std::size_t ResultCurr,
            std::size_t ArgBegin,
            std::size_t ArgEnd
            >
    struct merge_unroll
    {
        /**
        * @brief Copy one value from arg to the result, called recursively.
        * Copy value from the ArgBegin position from arg to the result at the ResultCurr position.
        * Recursively called for the next element, so it increases both ResultCurr and ArgBegin
        */
        template <
                typename... ResArgs,
                typename... VarArgs
                >
        static void go(std::tuple<ResArgs...>& result, const std::tuple<VarArgs...>& arg)
        {
            std::get<ResultCurr>(result) = std::get<ArgBegin>(arg);
            merge_unroll<ResultCurr + 1, ArgBegin + 1, ArgEnd>::go(result, arg);
        }
    };

    /**
    * @brief Last step in the loop unroll, ends processing of one of the merge function arguments
    * Hit when currently used position is the same as the size of the argument
    * @tparam ResultCurr - position at which result should be inserted
    * @tparam ArgEnd - size of the processed argument, indicates last loop unroll step
    */
    template <
            std::size_t ResultCurr,
            std::size_t ArgEnd
            >
    struct merge_unroll<ResultCurr, ArgEnd, ArgEnd>
    {
        /**
        * @brief Last recursive call, all values are copied so it does nothing
        */
        template <
                typename... ResArgs,
                typename... VarArgs
                >
        static void go(std::tuple<ResArgs...>&, const std::tuple<VarArgs...>&)
        { }
    };

    /**
    * @brief Helper struct which is used to fill std::tuple returned by the merge function
    * Recursively call merge_unroll for each std::tuple given as argument to the merge function. In
    * merge_unroll std::tuple which will be returned is filled piece by piece.
    * @tparam ResType - type of result which will be returned by merge function
    * @tparam ResultCurr - position in result at which merge_unroll will add values from merge arguments
    */
    template <
            typename ResType,
            std::size_t ResultCurr
            >
    struct merge_helper
    {
        /**
        * @brief Last step of overloaded go(std::tuple<ResArgs...>&, std::tuple<Args...>&, Rest&...) function
        * Invoked with only one std::tuple (result). There are no arguments left, do nothing and end recursion
        */
        static void go(const ResType&)
        {}

        /**
        * @brief Function that copies all values from arguments to the result
        * Recursively unroll one std::tuple and copy its value, then recursively process and unroll next arguments
        * until there is no argument left
        * @param result - std::tuple which will be returned by the tuple_utils::merge
        * @param tuple1, rest... - arguments of tuple_utils::merge, used to fill result with values
        */
        template <
                typename... Args,
                typename... Rest
                >
        static void go(ResType& result, const std::tuple<Args...>& tuple1, const Rest&... rest)
        {
            merge_unroll<ResultCurr, 0, sizeof...(Args)>::go(result, tuple1);
            merge_helper<ResType, ResultCurr + sizeof...(Args)>::go(result, rest...);
        }
    };
};

} //namespace details
///@endinternal

/**
 * @brief Merge few std::tuples into one using their values
 * Takes any number of heterogenous std::tuples and returns an aggregate std::tuple that contains each
 * value from the given arguments, in order.
 * @param tuple1, tuple2, rest... - at least two possibly heterogenous std::tuples
 * @return std::tuple with values from all std::tuples passed as arguments
 *
 * Example Usage:
 * @code
 *    auto t1 = std::make_tuple(1.1, 2, '3');
 *    auto t2 = std::make_tuple(4, 5);
 *    auto t3 = std::make_tuple("hello", "world");
 *    auto res = merge(t1, t2, t2); //res is a std::tuple<float, int, char, int, int, const char*, const char*>
 *    //with values {1.1, 2, '3', 4, 5, "hello", "world"};
 * @endcode
 */
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
std::tuple<Args...> merge(const std::tuple<Args...>& arg)
{
    return arg;
}

} //namespace tuple_utils

#endif // MERGE_TUPLES_H
