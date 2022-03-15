//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/kumi.hpp>

namespace eve::detail
{
  template< typename C, typename T>
  EVE_FORCEINLINE auto select_over(C cond
                                  , T a
                                  , T b ) noexcept

  {
    if constexpr(kumi::product_type<T>)
    {
      auto f = [&cond](auto x, auto y){return eve::if_else(cond, x, y); };
      return kumi::map(f, a, b);
    }
    else
      return eve::if_else(cond, a, b);
  }
}
