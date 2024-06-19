//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/translation.hpp>

#include <concepts>

namespace eve
{
  template <typename T>
  concept has_plain_translation = !std::same_as<translate_t<T>, T>;
}
