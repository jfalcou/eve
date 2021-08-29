//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/laguerre.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/cospi.hpp>
#include <eve/function/derivative.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{

  template<integral_real_value N, floating_value T>
  EVE_FORCEINLINE constexpr T laguerre_(EVE_SUPPORTS(cpu_)
                                       , diff_type<1> const &
                                       , N const & n
                                       , T const &x) noexcept
  requires index_compatible_values<N, T>
  {
    return -laguerre(1, n, x);
  }

  template<integral_real_value M, integral_real_value N, floating_value T>
  EVE_FORCEINLINE constexpr T laguerre_(EVE_SUPPORTS(cpu_)
                                       , diff_type<1> const &
                                       , M const & m
                                       , N const & n
                                       , T const &x) noexcept
  requires index_compatible_values<N, T> && index_compatible_values<M, T>
  {
    return if_else(is_eqz(n), zero, cospi(m)*laguerre(inc(m), saturated(dec)(n), x);
  }
}
