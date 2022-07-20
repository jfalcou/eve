//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <type_traits>

namespace eve
{
template<typename T>
concept plain_scalar_value = detail::one_of<T, float, double> || std::integral<T>;
}
