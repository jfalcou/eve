//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/saturated/sqr.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/sqrtvalmax.hpp>
#include "producers.hpp"

TTS_CASE_TPL("wide random check on sqr", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  if constexpr(eve::floating_value<T>)
  {
    auto std_sqr = [](auto e) { return e*e; };

    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>())+1, eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_sqr, eve::saturated(eve::sqr));
  }
  else if constexpr(eve::signed_value<T>)
  {
    auto std_sqr  = [](auto e) -> EVE_VALUE
                    {
                      return    (eve::abs(e) > eve::sqrtvalmax(eve::as<EVE_VALUE>()) || e == eve::valmin(eve::as<EVE_VALUE>()))
                              ? eve::valmax(eve::as<EVE_VALUE>())
                              : e*e;
                    };

    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_sqr, eve::saturated(eve::sqr));
  }
  else
  {
    auto std_sqr  = [](auto e)  -> EVE_VALUE
                    {
                      return  e > eve::sqrtvalmax(eve::as<EVE_VALUE>())
                            ? eve::valmax(eve::as<EVE_VALUE>())
                            : e*e;
                    };

    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_sqr, eve::saturated(eve::sqr));
  }
};