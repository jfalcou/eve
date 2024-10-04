//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/dec.hpp>
#include <eve/module/core/regular/is_greater.hpp>
#include <eve/module/core/regular/is_not_less_equal.hpp>
#include <eve/module/core/regular/trunc.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/inc.hpp>
#include <eve/module/core/regular/is_lez.hpp>
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/minus.hpp>
#include <eve/module/core/regular/oneminus.hpp>
#include <eve/module/core/regular/next.hpp>
#include <eve/module/core/detail/tolerance.hpp>

namespace eve::detail
{
  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr T
  floor_(EVE_REQUIRES(cpu_), O const& o, T const& a0) noexcept
  {
    if constexpr(integral_value<T>) return a0;
    else
    {
      if constexpr(O::contains(almost))
      {
        auto tol = o[almost].value(a0);
        if constexpr(integral_value<decltype(tol)>)
          return floor(next(a0, tol));
        else
        {
          // Hagerty's FL5 function
          auto q    = if_else(is_ltz(a0), one, oneminus(tol));
          auto rmax = q / (T(2) - tol);
          auto tol5 = tol / q;
          auto r    = floor(a0 + eve::max(tol, min(rmax, tol5 * eve::abs(inc(floor(a0))))));
          return if_else(is_lez(a0) || (r - a0 < rmax), r, dec(r));
        }
      }
      else
      {
        using elt_t = element_type_t<T>;
        using i_t   = as_integer_t<elt_t>;
        auto z = convert(convert(a0, as<i_t>()), as<elt_t>());

        auto already_integral = is_not_less_equal(eve::abs(a0), maxflint(eve::as<T>()));

             if constexpr( scalar_value<T> ) z = already_integral ? a0 : z;
        else if constexpr( simd_value<T> )   z = if_else(already_integral, a0, z);

        return dec[z > a0](z);
      }
    }
  }

  template<typename T, typename U, callable_options O>
  EVE_FORCEINLINE constexpr auto floor_(EVE_REQUIRES(cpu_), O const&, T const& a0, as<U>) noexcept
  {
    if constexpr(integral_value<T>) return convert(a0, as_element<as_integer_t<T,U>>{});
    else                            return convert(floor(a0), as_element<as_integer_t<T,U>>{});
  }
}
