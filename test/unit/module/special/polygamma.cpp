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
TTS_CASE_TPL("Check return types of polygamma", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::polygamma(T(), T()), T);
  TTS_EXPR_IS(eve::polygamma(v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::polygamma(int(), T()), T);
};

//==================================================================================================
// polygamma  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of polygamma on wide", eve::test::simd::ieee_reals)
  <typename T>(tts::type<T>)
{
  using eve::polygamma;
//  using e_t = eve::element_type_t<T>;

//   if constexpr( eve::platform::supports_invalids )
//   {
//     TTS_IEEE_EQUAL(polygamma(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
//     TTS_IEEE_EQUAL(polygamma(eve::inf(eve::as<T>())), eve::inf(eve::as<T>()));
//     TTS_IEEE_EQUAL(polygamma(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()));
//   }
  auto ulp = 2.0;
//  TTS_ULP_EQUAL(polygamma(3, T(0.125)), T(24580.14341906357), ulp);
  TTS_ULP_EQUAL(polygamma(3, T(1)), T(6.493939402266829), ulp);
//   TTS_ULP_EQUAL(polygamma(T(0.5)), T(e_t(-1.9635100260214234794409763329987555671931596046604L)), ulp);
//   TTS_ULP_EQUAL(polygamma(T(1)), T(e_t(-0.57721566490153286060651209008240243104215933593992L)), ulp);
//   TTS_ULP_EQUAL(
//       polygamma(T(1.5)), T(e_t(0.036489973978576520559023667001244432806840395339566L)), ulp * 40);
//   TTS_ULP_EQUAL(polygamma(T(1.5) - T(1) / 32),
//                 T(e_t(0.00686541147073577672813890866512415766586241385896200579891429L)),
//                 ulp * 100);
//   TTS_ULP_EQUAL(polygamma(T(2)), T(e_t(0.42278433509846713939348790991759756895784066406008L)), ulp);
//   TTS_ULP_EQUAL(polygamma(T(8)), T(e_t(2.0156414779556099965363450527747404261006978069172L)), ulp);
//   TTS_ULP_EQUAL(polygamma(T(12)), T(e_t(2.4426616799758120167383652547949424463027180089374L)), ulp);
//   TTS_ULP_EQUAL(polygamma(T(22)), T(e_t(3.0681430398611966699248760264450329818421699570581L)), ulp);
//   TTS_ULP_EQUAL(polygamma(T(50)), T(e_t(3.9019896734278921969539597028823666609284424880275L)), ulp);
//   TTS_ULP_EQUAL(polygamma(T(500)), T(e_t(6.2136077650889917423827750552855712637776544784569L)), ulp);
//   TTS_ULP_EQUAL(polygamma(T(3.193317413330078125)), T(polygamma(3.193317413330078125)), ulp);
//   TTS_ULP_EQUAL(polygamma(T(3.193317413330078125)), T(9.963879482071649e-01), ulp);
//   //
//   // negative values:
//   //
//   TTS_ULP_EQUAL(polygamma(T(-0.125)), T(e_t(7.1959829284523046176757814502538535827603450463013L)), ulp);
//   TTS_ULP_EQUAL(polygamma(T(-10.125)), T(e_t(9.9480538258660761287008034071425343357982429855241L)), ulp);
//   TTS_ULP_EQUAL(polygamma(T(-10.875)), T(e_t(-5.1527360383841562620205965901515879492020193154231L)), ulp);
//   TTS_ULP_EQUAL(polygamma(T(-1.5)), T(e_t(0.70315664064524318722569033366791109947350706200623L)), ulp);
};

// TTS_CASE_WITH("Check behavior of polygamma on wide",
//               eve::test::simd::ieee_reals,
//               tts::generate(tts::randoms(0.4, 4.0)))
// <typename T>(T const& a0) { TTS_ULP_EQUAL(eve::polygamma(a0), T(tts::map(eve::polygamma, a0)), 2); };


// //==================================================================================================
// // Tests for masked polygamma
// //==================================================================================================
// TTS_CASE_WITH("Check behavior of eve::masked(eve::polygamma)(eve::wide)",
//               eve::test::simd::ieee_reals,
//               tts::generate(tts::randoms(0.4, 4.0),
//               tts::logicals(0, 3)))
// <typename T, typename M>(T const& a0,
//                          M const& mask)
// {
//   TTS_IEEE_EQUAL(eve::polygamma[mask](a0),
//             eve::if_else(mask, eve::polygamma(a0), a0));
// };
