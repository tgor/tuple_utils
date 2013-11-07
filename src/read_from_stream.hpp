#ifndef READ_FROM_STREAM_HPP
#define READ_FROM_STREAM_HPP

#include <tuple>
#include <iostream>

template <typename T, typename ...Args>
struct TupleFromStream
{

    std::tuple<T, Args...> read(const std::istream &stream);
};

#endif // READ_FROM_STREAM_HPP
