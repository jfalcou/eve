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
  EVE_FORCEINLINE auto mask_op( ABI const &, C const& c, Op f, Arg0 const& a0, Args const&... as)
  {
    using r_t             = decltype(f(a0,as...));
    using condition_type  = decltype(c.condition(as_<r_t>()));
    auto const condition  = c.condition(as_<r_t>());

    // Scalar mode use ?: for efficiency
    if constexpr( scalar_value<condition_type> )
    {
      // If no optimizations are mandated by the conditional type, we just go over all mask cases.
      if constexpr( C::has_alternative && C::is_inverted)
      {
        return condition ? r_t(c.alternative) : f(a0,as...);
      }
      else if constexpr( C::has_alternative && !C::is_inverted)
      {
        return condition ? f(a0,as...): r_t(c.alternative);
      }
      else if constexpr( !C::has_alternative && C::is_inverted)
      {
        return condition ? r_t(a0) : f(a0,as...);
      }
      else if constexpr( !C::has_alternative && !C::is_inverted)
      {
        return condition ? f(a0,as...) : r_t(a0);
      }
    }
    else
    {
      // If no optimizations are mandated by the conditional type, we just go over all mask cases.
      if constexpr( C::has_alternative && C::is_inverted)
      {
        return if_else(condition, r_t(c.alternative), f(a0,as...) );
      }
      else if constexpr( C::has_alternative && !C::is_inverted)
      {
        return if_else(condition, f(a0,as...), r_t(c.alternative) );
      }
      else if constexpr( !C::has_alternative && C::is_inverted)
      {
        return if_else(condition, r_t(a0), f(a0,as...) );
      }
      else if constexpr( !C::has_alternative && !C::is_inverted)
      {
        return if_else(condition, f(a0,as...), r_t(a0) );
      }
    }
  }

  //================================================================================================
  // Handle the ignore_all/none cases to ensure no extra codegen
  //================================================================================================
  template<typename ABI, bool B, typename Op, typename Arg0, typename... Args>
  EVE_FORCEINLINE auto mask_op( ABI const&, ignore_<B> const&
                              , [[maybe_unused]] Op f
                              , [[maybe_unused]] Arg0 const& a0
                              , [[maybe_unused]] Args const&... as
                              )
  {
    if constexpr(B)
    {
      return f(a0,as...);
    }
    else
    {
      using r_t = decltype(std::declval<Op>()(a0,std::declval<Args>()...));
      return r_t(a0);
    }
  }
}
