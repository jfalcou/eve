//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/bit_width.hpp>
#include <eve/module/core/regular/converter.hpp>
#include <eve/module/core/regular/dec.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/ifrexp.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/regular/ldexp.hpp>

#include <type_traits>

namespace eve::detail
{
template<real_value T>
EVE_FORCEINLINE T
bit_floor_(EVE_SUPPORTS(cpu_), T v) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto vlt1 = v < one(eve::as(v));
    if constexpr( scalar_value<T> )
      if( vlt1 ) return zero(eve::as(v));
    if constexpr( floating_real_value<T> )
    {
      auto [m, e] = ifrexp(v);
      e           = dec(e);
      auto r      = eve::ldexp(one(eve::as(v)), e);
      if constexpr( scalar_value<T> ) return r;
      else return if_else(vlt1, eve::zero, r);
    }
    else if constexpr( signed_integral_value<T> )
    {
      auto uz = bit_floor(uint_(v));
      return if_else(is_ltz(v), zero, to_<T>(uz));
    }
    else { return if_else(is_eqz(v), zero, T {1} << dec(bit_width(v))); }
  }
  else return apply_over(bit_floor, v);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_value U>
EVE_FORCEINLINE auto
bit_floor_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::bit_floor, t);
}
}
