//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/plain_scalar.hpp>
#include <eve/concept/product_scalar.hpp>

namespace eve
{
template<typename T>
concept arithmetic_scalar_value = plain_scalar_value<T> || product_scalar_value<T>;
}
