//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/csc.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/smallestposval.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on csc", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_csc = [](auto e) -> EVE_VALUE { return 1/std::sin(double(e)); };

  if constexpr(eve::platform::supports_denormals)
  {
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_csc, eve::csc);
  }
  else
  {
    eve::uniform_prng<EVE_VALUE>  p(eve::smallestposval(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_csc, eve::csc);
  }
};