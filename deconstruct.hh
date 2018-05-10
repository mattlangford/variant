#pragma once

namespace detail
{
template <int i, typename T>
void destruct_object_at_index_impl(void* data, const int index)
{
    if (index == i)
    {
        static_cast<T*>(data)->~T();
    }
}

template <int i, typename T, typename T2, typename... Ts>
void destruct_object_at_index_impl(void* data, const int index)
{
    if (index == i)
    {
        static_cast<T*>(data)->~T();
    }
    else
    {
        destruct_object_at_index_impl<i + 1, T2, Ts...>(data, index + 1);
    }
}

template <typename... Ts>
void destruct_object_at_index(void *data, const int index)
{
    if (data == nullptr || index < 0)
        return;

    destruct_object_at_index_impl<0, Ts...>(data, index);
}
}
