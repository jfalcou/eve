//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/function/friends.hpp>
#include <eve/detail/function/lookup.hpp>
#include <eve/detail/function/slice.hpp>
#include <eve/detail/function/subscript.hpp>
#include <eve/detail/function/swizzle.hpp>
#include <eve/detail/function/patterns.hpp>
#include <eve/traits/element_type.hpp>
#include <eve/detail/spy.hpp>

#if defined(SPY_COMPILER_IS_GCC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

namespace eve::detail
{
  //================================================================================================
  //! @addtogroup details
  //! @{
  //================================================================================================
  //! @brief Storage-only element of wide/logical
  //!
  //! wide_storage acts as a wrapper for the storage and manipulation of the native SIMD register
  //! required by wide. This separate class is meant to limit compile-time by being instantiated
  //! once even if multiple wide instance requires the same SIMD register type.
  //!
  //! @tparam Storage Architecture-specific SIMD register type to store
  //================================================================================================
  template<typename Storage> struct wide_storage
  {
    using storage_type = Storage;

    wide_storage() {}
    wide_storage(storage_type const &r) : data_(r) {}

    //==============================================================================================
    //! @name Assignment operators
    //! @{
    //==============================================================================================
    //! @brief Assignment of an architecture-specific SIMD register
    //==============================================================================================
    wide_storage& operator=(storage_type const &r) { data_ = r; return *this; }

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Interface with architecture-specific intrinsics
    //! @{
    //==============================================================================================

    //==============================================================================================
    //! @brief Retrieve the architecture-specific storage help by wide
    //==============================================================================================
    EVE_FORCEINLINE storage_type const& storage() const & noexcept { return data_; }

    //! @overload
    EVE_FORCEINLINE storage_type &      storage() &       noexcept { return data_; }

    //! @overload
    EVE_FORCEINLINE storage_type        storage() &&      noexcept { return data_; }

    //==============================================================================================
    //! @brief Implicit conversion to the architecture-specific storage help by wide
    //==============================================================================================
    EVE_FORCEINLINE operator storage_type const& () const &  noexcept { return data_; }

    //! @overload
    EVE_FORCEINLINE operator storage_type&       () &        noexcept { return data_; }

    //! @overload
    EVE_FORCEINLINE operator storage_type        () &&       noexcept { return data_; }

    //==============================================================================================
    //! @}
    //==============================================================================================

    private:
    Storage data_;
  };

  //================================================================================================
  //! @brief Cardinal-only element of wide/logical
  //!
  //! wide_cardinal acts as a wrapper for the information about the number of lanes in a wide.
  //! This separate class is meant to limit compile-time by being instantiated
  //! once even if multiple wide instance requires the cardinal.
  //!
  //! @tparam Size Type encoding the cardinal of a wide
  //================================================================================================
  template<typename Size> struct wide_cardinal
  {
    //! Type describing the number of lanes of current wide
    using cardinal_type = Size;
    using size_type     = std::ptrdiff_t;

    static constexpr size_type  static_size  = Size::value;

    //==============================================================================================
    //! @name Sequence interface
    //! @{
    //==============================================================================================

    //==============================================================================================
    //! @brief Size of the wide in number of lanes
    //==============================================================================================
    static EVE_FORCEINLINE constexpr size_type size()     noexcept { return static_size; }

    //==============================================================================================
    //! @brief Maximal number of lanes for a given wide
    //==============================================================================================
    static EVE_FORCEINLINE constexpr size_type max_size() noexcept { return static_size; }

    //==============================================================================================
    //! @brief Check if a wide contains 0 lanes
    //==============================================================================================
    static EVE_FORCEINLINE constexpr bool      empty()    noexcept { return false; }
    //==============================================================================================
    //! @}
    //==============================================================================================
  };

  // Common operations on wide/logical
  template<typename Derived> struct wide_ops
  {
    //==============================================================================================
    // Misc.
    static EVE_FORCEINLINE constexpr auto alignment() noexcept
    {
      return Derived::static_alignment;
    }

    EVE_FORCEINLINE Derived& operator=(scalar_value auto v) noexcept
    {
      Derived that(v);
      swap(that);
      return self();
    }

    EVE_FORCEINLINE void swap(Derived& other) noexcept
    {
      std::swap(self().storage(), other.storage());
    }

    EVE_FORCEINLINE void swap(wide_ops &lhs, wide_ops &rhs) noexcept
    {
      lhs.self().swap(rhs);
    }

    //==============================================================================================
    // Shape related functions
    EVE_FORCEINLINE auto slice() const requires(cardinal_v<Derived> > 1)
    {
      return detail::slice(self());
    }

    EVE_FORCEINLINE auto slice(auto s) const requires(cardinal_v<Derived> > 1)
    {
      return detail::slice(self(), s);
    }

    //==============================================================================================
    // Reindexing operators
    template<typename Index>
    EVE_FORCEINLINE auto operator[](wide<Index,cardinal_t<Derived>> const& idx) const noexcept
    {
      return lookup(self(),idx);
    }

    template<std::ptrdiff_t... I>
    EVE_FORCEINLINE auto operator[](pattern_t<I...>) const noexcept
    requires(pattern_t<I...>{}.validate(cardinal_v<Derived>))
    {
      constexpr auto swizzler = find_optimized_pattern<cardinal_v<Derived>,I...>();
      return swizzler(self());
    }

    template<typename F>
    EVE_FORCEINLINE auto operator[](as_pattern<F> p) const noexcept
    {
      return self()[ fix_pattern<cardinal_v<Derived>>(p) ];
    }

    //==============================================================================================
    // Value access functions
    EVE_FORCEINLINE void set(std::size_t i, scalar_value auto v) noexcept
    {
      detail::insert(self(), i, v);
    }

    EVE_FORCEINLINE auto get(std::size_t i) const noexcept
    {
      return detail::extract(self(), i);
    }

    EVE_FORCEINLINE auto back()  const noexcept { return get(cardinal_v<Derived>-1); }
    EVE_FORCEINLINE auto front() const noexcept { return get(0); }

    //==============================================================================================
    // Common hidden friend operators
    friend EVE_FORCEINLINE auto operator!(wide_ops const& v) noexcept
    {
      return detail::self_lognot(v.self());
    }

    friend EVE_FORCEINLINE auto operator==(wide_ops const& v, wide_ops const& w) noexcept
    {
      return detail::self_eq(v.self(),w.self());
    }

    friend EVE_FORCEINLINE auto operator==(wide_ops const& v, scalar_value auto w) noexcept
    {
      return v == Derived{w};
    }

    friend EVE_FORCEINLINE auto operator==(scalar_value auto v, wide_ops const& w) noexcept
    {
      return w == v;
    }

    friend EVE_FORCEINLINE auto operator!=(wide_ops const& v, wide_ops const& w) noexcept
    {
      return detail::self_neq(v.self(),w.self());
    }

    friend EVE_FORCEINLINE auto operator!=(wide_ops const& v, scalar_value auto w) noexcept
    {
      return v != Derived{w};
    }

    friend EVE_FORCEINLINE auto operator!=(scalar_value auto v, wide_ops const& w) noexcept
    {
      return w != v;
    }

    private:
    EVE_FORCEINLINE Derived&        self()        { return static_cast<Derived&>(*this); }
    EVE_FORCEINLINE Derived const&  self() const  { return static_cast<Derived const&>(*this); }
  };
  //================================================================================================
  //! @}
  //================================================================================================
}

#if defined(SPY_COMPILER_IS_GCC)
#pragma GCC diagnostic pop
#endif
