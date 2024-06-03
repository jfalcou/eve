//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/vectorizable.hpp>
#include <eve/detail/function/friends.hpp>
#include <eve/detail/pragmas.hpp>

EVE_ALLOW_UNINITIALIZED_VARIABLES_PRAGMA

namespace eve::detail
{
  //====================================================================================================
  //! @struct wide_storage
  //! @brief Storage-only element of wide/logical
  //!
  //! wide_storage acts as a wrapper for the storage and manipulation of the native SIMD register
  //! required by wide. This separate class is meant to limit compile-time by being instantiated
  //! once even if multiple wide instance requires the same SIMD register type.
  //!
  //! @tparam Storage Architecture-specific SIMD register type to store
  //! @tparam PreventConversion Control the availability of the automatic conversion to the storage type
  //====================================================================================================
  template<typename Storage, bool PreventConversion> struct wide_storage
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
    EVE_FORCEINLINE explicit(PreventConversion) operator storage_type const& () const &  noexcept { return data_; }

    //! @brief Implicit conversion to the architecture-specific storage help by wide
    EVE_FORCEINLINE explicit(PreventConversion) operator storage_type&       () &        noexcept { return data_; }

    //! @brief Implicit conversion to the architecture-specific storage help by wide
    EVE_FORCEINLINE explicit(PreventConversion) operator storage_type        () &&       noexcept { return data_; }

    protected:
    Storage data_;
  };
}

EVE_RESTORE_ALLOW_UNINITIALIZED_VARIABLES_PRAGMA
