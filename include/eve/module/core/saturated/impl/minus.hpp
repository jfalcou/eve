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
#include <eve/module/core/constant/signmask.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/decorator/saturated.hpp>
#include <eve/module/core/regular/bit_xor.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/saturated/sub.hpp>

#include <type_traits>

namespace eve::detail
{
template<ordered_value T>
EVE_FORCEINLINE constexpr T
minus_(EVE_SUPPORTS(cpu_), saturated_type const&, T v) noexcept
{
  if constexpr( floating_value<T> ) return bit_xor(v, signmask(eve::as(v)));
  else return if_else(v == valmin(as<T>()), valmax(as<T>()), minus(v));
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, ordered_value U>
EVE_FORCEINLINE auto
minus_(EVE_SUPPORTS(cpu_), C const& cond, saturated_type const&, U const& t) noexcept
{
  return mask_op(cond, saturated(eve::minus), t);
}

template<conditional_expr C, ordered_value U, ordered_value V>
EVE_FORCEINLINE auto
minus_(EVE_SUPPORTS(cpu_),
       C const& cond,
       saturated_type const&,
       U const& t,
       V const& f) noexcept
->decltype(sub(t, f))
{
  auto substract = [](auto x, auto y) { return saturated(sub)(x, y); };
  return mask_op(cond, substract(t, f), t);
}
}
