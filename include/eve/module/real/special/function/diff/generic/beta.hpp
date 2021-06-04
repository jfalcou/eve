//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/beta.hpp>
#include <eve/function/digamma.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/fnma.hpp>

namespace eve::detail
{
  template<floating_value T, floating_value U, auto N>
  EVE_FORCEINLINE  auto beta_(EVE_SUPPORTS(cpu_)
                              , diff_type<N> const &
                              , T const &a
                              , U const &b) noexcept
  -> decltype(arithmetic_call(diff_type<N>{}(beta), a, b))
  {
    return arithmetic_call(diff_type<N>{}(beta), a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T beta_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , T const &x
                                  , T const &y) noexcept
  requires(has_native_abi_v<T>)
  {
    return fnma(digamma(x), beta(x, y), digamma(x + y));
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T beta_(EVE_SUPPORTS(cpu_)
                                  , diff_type<2> const &
                                  , T const &x
                                  , T const &y) noexcept
  requires(has_native_abi_v<T>)
  {
    return  fnma(digamma(y), beta(x, y), digamma(x + y));
  }
}
