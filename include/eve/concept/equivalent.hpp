//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/equivalent.hpp>

#include <concepts>

namespace eve
{
  template <typename T>
  concept has_equivalent = !std::same_as<as_equivalent_t<T>, T>;
}
