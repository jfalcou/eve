//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/laguerre.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/derivative.hpp>
#include <eve/detail/apply_over.hpp>
// temporary measure
#include <eve/detail/diff_div.hpp>
// temporary measure

namespace eve::detail
{

  template<integral_value N, floating_real_value T>
  EVE_FORCEINLINE constexpr T laguerre_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , N const & n
                                  , T const &x) noexcept
  requires index_compatible_values<N, T>
  {
    // TODO
    // as there is no available closed formule for laguerre derivative at the first order
    // will use vand algo as soon as complex will be available ie:
    //     complex<T> cx = {x, eps(as(x))};
    //     return = imag(laguerre(cx))/eps(as(x));
    // and will tested in time
    auto df2 = [](auto n, auto x){
      auto y =  [&n](auto a){ return eve::laguerre(n, a);  };
      return eve::detail::centered_diffdiv(y, x);
    };
    return df2(n, x); // this is not accurate
  }
}
