//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/polynomial/regular/polynom.hpp>
#include <vector>

namespace eve::detail
{
  //================================================================================================
  //== from_roots with range
  //================================================================================================

  template<detail::range R>
  EVE_FORCEINLINE constexpr auto from_roots_(EVE_SUPPORTS(cpu_), R const & roots) noexcept
  //  requires (floating_scalar_value<typename R::value_type>)
  {
    using value_type = typename R::value_type;
    using polynom_t = polynom<value_type>;
    using monom_t = monom<value_type>;
    size_t siz = end(roots)-begin(roots);
    polynom_t p(value_type(1));
    if (siz == 0) return p;
    monom_t x(value_type(1), 1);
    for(size_t i=0; i < siz; ++i)
    {
      p = p*x -p*roots[i];
    }
    return p;
  }

  //================================================================================================
  //== N parameters
  //================================================================================================

  template<value ...Ts>
  EVE_FORCEINLINE constexpr auto from_roots_(EVE_SUPPORTS(cpu_), Ts... rts) noexcept
  {
    using r_t = common_compatible_t<Ts...>;
    std::vector<r_t> v{r_t(rts)...};
    return from_roots(v);
  }
}
