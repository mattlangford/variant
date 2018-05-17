#pragma once

namespace detail
{

template <typename... Args>
struct visit_helpers
{
template <int i, typename visitor, typename T>
static void visit_impl(const void *data, const int index, Args... args)
{
    if (index == i)
    {
        visitor v;
        v(*static_cast<const T*>(data), args...);
    }
}

template <int i, typename visitor, typename T, typename T2, typename... Ts>
static void visit_impl(const void *data, const int index, Args... args)
{
    if (index == i)
    {
        visitor v;
        v(*static_cast<const T*>(data), args...);
    }
    else
    {
        visit_impl<i + 1, visitor, T2, Ts...>(data, index, args...);
    }
}

template <typename storage_type, typename visitor, typename... Ts>
static void visit(const storage_type& data, const int index, Args... args)
{
    if (index < 0)
        return;

    visit_impl<0, visitor, Ts...>(static_cast<const void*>(&data), index, args...);
}
};

}
