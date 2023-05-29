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
#include <eve/detail/skeleton_calls.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/fma.hpp>
#include <eve/module/core/regular/fms.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_finite.hpp>

namespace eve::detail
{
  template<ordered_value T, ordered_value U, ordered_value V, ordered_value W >
  EVE_FORCEINLINE auto sum_of_prod_(EVE_SUPPORTS(cpu_)
                                   , const T& a
                                   , const U& b
                                   , const V& c
                                   , const W& d
                                   ) noexcept -> decltype(a*b+c*d)
  {
    using r_t = decltype(a*b+c*d);
    return sum_of_prod(r_t(a), r_t(b), r_t(c), r_t(d));
  }

  template<ordered_value T>
  EVE_FORCEINLINE auto sum_of_prod_(EVE_SUPPORTS(cpu_)
                                   , const T& a
                                   , const T& b
                                   , const T& c
                                   , const T& d
                                   ) noexcept
  requires(has_native_abi_v<T>)
  {
    if constexpr(std::is_integral_v<eve::element_type_t<T>>)
      return fma(a, b, c*d);
    else
    {
      T mcd = -c * d;
      T err = fma(c, d, mcd);
      T dop = fms(a, b, mcd);
      return if_else(is_finite(err), dop + err, dop);
    }
  }

  template<ordered_value T, ordered_value U, ordered_value V, ordered_value W >
  EVE_FORCEINLINE auto sum_of_prod_(EVE_SUPPORTS(cpu_)
                                   , raw_type const &
                                   , const T& a
                                   , const U& b
                                   , const V& c
                                   , const W& d
                                   )  noexcept -> decltype(a*b+c*d)
  {
    return  raw(sum_of_prod)(r_t(a), r_t(b), r_t(c), r_t(d));
  }

  template<ordered_value T>
  EVE_FORCEINLINE auto sum_of_prod_(EVE_SUPPORTS(cpu_)
                                   , raw_type const &
                                   , const T& a
                                   , const T& b
                                   , const T& c
                                   , const T& d
                                   ) noexcept
  requires(has_native_abi_v<T>)
  {
    return fma(a, b, c*d);
  }
}
