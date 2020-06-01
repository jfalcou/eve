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
#include <eve/logical.hpp>

namespace eve
{
  template<typename T>
  struct as_arithmetic
  {
    using type = T;
  };

  template<>
  struct as_arithmetic<bool>
  {
    using type = bool;
  };

  template<typename T>
  struct as_arithmetic<logical<T>>
  {
    using type = T;
  };

  template<typename T>
  using as_arithmetic_t = typename as_arithmetic<T>::type;
}

