//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/as.hpp>
#include <eve/as_element.hpp>
#include <eve/conditional.hpp>
#include <eve/module/core/constant/false.hpp>
#include <eve/module/core/regular/convert.hpp>
#include <eve/module/core/regular/if_else.hpp>

namespace eve::detail
{
  //================================================================================================
  // What's the alternative for this case ?
  //================================================================================================
  template<conditional_expr C, typename Target, typename Arg>
  EVE_FORCEINLINE Target alternative(C const& c, Arg a0, as<Target>)
  {
    if constexpr( C::has_alternative )  return Target{c.alternative};
    else
    {
      if      constexpr(logical_value<Target>)    return false_(as<Target>{});
      else if constexpr(std::same_as<Arg,Target>) return a0;
      else if constexpr(scalar_value<Arg>)        return Target(a0);
      else                                        return convert(a0, eve::as_element<Target>());
    }
  }

  //================================================================================================
  // Turn a conditional into a mask
  //================================================================================================
  template<conditional_expr C, typename Target>
  EVE_FORCEINLINE auto expand_mask(C const& c, as<Target>)
  {
    auto msk = c.mask( as<Target>{} );
    return as_logical_t<Target>(msk);
  }

  //================================================================================================
  // Handle the basic if/if_else cases
  //================================================================================================
  template<conditional_expr C, typename Op, typename Arg0, typename... Args>
  EVE_FORCEINLINE auto mask_op( C const& c
                              , [[maybe_unused]] Op f
                              , [[maybe_unused]] Arg0 const& a0
                              , [[maybe_unused]] Args const&... ax
                              )
  {
    using r_t = decltype(f(a0, ax...));

          if constexpr( C::is_complete && !C::is_inverted ) return alternative(c, a0, as<r_t>{});
    else  if constexpr( C::is_complete &&  C::is_inverted ) return f(a0, ax...);
    else return if_else(c.mask(as<r_t>{}), f(a0, ax...), alternative(c, a0, as<r_t>{}));
  }
}
