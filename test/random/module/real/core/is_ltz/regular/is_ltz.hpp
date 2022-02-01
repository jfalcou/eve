//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/is_ltz.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/traits/as_logical.hpp>
#include "producers.hpp"

TTS_CASE_TPL("wide random check on is_ltz", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_is_ltz =  [](auto e)  ->eve::logical<EVE_VALUE> { return e < EVE_VALUE(0); };

  eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_is_ltz, eve::is_ltz);
};