//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/category.hpp>
#include <eve/function/combine.hpp>
#include <eve/function/convert.hpp>

namespace eve::detail
{
  template<integral_scalar_value T, typename N>
  EVE_FORCEINLINE
  auto mul_(EVE_SUPPORTS(neon128_),
            promoted_type const &,
            wide<T, N> a,
            wide<T, N> b) noexcept
  requires arm_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>();
    using r_t = wide<upgrade_t<T> , N>>;
    if constexpr(sizeof(T) == 8)            return a*b;
    else  if constexpr(c == category::int8x8   )  return r_t(vmull_s8(a, b));
    else  if constexpr(c == category::int16x4  )  return r_t(vmull_s16(a, b));
    else  if constexpr(c == category::int32x2  )  return r_t(vmull_s32(a, b));
    else  if constexpr(c == category::uint8x8  )  return r_t(vmull_u8(a, b));
    else  if constexpr(c == category::uint16x4 )  return r_t(vmull_u16(a, b));
    else  if constexpr(c == category::uint32x2 )  return r_t(vmull_u32(a, b));
    else
    {
      auto [la, ha] = a.slice();
      auto [lb, hb] = b.slice();
      return eve::combine( promoted(mul)(la,lb), promoted(mul)(ha,hb) );
    }
  }
}
