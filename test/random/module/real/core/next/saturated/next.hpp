//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/saturated/next.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide rng check on next", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  if constexpr(eve::floating_value<T>)
  {
    auto std_next = [](auto e)
      {
        return (e ==  eve::inf(eve::as<v_t>()))
        ?  eve::nan(eve::as<v_t>())
        : std::nextafter(e, eve::inf(eve::as<v_t>()));
      };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_next, eve::saturated(eve::next));
  }
  else
  {
    auto std_next = [](auto e) -> v_t { return e == eve::valmax(eve::as<v_t>()) ? e : e+1; };
    eve::uniform_prng<v_t> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_next, eve::saturated(eve::next));
  }
}
