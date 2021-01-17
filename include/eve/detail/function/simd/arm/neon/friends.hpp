//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  //================================================================================================
  // operator~ implementation
  //================================================================================================
  template<real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T,N,ABI> self_bitnot(wide<T,N,ABI> const& v) noexcept
  {
    constexpr auto c = categorize<wide<T, N, ABI>>();
    using i_t  = wide<as_integer_t<T, unsigned>, N>;

          if constexpr(c == category::int64x1 ) return vreinterpret_s64_s8(vmvn_s8(vreinterpret_s8_s64(v)));
    else  if constexpr(c == category::uint64x1) return vreinterpret_u64_u8(vmvn_u8(vreinterpret_u8_u64(v)));
    else  if constexpr(c == category::int64x2 ) return vreinterpretq_s64_s8(vmvnq_s8(vreinterpretq_s8_s64(v)));
    else  if constexpr(c == category::uint64x2) return vreinterpretq_u64_u8(vmvnq_u8(vreinterpretq_u8_u64(v)));
    else  if constexpr(c == category::int32x2 ) return vmvn_s32(v);
    else  if constexpr(c == category::uint32x2) return vmvn_u32(v);
    else  if constexpr(c == category::int32x4 ) return vmvnq_s32(v);
    else  if constexpr(c == category::uint32x4) return vmvnq_u32(v);
    else  if constexpr(c == category::int16x4 ) return vmvn_s16(v);
    else  if constexpr(c == category::uint16x4) return vmvn_u16(v);
    else  if constexpr(c == category::int16x8 ) return vmvnq_s16(v);
    else  if constexpr(c == category::uint16x8) return vmvnq_u16(v);
    else  if constexpr(c == category::int8x8  ) return vmvn_s8(v);
    else  if constexpr(c == category::uint8x8 ) return vmvn_u8(v);
    else  if constexpr(c == category::int8x16 ) return vmvnq_s8(v);
    else  if constexpr(c == category::uint8x16) return vmvnq_u8(v);
    else                                        return bit_cast(~bit_cast(v,as_<i_t>{}), as(v));
  }

  //================================================================================================
  // operator== implementation
  //================================================================================================
  template<real_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE as_logical_t<wide<T, N, ABI>> self_eq(wide<T,N,ABI> v, wide<T,N,ABI> w) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();
    [[maybe_unused]] constexpr auto eq  = []<typename E>(E const& e, E const& f)
                                          {
                                            return as_logical_t<E>(e == f);
                                          };

          if constexpr( cat == category::int32x4  ) return vceqq_s32(v, w);
    else  if constexpr( cat == category::int16x8  ) return vceqq_s16(v, w);
    else  if constexpr( cat == category::int8x16  ) return vceqq_s8 (v, w);
    else  if constexpr( cat == category::uint32x4 ) return vceqq_u32(v, w);
    else  if constexpr( cat == category::uint16x8 ) return vceqq_u16(v, w);
    else  if constexpr( cat == category::uint8x16 ) return vceqq_u8 (v, w);
    else  if constexpr( cat == category::float32x4) return vceqq_f32(v, w);
    else  if constexpr( cat == category::int32x2  ) return vceq_s32 (v, w);
    else  if constexpr( cat == category::int16x4  ) return vceq_s16 (v, w);
    else  if constexpr( cat == category::int8x8   ) return vceq_s8  (v, w);
    else  if constexpr( cat == category::uint32x2 ) return vceq_u32 (v, w);
    else  if constexpr( cat == category::uint16x4 ) return vceq_u16 (v, w);
    else  if constexpr( cat == category::uint8x8  ) return vceq_u8  (v, w);
    else  if constexpr( cat == category::float32x2) return vceq_f32 (v, w);
#if defined(__aarch64__)
    else  if constexpr( cat == category::float64x1) return vceq_f64 (v, w);
    else  if constexpr( cat == category::int64x1)   return vceq_s64 (v, w);
    else  if constexpr( cat == category::uint64x1)  return vceq_u64 (v, w);
    else  if constexpr( cat == category::float64x2) return vceqq_f64(v, w);
    else  if constexpr( cat == category::int64x2)   return vceqq_s64(v, w);
    else  if constexpr( cat == category::uint64x2)  return vceqq_u64(v, w);
#else
    else  if constexpr( sizeof(T) == 8 )            return map(eq, v, w);
#endif
  }
}
