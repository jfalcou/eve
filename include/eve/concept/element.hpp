//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <type_traits>
#include <concepts>
#include <eve/concept/scalar.hpp>
#include <eve/concept/underlying_storage.hpp>

namespace eve
{
  // represents any type that can be put into a eve::wide
  template <typename T>
  concept element_value = has_underlying_representation<T> || arithmetic_scalar_value<T>;
}
