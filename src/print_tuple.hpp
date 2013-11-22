#ifndef PRINT_TUPLES_H
#define PRINT_TUPLES_H

#include <tuple>
#include <iostream>
#include <string>
#include <sstream>

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
 * @brief Helper struct used by operator<<(std::basic_ostream, std::tuple)
 * Contains method for putting tuple into stream and static members which are used for formatting 
 */ 
struct tuple_printer
{
    static std::string delim;
    static std::string lbrace;
    static std::string rbrace;

    /**
     * @brief Struct used to go through each element in tuple and put them into the stream
     * @tparam Start - print tuple at this position, should start from 0 and increase by 1 in each step
     * @tparam Size - end printing tuple at this position, should be equal to the value returned by 
     * std::tuple_size<decltype(tuple)>::value
     */ 
    template<
            typename CharT,
            typename Traits,
            std::size_t Start,
            std::size_t Size,
            typename Type
            >
    struct tuple_printer_det
    {
        /**
         * @brief Recursively input all std::tuple element values into resulting stream
         * Each value from tuple is put into stream with delimiter set by change_delimiter
         * function. Recursively called until hit last element in tuple
         */ 
        static std::basic_ostream<CharT, Traits>& 
        execute(std::basic_ostream<CharT, Traits>& stream, const Type& tuple)
        {
            stream << std::get<Start>(tuple) << tuple_printer::delim;
            tuple_printer_det<CharT, Traits, Start + 1, Size, Type>::execute(stream, tuple);
            return stream;
        }
    };

    /**
     * @brief Used to stop recursion when stepping over tuple in the execute method
     */ 
    template <
            typename CharT,
            typename Traits,
            std::size_t Size,
            typename Type
            >
    struct tuple_printer_det<CharT, Traits, Size, Size, Type>
    {
        /**
         * @brief Last recursive step - send value of the last tuple element to the stream
         */ 
        static std::basic_ostream<CharT, Traits>& 
        execute(std::basic_ostream<CharT, Traits>& stream, const Type& tuple)
        {
            stream << std::get<Size>(tuple);
            return stream;
        }
    };
};

std::string tuple_printer::delim = ", ";
std::string tuple_printer::lbrace = "(";
std::string tuple_printer::rbrace = ")";

} //namespace details
///@endinternal

/**
 * @brief Change delimiter used to separate printed elements of std::tuple 
 * Delimiter is not limited to just one sign, could contain whole string instead.
 * Initial value is set to ", "
 */ 
void change_delim(std::string new_delim)
{
    details::tuple_printer::delim = std::move(new_delim);
}

/**
 * @brief Change limiting braces used when printing std::tuple
 * Braces are not limited to just one sign, could contain whole strings instead
 * Initial value for the left brace is set to "(" and for the right brace ")"
 */ 
void change_braces(std::string new_lbrace, std::string new_rbrace)
{
    details::tuple_printer::lbrace = std::move(new_lbrace);
    details::tuple_printer::rbrace = std::move(new_rbrace);
}

} //namespace tuple_utils

/**
 * @brief Print std::tuple with  an arbitrary number of elements to the given stream
 * Printed sequence starts with left brace [default value "("] and ends with right brace 
 * [default value ")"], each value is separated by a delimiter [default value ", "]. Those 
 * values can be changed with helper functions change_braces and change_delim.
 * @param str - reference to a stream which will be used as an output
 * @param tuple_arg - std::tuple which will be printed to the stream
 * @return reference to stream filled with content of tuple_arg
 * 
 * Example Usage:
 * @code
 *   auto tup = std::make_tuple(1, 2, "hello", "world", 6.01);
 *   std::cout << tup << std::endl; //prints "(1, 2, hello, world, 6.01)"
 *   tuple_utils::change_braces("[", "]");
 *   tuple_utils::change_delim(" ");
 *   std::cout << tup; //prints [1 2 hello world 6.01]
 * @endcode
 */ 
template <
        typename CharT,
        typename Traits,
        typename... Args
        >
std::basic_ostream<CharT, Traits>& 
operator<< (std::basic_ostream<CharT, Traits>& str, const std::tuple<Args...>& tuple_arg)
{
    str << tuple_utils::details::tuple_printer::lbrace;
    
    tuple_utils::details::tuple_printer::tuple_printer_det<
        CharT, 
        Traits, 
        0, 
        sizeof...(Args) - 1, 
        std::tuple<Args...>
    >::execute(str, tuple_arg);

    str << tuple_utils::details::tuple_printer::rbrace;

    return str;
}

/**
 * @brief For empty std::tuple do not print anything, just return stream as-is
 */ 
template <
        typename CharT,
        typename Traits
        >
std::basic_ostream<CharT, Traits>& 
operator<< (std::basic_ostream<CharT, Traits>& stream, const std::tuple<>&)
{
    return stream;
}

namespace tuple_utils
{

/**
 * @brief Return std::string with the content of std::tuple given as an argument
 * Returned std::string starts with left brace [default value "("] and ends with right brace
 * [default value ")"], each value is separated by a delimiter [default value ", "]. Those
 * values can be changed with helper functions change_braces and change_delim.
 */
template <
        typename... Args
        >
std::string to_string(const std::tuple<Args...>& tuple)
{
    std::ostringstream stream;
    stream << tuple;
    return stream.str();
}

/**
 * @brief For empty std::tuple return empty std::string
 */
std::string to_string(const std::tuple<>&)
{
    return std::string();
}

} //namespace tuple_utils

#endif // PRINT_TUPLES_H
