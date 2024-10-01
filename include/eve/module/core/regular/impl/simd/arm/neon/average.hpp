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
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/constant/half.hpp>
#include <eve/module/core/regular/fma.hpp>

#include <type_traits>

namespace eve::detail
{
template<arithmetic_scalar_value T, typename N, callable_options O>
EVE_FORCEINLINE wide<T, N> average_(EVE_REQUIRES(neon128_),
                                    O          const &opts,
                                    wide<T, N> const &v0,
                                    wide<T, N> const &v1) noexcept
requires arm_abi<abi_t<T, N>>
{
  constexpr auto cat = categorize<wide<T, N>>();

  if constexpr( O::contains(upper) && integral_value<T>)
    return average.behavior(cpu_{}, opts, v0, v1);
  if constexpr( std::is_floating_point_v<T> )
    return fma[opts](v0, half(eve::as(v0)), v1 * half(eve::as(v1)));
  else if constexpr( sizeof(T) == 8 ) return map_pt(as<wide<T, N>>{}, average, v0, v1);
  else if constexpr( cat == category::int32x4 ) return vhaddq_s32(v0, v1);
  else if constexpr( cat == category::int16x8 ) return vhaddq_s16(v0, v1);
  else if constexpr( cat == category::int8x16 ) return vhaddq_s8(v0, v1);
  else if constexpr( cat == category::uint32x4 ) return vhaddq_u32(v0, v1);
  else if constexpr( cat == category::uint16x8 ) return vhaddq_u16(v0, v1);
  else if constexpr( cat == category::uint8x16 ) return vhaddq_u8(v0, v1);
  else if constexpr( cat == category::int32x2 ) return vhadd_s32(v0, v1);
  else if constexpr( cat == category::int16x4 ) return vhadd_s16(v0, v1);
  else if constexpr( cat == category::int8x8 ) return vhadd_s8(v0, v1);
  else if constexpr( cat == category::uint32x2 ) return vhadd_u32(v0, v1);
  else if constexpr( cat == category::uint16x4 ) return vhadd_u16(v0, v1);
  else if constexpr( cat == category::uint8x8 ) return vhadd_u8(v0, v1);
}
}
