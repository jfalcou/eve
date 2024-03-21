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
#include <eve/module/core/regular/converter.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_not_less_equal.hpp>
#include <eve/module/core/regular/floor.hpp>
#include <eve/module/core/regular/copysign.hpp>
#include <eve/module/core/regular/next.hpp>


namespace eve::detail
{
  template<typename T, floating_value U, callable_options O>
  EVE_FORCEINLINE constexpr T
  trunc_(EVE_REQUIRES(cpu_), O const&, T const& a0, U const & eps) noexcept
  //  requires (O::contains(tolerant2))
  {
    return copysign(floor[tolerant2](eve::abs(a0), eps), a0);
  }
  template<typename T, integral_value U, callable_options O>
  EVE_FORCEINLINE constexpr T
  trunc_(EVE_REQUIRES(cpu_), O const&, T const& a0, U const & n) noexcept
  //  requires (O::contains(tolerant2))
  {
    return copysign(trunc(next(eve::abs(a0), n)), a0);
  }

  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr T
  trunc_(EVE_REQUIRES(cpu_), O const&, T const& a0) noexcept
  {
    auto rawtrunc = [](auto x){
      using elt_t = element_type_t<T>;
      using i_t   = as_integer_t<elt_t>;
      return convert(convert(x, as<i_t>()), as<elt_t>());
    };
    if constexpr(O::contains(raw2))
    {
      return rawtrunc(a0);
    }
    else if constexpr(O::contains(tolerant2))
    {
      return trunc[tolerant2](a0, 3*eps(as(a0)));
    }
    else
    {
      auto already_integral = is_not_less_equal(eve::abs(a0), maxflint(eve::as<T>()));
      if constexpr( scalar_value<T> )
        return already_integral ? a0 : rawtrunc(a0);
      else if constexpr( simd_value<T> )
        return if_else(already_integral, a0, rawtrunc(a0));
    }
  }
}
