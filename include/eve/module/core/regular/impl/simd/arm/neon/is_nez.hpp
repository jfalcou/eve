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
  is_nez_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> const& v) noexcept requires arm_abi<abi_t<T, N>>
  {
    if constexpr(O::contains(saturated))
    {
      return is_nez.behavior(cpu_{}, opts, v);
    }
    else
    {
      constexpr auto cat = categorize<wide<T, N>>();
      if      constexpr( cat == category::int32x4  ) return vtstq_s32(v, v);
      else if constexpr( cat == category::int16x8  ) return vtstq_s16(v, v);
      else if constexpr( cat == category::int8x16  ) return vtstq_s8(v, v);
      else if constexpr( cat == category::int32x2  ) return vtst_s32(v, v);
      else if constexpr( cat == category::int16x4  ) return vtst_s16(v, v);
      else if constexpr( cat == category::int8x8   ) return vtst_s8(v, v);
      else if constexpr( cat == category::uint32x4 ) return vtstq_u32(v, v);
      else if constexpr( cat == category::uint16x8 ) return vtstq_u16(v, v);
      else if constexpr( cat == category::uint8x16 ) return vtstq_u8(v, v);
      else if constexpr( cat == category::uint32x2 ) return vtst_u32(v, v);
      else if constexpr( cat == category::uint16x4 ) return vtst_u16(v, v);
      else if constexpr( cat == category::uint8x8  ) return vtst_u8(v, v);
      else  if constexpr( current_api >= asimd      )
      {
        if      constexpr( cat == category::uint64x1 ) return vtst_u64(v, v);
        else if constexpr( cat == category::uint64x2 ) return vtstq_u64(v, v);
        else if constexpr( cat == category::int64x1  ) return vtst_s64(v, v);
        else if constexpr( cat == category::int64x2  ) return vtstq_s64(v, v);
        else return is_nez.behavior(cpu_{}, opts, v);
      }
      else return is_nez.behavior(cpu_{}, opts, v);
    }
  }
}
