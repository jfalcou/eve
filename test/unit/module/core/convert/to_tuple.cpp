//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"
#include "unit/api/udt/udt.hpp"

#include <eve/module/core.hpp>
#include <eve/wide.hpp>

#include <utility>

//==================================================================================================
// Type computation of tuple-like entity conversion
//==================================================================================================
TTS_CASE("Check convert return type for UDT/tuple")
{
  TTS_EXPR_IS((eve::convert(udt::grid2d {}, eve::as<udt::label_position>())), udt::label_position);
  TTS_EXPR_IS((eve::convert(udt::label_position {}, eve::as<udt::grid2d>())), udt::grid2d);
  TTS_EXPR_IS((eve::convert(kumi::tuple<int, int> {}, eve::as<udt::grid2d>())), udt::grid2d);

  TTS_EXPR_IS((eve::convert(udt::grid2d {}, eve::as<kumi::tuple<int, int>>())),
              (kumi::tuple<int, int>));

  TTS_EXPR_IS((eve::convert(kumi::tuple<int, std::int8_t, float> {},
                            eve::as<kumi::tuple<short, double, std::uint32_t>>())),
              (kumi::tuple<short, double, std::uint32_t>));

  TTS_EXPR_IS((eve::convert(kumi::tuple<int, std::int8_t, float> {},
                            eve::as<kumi::tuple<short, double, std::uint32_t>>())),
              (kumi::tuple<short, double, std::uint32_t>));

  TTS_EXPR_IS(
      (eve::convert(kumi::tuple<int, kumi::tuple<int, std::int8_t, float>, float> {},
                    eve::as<kumi::tuple<int, short, double, std::uint32_t, std::int8_t>>())),
      (kumi::tuple<int, short, double, std::uint32_t, std::int8_t>));
};

//==================================================================================================
// Conversions
//==================================================================================================
TTS_CASE("Conversion from/to UDTs &nd tuples")
{
  TTS_EQUAL((eve::convert(udt::grid2d {-9, 70}, eve::as<udt::label_position>())),
            (udt::label_position {-9.f, 'F'}));

  TTS_EQUAL((eve::convert(udt::label_position {-9.f, 'F'}, eve::as<udt::grid2d>())),
            (udt::grid2d {-9, 70}));

  TTS_EQUAL((eve::convert(udt::grid2d {66, -9}, eve::as<kumi::tuple<std::int8_t, float>>())),
            (kumi::tuple {'B', -9.f}));

  TTS_EQUAL((eve::convert(kumi::tuple {'B', -9.f}, eve::as<udt::grid2d>())),
            (udt::grid2d {66, -9}));

  TTS_EQUAL((eve::convert(kumi::tuple {udt::grid2d {-9, 7}, udt::grid2d {3, 5}},
                          eve::as<kumi::tuple<int, int, int, int>>())),
            (kumi::tuple<int, int, int, int> {-9, 7, 3, 5}));

  TTS_EQUAL((eve::convert(kumi::tuple<int, int, int, int> {-9, 7, 3, 5},
                          eve::as<kumi::tuple<udt::grid2d, udt::grid2d>>())),
            (kumi::tuple {udt::grid2d {-9, 7}, udt::grid2d {3, 5}}));
};
