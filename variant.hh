#pragma once
#include <string>
#include <tuple>
#include <iostream>

#include "max.hh"

template <typename... Ts>
class variant
{
public: ///////////////////////////////////////////////////////////////////////

    ///
    ///
    ///
    variant()
        : storage({0})
    {
        std::cout << "constructing variant at: " << this << "\n";
    }

    ///
    ///
    ///
    variant(const variant& rhs);

    ///
    ///
    ///
    ~variant();

    ///
    /// Reconstruct the type of the other variant, and copy it into the storage of this one
    ///
    variant<Ts...>& operator=(const variant<Ts...>& t);

public: ///////////////////////////////////////////////////////////////////////
    ///
    /// Apply a struct with a call operator defined for each type in the variant. The correct operator will be called
    /// depending on what the variant is holding (if it's holding anything). The visitor can also take arguments that
    /// will be passed into it (if any extra are needed)
    ///
    template <typename visitor, typename... Args>
    void apply_visitor(Args... args) const;

    ///
    /// Get a specific type out of the variant, this is just a reference so don't rely on it to last long
    /// NOTE: This will throw if trying to get a type that doesn't match what is current set
    ///
    template <typename T>
    const T& get() const;
    template <typename T>
    T& get();

    ///
    /// Set the variant with the specified type, this will throw if the type isn't there
    ///
    template <typename T>
    void set(const T& t);
    template <typename T>
    void set(T&& t);

private: //////////////////////////////////////////////////////////////////////
    ///
    /// This is where we store the object that we create
    ///
    constexpr static size_t max_size = detail::max<sizeof(Ts)...>();
    constexpr static size_t max_align = detail::max<alignof(Ts)...>();
    typename std::aligned_storage<max_size, max_align>::type storage;

    ///
    /// This is an index into the triadic template arguments that we're currently holding
    ///
    int set_index = -1;
};

#include "variant.hh.inl"
