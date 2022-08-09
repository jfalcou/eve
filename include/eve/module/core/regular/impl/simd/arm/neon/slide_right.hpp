//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/function/bit_cast.hpp>

namespace eve::detail
{

template<typename T, typename N, std::ptrdiff_t Shift>
EVE_FORCEINLINE wide<T, N>
                slide_right_arm_extract(wide<T, N> x, wide<T, N> y, index_t<Shift>)
{
  constexpr auto c = categorize<wide<T, N>>();

  // This works for smaller than 8 byte wides on a slide right with 0.
  // I don't understand why but it does, I tested.
  // The previous comment, that I didn't understand was:
  //   The actual shift uses the expected cardinal so it has enough
  //   to push through the unused space.
  constexpr auto shf = expected_cardinal_v<T, abi_t<T, N>> - Shift;

  if constexpr( c == category::int64x2 ) return vextq_s64(x, y, shf);
  else if constexpr( c == category::uint64x2 ) return vextq_u64(x, y, shf);
  else if constexpr( c == category::int64x1 ) return vext_s64(x, y, shf);
  else if constexpr( c == category::uint64x1 ) return vext_u64(x, y, shf);
  else if constexpr( c == category::int32x4 ) return vextq_s32(x, y, shf);
  else if constexpr( c == category::uint32x4 ) return vextq_u32(x, y, shf);
  else if constexpr( c == category::int32x2 ) return vext_s32(x, y, shf);
  else if constexpr( c == category::uint32x2 ) return vext_u32(x, y, shf);
  else if constexpr( c == category::int16x8 ) return vextq_s16(x, y, shf);
  else if constexpr( c == category::uint16x8 ) return vextq_u16(x, y, shf);
  else if constexpr( c == category::int16x4 ) return vext_s16(x, y, shf);
  else if constexpr( c == category::uint16x4 ) return vext_u16(x, y, shf);
  else if constexpr( c == category::int8x16 ) return vextq_s8(x, y, shf);
  else if constexpr( c == category::uint8x16 ) return vextq_u8(x, y, shf);
  else if constexpr( c == category::int8x8 ) return vext_s8(x, y, shf);
  else if constexpr( c == category::uint8x8 ) return vext_u8(x, y, shf);
  else
  {
    using i_t = as_integer_t<wide<T, N>>;
    return bit_cast(
        slide_right_arm_extract(bit_cast(x, as<i_t> {}), bit_cast(y, as<i_t> {}), index<Shift>),
        as(x));
  }
}

template<real_scalar_value T, typename N, std::ptrdiff_t Shift>
    EVE_FORCEINLINE wide<T, N>
                    slide_right_(EVE_SUPPORTS(neon128_),
                                 wide<T, N>     x,
                                 wide<T, N>     y,
                                 index_t<Shift> s) requires(0 < Shift && Shift < N::value)
    && native_simd_for_abi<wide<T, N>, arm_64_, arm_128_>
{
  return slide_right_arm_extract(x, y, s);
}

template<real_scalar_value T, typename N, std::ptrdiff_t Shift>
    EVE_FORCEINLINE wide<T, N>
                    slide_right_(EVE_SUPPORTS(neon128_), wide<T, N> v, index_t<Shift> s) noexcept
    requires(0 < Shift && Shift < N::value)
    && arm_abi<abi_t<T, N>>
{
  return slide_right_arm_extract(wide<T, N> {0}, v, s);
}
}
