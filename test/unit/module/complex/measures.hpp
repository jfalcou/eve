//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/complex.hpp>

namespace tts
{
  template<typename T> double ulp_distance(T const &l, T const &r) requires( eve::is_complex_v<T> )
  {
    auto diff = l-r;
    auto [rl, il] = l;
    auto [rr, ir] = r;
    auto d = eve::if_else ( eve::almost(eve::is_real)(diff)
                          , eve::ulpdist(rl, rr)
                          , eve::if_else(eve::almost(eve::is_imag)(diff)
                                        , eve::ulpdist(il, ir)
                                        , eve::ulpdist(l, r)
                                        )
                          );
    return eve::maximum(d);
  }

  // template<typename T> auto relative_distance(T const &l, T const &r) requires(eve::is_complex_v<T>)
  // {
  //   return eve::maximum(eve::reldist(l, r));
  // }

  template<typename T> auto absolute_distance(T const &l, T const &r) requires(eve::is_complex_v<T>)
  {
     return eve::maximum(eve::dist(l, r));
  }
}
