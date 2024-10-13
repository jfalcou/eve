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
  template<arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE logical<wide<T, N>>
  is_eqz_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> const& v) noexcept requires arm_abi<abi_t<T, N>>
  {
    if constexpr(O::contains(saturated))
    {
      return is_eqz.behavior(cpu_{}, opts, v);
    }
    else
    {
      constexpr auto cat = categorize<wide<T, N>>();
      if      constexpr( cat == category::float32x4) return vceqzq_f32(v);
      else if constexpr( cat == category::int32x4  ) return vceqzq_s32(v);
      else if constexpr( cat == category::int16x8  ) return vceqzq_s16(v);
      else if constexpr( cat == category::int8x16  ) return vceqzq_s8(v);
      else if constexpr( cat == category::float32x2) return vceqz_f32(v);
      else if constexpr( cat == category::int32x2  ) return vceqz_s32(v);
      else if constexpr( cat == category::int16x4  ) return vceqz_s16(v);
      else if constexpr( cat == category::int8x8   ) return vceqz_s8(v);
      else if constexpr( cat == category::uint32x4 ) return vceqzq_u32(v);
      else if constexpr( cat == category::uint16x8 ) return vceqzq_u16(v);
      else if constexpr( cat == category::uint8x16 ) return vceqzq_u8(v);
      else if constexpr( cat == category::uint32x2 ) return vceqz_u32(v);
      else if constexpr( cat == category::uint16x4 ) return vceqz_u16(v);
      else if constexpr( cat == category::uint8x8  ) return vceqz_u8(v);
      else if constexpr( current_api >= asimd      )
      {
        if      constexpr( cat == category::float64x2) return vceqzq_f64(v);
        else if constexpr( cat == category::float64x1) return vceqz_f64(v);
        else if constexpr( cat == category::uint64x1 ) return vceqz_u64(v);
        else if constexpr( cat == category::uint64x2 ) return vceqzq_u64(v);
        else if constexpr( cat == category::int64x1  ) return vceqz_s64(v);
        else if constexpr( cat == category::int64x2  ) return vceqzq_s64(v);
        else return is_eqz.behavior(cpu_{}, opts, v);
      }
      else return is_eqz.behavior(cpu_{}, opts, v);
    }
  }
}
