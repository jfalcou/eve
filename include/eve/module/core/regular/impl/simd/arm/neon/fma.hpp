//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
template<typename T, typename N, callable_options O>
EVE_FORCEINLINE wide<T, N>
fma_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> const& a, wide<T, N> const& b, wide<T, N> const& c) noexcept
requires arm_abi<abi_t<T, N>>
{
  // We don't care about PROMOTE as we takes single type
  // We don't care about PEDANTIC as we always end up using a vmla/vfma or we map
  constexpr auto cat = categorize<wide<T, N>>();

  if constexpr(O::contains(lower) || O::contains(upper)) return fma.behavior(cpu_{}, opts, a, b, c);
  else if constexpr( cat == category::float32x4 )   return vfmaq_f32(c, b, a);
  else if constexpr( cat == category::float32x2 )   return vfma_f32 (c, b, a);
  else if constexpr( cat == category::int32x4   )   return vmlaq_s32(c, b, a);
  else if constexpr( cat == category::int32x2   )   return vmla_s32 (c, b, a);
  else if constexpr( cat == category::int16x8   )   return vmlaq_s16(c, b, a);
  else if constexpr( cat == category::int16x4   )   return vmla_s16 (c, b, a);
  else if constexpr( cat == category::int8x16   )   return vmlaq_s8 (c, b, a);
  else if constexpr( cat == category::int8x8    )   return vmla_s8  (c, b, a);
  else if constexpr( cat == category::uint32x4  )   return vmlaq_u32(c, b, a);
  else if constexpr( cat == category::uint32x2  )   return vmla_u32 (c, b, a);
  else if constexpr( cat == category::uint16x8  )   return vmlaq_u16(c, b, a);
  else if constexpr( cat == category::uint16x4  )   return vmla_u16 (c, b, a);
  else if constexpr( cat == category::uint8x16  )   return vmlaq_u8 (c, b, a);
  else if constexpr( cat == category::uint8x8   )   return vmla_u8  (c, b, a);
  else if constexpr( current_api >= asimd )
  {
    if      constexpr( cat == category::float64x2 ) return vfmaq_f64(c, b, a);
    else if constexpr( cat == category::float64x1 ) return vfma_f64 (c, b, a);
    else                                            return fma.behavior(cpu_{}, opts, a, b, c);
  }
  else                                              return fma.behavior(cpu_{}, opts, a, b, c);
}
}
