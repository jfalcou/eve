//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/special.hpp>

#include <cmath>

//==================================================================================================
// hurwitz  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of hurwitz on wide", eve::test::simd::ieee_reals)
  <typename T>(tts::type<T>)
{
  using eve::hurwitz;
  using eve::hurwitz2;
  using e_t = eve::element_type_t<T>;

  auto ulp = 2.0;
  if constexpr(sizeof(e_t) == 8  && eve::cardinal_v<T> == 1)
  {
//      if constexpr( eve::platform::supports_invalids )
//      {
//        TTS_IEEE_EQUAL(hurwitz(e_t(3), eve::nan(eve::as<e_t>())), eve::nan(eve::as<e_t>()));
//        TTS_IEEE_EQUAL(hurwitz2(e_t(3), eve::nan(eve::as<e_t>())), eve::nan(eve::as<e_t>()));
//  //      TTS_IEEE_EQUAL(T(hurwitz(e_t(3), eve::nan(eve::as<e_t>()))), hurwitz(e_t(3), eve::nan(eve::as<T>())));
//        TTS_IEEE_EQUAL(hurwitz(e_t(3), eve::inf(eve::as<e_t>())), eve::zero(eve::as<e_t>()));
//        TTS_IEEE_EQUAL(hurwitz2(e_t(3), eve::inf(eve::as<e_t>())), eve::zero(eve::as<e_t>()));
//  //      TTS_IEEE_EQUAL(T(hurwitz(e_t(3), eve::inf(eve::as<e_t>()))), hurwitz(e_t(3), eve::inf(eve::as<T>())));

//        TTS_IEEE_EQUAL(hurwitz(e_t(3), eve::minf(eve::as<e_t>())), eve::nan(eve::as<e_t>()));
//        TTS_IEEE_EQUAL(hurwitz2(e_t(3), eve::minf(eve::as<e_t>())), eve::nan(eve::as<e_t>()));
//  //      TTS_IEEE_EQUAL(T(hurwitz(e_t(3), eve::minf(eve::as<e_t>()))), hurwitz(e_t(3), eve::minf(eve::as<T>())));

//      }

//       TTS_ULP_EQUAL(hurwitz(e_t(3), e_t(0.125)), e_t(512.8766690590678412978L), ulp);
    TTS_ULP_EQUAL(hurwitz2(e_t(3), e_t(0.125)), e_t(512.8766690590678412978L), ulp);
    TTS_ULP_EQUAL(T(hurwitz2(e_t(3), e_t(0.125))), hurwitz2(e_t(3), T(0.125)), ulp);


//       TTS_ULP_EQUAL(hurwitz(e_t(3), e_t(6)), e_t(0.0163948661225572483627L), ulp);
    TTS_ULP_EQUAL(hurwitz2(e_t(3), e_t(6)), e_t(0.0163948661225572483627L), ulp);
    TTS_ULP_EQUAL(T(hurwitz2(e_t(3), e_t(6))), hurwitz2(e_t(3), T(6)), ulp);


//       TTS_ULP_EQUAL(hurwitz(e_t(3), T(1)), T(1.2020569031595942853997L), ulp);
    TTS_ULP_EQUAL(hurwitz2(e_t(3), T(1)), T(1.2020569031595942853997L), ulp);
    TTS_ULP_EQUAL(T(hurwitz2(e_t(3), e_t(1))), hurwitz2(e_t(3), T(1)), ulp);


//     TTS_ULP_EQUAL(hurwitz(e_t(3), e_t(-2.45)), e_t(17.761703009137815L)    , ulp);
    TTS_ULP_EQUAL(hurwitz2(e_t(3), e_t(-2.45)), e_t(17.761703009137815L)    , ulp);
    TTS_ULP_EQUAL(T(hurwitz2(e_t(3), e_t(-2.45))), hurwitz2(e_t(3), T(-2.45)), ulp);

//     TTS_ULP_EQUAL(hurwitz(e_t(3), e_t(15)),e_t(0.0023753013582757773733L) , ulp);
     TTS_ULP_EQUAL(hurwitz2(e_t(3), e_t(15)),e_t(0.0023753013582757773733L) , ulp);
     TTS_ULP_EQUAL(T(hurwitz2(e_t(3), e_t(15))), hurwitz2(e_t(3), T(15)), ulp);

//        TTS_ULP_EQUAL(hurwitz(e_t(-3), e_t(15)),e_t(-11024.991666666667)       , ulp);
     TTS_ULP_EQUAL(hurwitz2(e_t(-3), e_t(15)),e_t(-11024.991666666667)       , ulp);
     TTS_ULP_EQUAL(hurwitz2(e_t(-3), T(15)),T(-11024.991666666667)       , ulp);

//        TTS_ULP_EQUAL(hurwitz(e_t(-3), e_t(0.125)), e_t(0.005342610677085968)  , ulp);
     TTS_ULP_EQUAL(hurwitz2(e_t(-3), e_t(0.125)), e_t(0.005342610677085968)  , ulp);
     TTS_ULP_EQUAL(hurwitz2(e_t(-3), T(0.125)), T(0.005342610677085968)  , 1000*ulp);
// //     TTS_ULP_EQUAL(hurwitz(e_t(-3), T( 2.0)), T(-.9916666666666689)    , 1000*ulp);


     eve::wide<double, eve::fixed<4>> z{0.125, 15, -2.45, 1.0};
     eve::wide<double, eve::fixed<4>> r{512.8766690590678412978, 0.0023753013582757773733, 17.761703009137815, 1.2020569031595942853997};
     TTS_ULP_EQUAL(hurwitz2(e_t(3), z), r    , ulp);

  }
//else TTS_EQUAL(0, 0);
};
