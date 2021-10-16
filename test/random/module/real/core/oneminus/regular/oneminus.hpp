//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/oneminus.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"

TTS_CASE_TPL("wide random check on oneminus", EVE_TYPE)
<typename T>(::tts::type<T>)
{

  if constexpr(std::is_unsigned_v<EVE_VALUE>)
  {
    auto std_oneminus = [](auto e) -> EVE_VALUE { return EVE_VALUE(1)-e; };

    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_oneminus, eve::oneminus);
  }
  else
  {
    auto std_oneminus = [](auto e) -> EVE_VALUE { return EVE_VALUE(1)-e; };

    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>())+1, eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_oneminus, eve::oneminus);
  }
};