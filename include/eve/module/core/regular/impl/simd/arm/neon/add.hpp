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

 //  template<callable_options O, typename T, typename N>
//   EVE_FORCEINLINE  auto add_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> v, wide<T, N> w) noexcept
//   requires (arm_abi<abi_t<T, N>> && (O::contains(narrow) || O::contains(widen)))
//   {
//     constexpr auto c = categorize<wide<T, N>>();
//     if constexpr(O::contains(narrow))
//     {
//       if constexpr( c == category::int64x1    ) return vhadd_s64 (v, w);
//       else if constexpr( c == category::int64x2    ) return vhaddq_s64(v, w);
//       else if constexpr( c == category::uint64x1   ) return vhadd_u64 (v, w);
//       else if constexpr( c == category::uint64x2   ) return vhaddq_u64(v, w);
//       else if constexpr( c == category::int32x2    ) return vhadd_s32 (v, w);
//       else if constexpr( c == category::int32x4    ) return vhaddq_s32(v, w);
//       else if constexpr( c == category::uint32x2   ) return vhadd_u32 (v, w);
//       else if constexpr( c == category::uint32x4   ) return vhaddq_u32(v, w);
//       else if constexpr( c == category::int16x4    ) return vhadd_s16 (v, w);
//       else if constexpr( c == category::int16x8    ) return vhaddq_s16(v, w);
//       else if constexpr( c == category::uint16x4   ) return vhadd_u16 (v, w);
//       else if constexpr( c == category::uint16x8   ) return vhaddq_u16(v, w);
//       else return add.behavior(cpu_{}, opts, v, w);
//     }
//     else if (O::contains(widen))
//     {
//       if      constexpr( c == category::int32x2    ) return vaddl_s32 (v, w);
//       else if constexpr( c == category::int32x4    ) return vaddlq_s32(v, w);
//       else if constexpr( c == category::uint32x2   ) return vaddl_u32 (v, w);
//       else if constexpr( c == category::uint32x4   ) return vaddlq_u32(v, w);
//       else if constexpr( c == category::int16x4    ) return vaddl_s16 (v, w);
//       else if constexpr( c == category::int16x8    ) return vaddlq_s16(v, w);
//       else if constexpr( c == category::uint16x4   ) return vaddl_u16 (v, w);
//       else if constexpr( c == category::uint16x8   ) return vaddlq_u16(v, w);
//       else if constexpr( c == category::int8x8     ) return vaddl_s8  (v, w);
//       else if constexpr( c == category::int8x16    ) return vaddlq_s8 (v, w);
//       else if constexpr( c == category::uint8x8    ) return vaddl_u8  (v, w);
//       else if constexpr( c == category::uint8x16   ) return vaddlq_u8 (v, w);
//       else return add.behavior(cpu_{}, opts, v, w);
//     }
//   }

  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> add_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> v, wide<T, N> w) noexcept
  requires arm_abi<abi_t<T, N>>
  {
    if constexpr(O::contains_any(narrow, widen) ||
      (O::contains_any(lower, upper)  && floating_value<T>) ||
      (O::contains(saturated) && std::integral<T>))
    {
      return add.behavior(cpu_{}, opts, v, w);
    }
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
      else if constexpr( current_api >= asimd )
      {
        if constexpr( c == category::float64x1 ) return vadd_f64  (v, w);
        else  if constexpr( c == category::float64x2 ) return vaddq_f64 (v, w);
      }
    }
  }
}
