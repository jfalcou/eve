//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/prev.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/nan.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide rng check on prev", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  if constexpr(eve::floating_value<T>)
  {
    auto std_prev = [](auto e)
                    {
                      return  (e ==  eve::minf(eve::as<v_t>()))  ?
                              eve::nan(eve::as<v_t>())
                            : std::nextafter(e, eve::minf(eve::as<v_t>()));
                    };
    eve::uniform_prng<v_t> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_prev, eve::prev);
  }
  else
  {
    auto std_prev = [](auto e) -> v_t { return e-1; };
    eve::uniform_prng<v_t> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_prev, eve::prev);
  }
};
