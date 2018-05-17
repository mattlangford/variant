#pragma once
#include <type_traits>
#include <iostream>

namespace detail
{

template <typename T>
void deconstruct(void *data)
{
    reinterpret_cast<T*>(data)->~T();
}

template <int i, typename T>
void destruct_object_at_index_impl(void* data, const int index)
{
    if (index == i)
    {
        deconstruct<T>(data);
    }
}

template <int i, typename T, typename T2, typename... Ts>
void destruct_object_at_index_impl(void* data, const int index)
{
    if (index == i)
    {
        deconstruct<T>(data);
    }
    else
    {
        destruct_object_at_index_impl<i + 1, T2, Ts...>(data, index);
    }
}

template <typename storage_type, typename... Ts>
void destruct_object_at_index(storage_type &data, const int index)
{
    if (index < 0)
        return;

    destruct_object_at_index_impl<0, Ts...>(static_cast<void*>(&data), index);
}
}
