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
  auto compress_(EVE_SUPPORTS(avx512_), C c, wide<T, N> v, logical<wide<U, N>> mask) noexcept
    requires (min_scalar_size_v<T> >= 4)
  {
    return compress_using_bmi[c](v, mask);
  }
}
