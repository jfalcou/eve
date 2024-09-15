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
    auto sm = signmask(eve::as<r_t>());
    r_t a0    = bit_cast(a, as<r_t>());
    if constexpr(scalar_value<T>)
    {
      using u_t = as_integer_t<T, unsigned>;
      return is_gez(a0) ? a0 :   r_t(u_t(sm)-u_t(a0));
    }
    else
      return if_else(is_gez(a0), a0, signmask(eve::as<r_t>()) - a0);
  }

  template<typename T>
  EVE_FORCEINLINE constexpr as_floating_point_t<T>
  bitfloating(T const& a) noexcept
  {
    using r_t = as_floating_point_t<T>;
    T s       = bit_cast(signmask(eve::as<r_t>()), as<T>());
    if constexpr(signed_integral_scalar_value<T>)
    {
      using u_t = as_integer_t<T, unsigned>;
      return  bit_cast(is_gez(a) ? a : (u_t(s)+u_t(-a)), as<r_t>());
    }
    else
      return bit_cast(if_else(is_gez(a), a, s - a), as<r_t>());
  }

}
