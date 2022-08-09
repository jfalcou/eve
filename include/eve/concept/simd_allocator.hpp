//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <concepts>

namespace eve
{
  template<typename T>
  concept simd_allocator = requires(T& t)
  {
    { t.allocate_aligned(0,1)        } -> std::same_as<void*>;
    { t.deallocate_aligned(nullptr)  };
  };
}
