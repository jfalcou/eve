//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  namespace tag { struct prime_floor_; }

  template<>
  struct supports_optimized_conversion<tag::prime_floor_> : std::true_type {};

  EVE_MAKE_CALLABLE(prime_floor_, prime_floor);
}

#include <eve/module/real/combinatorial/function/regular/generic/prime_floor.hpp>
