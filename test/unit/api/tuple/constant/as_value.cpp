//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "test.hpp"

#include <eve/constant/as_value.hpp>
#include <eve/constant/zero.hpp>

#include "unit/api/udt/udt.hpp"

TTS_CASE("as_value for different tuples")
{
  {
    using plain_tuple = kumi::tuple<int, std::int8_t>;
    plain_tuple expected {0, 0};

    plain_tuple actual = eve::as_value(eve::zero, eve::as<plain_tuple>{});

    TTS_EQUAL(expected, actual);

    actual = eve::as_value(expected, eve::as<plain_tuple>{});
    TTS_EQUAL(expected, actual);
  }
  {
    udt::grid2d expected{0, 0};

    udt::grid2d actual = eve::as_value(eve::zero, eve::as<udt::grid2d>{});
    TTS_EQUAL(expected, actual);

    actual = eve::as_value(expected, eve::as<udt::grid2d>{});
    TTS_EQUAL(expected, actual);
  }
};
