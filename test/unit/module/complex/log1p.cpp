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

// template < typename T >
// auto cv(std::complex <T> sc)
// {
//   return eve::complex<T>(sc.real(), sc.imag());
// }

EVE_TEST_TYPES( "Check behavior of log2"
        , eve::test::simd::ieee_reals
            )
  <typename T>(eve::as<T>)
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
