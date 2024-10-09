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
#include <eve/module/core/regular/simd_cast.hpp>

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE upgrade_t<wide<T, N>> add_(EVE_REQUIRES(neon128_), O const& opts,
                                              wide<T, N> v, wide<T, N> w) noexcept
  requires (arm_abi<abi_t<T, N>> && O::contains(widen))
  {
    constexpr auto c = categorize<wide<T, N>>();

    auto fix = [](auto r)
    {
      using u_t  = upgrade_t<T>;
      using uw_t = upgrade_t<wide<T, N>>;
      if constexpr(N::value == expected_cardinal_v<u_t>) return uw_t{r};
      else                                               return simd_cast(wide<u_t>{r}, as<uw_t>{});
    };

    if      constexpr( c == category::int32x2  ) return fix(vaddl_s32(v, w));
    else if constexpr( c == category::uint32x2 ) return fix(vaddl_u32(v, w));
    else if constexpr( c == category::int16x4  ) return fix(vaddl_s16(v, w));
    else if constexpr( c == category::uint16x4 ) return fix(vaddl_u16(v, w));
    else if constexpr( c == category::int8x8   ) return fix(vaddl_s8 (v, w));
    else if constexpr( c == category::uint8x8  ) return fix(vaddl_u8 (v, w));
    else if constexpr( match(c, category::integer_) && sizeof(T) <= 4 )
    {
      auto [vlo, vhi] = v.slice();
      auto [wlo, whi] = w.slice();
      return combine(add[opts](vlo, wlo), add[opts](wlo, whi));
    }    else return add.behavior(cpu_{}, opts, v, w);
  }

  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> add_(EVE_REQUIRES(neon128_), O const& opts,
                                               wide<T, N> v, wide<T, N> w) noexcept
    requires (arm_abi<abi_t<T, N>> && !O::contains(widen))
  {
    constexpr auto c = categorize<wide<T, N>>();
    if constexpr((O::contains_any(lower, upper)  && floating_value<T>) ||
                 (O::contains(saturated) && std::integral<T>))
    {
      return add.behavior(cpu_{}, opts, v, w);
    }

    else
    {
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
      else if constexpr( current_api >= asimd )
      {
        if constexpr( c == category::float64x1 ) return vadd_f64  (v, w);
        else  if constexpr( c == category::float64x2 ) return vaddq_f64 (v, w);
      }
    }
  }
}
