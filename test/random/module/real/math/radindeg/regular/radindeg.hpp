//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/radindeg.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/pi.hpp>
#include "producers.hpp"

TTS_CASE_TPL("wide random check on radindeg", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_indeg =  [](auto e)
    {
      if (eve::abs(e) < eve::eps(eve::as(e)))
        return (eve::sqr((eve::sqrt(e)/eve::sqrt(eve::pi(eve::as<EVE_VALUE>())))*eve::sqrt(EVE_VALUE(180))));
      else
        return (e/eve::pi(eve::as<EVE_VALUE>()))*EVE_VALUE(180);
    };

  eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK_WITH(p, std_indeg, eve::radindeg, 4);
};