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
  EVE_FORCEINLINE logical<wide<T, N>>
  is_equal_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
  requires arm_abi<abi_t<T, N>>
  {
    if constexpr( O::contains(almost) || O::contains(numeric))
    {
      return is_equal[opts].retarget(cpu_{}, a, b);
    }
    else
    {
      constexpr auto cat = categorize<wide<T, N>>();
      [[maybe_unused]] constexpr auto eq  = []<typename E>(E const& e, E const& f)
                                            {
                                              return as_logical_t<E>(e == f);
                                            };

            if constexpr( cat == category::int32x4  ) return vceqq_s32(a, b);
      else  if constexpr( cat == category::int16x8  ) return vceqq_s16(a, b);
      else  if constexpr( cat == category::int8x16  ) return vceqq_s8 (a, b);
      else  if constexpr( cat == category::uint32x4 ) return vceqq_u32(a, b);
      else  if constexpr( cat == category::uint16x8 ) return vceqq_u16(a, b);
      else  if constexpr( cat == category::uint8x16 ) return vceqq_u8 (a, b);
      else  if constexpr( cat == category::float32x4) return vceqq_f32(a, b);
      else  if constexpr( cat == category::int32x2  ) return vceq_s32 (a, b);
      else  if constexpr( cat == category::int16x4  ) return vceq_s16 (a, b);
      else  if constexpr( cat == category::int8x8   ) return vceq_s8  (a, b);
      else  if constexpr( cat == category::uint32x2 ) return vceq_u32 (a, b);
      else  if constexpr( cat == category::uint16x4 ) return vceq_u16 (a, b);
      else  if constexpr( cat == category::uint8x8  ) return vceq_u8  (a, b);
      else  if constexpr( cat == category::float32x2) return vceq_f32 (a, b);
      else if constexpr( current_api >= asimd)
      {
        if constexpr( cat == category::float64x1) return vceq_f64 (a, b);
        else  if constexpr( cat == category::int64x1)   return vceq_s64 (a, b);
        else  if constexpr( cat == category::uint64x1)  return vceq_u64 (a, b);
        else  if constexpr( cat == category::float64x2) return vceqq_f64(a, b);
        else  if constexpr( cat == category::int64x2)   return vceqq_s64(a, b);
        else  if constexpr( cat == category::uint64x2)  return vceqq_u64(a, b);
      }
      else  if constexpr( sizeof(T) == 8 )            return map(eq, a, b);
    }
  }
}
