//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_PPC_LIMITS_HPP_INCLUDED
#define EVE_ARCH_PPC_LIMITS_HPP_INCLUDED

#include <eve/arch/ppc/tags.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>
#include <cstdint>
#include <cstddef>

namespace eve
{
  template<> struct limits<eve::vmx_>
  {
    using parent = eve::simd_;

    template<typename Sign>
    using largest_integer =
        std::conditional_t<std::is_same_v<Sign, unsigned>, std::uint32_t, std::int32_t>;

    template<typename Sign>
    using smallest_integer =
        std::conditional_t<std::is_same_v<Sign, unsigned>, std::uint8_t, std::int8_t>;

    using largest_real  = float;
    using smallest_real = float;

    static constexpr std::size_t bits  = 128;
    static constexpr std::size_t bytes = 16;
    static constexpr bool is_bitwise_logical = true;

    template<typename Type>
    static constexpr std::size_t expected_cardinal = bytes / sizeof(Type);

    using supported_types = detail::types<float,
                                          std::int8_t,
                                          std::int16_t,
                                          std::int32_t,
                                          std::uint8_t,
                                          std::uint16_t,
                                          std::uint32_t>;
  };

  template<> struct limits<eve::vsx_>
  {
    using parent = eve::vmx_;

    template<typename Sign>
    using largest_integer =
        std::conditional_t<std::is_same_v<Sign, unsigned>, std::uint64_t, std::int64_t>;

    template<typename Sign>
    using smallest_integer =
        std::conditional_t<std::is_same_v<Sign, unsigned>, std::uint8_t, std::int8_t>;

    using largest_real  = double;
    using smallest_real = float;

    static constexpr std::size_t bits  = 128;
    static constexpr std::size_t bytes = 16;
    static constexpr bool is_bitwise_logical = true;

    template<typename Type>
    static constexpr std::size_t expected_cardinal = bytes / sizeof(Type);

    using supported_types = detail::types<float,
                                          double,
                                          std::int8_t,
                                          std::int16_t,
                                          std::int32_t,
                                          std::int64_t,
                                          std::uint8_t,
                                          std::uint16_t,
                                          std::uint32_t,
                                          std::uint64_t>;
  };
}

#endif
