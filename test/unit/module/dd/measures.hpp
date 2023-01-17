//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/dd.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
namespace bm =  boost::multiprecision;

namespace tts
{
  template<typename T>
  auto uptype(T const & z)
  {
    if constexpr(sizeof(T) == 4) return eve::to_double(z);
    else return eve::to_float128(z);
  }
  template<typename T>
  double ulp_distance_impl(T const &l, T const &r)
  {
    auto diff = l-r;
    auto [rl, il] = l;
    auto [rr, ir] = r;
    auto udr = eve::ulpdist(il, ir);
    auto udi = eve::ulpdist(rl, rr);
    if(eve::is_eqz(eve::maximum(udr))) return eve::maximum(udi);
    if(eve::is_eqz(eve::maximum(udi))) return eve::maximum(udr);
    udr = eve::if_else(eve::is_not_finite(udr), eve::inf(eve::as(udr)), udr);
    udi = eve::if_else(eve::is_not_finite(udi), eve::inf(eve::as(udi)), udi);
    auto d = eve::if_else ( eve::almost(eve::is_real)(diff)
                          , udr
                          , eve::if_else( eve::almost(eve::is_imag)(diff)
                                        , udi
                                        , eve::max(udi, udr)
                                        )
                          );
    return eve::maximum(d);
  }

  template<typename T>
  double ulp_distance(T const &l, T const &r) requires( eve::is_dd_v<T> )
  {
    return ulp_distance_impl(l,r);
  }

  template<typename T, typename N>
  double ulp_distance(eve::wide<T,N> const &l, eve::wide<T,N> const &r)
  requires( eve::is_dd_v<T> )
  {
    return ulp_distance_impl(l,r);
  }

  template<typename T> auto relative_distance(T const &l, T const &r) requires(eve::is_dd_v<T>)
  {
    auto [rl,il] = l;
    auto [rr,ir] = r;

    return eve::max(relative_distance(rl,rr), relative_distance(il,ir));
  }

  template<typename T, typename N>
  auto relative_distance(eve::wide<T,N> const &l, eve::wide<T,N> const &r) requires(eve::is_dd_v<T>)
  {
    auto [rl,il] = l;
    auto [rr,ir] = r;

    return eve::max(relative_distance(rl,rr), relative_distance(il,ir));
  }

  template<typename T> auto absolute_distance(T const &l, T const &r) requires(eve::is_dd_v<T>)
  {
     return eve::maximum(eve::dist(l, r));
  }

  template<typename T, typename N>
  auto absolute_distance(eve::wide<T,N> const &l, eve::wide<T,N> const &r) requires(eve::is_dd_v<T>)
  {
     return eve::maximum(eve::dist(l, r));
  }
}
