#pragma once
#include <string>
#include <type_traits>
#include <tuple>

#include "deconstruct.hh"
#include "matching_types.hh"
#include "max.hh"
#include "visit.hh"

template <typename... Ts>
class variant
{
public: ///////////////////////////////////////////////////////////////////////

    ///
    ///
    ///
    variant() = default;

    ///
    /// This allows for implicit conversion between T and this variant
    /// TODO
    ///
    template <typename T>
    variant(const T& t) = delete;

    ///
    ///
    ///
    ~variant();

public: ///////////////////////////////////////////////////////////////////////

    ///
    /// Apply a struct with a call operator defined for each type in the variant. The correct operator will be called
    /// depending on what the variant is holding (if it's holding anything)
    ///
    template <typename visitor>
    void apply_visitor();

    ///
    /// Set the variant with a const reference, this will deconstruct whatever is being held by the variant and create
    /// a copy of the object passed in
    /// NOTE: This will throw if trying to put an invalid type in
    ///
    template <typename T>
    void operator=(const T& t);

    ///
    /// Set the variant with an rvalue reference, this will deconstruct whatever is being held by the variant
    /// NOTE: This will throw if trying to put an invalid type in
    ///
    template <typename T>
    void operator=(T&& t);

    ///
    /// Get a specific type out of the variant, this is just a reference so don't rely on it to last long
    /// NOTE: This will throw if trying to get a type that doesn't match what is current set
    ///
    template <typename T>
    const T& get() const;

    ///
    /// Get a specific type out of the variant, this is just a reference so don't rely on it to last long
    /// NOTE: This will throw if trying to get a type that doesn't match what is current set
    ///
    template <typename T>
    T& get();

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
