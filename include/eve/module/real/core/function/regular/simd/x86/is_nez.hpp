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

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/function/simd/x86/flags.hpp>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE
  logical<wide<T, N, ABI>> is_nez_(EVE_SUPPORTS(avx512_), wide<T, N, ABI> const &v) noexcept
  {
    constexpr auto c = categorize<wide<T, N, ABI>>();
    constexpr auto m = fpclass::poszero | fpclass::negzero;

    using storage_t = typename logical<wide<T, N, ABI>>::storage_type;
    using i_t       = typename storage_t::type;

          if constexpr( c == category::float32x16 ) return mask16{i_t(~(_mm512_fpclass_ps_mask(v, m)))};
    else  if constexpr( c == category::float64x8  ) return mask8 {i_t(~(_mm512_fpclass_pd_mask(v, m)))};
    else  if constexpr( c == category::float32x8  ) return mask8 {i_t(~(_mm256_fpclass_ps_mask(v, m)))};
    else  if constexpr( c == category::float64x4  ) return mask8 {i_t(~(_mm256_fpclass_pd_mask(v, m)))};
    else  if constexpr( c == category::float32x4  ) return mask8 {i_t(~(_mm_fpclass_ps_mask   (v, m)))};
    else  if constexpr( c == category::float64x2  ) return mask8 {i_t(~(_mm_fpclass_pd_mask   (v, m)))};
  }
}
