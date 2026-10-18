//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/meta.hpp>
#include <eve/detail/wide_forward.hpp>
#include <eve/traits/translation.hpp>

namespace eve
{
  namespace _
  {
    template<typename T>
    extern _::make_floating_point<(sizeof(T) <= 2) ? 2 : sizeof(T)> as_floating_point;

    template<typename T, typename N>
    extern wide<decltype(as_floating_point<T>), N> as_floating_point<wide<T,N>>;

    template<typename T>
    extern logical<decltype(as_floating_point<T>)> as_floating_point<logical<T>>;
  }

  template<typename T>
  using as_floating_point_t = typename as_floating_point<T>::type;
}
