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
  namespace tag { struct primes_; }

  template<>
  struct supports_optimized_conversion<tag::primes_> : std::true_type {};

  EVE_MAKE_CALLABLE(primes_, primes);
}

#include <eve/module/combinatorial/function/generic/primes.hpp>
