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

#include <eve/arch/cpu/tags.hpp>
#include <type_traits>
#include <cstdint>
#include <cstddef>

namespace eve
{
  template<typename Tag>
  struct limits
  {
    using parent = eve::simd_;

    template<typename Sign>
    using largest_integer =
        std::conditional_t<std::is_same_v<Sign, unsigned>, std::uint64_t, std::int64_t>;

    template<typename Sign>
    using smallest_integer =
        std::conditional_t<std::is_same_v<Sign, unsigned>, std::uint8_t, std::int8_t>;

    using largest_real  = double;
    using smallest_real = float;

    static constexpr std::size_t bits               = 128;
    static constexpr std::size_t bytes              = 16;
    static constexpr bool        is_bit_logical = true;

    template<typename Type>
    static constexpr std::size_t expected_cardinal = bytes / sizeof(Type);
  };
}

