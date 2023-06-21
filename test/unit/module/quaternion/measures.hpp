//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/quaternion.hpp>

namespace tts
{

  template<typename T> auto relative_distance(T const &l, T const &r) requires(eve::is_quaternion_v<T>)
  {
    return eve::sqrt(eve::sqr_abs(l-r)/eve::max(eve::sqr_abs(l), eve::sqr_abs(r)));
  }

  template<typename T, typename N>
  auto relative_distance(eve::wide<T,N> const &l, eve::wide<T,N> const &r) requires(eve::is_quaternion_v<T>)
  {
    return eve::maximum(eve::sqrt(eve::sqr_abs(l-r)/eve::max(eve::sqr_abs(l), eve::sqr_abs(r))));
  }

  template<typename T> auto absolute_distance(T const &l, T const &r) requires(eve::is_quaternion_v<T>)
  {
    return eve::abs(l-r);
  }

  template<typename T, typename N>
  auto absolute_distance(eve::wide<T,N> const &l, eve::wide<T,N> const &r) requires(eve::is_quaternion_v<T>)
  {
    return eve::maxabs(l-r);
  }
}
