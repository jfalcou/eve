//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/vectorizable.hpp>
#include <eve/detail/function/friends.hpp>
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
    //! @name Interface with architecture-specific intrinsics
    //! @{
    //==============================================================================================
    //! @brief Retrieve the architecture-specific storage help by wide
    EVE_FORCEINLINE storage_type const& storage() const & noexcept { return data_; }

    //! @brief Retrieve the architecture-specific storage help by wide
    EVE_FORCEINLINE storage_type &      storage() &       noexcept { return data_; }

    //! @brief Retrieve the architecture-specific storage help by wide
    EVE_FORCEINLINE storage_type        storage() &&      noexcept { return data_; }

    //! @brief Implicit conversion to the architecture-specific storage help by wide
    EVE_FORCEINLINE operator storage_type const& () const &  noexcept { return data_; }

    //! @brief Implicit conversion to the architecture-specific storage help by wide
    EVE_FORCEINLINE operator storage_type&       () &        noexcept { return data_; }

    //! @brief Implicit conversion to the architecture-specific storage help by wide
    EVE_FORCEINLINE operator storage_type        () &&       noexcept { return data_; }
    //==============================================================================================
    //! @}
    //==============================================================================================

    protected:
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
    //! @brief Size of the wide in number of lanes
    static EVE_FORCEINLINE constexpr size_type size()     noexcept { return static_size; }

    //! @brief Maximal number of lanes for a given wide
    static EVE_FORCEINLINE constexpr size_type max_size() noexcept { return static_size; }

    //! @brief Check if a wide contains 0 lanes
    static EVE_FORCEINLINE constexpr bool      empty()    noexcept { return false; }
    //==============================================================================================
    //! @}
    //==============================================================================================
  };

  //================================================================================================
  //! @brief Common operations for wide/logical
  //!
  //! wide_ops acts as a wrapper for all the common operations between wide and logical.
  //!
  //! @tparam Size Type encoding the cardinal of a wide
  //================================================================================================
  template<typename Derived> struct wide_ops
  {
    //==============================================================================================
    // Common hidden friend operators
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
