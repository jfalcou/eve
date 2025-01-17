//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/ldexp.hpp>
#include <eve/module/core/regular/round.hpp>


namespace eve::detail
{
  template<auto S, typename T, callable_options O>
  EVE_FORCEINLINE constexpr T roundscale_(EVE_REQUIRES(cpu_),
                                         O const& o,
                                         T const& a0,
                                         index_t<S> const &) noexcept
  {
    return roundscale[o](a0, S);
  }

  template<typename T, typename S, callable_options O>
  EVE_FORCEINLINE constexpr T roundscale_(EVE_REQUIRES(cpu_),
                                         O const & o,
                                         T const & a0,
                                         S const & scale) noexcept
  {
    return ldexp(round[o](ldexp(a0, scale)), -scale);
  }
}
