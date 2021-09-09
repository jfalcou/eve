//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "test.hpp"

#include <eve/constant/zero.hpp>

#include "unit/api/udt/udt.hpp"

TTS_CASE("zero for different tuples")
{
  using plain_tuple = kumi::tuple<int, std::int8_t>;
  TTS_TYPE_IS(plain_tuple, decltype(eve::zero(eve::as<plain_tuple>{})));

  TTS_TYPE_IS(udt::grid2d, decltype(eve::zero(eve::as<udt::grid2d>{})));
  TTS_TYPE_IS(eve::wide<udt::grid2d>, decltype(eve::zero(eve::as<eve::wide<udt::grid2d>>{})));
}
