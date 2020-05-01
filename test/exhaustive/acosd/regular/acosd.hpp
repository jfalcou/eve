//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/acosd.hpp>
#include <eve/function/radindeg.hpp>

#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <tts/tests/range.hpp>

TTS_CASE("wide exhaustive check on acosd")
{
  auto std_acosd = tts::vectorize<EVE_TYPE>([](auto e) { return eve::radindeg(std::acos(e)); });

  eve::exhaustive_producer<EVE_TYPE> p(-1, 1);
  TTS_RANGE_CHECK(p, std_acosd, eve::acosd);
}
