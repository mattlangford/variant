#pragma once

namespace detail
{
template <int i, typename T, typename T1>
constexpr int get_matching_type_impl()
{
    return -1;
}

template <int i, typename T, typename T1, typename T2, typename... Ts>
constexpr int get_matching_type_impl()
{
    return std::is_same<T, T1>::value ? i : get_matching_type_impl<i + 1, T, T2, Ts...>();
}

template <typename T, typename... Ts>
constexpr int get_matching_type()
{
    return get_matching_type_impl<0, T, Ts...>();
}
}
