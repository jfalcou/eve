//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<ordered_value T, ordered_value U, ordered_value V, ordered_value W >
  EVE_FORCEINLINE auto sum_of_prod_(EVE_SUPPORTS(cpu_)
                                   , pedantic_type const &
                                   , const T& a
                                   , const U& b
                                   , const V& c
                                   , const W& d
                                   ) noexcept -> decltype(a*b+c*d)
  {
    using r_t = decltype(a*b+c*d);
    return pedantic(sum_of_prod)(r_t(a), r_t(b), r_t(c), r_t(d));
  }

  template<ordered_value T>
  EVE_FORCEINLINE T sum_of_prod_(EVE_SUPPORTS(cpu_)
                                   , pedantic_type const &
                                   , const T& a
                                   , const T& b
                                   , const T& c
                                   , const T& d
                                   ) noexcept
  {
    if constexpr(std::is_integral_v<eve::element_type_t<T>>)
      return fma(a, b, c*d);
    else
    {
      T mcd = -c * d;
      T err = pedantic(fma)(c, d, mcd);
      T dop = pedantic(fms)(a, b, mcd);
      T r = if_else(is_finite(err), dop + err, dop);
      return r;
    }
  }
}
