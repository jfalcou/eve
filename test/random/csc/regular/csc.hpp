//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/csc.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/smallestposval.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on csc", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto std_csc = tts::vectorize<T>( [](auto e) { return 1/std::sin(double(e)); } );

  if constexpr(eve::platform::supports_denormals)
  {
    eve::rng_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
    TTS_RANGE_CHECK(p, std_csc, eve::csc);
  }
  else
  {
    eve::rng_producer<T>  p(eve::Smallestposval<v_t>(), eve::Valmax<v_t>());
    TTS_RANGE_CHECK(p, std_csc, eve::csc);
  }
}
