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
#include <eve/forward.hpp>

namespace eve::detail
{
  //================================================================================================
  // operator== implementation
  //================================================================================================
  template<arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> self_eq(wide<T,N> v, wide<T,N> w) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    constexpr auto cat = categorize<wide<T, N>>();
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
    else if constexpr( current_api >= asimd)
    {
      if constexpr( cat == category::float64x1) return vceq_f64 (v, w);
      else  if constexpr( cat == category::int64x1)   return vceq_s64 (v, w);
      else  if constexpr( cat == category::uint64x1)  return vceq_u64 (v, w);
      else  if constexpr( cat == category::float64x2) return vceqq_f64(v, w);
      else  if constexpr( cat == category::int64x2)   return vceqq_s64(v, w);
      else  if constexpr( cat == category::uint64x2)  return vceqq_u64(v, w);
    }
    else  if constexpr( sizeof(T) == 8 )            return map(eq, v, w);
  }

  //================================================================================================
  // operator!= implementation
  //================================================================================================
  template<arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> self_neq(wide<T,N> v, wide<T,N> w) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    return !(v == w);
  }

  template<typename T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> self_geq(wide<T, N> v, wide<T, N> w) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    constexpr auto cat = categorize<wide<T, N>>();

          if constexpr( cat == category::int32x4  ) return vcgeq_s32(v, w);
    else  if constexpr( cat == category::int16x8  ) return vcgeq_s16(v, w);
    else  if constexpr( cat == category::int8x16  ) return vcgeq_s8(v, w);
    else  if constexpr( cat == category::uint32x4 ) return vcgeq_u32(v, w);
    else  if constexpr( cat == category::uint16x8 ) return vcgeq_u16(v, w);
    else  if constexpr( cat == category::uint8x16 ) return vcgeq_u8(v, w);
    else  if constexpr( cat == category::float32x4) return vcgeq_f32(v, w);
    else  if constexpr( cat == category::int32x2  ) return vcge_s32(v, w);
    else  if constexpr( cat == category::int16x4  ) return vcge_s16(v, w);
    else  if constexpr( cat == category::int8x8   ) return vcge_s8(v, w);
    else  if constexpr( cat == category::uint32x2 ) return vcge_u32(v, w);
    else  if constexpr( cat == category::uint16x4 ) return vcge_u16(v, w);
    else  if constexpr( cat == category::uint8x8  ) return vcge_u8(v, w);
    else  if constexpr( cat == category::float32x2) return vcge_f32(v, w);
    else if constexpr( current_api >= asimd)
    {
      if constexpr( cat == category::float64x1) return vcge_f64(v, w);
      else  if constexpr( cat == category::int64x1)   return vcge_s64(v, w);
      else  if constexpr( cat == category::uint64x1)  return vcge_u64(v, w);
      else  if constexpr( cat == category::float64x2) return vcgeq_f64(v, w);
      else  if constexpr( cat == category::int64x2)   return vcgeq_s64(v, w);
      else  if constexpr( cat == category::uint64x2)  return vcgeq_u64(v, w);
    }
    else  if constexpr( sizeof(T) == 8 )
        return map([]<typename E>(E const& e, E const& f){ return as_logical_t<E>(e >= f); }, v, w);
  }
}
