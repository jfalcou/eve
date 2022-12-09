//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/reduce.hpp>

namespace eve::detail
{
template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE T
maximum_(EVE_SUPPORTS(neon128_), wide<T, N> v) noexcept requires arm_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();

  if constexpr( eve::current_api >= eve::asimd )
  {
    using ec_t = expected_cardinal_t<T, abi_t<T, N>>;

    if constexpr( N::value == 1 ) return v.get(0);
    else if constexpr( N::value < ec_t::value ) return butterfly_reduction(v, eve::max).get(0);
    else if constexpr( c == category::float64x2 ) return vmaxvq_f64(v);
    else if constexpr( c == category::float32x2 ) return vmaxv_f32(v);
    else if constexpr( c == category::float32x4 ) return vmaxvq_f32(v);
    else if constexpr( c == category::int32x2 ) return vmaxv_s32(v);
    else if constexpr( c == category::int32x4 ) return vmaxvq_s32(v);
    else if constexpr( c == category::uint32x2 ) return vmaxv_u32(v);
    else if constexpr( c == category::uint32x4 ) return vmaxvq_u32(v);
    else if constexpr( c == category::int16x4 ) return vmaxv_s16(v);
    else if constexpr( c == category::int16x8 ) return vmaxvq_s16(v);
    else if constexpr( c == category::uint16x4 ) return vmaxv_u16(v);
    else if constexpr( c == category::uint16x8 ) return vmaxvq_u16(v);
    else if constexpr( c == category::int8x8 ) return vmaxv_s8(v);
    else if constexpr( c == category::int8x16 ) return vmaxvq_s8(v);
    else if constexpr( c == category::uint8x8 ) return vmaxv_u8(v);
    else if constexpr( c == category::uint8x16 ) return vmaxvq_u8(v);
    else return butterfly_reduction(v, eve::max).get(0);
  }
  else { return splat(maximum)(v).get(0); }
}

template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                maximum_(EVE_SUPPORTS(neon128_),
                         splat_type const&,
                         wide<T, N> const                &v) noexcept requires arm_abi<abi_t<T, N>>
{
  if constexpr( eve::current_api >= eve::asimd ) { return wide<T, N>(maximum(v)); }
  else
  {
    constexpr auto pairwise_max = []<typename W>(W const& a, W const& b)
    {
      constexpr auto c = categorize<W>();

      if constexpr( c == category::float32x2 ) return vpmax_f32(a, b);
      else if constexpr( c == category::int32x2 ) return vpmax_s32(a, b);
      else if constexpr( c == category::uint32x2 ) return vpmax_u32(a, b);
      else if constexpr( c == category::int16x4 ) return vpmax_s16(a, b);
      else if constexpr( c == category::uint16x4 ) return vpmax_u16(a, b);
      else if constexpr( c == category::int8x8 ) return vpmax_s8(a, b);
      else if constexpr( c == category::uint8x8 ) return vpmax_u8(a, b);
    };

    using type = wide<T, N>;

    if constexpr( N::value == 1 ) return v;
    else if constexpr( N::value == 2 ) return type(eve::max(v.get(0), v.get(1)));
    else if constexpr( std::same_as<abi_t<T, N>, arm_64_> )
    {
      if( N::value == expected_cardinal_v<T, abi_t<T, N>> )
      {
        wide<T, N> s = pairwise_max(v, v);
        if constexpr( N::value >= 2 ) s = pairwise_max(s, s);
        if constexpr( N::value >= 4 ) s = pairwise_max(s, s);
        if constexpr( N::value >= 8 ) s = pairwise_max(s, s);
        return s;
      }
      else { return butterfly_reduction(v, eve::max); }
    }
    else if constexpr( std::same_as<abi_t<T, N>, arm_128_> )
    {
      auto [l, h] = v.slice();
      if constexpr( N::value >= 4 ) l = pairwise_max(l, h);
      if constexpr( N::value >= 8 ) l = pairwise_max(l, l);
      if constexpr( N::value >= 16 ) l = pairwise_max(l, l);
      l = pairwise_max(l, l);

      return wide<T, N>(l, l);
    }
  }
}
}
