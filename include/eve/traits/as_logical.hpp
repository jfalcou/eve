//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/wide_forward.hpp>
#include <eve/detail/kumi.hpp>

namespace eve
{
  template<typename T>
  struct as_logical
  {
    using type = logical<T>;
  };

  template<>
  struct as_logical<bool>
  {
    using type = bool;
  };

  template<typename T>
  struct as_logical<logical<T>>
  {
    using type = logical<T>;
  };


  template<typename T>
  requires( kumi::product_type<T> )
  struct as_logical<T> : as_logical< kumi::element_t<0,T> >
  {};

  template<typename T>
  using as_logical_t = typename as_logical<T>::type;
}
