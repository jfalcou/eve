//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/memory/aligned_ptr.hpp>
#include <eve/assert.hpp>
#include <cstddef>

namespace eve
{
  template<std::size_t Alignment>
  aligned_ptr<void, Alignment> aligned_alloc(std::size_t nbelem)
  {
    constexpr auto alignment = std::max(Alignment, sizeof(void *));
    EVE_ASSERT( (nbelem % alignment == 0), "[eve] Size is not a multiple of selected alignement");

    void *result = std::aligned_alloc(alignment, nbelem);

    return {result};
  }
}

