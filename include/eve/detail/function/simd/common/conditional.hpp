//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/if_else.hpp>
#include <eve/constant/iota.hpp>

namespace eve::detail
{
  //================================================================================================
  // Handle the basic if{not}{_else} cases
  //================================================================================================
  template<typename ABI, conditional_expr C, typename Op, typename Arg0, typename... Args>
  EVE_FORCEINLINE auto mask_op( ABI const&, C const& c
                              , [[maybe_unused]] Op f
                              , [[maybe_unused]] Arg0 const& a0
                              , [[maybe_unused]] Args const&... as
                              )
  {
    using r_t             = decltype(f(a0,as...));
    auto const condition  = c.mask(eve::as<r_t>());

    // If the ignore/keep is complete we can jump over if_else
    if constexpr( C::is_complete )
    {
      if constexpr(C::is_inverted)  { return f(a0,as...); }
      else                          { return r_t(a0);     }
    }
    else
    {
      // If no optimizations are mandated by the conditional type, we just go over all mask cases.
      if constexpr( C::has_alternative && C::is_inverted)
      {
        return if_else(condition, c.alternative, f(a0,as...) );
      }
      else if constexpr( C::has_alternative && !C::is_inverted)
      {
        return if_else(condition, f(a0,as...), c.alternative );
      }
      else if constexpr( !C::has_alternative && C::is_inverted)
      {
        return if_else(condition, a0, f(a0,as...) );
      }
      else if constexpr( !C::has_alternative && !C::is_inverted)
      {
        return if_else(condition, f(a0,as...), a0 );
      }
    }
  }
}
