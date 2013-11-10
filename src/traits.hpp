#ifndef TRAITS_HPP
#define TRAITS_HPP

namespace tuple_utils
{

template <typename... Args>
struct common_type_var;

template <
        typename T
        >
struct common_type_var<T>
{
    using type = T;
};

template <
        typename T,
        typename Y
        >
struct common_type_var<T, Y>
{
    using type = typename std::common_type<T, Y>::type;
};

template <
        typename T,
        typename... Args
        >
struct common_type_var<T, Args...>
{
    using type = typename std::common_type<T, typename common_type_var<Args...>::type>::type;
};

} // namespace tuple_utils

#endif // TRAITS_HPP
