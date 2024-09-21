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
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> add_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> v, wide<T, N> w) noexcept
    requires arm_abi<abi_t<T, N>>
  {
    if constexpr(O::contains(lower) || O::contains(upper))
      return add.behavior(cpu_{}, opts, v, w);
    else if constexpr (O::contains(saturated) && std::integral<T>)
    {
      return add.behavior(cpu_{}, opts, v, w);
    }
    if constexpr(((O::contains(lower) || O::contains(upper)) && floating_value<T>) ||
                 (O::contains(saturated) && std::integral<T>))
      return add.behavior(cpu_{}, opts, v, w);
    else
    {
      constexpr auto c = categorize<wide<T, N>>();

      if constexpr( c == category::int64x1    ) return vadd_s64 (v, w);
      else if constexpr( c == category::int64x2    ) return vaddq_s64(v, w);
      else if constexpr( c == category::uint64x1   ) return vadd_u64 (v, w);
      else if constexpr( c == category::uint64x2   ) return vaddq_u64(v, w);
      else if constexpr( c == category::int32x2    ) return vadd_s32 (v, w);
      else if constexpr( c == category::int32x4    ) return vaddq_s32(v, w);
      else if constexpr( c == category::uint32x2   ) return vadd_u32 (v, w);
      else if constexpr( c == category::uint32x4   ) return vaddq_u32(v, w);
      else if constexpr( c == category::int16x4    ) return vadd_s16 (v, w);
      else if constexpr( c == category::int16x8    ) return vaddq_s16(v, w);
      else if constexpr( c == category::uint16x4   ) return vadd_u16 (v, w);
      else if constexpr( c == category::uint16x8   ) return vaddq_u16(v, w);
      else if constexpr( c == category::int8x8     ) return vadd_s8  (v, w);
      else if constexpr( c == category::int8x16    ) return vaddq_s8 (v, w);
      else if constexpr( c == category::uint8x8    ) return vadd_u8  (v, w);
      else if constexpr( c == category::uint8x16   ) return vaddq_u8 (v, w);
      else if constexpr( c == category::float32x2  ) return vadd_f32 (v, w);
      else if constexpr( c == category::float32x4  ) return vaddq_f32(v, w);
      elseif constexpr( current_api >= asimd )
      {
        if constexpr( c == category::float64x1 ) return vadd_f64  (v, w);
        else  if constexpr( c == category::float64x2 ) return vaddq_f64 (v, w);
      }
    }
  }
}
