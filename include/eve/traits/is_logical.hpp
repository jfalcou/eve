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
  template<typename T>
  inline constexpr bool is_logical_v = false;

  template<typename T>
  inline constexpr bool is_logical_v<logical<T>> = true; 
}
