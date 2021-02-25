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
  namespace tag { struct lcm_; }

  template<>
  struct supports_optimized_conversion<tag::lcm_> : std::true_type {};

  EVE_MAKE_CALLABLE(lcm_, lcm);
}

#include <eve/module/real/combinatorial/function/regular/generic/lcm.hpp>
