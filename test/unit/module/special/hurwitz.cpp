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
// Types tests
//==================================================================================================
// TTS_CASE_TPL("Check return types of hurwitz", eve::test::simd::ieee_reals)
// <typename T>(tts::type<T>)
// {
//   using v_t = eve::element_type_t<T>;

//   TTS_EXPR_IS(eve::hurwitz(T(), T()), T);
//   TTS_EXPR_IS(eve::hurwitz(v_t(), v_t()), v_t);
//   TTS_EXPR_IS(eve::hurwitz(int(), T()), T);
// };

//==================================================================================================
// hurwitz  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of hurwitz on wide", eve::test::simd::ieee_reals)
  <typename T>(tts::type<T>)
{
  using eve::hurwitz;
  using e_t = eve::element_type_t<T>;

//   if constexpr( eve::platform::supports_invalids )
//   {
//     TTS_IEEE_EQUAL(hurwitz(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
//     TTS_IEEE_EQUAL(hurwitz(eve::inf(eve::as<T>())), eve::inf(eve::as<T>()));
//     TTS_IEEE_EQUAL(hurwitz(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()));
//   }
  auto ulp = 2.0;
  if constexpr(sizeof(e_t) == 8  && eve::cardinal_v<T> == 1)
{
//    TTS_ULP_EQUAL(hurwitz(e_t(3), T(0.125)), T(512.8766690590678412978L), ulp);
//    TTS_ULP_EQUAL(hurwitz(e_t(3), T(1)), T(1.2020569031595942853997L), ulp);
//    TTS_ULP_EQUAL(hurwitz(e_t(3), T(6)), T(0.0163948661225572483627L), ulp);

   TTS_ULP_EQUAL(hurwitz(e_t(3), e_t(-2.45)), e_t(17.761703009137815L)    , ulp);
   TTS_ULP_EQUAL(hurwitz(e_t(3), T(-2.45)), T(17.761703009137815L)     , ulp);


//    TTS_ULP_EQUAL(hurwitz(e_t(3), T(15)),T(0.0023753013582757773733L) , ulp);


//    TTS_ULP_EQUAL(hurwitz(e_t(-3), T(15)),T(-11024.991666666667)       , ulp);
//    TTS_ULP_EQUAL(hurwitz(e_t(-3), T(0.125)), T(0.005342610677085968)  , 1000*ulp);
//    TTS_ULP_EQUAL(hurwitz(e_t(-3), T( 2.0)), T(-.9916666666666689)    , 1000*ulp);


}
//else TTS_EQUAL(0, 0);
};

// TTS_CASE_WITH("Check behavior of hurwitz on wide",
//               eve::test::simd::ieee_reals,
//               tts::generate(tts::randoms(0.4, 4.0)))
// <typename T>(T const& a0) { TTS_ULP_EQUAL(eve::hurwitz(a0), T(tts::map(eve::hurwitz, a0)), 2); };


// //==================================================================================================
// // Tests for masked hurwitz
// //==================================================================================================
// TTS_CASE_WITH("Check behavior of eve::masked(eve::hurwitz)(eve::wide)",
//               eve::test::simd::ieee_reals,
//               tts::generate(tts::randoms(0.4, 4.0),
//               tts::logicals(0, 3)))
// <typename T, typename M>(T const& a0,
//                          M const& mask)
// {
//   TTS_IEEE_EQUAL(eve::hurwitz[mask](a0),
//             eve::if_else(mask, eve::hurwitz(a0), a0));
// };
