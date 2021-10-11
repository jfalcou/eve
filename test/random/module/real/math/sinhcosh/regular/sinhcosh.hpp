//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/sinhcosh.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/log_2.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on sinhcosh", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_sin    = [](auto e) -> EVE_VALUE { return std::sinh(double(e)); };
  auto std_cos    = [](auto e) -> EVE_VALUE { return std::cosh(double(e)); };
  auto sinhcosh_s = [](auto e) { auto [s, c] = eve::sinhcosh(e); return s; };
  auto sinhcosh_c = [](auto e) { auto [s, c] = eve::sinhcosh(e); return c; };

  eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_sin, sinhcosh_s);
  TTS_RANGE_CHECK(p, std_cos, sinhcosh_c);
};