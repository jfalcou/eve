//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/reduce.hpp>
#include <eve/function/max.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE T maximum_ ( EVE_SUPPORTS(neon128_)
                                , wide<T,N,ABI> const &v
                                ) noexcept
  {
    if constexpr ( eve::current_api >= eve::asimd )
    {
      constexpr auto c = categorize<wide<T,N,ABI>>();

            if constexpr( c == category::int64x1  ) return v.get(0);
      else  if constexpr( c == category::uint64x1 ) return v.get(0);
      else  if constexpr( c == category::int32x2  ) return vmaxv_s32 (v);
      else  if constexpr( c == category::int32x4  ) return vmaxvq_s32(v);
      else  if constexpr( c == category::uint32x2 ) return vmaxv_u32 (v);
      else  if constexpr( c == category::uint32x4 ) return vmaxvq_u32(v);
      else  if constexpr( c == category::int16x4  ) return vmaxv_s16 (v);
      else  if constexpr( c == category::int16x8  ) return vmaxvq_s16(v);
      else  if constexpr( c == category::uint16x4 ) return vmaxv_u16 (v);
      else  if constexpr( c == category::uint16x8 ) return vmaxvq_u16(v);
      else  if constexpr( c == category::int8x8   ) return vmaxv_s8  (v);
      else  if constexpr( c == category::int8x16  ) return vmaxvq_s8 (v);
      else  if constexpr( c == category::uint8x8  ) return vmaxv_u8  (v);
      else  if constexpr( c == category::uint8x16 ) return vmaxvq_u8 (v);
      else  if constexpr( c == category::float32x2) return vmaxv_f32 (v);
      else  if constexpr( c == category::float32x4) return vmaxvq_f32(v);
      else  if constexpr( c == category::float64x1) return v.get(0);
      else  if constexpr( c == category::float64x2) return vmaxvq_f64(v);
      else  return reduce(v, eve::max);
    }
    else
    {
      return reduce(v, eve::max);
    }
  }

  template<real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE auto maximum_ ( EVE_SUPPORTS(neon128_)
                                , splat_type const&, wide<T,N,ABI> const &v
                                ) noexcept
  {
    return wide<T,N,ABI>( maximum(v) );
  }
}
