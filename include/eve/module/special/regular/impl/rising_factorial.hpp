//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special/regular/lrising_factorial.hpp>
#include <eve/module/special/regular/signgam.hpp>
#include <eve/module/special/regular/tgamma.hpp>
#include <eve/traits/common_value.hpp>

namespace eve::detail
{
  template<typename I, typename T, callable_options O>
  constexpr EVE_FORCEINLINE as_wide_as_t<T, I>
  rising_factorial_(EVE_REQUIRES(cpu_), O const& d, I a, T x) noexcept
  {
    // Integral first parameter
    if constexpr(integral_value<I> )
    {
      if constexpr( integral_simd_value<I> )
      {
        using elt_t = element_type_t<T>;
        using r_t   = as_wide_t<elt_t, cardinal_t<I>>;
        auto aa     = convert(a, as(elt_t()));
        return rising_factorial[d](aa, r_t(x));
      }
      else if constexpr( integral_scalar_value<I> )
      {
        return rising_factorial[d](T(a), x);
      }
    }
    else
    {
      if constexpr( has_native_abi_v<T> )
      {
        if constexpr(O::contains(raw2))
        {
          // raw direct computation not matter why. nan if a+x or x is non positive
          return eve::tgamma(x + a) / tgamma(a);
        }
        else if constexpr(O::contains(pedantic2))
        {
          auto sga   = if_else(is_flint(a), one, signgam(a));
          auto sgapx = if_else(is_flint(a + x), one, signgam(a + x));
          return eve::exp(lrising_factorial[pedantic](a, x))*(sga * sgapx);
        }
        else if constexpr(O::contains(regular2))
        {
          // regular  nan if a+x or x is nnegative,  better computation than raw
          return eve::exp(lrising_factorial(a, x));
        }
        else return eve::exp(lrising_factorial[regular](a, x));
      }
      else
        return apply_over(regular(rising_factorial[d]), a, x);
    }
  }
}
