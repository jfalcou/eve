//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/complex.hpp>
#include <complex>

TTS_CASE_TPL( "Check behavior of log2", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using z_t = eve::as_complex_t<T>;
//   auto inf = eve::inf(as<T>());
//   auto minf = eve::minf(as<T>());
//   auto zer = eve::zero(as<T>());
//   auto pi  = eve::pi(as<T>());
//   auto eps = eve::eps(as<T>());
  auto nan = eve::nan(as<T>());
//   auto mone= eve::mone(as<T>());
//   auto one= eve::one(as<T>());
//   auto e =  eve::euler(as<T>());
//   TTS_ULP_EQUAL(eve::expm1(z_t{inf, zer}),   (z_t{inf, zer}), 0.5);
//   TTS_ULP_EQUAL(eve::expm1(z_t{minf, zer}),  (z_t{inf, mone}), 0.5);

//   TTS_ULP_EQUAL(eve::expm1(z_t{nan, zer}),   (z_t{nan, zer}), 0.5);
  TTS_ULP_EQUAL(eve::expm1(z_t{nan, nan}),   (z_t{nan, nan}), 0.5);
//   TTS_ULP_EQUAL(eve::expm1(z_t{one, zer}),   (z_t{e-one, zer}), 0.5);
//   TTS_ULP_EQUAL(eve::expm1(z_t{zer, zer}),   (z_t{zer, zer}), 0.5);
// //  TTS_ABSOLUTE_EQUAL(eve::expm1(z_t{zer, pi}),    (z_t{e_t(-2.0), zer}), 2*eps);
//   TTS_EXPECT(eve::all(eve::abs(eve::expm1(z_t{zer, pi})-(z_t{e_t(-2.0), zer})) <= 2*eps));
//   TTS_ULP_EQUAL(eve::expm1(z_t{eps, zer}),   (z_t{eps, zer}), 0.5);
 };
