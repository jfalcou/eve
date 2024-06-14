//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/transparent.hpp>

#include <concepts>

namespace eve
{
  template <typename T>
  concept transparent_value = !std::same_as<transparent_inner_t<T>, T>;
}
