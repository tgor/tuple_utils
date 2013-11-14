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

struct tuple_printer
{
    static std::string delim;
    static std::string lbrace;
    static std::string rbrace;

    template<
            typename CharT,
            typename Traits,
            std::size_t Start,
            std::size_t Size,
            typename Type
            >
    struct tuple_printer_det
    {
        static std::basic_ostream<CharT, Traits>& 
        execute(std::basic_ostream<CharT, Traits>& stream, const Type& tuple, std::string& delim)
        {
            stream << std::get<Start>(tuple) << delim;
            tuple_printer_det<CharT, Traits, Start + 1, Size, Type>::execute(
                stream, 
                tuple, 
                tuple_printer::delim
            );
            return stream;
        }
    };

    template <
            typename CharT,
            typename Traits,
            std::size_t Size,
            typename Type
            >
    struct tuple_printer_det<CharT, Traits, Size, Size, Type>
    {
        static std::basic_ostream<CharT, Traits>& 
        execute(std::basic_ostream<CharT, Traits>& stream, const Type& tuple, std::string&)
        {
            stream << std::get<Size>(tuple) << rbrace;
            return stream;
        }
    };
};

std::string tuple_printer::delim = ", ";
std::string tuple_printer::lbrace = "(";
std::string tuple_printer::rbrace = ")";

} //namespace details
///@endinternal

void change_delim(std::string new_delim)
{
    details::tuple_printer::delim = std::move(new_delim);
}

void change_braces(std::string new_lbrace, std::string new_rbrace)
{
    details::tuple_printer::lbrace = std::move(new_lbrace);
    details::tuple_printer::rbrace = std::move(new_rbrace);
}

template <
        typename... Args
        >
std::string to_string(const std::tuple<Args...>& tuple)
{
    std::ostringstream stream;
    stream << tuple;
    return stream.str();
}

//simple no-op for empty tuple
std::string to_string(const std::tuple<>&)
{
    return std::string();
}

} //namespace tuple_utils

template <
        typename CharT,
        typename Traits,
        typename... Args
        >
std::basic_ostream<CharT, Traits>& 
operator<< (std::basic_ostream<CharT, Traits>& stream, const std::tuple<Args...>& tuple_arg)
{
    stream << tuple_utils::details::tuple_printer::lbrace;
    
    tuple_utils::details::tuple_printer::tuple_printer_det<
        CharT, 
        Traits, 
        0, 
        sizeof...(Args) - 1, 
        std::tuple<Args...>
    >::execute(stream, tuple_arg, tuple_utils::details::tuple_printer::delim);

    return stream;
}

//simple no-op
template <
        typename CharT,
        typename Traits
        >
std::basic_ostream<CharT, Traits>& 
operator<< (std::basic_ostream<CharT, Traits>& stream, const std::tuple<>&)
{
    return stream;
}

#endif // PRINT_TUPLES_H
