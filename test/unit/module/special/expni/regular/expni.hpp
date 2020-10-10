//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <boost/math/special_functions/expint.hpp>
#include <eve/function/expni.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::expni return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::expni(T(0), T(0)), T);
}

TTS_CASE_TPL("Check eve::expni behavior", EVE_TYPE)
{
  auto eve__expni   =  [](auto x, auto y) { return eve::expni(x, y); };
  auto boost__expni =  [](auto x, auto y) { return boost::math::expint(x, y); };

//   if constexpr( eve::platform::supports_invalids )
//   {
//     TTS_IEEE_EQUAL(eve__expni(T(1), eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
//     TTS_IEEE_EQUAL(eve__expni(T(1), eve::inf(eve::as<T>()))   , T(0) );
//   }


  for(int i=2; i < 3 ; ++i)
  {
    std::cout << i << std::endl;
//    TTS_ULP_EQUAL(eve__expni(T(i), T(0))  , T(boost__expni(i, 0.0)), 0.5);
    TTS_ULP_EQUAL(eve__expni(T(i), T(0.5)), T(boost__expni(i, 0.5)), 2.0);
//      TTS_ULP_EQUAL(eve__expni(T(i), T(1))  , T(boost__expni(i, 1.0)), 4.0);
//      TTS_ULP_EQUAL(eve__expni(T(i), T(10)) , T(boost__expni(i, 10.0)), 0.5);
  }
  using elt_t =  eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve__expni(elt_t(2.0), elt_t(0.5)), (boost__expni(elt_t(2), elt_t(0.5))), 2.0);
}
