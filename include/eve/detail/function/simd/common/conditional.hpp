//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/if_else.hpp>
#include <eve/conditional.hpp>

namespace eve::detail
{
  //================================================================================================
  // What's the alternative for this case ?
  //================================================================================================
  template<conditional_expr C, typename Target, typename Arg>
  EVE_FORCEINLINE auto alternative(C const& c, Arg a0, as_<Target> const&)
  {
    if constexpr( C::has_alternative )  return Target{c.alternative};
    else                                return a0;
  }

  //================================================================================================
  // Turn a conditional into a mask
  //================================================================================================
  template<conditional_expr C, typename Target>
  EVE_FORCEINLINE auto expand_mask(C const& c, as_<Target> const&)
  {
    auto m = [](auto cx)
    {
      auto msk = cx.mask( as_<Target>{} );
      return as_wide_t<decltype(msk), cardinal_t<Target>>(msk);
    }(c);

    if constexpr( C::is_inverted ) m = !m;
    return m;
  }

  //================================================================================================
  // Handle the basic if/if_else cases
  //================================================================================================
  template<conditional_expr C, typename Op, typename Arg0, typename... Args>
  EVE_FORCEINLINE auto mask_op( C const& c
                              , [[maybe_unused]] Op f
                              , [[maybe_unused]] Arg0 const& a0
                              , [[maybe_unused]] Args const&... as
                              )
  {
    using r_t       = decltype(f(a0,as...));
    auto const cond = c.mask(eve::as<r_t>());

          if constexpr( C::is_complete && !C::is_inverted ) return alternative(c,a0,as_<r_t>{});
    else  if constexpr( C::is_complete &&  C::is_inverted ) return f(a0,as...);
    else                                                    return if_else( cond
                                                                          , f(a0,as...)
                                                                          , alternative(c,a0,as_<r_t>{})
                                                                          );
  }
}
