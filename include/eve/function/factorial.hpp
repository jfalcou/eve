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
  namespace tag { struct factorial_; }

  template<>
  struct supports_optimized_conversion<tag::factorial_> : std::true_type {};

  EVE_MAKE_CALLABLE(factorial_, factorial);
}

#include <eve/module/combinatorial/function/generic/factorial.hpp>
