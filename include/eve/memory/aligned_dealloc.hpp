//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
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

