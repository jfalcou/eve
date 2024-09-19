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

namespace eve::detail
{

  template<callable_options O, arithmetic_scalar_value T, typename N, typename U>
  EVE_FORCEINLINE wide<T, N> mul_(EVE_REQUIRES(neon128_), O const &opts, wide<T, N> a, U b) noexcept
  requires arm_abi<abi_t<T, N>>
  {
    if constexpr(((O::contains(downward) || O::contains(upward)) && floating_value<T>) ||
                 (O::contains(saturated) && std::integral<T>))
    {
      return mul.behavior(cpu_{}, opts, a, b);
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
            return mul.behavior(cpu_{}, opts, a, b);
          }
        }
        else
        {
          return mul.behavior(cpu_{}, opts, a, b);
        }
      }
    }
  }

}
