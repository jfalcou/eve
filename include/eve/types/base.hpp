//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/vectorizable.hpp>
#include <eve/detail/pragmas.hpp>

EVE_ALLOW_UNINITIALIZED_VARIABLES_PRAGMA

EVE_NAMESPACE::_
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
  // The explicit alignas does not change the alignment, it makes it a required one. Without it,
  // clang-cl lets an enclosing #pragma pack lower it, unlike MSVC where the __declspec(align) of
  // __m128 & co. propagates. The MS STL declares std::array, std::pair, ... under
  // #pragma pack(_CRT_PACKING), so a std::array<wide,N> ends up 8-aligned and aligned SSE/AVX
  // accesses to its elements crash.
  template<typename Storage> struct alignas(alignof(Storage)) wide_storage
  {
    using storage_type = Storage;

    wide_storage() = default;

    wide_storage(storage_type const &r) : data_(r) {}

    //! @brief Retrieve the architecture-specific storage help by wide
     storage_type const& storage() const & noexcept { return data_; }

    //! @brief Retrieve the architecture-specific storage help by wide
     storage_type &      storage() &       noexcept { return data_; }

    //! @brief Retrieve the architecture-specific storage help by wide
     storage_type        storage() &&      noexcept { return data_; }

    //! @brief Implicit conversion to the architecture-specific storage help by wide
     operator storage_type const& () const &  noexcept { return data_; }

    //! @brief Implicit conversion to the architecture-specific storage help by wide
     operator storage_type&       () &        noexcept { return data_; }

    //! @brief Implicit conversion to the architecture-specific storage help by wide
     operator storage_type        () &&       noexcept { return data_; }

    protected:
    Storage data_;
  };
}

EVE_RESTORE_ALLOW_UNINITIALIZED_VARIABLES_PRAGMA
