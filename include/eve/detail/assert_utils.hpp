//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/meta.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename A0, callable_options O, eve::value A1>
  constexpr EVE_FORCEINLINE bool assert_shift(O const& opts, A1 t) noexcept
  {
    using v1_t = element_type_t<A1>;
    constexpr v1_t Mx  = sizeof(element_type_t<A0>) * 8;
    auto m = opts[condition_key];

    auto wt = if_else(m, as_wide_as_t<A1, A0>{t}, v1_t{0});
    return eve::all((wt < Mx) && (wt >= 0));
  }

  template<typename A0, eve::value A1>
  constexpr EVE_FORCEINLINE bool assert_relative_shift(A1 t) noexcept
  {
    using v1_t = element_type_t<A1>;
    constexpr v1_t Mx  = sizeof(element_type_t<A0>) * 8;

    if constexpr(std::is_unsigned_v<element_type_t<A1>>)
    {
      return eve::all( t < Mx );
    }
    else
    {
      return eve::all( (t < Mx) && (t > -Mx) );
    }
  }

  template<typename A0, callable_options O, eve::value A1>
  constexpr EVE_FORCEINLINE bool assert_relative_shift(O const& opts, A1 t) noexcept
  {
    using v1_t = element_type_t<A1>;
    constexpr v1_t Mx  = sizeof(element_type_t<A0>) * 8;
    auto m = opts[condition_key];

    auto wt = if_else(m, as_wide_as_t<A1, A0>{t}, v1_t{0});
  
    if constexpr(std::is_unsigned_v<element_type_t<A1>>)
    {
      return eve::all( wt < Mx );
    }
    else
    {
      return eve::all( (wt < Mx) && (wt > -Mx) );
    }
  }
}
