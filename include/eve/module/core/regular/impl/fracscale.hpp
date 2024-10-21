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
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/ldexp.hpp>
#include <eve/module/core/regular/round.hpp>

namespace eve::detail
{
  template<auto S, typename T, callable_options O>
  EVE_FORCEINLINE constexpr T fracscale_(EVE_REQUIRES(cpu_),
                                         O const& o,
                                         T const& a0,
                                         index_t<S> const &) noexcept
  {
    return fracscale[o](a0, S);
  }

  template<typename T, typename S, callable_options O>
  EVE_FORCEINLINE constexpr T fracscale_(EVE_REQUIRES(cpu_),
                                         O const& o,
                                         T const & a0,
                                         S const & scale) noexcept
  {
    auto tmp =  a0 - ldexp(round[o.drop(pedantic)](ldexp(a0, scale)), -scale);
    if constexpr(O::contains(pedantic) && platform::supports_infinites)
      return if_else(is_infinite(a0), zero, tmp);
    else
      return tmp;
  }
}
