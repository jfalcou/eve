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
  namespace tag { struct is_not_real_; }

  template<>
  struct supports_conditionnal<tag::is_not_real_> : std::false_type
  {};

  EVE_MAKE_CALLABLE(is_not_real_, is_not_real);
}

