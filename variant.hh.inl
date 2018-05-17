#pragma once
#include "variant.hh"
#include <typeinfo>

#include "copy.hh"
#include "deconstruct.hh"
#include "matching_types.hh"
#include "visit.hh"

//
// ############################################################################
//

template <typename... variant_Ts>
variant<variant_Ts...>::variant(const variant<variant_Ts...>& rhs)
{
    set_index = rhs.set_index;
    detail::copy_object_at_index<decltype(storage), variant_Ts...>(rhs.storage, storage, set_index);
}

//
// ############################################################################
//

template <typename... variant_Ts>
variant<variant_Ts...>::~variant()
{
    detail::destruct_object_at_index<decltype(storage), variant_Ts...>(storage, set_index);
    std::cout << "deleted\n";
}

//
// ############################################################################
//

template <typename... variant_Ts>
variant<variant_Ts...>& variant<variant_Ts...>::operator=(const variant<variant_Ts...>& t)
{
    set_index = t.set_index;
    detail::copy_object_at_index<decltype(storage), variant_Ts...>(t.storage, storage, set_index);
    return *this;
}

//
// ############################################################################
//

template <typename... variant_Ts>
template <typename visitor, typename... Args>
void variant<variant_Ts...>::apply_visitor(Args... args) const
{
    detail::visit_helpers<decltype(storage), Args...>::template visit<visitor, variant_Ts...>(storage, set_index, args...);
}

//
// ############################################################################
//

template <typename... variant_Ts>
template <typename T>
const T& variant<variant_Ts...>::get() const
{
    if (set_index != detail::get_matching_type<typename std::decay<T>::type, variant_Ts...>())
    {
        throw std::logic_error("Tried to get an invalid type out of an optional!");
    }

    return *reinterpret_cast<const T*>(&storage);
}

//
// ############################################################################
//

template <typename... variant_Ts>
template <typename T>
T& variant<variant_Ts...>::get()
{
    if (set_index != detail::get_matching_type<typename std::decay<T>::type, variant_Ts...>())
    {
        throw std::logic_error("Tried to get an invalid type out of an optional!");
    }

    return *reinterpret_cast<T*>(&storage);
}

//
// ############################################################################
//

template <typename... variant_Ts>
template <typename T>
void variant<variant_Ts...>::set(const T& t)
{
    set(T(t));
}

//
// ############################################################################
//

template <typename... variant_Ts>
template <typename T>
void variant<variant_Ts...>::set(T&& t)
{
    detail::destruct_object_at_index<decltype(storage), variant_Ts...>(storage, set_index);

    set_index = detail::get_matching_type<typename std::decay<T>::type, variant_Ts...>();
    if (set_index < 0)
    {
        throw std::logic_error("Tried to put a bad type into an optional!");
    }

    new (static_cast<void*>(&storage)) T(std::move(t));
    std::cout << "new: " << &storage << " (" << typeid(T).name() << ")\n";
}
//
// ############################################################################
//

