//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_BRANCH_HPP_INCLUDED
#define EVE_DETAIL_BRANCH_HPP_INCLUDED

namespace eve::detail
{
  template<bool Check, typename Cond, typename TC, typename TF>
  EVE_FORCEINLINE auto branch( Cond const & c, TC t, TF f)
  {
    if constexpr(Check) return [&c, t, f](auto&&... x) { return c ? t(x...) : f(x...); };
    else                return [&c, t, f](auto&&... x) { return if_else(c,t(x...),f(x...)); };
  }
}

#endif
