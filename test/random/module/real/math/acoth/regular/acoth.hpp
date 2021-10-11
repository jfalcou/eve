//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/acoth.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on acoth", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_acoth = [](auto e) { return std::atanh(eve::rec(e)); };

  eve::uniform_prng<EVE_VALUE> p1(EVE_VALUE(1), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK_WITH(p1, std_acoth, eve::acoth, 64);

  eve::uniform_prng<EVE_VALUE> p2(eve::valmin(eve::as<EVE_VALUE>()), EVE_VALUE(-1));
  TTS_RANGE_CHECK_WITH(p2, std_acoth, eve::acoth, 64);
};