//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/is_real.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include "producers.hpp"

TTS_CASE_TPL("wide random check on is_real", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  using l_t = eve::as_logical_t<EVE_VALUE>;
  auto std_is_real = [](auto) { return l_t(true); };

  eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_is_real, eve::is_real);
};