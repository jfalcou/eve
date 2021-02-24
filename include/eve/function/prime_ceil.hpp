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
  namespace tag { struct prime_ceil_; }

  template<>
  struct supports_optimized_conversion<tag::prime_ceil_> : std::true_type {};

  EVE_MAKE_CALLABLE(prime_ceil_, prime_ceil);
}

#include <eve/module/real/combinatorial/function/regular/generic/prime_ceil.hpp>
