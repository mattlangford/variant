#pragma once

///
/// Compute the max of a set of integer template parameters
///

namespace detail
{
template<int T>
constexpr int max()
{
    return T;
}

template<int T, int T2, int... Ts>
constexpr int max()
{
    return T < max<T2, Ts...>() ? max<T2, Ts...>() : T;
}
}
