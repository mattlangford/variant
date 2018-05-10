#pragma once

namespace detail
{
template <int i, typename visitor, typename T>
void visit_impl(void *data, const int index)
{
    if (index == i)
    {
        visitor v;
        v(*static_cast<T*>(data));
    }
}

template <int i, typename visitor, typename T, typename T2, typename... Ts>
void visit_impl(void *data, const int index)
{
    if (index == i)
    {
        visitor v;
        v(*static_cast<T*>(data));
    }
    else
    {
        visit_impl<i + 1, visitor, T2, Ts...>(data, index);
    }
}

template <typename visitor, typename... Ts>
void visit(void *data, const int index)
{
    if (data == nullptr || index < 0)
        return;

    visit_impl<0, visitor, Ts...>(data, index);
}
}
