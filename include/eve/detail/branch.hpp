//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/if_else.hpp>

namespace eve::detail
{
  template<bool Check, typename Cond, typename TC, typename TF>
  EVE_FORCEINLINE auto branch( Cond const & c, TC t, TF f)
  {
    if constexpr(Check) return [&c, t, f](auto&&... x) { return c ? t(x...) : f(x...); };
    else                return [&c, t, f](auto&&... x) { return if_else(c, t(x...), f(x...)); };
  }

  template<bool Check, typename Cond, typename TC>
  EVE_FORCEINLINE auto branch( Cond const & c, TC t)
  {
    if constexpr(Check) return [&c, t](auto&& x0, auto&&... x) { return c ? t(x0, x...) : x0; };
    else                return [&c, t](auto&& x0, auto&&... x) { return if_else(c, t(x0, x...), x0); };
  }
  template<bool Check, typename TC, typename TF>
  EVE_FORCEINLINE auto choose(TC t, TF f)
  {
    if constexpr(Check) return [t, f](auto&&... x) { return t(x...);  };
    else                return [t, f](auto&&... x) { return f(x...); };
  }
}
