//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/memory/aligned_ptr.hpp>
#include <eve/assert.hpp>
#include <cstddef>

namespace eve
{
  //================================================================================================
  //! @relates eve::aligned_ptr
  //! @brief Allocate an aligned pointer
  //! @param  nbelem      Quantity of bytes to allocate.
  //! @tparam Alignment   Alignment constraint to verify. Behavior is undefined if this constraint
  //!                     is not a power of 2.
  //! @return An aligned_ptr holding the newly allocated memory
  //================================================================================================
  template<std::size_t Alignment>
  aligned_ptr<void, Alignment> aligned_alloc(std::size_t nbelem)
  {
    constexpr auto alignment = std::max(Alignment, sizeof(void *));
    EVE_ASSERT( (nbelem % alignment == 0), "[eve] Size is not a multiple of selected alignement");

    void *result = std::aligned_alloc(alignment, nbelem);

    return {result};
  }
}

