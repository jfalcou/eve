//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/compress/compress_using_bmi.hpp>

namespace eve::detail
{
  template<relative_conditional_expr C, typename T, typename U, typename N>
  EVE_FORCEINLINE
  auto compress_(EVE_SUPPORTS(avx2_), C c, wide<T, N> v, logical<wide<U, N>> mask) noexcept
    requires (N() >= 4)
  {
    if constexpr ( C::is_complete && !C::is_inverted )
    {
      kumi::tuple cur{ v, (std::ptrdiff_t) 0 };
      return kumi::tuple<decltype(cur)> { cur };
    }
    else return compress_using_bmi(v, top_bits{mask, c});
  }
}
