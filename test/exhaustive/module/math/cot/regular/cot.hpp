//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cot.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/smallestposval.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on cot", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_cot = tts::vectorize<T>( [](auto e) { return 1/std::tan(double(e)); } );

  if constexpr(eve::platform::supports_denormals)
  {
    eve::exhaustive_producer<T>  p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_cot, eve::cot);
  }
  else
  {
    eve::exhaustive_producer<T>  p(eve::smallestposval(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
    TTS_RANGE_CHECK(p, std_cot, eve::cot);
  }
}
