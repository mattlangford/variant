#pragma once

namespace detail
{

template <typename... Args>
struct visit_helpers
{
template <int i, typename visitor, typename T>
static void visit_impl(void *data, const int index, Args... args)
{
    if (index == i)
    {
        visitor v;
        v(*static_cast<T*>(data), args...);
    }
}

template <int i, typename visitor, typename T, typename T2, typename... Ts>
static void visit_impl(void *data, const int index, Args... args)
{
    if (index == i)
    {
        visitor v;
        v(*static_cast<T*>(data), args...);
    }
    else
    {
        visit_impl<i + 1, visitor, T2, Ts...>(data, index, args...);
    }
}

template <typename visitor, typename... Ts>
static void visit(void *data, const int index, Args... args)
{
    if (data == nullptr || index < 0)
        return;

    visit_impl<0, visitor, Ts...>(data, index, args...);
}
};

}
