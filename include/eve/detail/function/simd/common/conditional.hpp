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
#include <eve/conditional.hpp>

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

  template<conditional_expr C, typename BaseOp, typename MaskOp, typename Arg0, typename... Args>
  EVE_FORCEINLINE auto mask_op( x86_512_ const&, C const& c
                              , [[maybe_unused]] BaseOp f
                              , [[maybe_unused]] MaskOp g
                              , [[maybe_unused]] Arg0 const& a0
                              , [[maybe_unused]] Args const&... as
                              )
  {
    using r_t = decltype(f(a0,as...));

    // If the ignore/keep is complete we can jump over calling the masked operations
    if constexpr( C::is_complete )
    {
      if constexpr(C::is_inverted)  { return f(a0,as...); }
      else                          { return r_t(a0);     }
    }
    else
    {
      // Extract bitmap then use the function with mask support
      auto mask = [&](auto const& cx)
      {
        auto m = cx.bitmap( as_<r_t>{} );
        if constexpr( C::is_inverted )  return ~m;
        else                            return m;
      };

      // Prepare the source value
      auto src = [&](auto const& cx, auto const& s)
      {
        if constexpr( C::has_alternative )  return r_t{cx.alternative}; else return s;
      };

      return g( mask(c), src(c,a0), a0, as...);
    }
  }
}
