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
  template<typename T>
  double ulp_distance_impl(T const &l, T const &r)
  {
    auto diff = l-r;
    auto [rl, il] = l;
    auto [rr, ir] = r;
    auto udr = eve::ulpdist(il, ir);
    auto udi = eve::ulpdist(rl, rr);
//     std::cout << "        udi " << udi << std::endl;
//     std::cout << "        udr " << udr << std::endl;
    udr = eve::if_else(eve::is_nan(udr), eve::inf(eve::as(udr)), udr);
    udi = eve::if_else(eve::is_nan(udi), eve::inf(eve::as(udi)), udi);
    auto d = eve::if_else ( eve::almost(eve::is_real)(diff)
                          , udr
                          , eve::if_else( eve::almost(eve::is_imag)(diff)
                                        , udi
                                        , eve::max(udi, udr)
                                        )
                          );
//     std::cout << " alisr    " << eve::almost(eve::is_real)(diff)<< std::endl;
//     std::cout << " alisi    " << eve::almost(eve::is_imag)(diff)<< std::endl;
//     std::cout << "        l " << l << std::endl;
//     std::cout << "        r " << r << std::endl;
//     std::cout << "        d " << d << std::endl;
//     std::cout << "       md " << eve::maximum(d)<< std::endl;
    return eve::maximum(d);
  }

  template<typename T>
  double ulp_distance(T const &l, T const &r) requires( eve::is_complex_v<T> )
  {
    return ulp_distance_impl(l,r);
  }

  template<typename T, typename N>
  double ulp_distance(eve::wide<T,N> const &l, eve::wide<T,N> const &r)
  requires( eve::is_complex_v<T> )
  {
    return ulp_distance_impl(l,r);
  }

  template<typename T> auto relative_distance(T const &l, T const &r) requires(eve::is_complex_v<T>)
  {
    auto [rl,il] = l;
    auto [rr,ir] = r;

    return eve::max(relative_distance(rl,rr), relative_distance(il,ir));
  }

  template<typename T, typename N>
  auto relative_distance(eve::wide<T,N> const &l, eve::wide<T,N> const &r) requires(eve::is_complex_v<T>)
  {
    auto [rl,il] = l;
    auto [rr,ir] = r;

    return eve::max(relative_distance(rl,rr), relative_distance(il,ir));
  }

  template<typename T> auto absolute_distance(T const &l, T const &r) requires(eve::is_complex_v<T>)
  {
     return eve::maximum(eve::dist(l, r));
  }

  template<typename T, typename N>
  auto absolute_distance(eve::wide<T,N> const &l, eve::wide<T,N> const &r) requires(eve::is_complex_v<T>)
  {
     return eve::maximum(eve::dist(l, r));
  }
}
