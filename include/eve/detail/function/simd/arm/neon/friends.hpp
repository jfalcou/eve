//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
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
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T,N> self_bitnot(wide<T,N> const& v) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
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
    else                                        return bit_cast(~bit_cast(v,as<i_t>{}), as(v));
  }

  //================================================================================================
  // operator== implementation
  //================================================================================================
  template<real_value T, typename N>
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
  template<real_value T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> self_neq(neon128_ const&, wide<T,N> v, wide<T,N> w) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    return !(v == w);
  }

  //================================================================================================
  // operator!= implementation
  //================================================================================================
  template<typename T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> self_less ( wide<T, N> v
                                                    , wide<T, N> w
                                                    ) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    constexpr auto cat = categorize<wide<T, N>>();

    if constexpr( cat == category::int32x4  ) return vcltq_s32(v, w);
    else  if constexpr( cat == category::int16x8  ) return vcltq_s16(v, w);
    else  if constexpr( cat == category::int8x16  ) return vcltq_s8(v, w);
    else  if constexpr( cat == category::uint32x4 ) return vcltq_u32(v, w);
    else  if constexpr( cat == category::uint16x8 ) return vcltq_u16(v, w);
    else  if constexpr( cat == category::uint8x16 ) return vcltq_u8(v, w);
    else  if constexpr( cat == category::float32x4) return vcltq_f32(v, w);
    else  if constexpr( cat == category::int32x2  ) return vclt_s32(v, w);
    else  if constexpr( cat == category::int16x4  ) return vclt_s16(v, w);
    else  if constexpr( cat == category::int8x8   ) return vclt_s8(v, w);
    else  if constexpr( cat == category::uint32x2 ) return vclt_u32(v, w);
    else  if constexpr( cat == category::uint16x4 ) return vclt_u16(v, w);
    else  if constexpr( cat == category::uint8x8  ) return vclt_u8(v, w);
    else  if constexpr( cat == category::float32x2) return vclt_f32(v, w);
    else if constexpr( current_api >= asimd)
    {
      if constexpr( cat == category::float64x1) return vclt_f64(v, w);
      else  if constexpr( cat == category::int64x1)   return vclt_s64(v, w);
      else  if constexpr( cat == category::uint64x1)  return vclt_u64(v, w);
      else  if constexpr( cat == category::float64x2) return vcltq_f64(v, w);
      else  if constexpr( cat == category::int64x2)   return vcltq_s64(v, w);
      else  if constexpr( cat == category::uint64x2)  return vcltq_u64(v, w);
    }
    else  if constexpr( sizeof(T) == 8 )
      return map([]<typename E>(E const& e, E const& f){ return as_logical_t<E>(e < f); }, v, w);

  }

  template<typename T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> self_greater( wide<T, N> v
                                                      , wide<T, N> w
                                                      ) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    constexpr auto cat = categorize<wide<T, N>>();

          if constexpr( cat == category::int32x4  ) return vcgtq_s32(v, w);
    else  if constexpr( cat == category::int16x8  ) return vcgtq_s16(v, w);
    else  if constexpr( cat == category::int8x16  ) return vcgtq_s8(v, w);
    else  if constexpr( cat == category::uint32x4 ) return vcgtq_u32(v, w);
    else  if constexpr( cat == category::uint16x8 ) return vcgtq_u16(v, w);
    else  if constexpr( cat == category::uint8x16 ) return vcgtq_u8(v, w);
    else  if constexpr( cat == category::float32x4) return vcgtq_f32(v, w);
    else  if constexpr( cat == category::int32x2  ) return vcgt_s32(v, w);
    else  if constexpr( cat == category::int16x4  ) return vcgt_s16(v, w);
    else  if constexpr( cat == category::int8x8   ) return vcgt_s8(v, w);
    else  if constexpr( cat == category::uint32x2 ) return vcgt_u32(v, w);
    else  if constexpr( cat == category::uint16x4 ) return vcgt_u16(v, w);
    else  if constexpr( cat == category::uint8x8  ) return vcgt_u8(v, w);
    else  if constexpr( cat == category::float32x2) return vcgt_f32(v, w);
    else if constexpr( current_api >= asimd)
    {
      if constexpr( cat == category::float64x1) return vcgt_f64(v, w);
      else  if constexpr( cat == category::int64x1)   return vcgt_s64(v, w);
      else  if constexpr( cat == category::uint64x1)  return vcgt_u64(v, w);
      else  if constexpr( cat == category::float64x2) return vcgtq_f64(v, w);
      else  if constexpr( cat == category::int64x2)   return vcgtq_s64(v, w);
      else  if constexpr( cat == category::uint64x2)  return vcgtq_u64(v, w);
    }
    else  if constexpr( sizeof(T) == 8 )
      return map([]<typename E>(E const& e, E const& f){ return as_logical_t<E>(e > f); }, v, w);
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

  template<typename T, typename N>
  EVE_FORCEINLINE logical<wide<T,N>> self_leq(wide<T, N> v,wide<T, N> w) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    constexpr auto cat = categorize<wide<T, N>>();

          if constexpr( cat == category::int32x4  ) return vcleq_s32(v, w);
    else  if constexpr( cat == category::int16x8  ) return vcleq_s16(v, w);
    else  if constexpr( cat == category::int8x16  ) return vcleq_s8(v, w);
    else  if constexpr( cat == category::uint32x4 ) return vcleq_u32(v, w);
    else  if constexpr( cat == category::uint16x8 ) return vcleq_u16(v, w);
    else  if constexpr( cat == category::uint8x16 ) return vcleq_u8(v, w);
    else  if constexpr( cat == category::float32x4) return vcleq_f32(v, w);
    else  if constexpr( cat == category::int32x2  ) return vcle_s32(v, w);
    else  if constexpr( cat == category::int16x4  ) return vcle_s16(v, w);
    else  if constexpr( cat == category::int8x8   ) return vcle_s8(v, w);
    else  if constexpr( cat == category::uint32x2 ) return vcle_u32(v, w);
    else  if constexpr( cat == category::uint16x4 ) return vcle_u16(v, w);
    else  if constexpr( cat == category::uint8x8  ) return vcle_u8(v, w);
    else  if constexpr( cat == category::float32x2) return vcle_f32(v, w);
    else if constexpr( current_api >= asimd)
    {
      if constexpr( cat == category::float64x1) return vcle_f64(v, w);
      else  if constexpr( cat == category::int64x1)   return vcle_s64(v, w);
      else  if constexpr( cat == category::uint64x1)  return vcle_u64(v, w);
      else  if constexpr( cat == category::float64x2) return vcleq_f64(v, w);
      else  if constexpr( cat == category::int64x2)   return vcleq_s64(v, w);
      else  if constexpr( cat == category::uint64x2)  return vcleq_u64(v, w);
    }
    else  if constexpr( sizeof(T) == 8 )
        return map([]<typename E>(E const& e, E const& f){ return as_logical_t<E>(e <= f); }, v, w);
  }
}
