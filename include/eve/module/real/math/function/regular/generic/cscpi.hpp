//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pi.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/csc.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/sin.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/module/real/math/detail/generic/rem2.hpp>
#include <eve/module/real/math/detail/generic/trig_finalize.hpp>

#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto
  cscpi_(EVE_SUPPORTS(cpu_), restricted_type const &, T const &a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return restricted(csc)(a0 * pi(eve::as<T>()));
    }
    else
      return apply_over(restricted(cscpi), a0);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////
  // medium,  big,  small
  template<decorator D, floating_real_value T>
  EVE_FORCEINLINE constexpr auto cscpi_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( scalar_value<T> )
      {
        if( is_eqz(a0) )
          return rec(a0);
        if( is_flint(a0) || is_not_finite(a0) )
          return nan(eve::as<T>()); // nan or Inf input
      }
      T x = abs(a0);
      if constexpr( simd_value<T> )
      {
        x = if_else(is_nez(a0) && (is_not_finite(x) || is_flint(x)), eve::allbits, x);
      }
      auto [fn, xr, dxr] = rem2(x);
      return rec(sin_finalize(bitofsign(a0), quadrant(fn), xr, dxr));
    }
    else
      return apply_over(D()(cscpi), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cscpi_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if( eve::all(eve::abs(a0) <= T(0.25)) )
        return restricted(cscpi)(a0);
      else
        return big(cscpi)(a0);
    }
    else
      return apply_over(cscpi, a0);
  }
}
