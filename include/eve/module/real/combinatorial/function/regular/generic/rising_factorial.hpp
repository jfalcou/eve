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
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/tgamma.hpp>
#include <eve/function/lrising_factorial.hpp>
#include <eve/function/raw.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/exp.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/traits/common_compatible.hpp>
#include <type_traits>


namespace eve::detail
{
  template<real_value I, floating_real_value T, decorator D>
  EVE_FORCEINLINE auto rising_factorial_(EVE_SUPPORTS(cpu_)
                                        , D const & d
                                        , I n,  T x) noexcept
  {
    if constexpr(integral_simd_value<I>)
    {
      using elt_t = element_type_t<T>;
      using r_t = as_wide_t<elt_t, cardinal_t<I>>;
      auto nn = convert(n, as(elt_t()));
      return d(rising_factorial)(nn, r_t(x));
    }
    else if  constexpr(integral_scalar_value<I>)
    {
      return d(rising_factorial)(T(n), x);
    }
    else
    {
      using r_t = common_compatible_t<I, T>;
      return d(rising_factorial)(r_t(n), r_t(x));
    }
  }

  // regular wrapping : no decorator
  template<real_value I,floating_real_value T>
  EVE_FORCEINLINE auto rising_factorial_(EVE_SUPPORTS(cpu_)
                                         , I a,  T x) noexcept
  {
    return rising_factorial(regular_type(), a, x);
  }

  // regular  nan if a+x or x is nnegative,  better computation than raw
  template<floating_real_value T>
  EVE_FORCEINLINE auto rising_factorial_(EVE_SUPPORTS(cpu_)
                                        , regular_type const &
                                        , T a,  T x) noexcept
  {
     if constexpr(has_native_abi_v<T>)
     {
       auto lrn = lrising_factorial(a, x);
       return eve::exp(lrn);
     }
    else
      return apply_over(regular_type()(rising_factorial), a, x);
  }

  // raw
  template<floating_real_value T>
  EVE_FORCEINLINE auto rising_factorial_(EVE_SUPPORTS(cpu_)
                                        , raw_type const &
                                        , T a,  T x) noexcept
  {
     if constexpr(has_native_abi_v<T>)
     {
       return eve::tgamma(x+a)/tgamma(a);
     }
    else
      return apply_over(regular_type()(rising_factorial), a, x);
  }
}
