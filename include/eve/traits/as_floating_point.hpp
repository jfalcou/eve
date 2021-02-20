//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/forward.hpp>
#include <eve/detail/meta.hpp>

namespace eve
{
  template<typename T>
  struct as_floating_point : detail::make_floating_point<(sizeof(T) <= 4) ? 4: sizeof(T)>
  {};

  template<typename T, typename N, typename ABI>
  struct as_floating_point<wide<T,N,ABI>>
  {
    using type = wide<typename as_floating_point<T>::type, N>;
  };

  template<typename T>
  struct as_floating_point<logical<T>>
  {
    using type = logical< typename as_floating_point<T>::type >;
  };

  template<typename T>
  using as_floating_point_t = typename as_floating_point<T>::type;
}
