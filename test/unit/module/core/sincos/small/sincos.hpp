//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sincos.hpp>
#include <eve/function/sin.hpp>
#include <eve/function/cos.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <utility>
#include <cmath>

TTS_CASE_TPL("Check sincos return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::small_(eve::sincos)(T()), (std::tuple<T,T>));
}

TTS_CASE_TPL("Check (eve::sincos behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  static const int N = 9;
  v_t x[N] = {  eve::Pi<v_t>()/8, -eve::Pi<v_t>()/8
                  , eve::Pi<v_t>()/4, -eve::Pi<v_t>()/4
                  , 3*eve::Pi<v_t>()/8, -3*eve::Pi<v_t>()/8
                  , eve::Pio_2<v_t>(), -eve::Pi<v_t>()/2, v_t(1.57079632679489655800e+00)
  };

  for(int i=0; i < N ; ++i)
  {
    auto [p0, p1] = eve::small_(eve::sincos)(T(x[i]));
    TTS_ULP_EQUAL(p0, T(std::sin(x[i])), 3.5);
    TTS_ULP_EQUAL(p1, T(std::cos(x[i])), 3.5);
  }
}
