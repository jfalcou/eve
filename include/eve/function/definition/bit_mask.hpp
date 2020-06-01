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
   namespace tag { struct bit_mask_; }

  template<>
  struct supports_conditionnal<tag::bit_mask_> : std::false_type
  {};

  EVE_MAKE_CALLABLE(bit_mask_, bit_mask);
}

