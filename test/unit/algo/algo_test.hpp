//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#pragma once
#include "test.hpp"

namespace algo_test
{
  inline constexpr eve::detail::types<
      eve::wide<std::int8_t, eve::fixed<1>>
    , eve::wide<std::uint8_t>
    , eve::wide<std::int16_t>
    , eve::wide<std::uint16_t, eve::fixed<4>>
    , eve::wide<int>
    , eve::wide<float>
    , eve::wide<double>
    , eve::wide<std::uint64_t>
#if !defined(SPY_SIMD_IS_X86_AVX512)
    , eve::wide < std::uint32_t
                , eve::fixed<eve::expected_cardinal_v<std::uint32_t> * 2>
                >
#endif
  > selected_types;
}
