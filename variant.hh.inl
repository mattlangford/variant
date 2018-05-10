#pragma once
#include "variant.hh"

//
// ############################################################################
//

template <typename... variant_Ts>
variant<variant_Ts...>::~variant()
{
    detail::destruct_object_at_index<variant_Ts...>(&storage, set_index);
}

//
// ############################################################################
//

template <typename... variant_Ts>
template <typename visitor>
void variant<variant_Ts...>::apply_visitor()
{
    detail::visit<visitor, variant_Ts...>(&storage, set_index);
}

//
// ############################################################################
//

template <typename... variant_Ts>
template <typename T>
void variant<variant_Ts...>::operator=(const T& t)
{
    T t_copy(t);
    operator=(std::move(t));
}

//
// ############################################################################
//

template <typename... variant_Ts>
template <typename T>
void variant<variant_Ts...>::operator=(T&& t)
{
    detail::destruct_object_at_index<variant_Ts...>(&storage, set_index);

    if (set_index < 0)
    {
        throw std::logic_error("Tried to put a bad type into an optional!");
    }

    new (static_cast<void*>(&storage)) T(std::move(t));
    set_index = detail::get_matching_type<T, variant_Ts...>();
}

//
// ############################################################################
//

template <typename... variant_Ts>
template <typename T>
const T& variant<variant_Ts...>::get() const
{
    if (set_index != detail::get_matching_type<T, variant_Ts...>())
    {
        throw std::logic_error("Tried to get an invalid type out of an optional!");
    }

    return *reinterpret_cast<const T*>(&storage);
}
