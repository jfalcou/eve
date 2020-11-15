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

#include <eve/detail/overload.hpp>

namespace eve
{
  namespace tag { struct prime_floor_; }

  template<>
  struct supports_optimized_conversion<tag::prime_floor_> : std::true_type {};

  EVE_MAKE_CALLABLE(prime_floor_, prime_floor);
}

#include <eve/module/combinatorial/function/generic/prime_floor.hpp>
