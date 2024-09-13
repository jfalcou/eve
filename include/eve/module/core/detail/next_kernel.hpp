//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/constant/signmask.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_gez.hpp>

namespace eve::detail
{
template<typename T>
EVE_FORCEINLINE constexpr as_integer_t<T>
bitinteger(T const& a) noexcept
{
  using r_t = as_integer_t<T>;
  r_t a0    = bit_cast(a, as<r_t>());
  auto test = is_gez(a0);
  r_t a0m   = if_else(test, zero, a0);
  return if_else(test, a0, signmask(eve::as<r_t>()) - a0m);
}

template<typename T>
EVE_FORCEINLINE constexpr as_floating_point_t<T>
bitfloating(T const& a) noexcept
{
  using r_t = as_floating_point_t<T>;
  auto test = is_gez(a);
  auto am   =  if_else(test, zero, a);
  T s       = bit_cast(signmask(eve::as<r_t>()), as<T>());
  return bit_cast(if_else(test, a, s - am), as<r_t>());
}

}
