//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/complex.hpp>

namespace tts
{

  template<typename T> auto relative_distance(T const &l, T const &r) requires(eve::is_quaternion_v<T>)
  {
    auto d = eve::sqr_abs(l-r);
    return eve::sqrt(d/max(sqr_abs(l)*sqr(abs(r)));
  }

  template<typename T, typename N>
  auto relative_distance(eve::wide<T,N> const &l, eve::wide<T,N> const &r) requires(eve::is_quaternion_v<T>)
  {
    auto d = eve::sqr_abs(l-r);
    return eve::sqrt(d/eve::max(eve::sqr_abs(l)*eve::sqr(abs(r)));
  }

  template<typename T> auto absolute_distance(T const &l, T const &r) requires(eve::is_quaternion_v<T>)
  {
    return eve::abs(l-r);

  template<typename T, typename N>
  auto absolute_distance(eve::wide<T,N> const &l, eve::wide<T,N> const &r) requires(eve::is_quaternion_v<T>)
  {
    return eve::abs(l-r);
  }
}
