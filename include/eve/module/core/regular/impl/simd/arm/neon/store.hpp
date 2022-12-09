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

#include <type_traits>

namespace eve::detail
{
template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE void
store_(EVE_SUPPORTS(neon128_), wide<T, N> value, T *ptr) noexcept requires arm_abi<abi_t<T, N>>
{
  if constexpr( std::is_same_v<abi_t<T, N>, arm_64_> && (N::value * sizeof(T) != arm_64_::bytes) )
  {
    memcpy(ptr, (T const *)(&value), N::value * sizeof(T));
  }
  else
  {
    constexpr auto cat = categorize<wide<T, N>>();
    if constexpr( cat == category::float32x2 ) vst1_f32(ptr, value);
    else if constexpr( cat == category::float32x4 ) vst1q_f32(ptr, value);
    else if constexpr( cat == category::int64x1 ) vst1_s64(ptr, value);
    else if constexpr( cat == category::int64x2 ) vst1q_s64(ptr, value);
    else if constexpr( cat == category::uint64x1 ) vst1_u64(ptr, value);
    else if constexpr( cat == category::uint64x2 ) vst1q_u64(ptr, value);
    else if constexpr( cat == category::int32x2 ) vst1_s32(ptr, value);
    else if constexpr( cat == category::int32x4 ) vst1q_s32(ptr, value);
    else if constexpr( cat == category::uint32x2 ) vst1_u32(ptr, value);
    else if constexpr( cat == category::uint32x4 ) vst1q_u32(ptr, value);
    else if constexpr( cat == category::int16x4 ) vst1_s16(ptr, value);
    else if constexpr( cat == category::int16x8 ) vst1q_s16(ptr, value);
    else if constexpr( cat == category::uint16x4 ) vst1_u16(ptr, value);
    else if constexpr( cat == category::uint16x8 ) vst1q_u16(ptr, value);
    else if constexpr( cat == category::int8x8 ) vst1_s8(ptr, value);
    else if constexpr( cat == category::int8x16 ) vst1q_s8(ptr, value);
    else if constexpr( cat == category::uint8x8 ) vst1_u8(ptr, value);
    else if constexpr( cat == category::uint8x16 ) vst1q_u8(ptr, value);
    else if constexpr( current_api >= asimd )
    {
      if constexpr( cat == category::float64x1 ) vst1_f64(ptr, value);
      else if constexpr( cat == category::float64x2 ) vst1q_f64(ptr, value);
    }
  }
}

#if defined(SPY_COMPILER_IS_MSVC)
template<arithmetic_scalar_value T, typename N, typename Lanes>
EVE_FORCEINLINE void
store_(EVE_SUPPORTS(neon128_),
       wide<T, N>            value,
       aligned_ptr<T, Lanes> ptr) noexcept requires arm_abi<abi_t<T, N>>
{
  if constexpr( std::is_same<abi_t<T, N>, arm_64_> && (N::value * sizeof(T) != arm_64_::bytes) )
  {
    memcpy(ptr, (T const *)(&value), N::value * sizeof(T));
  }
  else
  {
    constexpr auto cat = categorize<wide<T, N>>();
    if constexpr( cat == category::float32x2 ) vst1_f32_ex(ptr, value, 64);
    else if constexpr( cat == category::float32x4 ) vst1_f32_ex(ptr, value, 128);
    else if constexpr( cat == category::int64x1 ) vst1_s64_ex(ptr, value, 64);
    else if constexpr( cat == category::int64x2 ) vst1_s64_ex(ptr, value, 128);
    else if constexpr( cat == category::uint64x1 ) vst1_u64_ex(ptr, value, 64);
    else if constexpr( cat == category::uint64x2 ) vst1_u64_ex(ptr, value, 128);
    else if constexpr( cat == category::int32x2 ) vst1_s32_ex(ptr, value, 64);
    else if constexpr( cat == category::int32x4 ) vst1_s32_ex(ptr, value, 128);
    else if constexpr( cat == category::uint32x2 ) vst1_u32_ex(ptr, value, 64);
    else if constexpr( cat == category::uint32x4 ) vst1_u32_ex(ptr, value, 128);
    else if constexpr( cat == category::int16x4 ) vst1_s16_ex(ptr, value, 64);
    else if constexpr( cat == category::int16x8 ) vst1_s16_ex(ptr, value, 128);
    else if constexpr( cat == category::uint16x4 ) vst1_u16_ex(ptr, value, 64);
    else if constexpr( cat == category::uint16x8 ) vst1_u16_ex(ptr, value, 128);
    else if constexpr( cat == category::int8x8 ) vst1_s8_ex(ptr, value, 64);
    else if constexpr( cat == category::int8x16 ) vst1_s8_ex(ptr, value, 128);
    else if constexpr( cat == category::uint8x8 ) vst1_u8_ex(ptr, value, 64);
    else if constexpr( cat == category::uint8x16 ) vst1_u8_ex(ptr, value, 128);
    else if constexpr( current_api >= asimd )
    {
      if constexpr( cat == category::float64x1 ) vst1_f64_ex(ptr, value, 64);
      else if constexpr( cat == category::float64x2 ) vst1_f64_ex(ptr, value, 128);
    }
  }
}
#else
template<arithmetic_scalar_value T, typename S, typename Lanes>
EVE_FORCEINLINE void
store_(EVE_SUPPORTS(neon128_),
       wide<T, S>            value,
       aligned_ptr<T, Lanes> ptr) noexcept requires arm_abi<abi_t<T, S>>
{
  store(value, ptr.get());
}
#endif
}
