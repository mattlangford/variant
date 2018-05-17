#pragma once

namespace detail
{

template <typename storage_type, typename... Args>
struct visit_helpers
{

template <typename visitor, typename T>
static void apply(const storage_type& data, Args... args)
{
    visitor v;
    v(*reinterpret_cast<const T*>(&data), args...);
}

template <int i, typename visitor, typename T>
static void visit_impl(const storage_type& data, const int index, Args... args)
{
    if (index == i)
    {
        apply<visitor, T>(data, args...);
    }
}

template <int i, typename visitor, typename T, typename T2, typename... Ts>
static void visit_impl(const storage_type &data, const int index, Args... args)
{

    if (index == i)
    {
        apply<visitor, T>(data, args...);
    }
    else
    {
        visit_impl<i + 1, visitor, T2, Ts...>(data, index, args...);
    }
}

template <typename visitor, typename... Ts>
static void visit(const storage_type& data, const int index, Args... args)
{
    if (index < 0)
        return;

    visit_impl<0, visitor, Ts...>(data, index, args...);
}
};

}
