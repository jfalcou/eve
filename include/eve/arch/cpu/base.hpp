//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
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
  //! @struct wide_storage
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

    protected:
    Storage data_;
  };
}

#if defined(SPY_COMPILER_IS_GCC)
#pragma GCC diagnostic pop
#endif
