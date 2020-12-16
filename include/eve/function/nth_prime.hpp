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
  namespace tag { struct nth_prime_; }

  template<>
  struct supports_optimized_conversion<tag::nth_prime_> : std::true_type {};

  EVE_MAKE_CALLABLE(nth_prime_, nth_prime);
}

#include <eve/module/real/combinatorial/function/regular/generic/nth_prime.hpp>
