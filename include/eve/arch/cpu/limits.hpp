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

#include <cstddef>

namespace eve
{
  template<typename Tag> struct limits
  {
    static constexpr std::size_t bits               = 128;
    static constexpr std::size_t bytes              = 16;
    static constexpr bool        is_bit_logical = true;

    template<typename Type>
    static constexpr std::size_t expected_cardinal = bytes / sizeof(Type);
  };
}

