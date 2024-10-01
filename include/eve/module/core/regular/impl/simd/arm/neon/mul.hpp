//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/simd_cast.hpp>

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE upgrade_t<wide<T, N>> mul_(EVE_REQUIRES(neon128_), O const& opts,
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

    if      constexpr( c == category::int32x2  ) return fix(vmull_s32(v, w));
    else if constexpr( c == category::uint32x2 ) return fix(vmull_u32(v, w));
    else if constexpr( c == category::int16x4  ) return fix(vmull_s16(v, w));
    else if constexpr( c == category::uint16x4 ) return fix(vmull_u16(v, w));
    else if constexpr( c == category::int8x8   ) return fix(vmull_s8 (v, w));
    else if constexpr( c == category::uint8x8  ) return fix(vmull_u8 (v, w));
    else if constexpr( match(c, category::integer_) && sizeof(T) <= 4 )
    {
      auto [vlo, vhi] = v.slice();
      auto [wlo, whi] = w.slice();
      return eve::combine(mul[opts](vlo, wlo), mul[opts](wlo, whi));
    }
    else return mul.behavior(cpu_{}, opts, v, w);
  }

  template<callable_options O, arithmetic_scalar_value T, typename N, typename U>
  EVE_FORCEINLINE wide<T, N> mul_(EVE_REQUIRES(neon128_), O const &opts, wide<T, N> a, U b) noexcept
  requires (arm_abi<abi_t<T, N>> && !O::contains(widen))
  {
    if constexpr(((O::contains_any(lower, upper)) && floating_value<T>) ||
                 (O::contains(saturated) && std::integral<T>))
    {
      return mul.behavior(as<wide<T, N>>{}, cpu_{}, opts, a, b);
    }
    else
    {
      constexpr auto c = categorize<wide<T, N>>();

      if constexpr( plain_scalar_value<U> )
      {
        if constexpr( c == category::int32x2  )   return vmul_n_s32 (a, b);
        else  if constexpr( c == category::int32x4    ) return vmulq_n_s32(a, b);
        else  if constexpr( c == category::uint32x2   ) return vmul_n_u32 (a, b);
        else  if constexpr( c == category::uint32x4   ) return vmulq_n_u32(a, b);
        else  if constexpr( c == category::int16x4    ) return vmul_n_s16 (a, b);
        else  if constexpr( c == category::int16x8    ) return vmulq_n_s16(a, b);
        else  if constexpr( c == category::uint16x4   ) return vmul_n_u16 (a, b);
        else  if constexpr( c == category::uint16x8   ) return vmulq_n_u16(a, b);
        else  if constexpr( c == category::int8x8     ) return vmul_s8    (a, wide<T, N>{b});
        else  if constexpr( c == category::int8x16    ) return vmulq_s8   (a, wide<T, N>{b});
        else  if constexpr( c == category::uint8x8    ) return vmul_u8    (a, wide<T, N>{b});
        else  if constexpr( c == category::uint8x16   ) return vmulq_u8   (a, wide<T, N>{b});
        else  if constexpr( c == category::float32x2  ) return vmul_n_f32 (a, b);
        else  if constexpr( c == category::float32x4  ) return vmulq_n_f32(a, b);
        else if constexpr( current_api >= asimd )
        {
          if constexpr( c == category::float64x1 ) return vmul_n_f64  (a, b);
          else if constexpr( c == category::float64x2 ) return vmulq_n_f64 (a, b);
          else
          {
            apply<N::value>([&](auto... I) { (a.set(I, a.get(I) * b), ...); });
            return a;
          }
        }
        else
        {
          apply<N::value>([&](auto... I) { (a.set(I, a.get(I) * b), ...); });
          return a;
        }
      }
      else if constexpr (std::same_as<wide<T, N>, U>)
      {
        constexpr auto c = categorize<wide<T, N>>();

        if constexpr( c == category::int32x2    ) return vmul_s32 (a, b);
        else  if constexpr( c == category::int32x4    ) return vmulq_s32(a, b);
        else  if constexpr( c == category::uint32x2   ) return vmul_u32 (a, b);
        else  if constexpr( c == category::uint32x4   ) return vmulq_u32(a, b);
        else  if constexpr( c == category::int16x4    ) return vmul_s16 (a, b);
        else  if constexpr( c == category::int16x8    ) return vmulq_s16(a, b);
        else  if constexpr( c == category::uint16x4   ) return vmul_u16 (a, b);
        else  if constexpr( c == category::uint16x8   ) return vmulq_u16(a, b);
        else  if constexpr( c == category::int8x8     ) return vmul_s8  (a, b);
        else  if constexpr( c == category::int8x16    ) return vmulq_s8 (a, b);
        else  if constexpr( c == category::uint8x8    ) return vmul_u8  (a, b);
        else  if constexpr( c == category::uint8x16   ) return vmulq_u8 (a, b);
        else  if constexpr( c == category::float32x2  ) return vmul_f32 (a, b);
        else  if constexpr( c == category::float32x4  ) return vmulq_f32(a, b);
        else  if constexpr( current_api >= asimd )
        {
          if constexpr( c == category::float64x1 )  return vmul_f64  (a, b);
          else if constexpr( c == category::float64x2 ) return vmulq_f64 (a, b);
          else
          {
            return mul.behavior(as<wide<T, N>>{}, cpu_{}, opts, a, b);
          }
        }
        else
        {
          return mul.behavior(as<wide<T, N>>{}, cpu_{}, opts, a, b);
        }
      }
    }
  }

}
