#pragma once
#include <iostream>

namespace detail
{

template <typename T>
void copy(const void* from_data, void* to_data)
{
    new (to_data) T(*reinterpret_cast<const T*>(from_data));
}

template <int i, typename T>
void copy_object_at_index_impl(const void *from_data, void *to_data, const int index)
{
    if (index == i)
    {
        copy<T>(from_data, to_data);
    }
}

template <int i, typename T, typename T2, typename... Ts>
void copy_object_at_index_impl(const void *from_data, void *to_data, const int index)
{
    if (index == i)
    {
        copy<T>(from_data, to_data);
    }
    else
    {
        copy_object_at_index_impl<i + 1, T2, Ts...>(from_data, to_data, index);
    }
}

template <typename storage_type, typename... Ts>
void copy_object_at_index(const storage_type& from_data, storage_type& to_data, const int index)
{
    if (index < 0)
        return;

    copy_object_at_index_impl<0, Ts...>(static_cast<const void*>(&from_data), static_cast<void*>(&to_data), index);
}
}
