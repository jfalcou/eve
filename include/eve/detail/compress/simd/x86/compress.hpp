//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/compress/compress_using_bmi.hpp>
#include <eve/detail/compress/compress_using_switch.hpp>

namespace eve::detail
{
  template<relative_conditional_expr C, typename T, typename U, typename N>
  EVE_FORCEINLINE
  auto compress_(EVE_SUPPORTS(sse2_), C c, wide<T, N> v, logical<wide<U, N>> mask) noexcept
    requires (current_api < ssse3)
  {
    return compress_using_switch[c](v, mask);
  }

  template<relative_conditional_expr C, typename T, typename U, typename N>
  EVE_FORCEINLINE
  auto compress_(EVE_SUPPORTS(avx2_), C c, wide<T, N> v, logical<wide<U, N>> mask) noexcept
    requires (N() >= 4 && supports_bmi_well)
  {
    if constexpr ( C::is_complete && !C::is_inverted )
    {
      kumi::tuple cur{ v, (std::ptrdiff_t) 0 };
      return kumi::tuple<decltype(cur)> { cur };
    }
    else return compress_using_bmi(v, top_bits{mask, c});
  }
}
