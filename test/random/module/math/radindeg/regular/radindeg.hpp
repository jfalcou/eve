//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/radindeg.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/pi.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on radindeg", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto rid =  [](auto e)
    {
      if (eve::abs(e) < eve::eps(eve::as(e)))
        return (eve::sqr((eve::sqrt(e)/eve::sqrt(eve::pi(eve::as<v_t>())))*eve::sqrt(v_t(180))));
      else
        return (e/eve::pi(eve::as<v_t>()))*v_t(180);
    };


  auto std_indeg = tts::vectorize<T>( rid );

  eve::rng_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
  TTS_ULP_RANGE_CHECK(p, std_indeg, eve::radindeg, 4);
}
