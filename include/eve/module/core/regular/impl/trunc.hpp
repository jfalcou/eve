//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/module/core/constant/maxflint.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/convert.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_not_less_equal.hpp>
#include <eve/module/core/regular/floor.hpp>
#include <eve/module/core/regular/copysign.hpp>
#include <eve/module/core/regular/next.hpp>

namespace eve::detail
{

  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr T
  trunc_(EVE_REQUIRES(cpu_), O const& o, T a0) noexcept
  {
    if constexpr(integral_value<T>)
      return a0;
    else
    {
      if constexpr(O::contains(raw))
      {
        using elt_t = element_type_t<T>;
        using i_t   = as_integer_t<elt_t>;
        return convert(convert(a0, as<i_t>()), as<elt_t>());
      }
      else if constexpr(O::contains(almost))
      {
        auto tol = o[almost].value(a0);
        if constexpr(integral_value<decltype(tol)>)
          return copysign(eve::trunc(next(eve::abs(a0), tol)), a0);
        else
          return copysign(floor[o](eve::abs(a0)), a0);
      }
      else
      {
        auto not_already_integral = !is_not_less_equal(abs(a0), maxflint(eve::as<T>()));
        auto a = if_else(not_already_integral, a0, zero);
        return if_else(not_already_integral, trunc[raw](a), a0);
      }
    }
  }

  template<typename T, typename U, callable_options O>
  EVE_FORCEINLINE constexpr auto
  trunc_(EVE_REQUIRES(cpu_), O const& o, T const & a0, as<U> const& ) noexcept
  {
    if constexpr(integral_value<T>)
      return convert(a0, as_element<as_integer_t<T,U>>{});
    else
      return convert(trunc[o](a0), as_element<as_integer_t<T,U>>{});
  }
}
