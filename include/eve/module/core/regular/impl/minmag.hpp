//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/common_value.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_not_less_equal.hpp>
#include <eve/module/core/regular/min.hpp>

namespace eve::detail
{
  template<typename T0, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr common_value_t<T0, Ts...>
  minmag_(EVE_REQUIRES(cpu_), O const & o, T0 a0, Ts... as) noexcept
  {
    using r_t = common_value_t<T0, Ts...>;
    auto mino = min[o.drop(saturated)];
    auto abso = abs[saturated];
    auto a = r_t(a0);
    if constexpr(sizeof...(Ts) == 1) // 2 parameters
    {
      auto b = r_t(as...);
      if constexpr(O::contains(numeric))
      {
        auto aaa = if_else(is_nan(a), b, a);
        auto bbb = if_else(is_nan(b), a, b);
        return eve::minmag[pedantic](aaa, bbb);
      }
      else
      {
        auto ra = r_t(a);
        auto rb = r_t(b);
        constexpr bool is_scalar = scalar_value<r_t>;
        auto aa = abso(ra);
        auto bb = abso(rb);
        if constexpr(is_scalar)
        {
          return aa < bb ? ra : bb < aa ? rb : mino(ra, rb);
        }
        else
        {
          auto tmp = if_else(is_not_less_equal(aa, bb), rb, mino(ra, rb));
          return if_else(is_not_less_equal(bb, aa), ra, tmp);
        }
      }
    }
    else // N > 2 parameters
    {
      if constexpr(scalar_value<r_t> && (sizeof...(Ts)+1 >= eve::expected_cardinal_v<r_t>))
      {
        auto head = eve::as_wides(eve::majorant(eve::as<r_t>()), a, as...);
        auto s = eve::minmag[o](head);
        return butterfly_reduction(s, eve::minmag[o]).get(0);
      }
      else
      {
        r_t that(a);
        ((that = eve::minmag[o](that, r_t(as))), ...);
        return that;
      }
    }
  }
}
