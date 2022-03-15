//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/detail/hz_device.hpp>
#include <eve/module/special/detail/lrising_factorial.hpp>

namespace eve::detail
{
  //general case
  template<real_value I, floating_real_value T, decorator D>
  EVE_FORCEINLINE common_compatible_t<I, T> lrising_factorial_(EVE_SUPPORTS(cpu_)
                                         , D const & d
                                         , I n,  T x) noexcept
  {
    if constexpr(integral_simd_value<I>)
    {
      using elt_t = element_type_t<T>;
      using r_t = as_wide_t<elt_t, cardinal_t<I>>;
      auto nn = convert(n, as(elt_t()));
      return d(lrising_factorial)(nn, r_t(x));
    }
    else if  constexpr(integral_scalar_value<I>)
    {
      return d(lrising_factorial)(T(n), x);
    }
    else
    {
      using r_t = common_compatible_t<I, T>;
      return d(lrising_factorial)(r_t(n), r_t(x));
    }
  }

  // regular wrapping : no decorator
  template<real_value I,floating_real_value T>
  EVE_FORCEINLINE auto lrising_factorial_(EVE_SUPPORTS(cpu_)
                                         , I a,  T x) noexcept
  {
    return lrising_factorial(regular_type(), a, x);
  }

  // regular  nan if a+x or x is nnegative,  better computation than raw
  template<floating_real_value T>
  EVE_FORCEINLINE auto lrising_factorial_(EVE_SUPPORTS(cpu_)
                                         , regular_type const &
                                         , T a,  T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto lr0 = []()
        {
          return zero(as(T()));
        };
      auto lrpos = [](auto a, auto x)
        {
          return inner_lrising_factorial(a, x);
        };

      auto r = nan(as(a));
      auto notdone = is_nltz(x) || is_nltz(a+x);
      if( eve::any(notdone) )
      {
        notdone = next_interval(lr0,  notdone, is_eqz(x), r);
        if( eve::any(notdone) )
        {
          notdone = last_interval(lrpos, notdone, r, a, x);
        }
      }
      return r;
    }
    else
      return apply_over(regular(lrising_factorial), a, x);
  }

  // raw direct computation not matter why. nan if a+x or x is non positive
  template<floating_real_value T>
  EVE_FORCEINLINE auto lrising_factorial_(EVE_SUPPORTS(cpu_)
                                         , raw_type const &
                                         , T a,  T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto notdone = is_nlez(x) && is_nlez(a+x);
      return if_else(notdone, lgamma(x+a)-lgamma(a), allbits);
    }
    else
      return apply_over(raw(lrising_factorial), a, x);
  }
}
