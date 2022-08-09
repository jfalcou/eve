//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include <eve/module/core.hpp>
#include "test.hpp"


#include "unit/api/udt/udt.hpp"

TTS_CASE("zero for different tuples")
{
  using plain_tuple = kumi::tuple<int, std::int8_t>;
  TTS_TYPE_IS(plain_tuple, decltype(eve::zero(eve::as<plain_tuple>{})));

  TTS_TYPE_IS(udt::grid2d, decltype(eve::zero(eve::as<udt::grid2d>{})));
  TTS_TYPE_IS(eve::wide<udt::grid2d>, decltype(eve::zero(eve::as<eve::wide<udt::grid2d>>{})));
};

TTS_CASE("copy zero tuple (armv-v7 bug)")
{
  using s_t = kumi::tuple<std::int8_t, std::int64_t, double>;
  using w_t = eve::wide<s_t>;

  w_t src = eve::zero(eve::as<w_t>{});
  w_t cpy{src};
  TTS_EQUAL(src, cpy);
};
