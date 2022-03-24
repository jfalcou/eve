//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <concepts>

namespace eve
{
  template<typename T>
  concept simd_allocator = requires(T& t)
  {
    { t.aligned_alloc(0,0)          } -> std::same_as<void*>;
    { t.aligned_dealloc(nullptr,0)  };
  };
}
