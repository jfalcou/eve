//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/function/compress_store_swizzle_mask_num.hpp>
#include <eve/function/store.hpp>
#include <eve/memory/pointer.hpp>

namespace eve::detail
{
  template<eve::relative_conditional_expr C, typename T, typename U, typename Ptr>
  EVE_FORCEINLINE auto compress_store_unsafe_switch_(EVE_SUPPORTS(cpu_),
                                                     C c,
                                                     wide<T, fixed<4>> v,
                                                     logical<wide<U, fixed<4>>> mask,
                                                     Ptr ptr)
  {
    auto [num, last_set] = compress_store_swizzle_mask_num[c](mask);
    int count;  // left undefined to allow optimzing default
    switch (num) {
      case 0: { count = 0; v = v[pattern<3, 0, 0, 0>]; break; } // 000
      case 1: { count = 1; v = v[pattern<0, 3, 0, 0>]; break; } // 001
      case 2: { count = 1; v = v[pattern<1, 3, 0, 0>]; break; } // 010
      case 3: { count = 2; v = v[pattern<0, 1, 3, 0>]; break; } // 011
      case 4: { count = 1; v = v[pattern<2, 3, 0, 0>]; break; } // 100
      case 5: { count = 2; v = v[pattern<0, 2, 3, 0>]; break; } // 101
      case 6: { count = 2; v = v[pattern<1, 2, 3, 0>]; break; } // 110
      case 7: { count = 3;                             break; } // 111
    }
    count += last_set ? 1 : 0;
    eve::store(v, ptr);
    return as_raw_pointer(ptr) + count;
  }

  template<typename T, typename U, typename Ptr>
  EVE_FORCEINLINE auto compress_store_unsafe_switch_(EVE_SUPPORTS(cpu_),
                                                     wide<T, fixed<4>> v,
                                                     logical<wide<U, fixed<4>>> mask,
                                                     Ptr ptr)
  {
    return compress_store_unsafe_switch[ignore_none](v, mask, ptr);
  }
}
