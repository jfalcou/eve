//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/log.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/factorial.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/none.hpp>
#include <eve/function/pow.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/derivative.hpp>
#include <eve/constant/one.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N>
  EVE_FORCEINLINE constexpr T log_(EVE_SUPPORTS(cpu_)
                                   , diff_type<1> const &
                                   , T x
                                   , N n) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      using elt_t = element_type_t<T>;
      x = if_else(is_ltz(x), allbits, x);

      auto tmp = inc(-2*to_<elt_t>(n-(n/2)*2))*pow(rec(x), n)*factorial(dec(n));
      if (none(is_eqz(n))) return tmp;
      return if_else(is_gtz(n), tmp, log(x));
    }
    else
      return apply_over(diff_1st(log), x, n);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T log_(EVE_SUPPORTS(cpu_)
                                    , diff_type<1> const &
                                    , T x) noexcept
  {
    return if_else(is_gtz(x), rec(x), allbits); ;
  }
}
