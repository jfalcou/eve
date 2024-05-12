//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/complex.hpp>
#include <complex>

TTS_CASE_TPL( "Check behavior of log1p", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using e_t = eve::element_type_t<T>;
  using z_t = eve::as_complex_t<T>;
  auto inf = eve::inf(as<T>());
  auto minf = eve::minf(as<T>());
  auto zer = eve::zero(as<T>());
  auto pi  = eve::pi(as<T>());
  auto eps = eve::eps(as<T>());
  using z_t = eve::as_complex_t<T>;
  TTS_ULP_EQUAL(eve::log(z_t{inf, zer}),   (z_t{inf, zer}), 0.5);
  TTS_ULP_EQUAL(eve::log1p(z_t{minf, zer}),  (z_t{inf, pi}), 0.5);
  TTS_ULP_EQUAL(eve::log1p(z_t{eve::mone(as<e_t>()), zer}),   (z_t{minf, zer}), 0.5);
  TTS_ULP_EQUAL(eve::log1p(z_t{eve::nan(eve::as<e_t>()), zer}),   (z_t{eve::nan(eve::as<e_t>()), zer}), 0.5);
  TTS_ULP_EQUAL(eve::log1p(z_t{eve::nan(eve::as<e_t>()),eve::nan(eve::as<e_t>())}),  (z_t{eve::nan(eve::as<e_t>()), eve::nan(eve::as<e_t>())}), 0.5);
  TTS_ULP_EQUAL(eve::log1p(z_t{eve::one(eve::as<e_t>()), zer}),   (z_t{eve::log_2(eve::as<T>()), zer}), 0.5);
  TTS_ULP_EQUAL(eve::log1p(z_t{zer, zer}), (z_t{zer, zer}), 0.5);
  TTS_ULP_EQUAL(eve::log1p(z_t{zer, eve::one(eve::as<e_t>())}), (z_t{eve::log(eve::sqrt_2(eve::as<e_t>())), eve::pio_4(eve::as<e_t>())}), 0.5);
  TTS_ULP_EQUAL(eve::log1p(z_t{eps, zer}), (z_t{eve::log1p(eps), zer}), 0.5);
 };
