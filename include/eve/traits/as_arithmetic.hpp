//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/wide_forward.hpp>

namespace eve
{
  namespace _
  {
    template<typename T>
    extern T as_arithmetic;

    template<typename T>
    requires( std::same_as<T,bool> )
    extern bool as_arithmetic<T>;

    template<typename T>
    extern T as_arithmetic<logical<T>>;
  }

  template<typename T>
  using as_arithmetic_t = decltype(_::as_arithmetic<T>);
}
