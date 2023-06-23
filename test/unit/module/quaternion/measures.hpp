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

  template<typename T> double relative_distance(T const &l, T const &r) requires(eve::is_quaternion_v<T>)
  {
    return 100.0*eve::reldist(l, r);
    }

  template<typename T, typename N>
  double relative_distance(eve::wide<T,N> const &l, eve::wide<T,N> const &r) requires(eve::is_quaternion_v<T>)
  {
    return 100.0*eve::maximum(eve::reldist(l, r));
  }

  template<typename T> double absolute_distance(T const &l, T const &r) requires(eve::is_quaternion_v<T>)
  {
     return eve::dist(l, r);
  }

  template<typename T, typename N>
  double absolute_distance(eve::wide<T,N> const &l, eve::wide<T,N> const &r) requires(eve::is_quaternion_v<T>)
  {
     return eve::maximum(eve::dist(l, r));
  }
}
