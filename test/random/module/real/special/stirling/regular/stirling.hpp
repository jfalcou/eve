//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/stirling.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/minlog.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on stirling", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_stirling = [](auto e) { return std::stirling(e); };
  auto eve_stirling = [](auto e) { return eve::stirling(e); };

  eve::uniform_prng<T>  p ( eve::minlog(eve::as<EVE_VALUE>())
                          , eve::maxlog(eve::as<EVE_VALUE>()) - 1
                          );

  TTS_RANGE_CHECK(p, std_stirling, eve_stirling);
};