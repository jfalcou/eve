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
//   EVE_FORCEINLINE  wide<up_t<T>, N> add_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> v, wide<T, N> w) noexcept
//   requires (arm_abi<abi_t<T, N>> && O::contains(widen))
//   {
//     constexpr auto c = categorize<wide<T, N>>();

//     if      constexpr( c == category::int32x2    ) return vaddl_s32 (v, w);
//     else if constexpr( c == category::uint32x2   ) return vaddl_u32 (v, w);
//     else if constexpr( c == category::int16x4    ) return vaddl_s16 (v, w);
//     else if constexpr( c == category::uint16x4   ) return vaddl_u16 (v, w);
//     else if constexpr( c == category::int8x8     ) return vaddl_s8  (v, w);
//     else if constexpr( c == category::uint8x8    ) return vaddl_u8  (v, w);
//     else return add.behavior(cpu_{}, opts, v, w);
//   }

  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE auto add_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> v, wide<T, N> w) noexcept
  -> decltype(eve::detail::resize_it(O(), wide<T, N>()))
  requires (arm_abi<abi_t<T, N>> && !O::contains(widen))
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr(O::contains_any(narrow, widen))
    {
      return add.behavior(cpu_{}, opts, v, w);
    }
//     else if (O::contains(widen))
//     {
// //      using r_t = as_wide_as<decltype(v), up_t<T>>;
// //       if      constexpr( c == category::int32x2    ) return eve::wide<int64_t, fixed<2>>(vaddl_s32 (v, w));//*
// //       else if constexpr( c == category::uint32x2   ) return eve::wide<uint64_t, fixed<2>>(vaddl_u32 (v, w));//*
// //       else if constexpr( c == category::int16x4    ) return eve::wide<int32_t, fixed<4>>(vaddl_s16 (v, w));//*
// //       else if constexpr( c == category::uint16x4   ) return eve::wide<uint32_t, fixed<4>>(vaddl_u16 (v, w));//*
// //       else if constexpr( c == category::int8x8     ) return eve::wide<int16_t, fixed<8>>(vaddl_s8  (v, w));//*
// //       else if constexpr( c == category::uint8x8    ) return eve::wide<uint16_t, fixed<8>>(vaddl_u8  (v, w));//*
//       else return add.behavior(cpu_{}, opts, v, w);
//     }
    else if ((O::contains_any(lower, upper)  && floating_value<T>) ||
      (O::contains(saturated) && std::integral<T>))
    {
      return add.behavior(cpu_{}, opts, v, w);
    }
    else
    {
      using r_t = eve::wide<T, N>;
      if      constexpr( c == category::int64x1    ) return r_t(vadd_s64 (v, w));
      else if constexpr( c == category::int64x2    ) return r_t(vaddq_s64(v, w));
      else if constexpr( c == category::uint64x1   ) return r_t(vadd_u64 (v, w));
      else if constexpr( c == category::uint64x2   ) return r_t(vaddq_u64(v, w));
      else if constexpr( c == category::int32x2    ) return r_t(vadd_s32 (v, w));
      else if constexpr( c == category::int32x4    ) return r_t(vaddq_s32(v, w));
      else if constexpr( c == category::uint32x2   ) return r_t(vadd_u32 (v, w));
      else if constexpr( c == category::uint32x4   ) return r_t(vaddq_u32(v, w));
      else if constexpr( c == category::int16x4    ) return r_t(vadd_s16 (v, w));
      else if constexpr( c == category::int16x8    ) return r_t(vaddq_s16(v, w));
      else if constexpr( c == category::uint16x4   ) return r_t(vadd_u16 (v, w));
      else if constexpr( c == category::uint16x8   ) return r_t(vaddq_u16(v, w));
      else if constexpr( c == category::int8x8     ) return r_t(vadd_s8  (v, w));
      else if constexpr( c == category::int8x16    ) return r_t(vaddq_s8 (v, w));
      else if constexpr( c == category::uint8x8    ) return r_t(vadd_u8  (v, w));
      else if constexpr( c == category::uint8x16   ) return r_t(vaddq_u8 (v, w));
      else if constexpr( c == category::float32x2  ) return r_t(vadd_f32 (v, w));
      else if constexpr( c == category::float32x4  ) return r_t(vaddq_f32(v, w));
      else if constexpr( current_api >= asimd )
      {
        if constexpr( c == category::float64x1 ) return r_t(vadd_f64  (v, w));
        else  if constexpr( c == category::float64x2 ) return r_t(vaddq_f64 (v, w));
      }
    }
  }
}
