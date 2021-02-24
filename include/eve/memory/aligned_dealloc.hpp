//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/memory/aligned_ptr.hpp>
#include <cstddef>

namespace eve
{
  template<typename T, std::size_t Alignment>
 void aligned_dealloc(aligned_ptr<T, Alignment> const &ptr)
  {
    std::free((void *)ptr.get());
  }
}
