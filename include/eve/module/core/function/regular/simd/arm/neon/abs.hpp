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
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> abs_(EVE_SUPPORTS(neon128_), wide<T, N, ABI> const& v) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();

          if constexpr( cat && category::unsigned_) return v;
    else  if constexpr( cat && category::size64_  ) return map(eve::abs, v);
    else  if constexpr( cat == category::float32x4) return vabsq_f32(v);
    else  if constexpr( cat == category::int32x4  ) return vabsq_s32(v);
    else  if constexpr( cat == category::int16x8  ) return vabsq_s16(v);
    else  if constexpr( cat == category::int8x16  ) return vabsq_s8(v);
    else  if constexpr( cat == category::float32x2) return vabs_f32(v);
    else  if constexpr( cat == category::int32x2  ) return vabs_s32(v);
    else  if constexpr( cat == category::int16x4  ) return vabs_s16(v);
    else  if constexpr( cat == category::int8x8   ) return vabs_s8(v);
#if defined(__aarch64__)
    else  if constexpr( cat == category::float64x2) return vabsq_f64(v);
    else  if constexpr( cat == category::float64x1) return vabs_f64(v);
#endif
  }
}
