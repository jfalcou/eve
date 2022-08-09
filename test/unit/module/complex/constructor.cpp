//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/complex.hpp>

TTS_CASE_TPL( "Check complex constructor from constants", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using w_t = eve::wide<T>;
  auto spi  = eve::pi(eve::as<T>{});
  auto so   = T{1};
  auto wpi  = w_t(spi);
  auto wo   = w_t(so);

  eve::complex<T>             z_sd{};
  eve::complex<T>             z_s0{spi};
  eve::complex<T>             z_ss{spi,so};
  eve::wide<eve::complex<T>>  z_vd{};
  eve::wide<eve::complex<T>>  z_vs{wo,spi};
  eve::wide<eve::complex<T>>  z_sv{spi,wo};
  eve::wide<eve::complex<T>>  z_vv{wo,wpi};

  TTS_EQUAL( eve::real(z_sd), T{0}  );
  TTS_EQUAL( eve::imag(z_sd), T{0} );

  TTS_EQUAL( eve::real(z_s0), spi  );
  TTS_EQUAL( eve::imag(z_s0), T{0} );

  TTS_EQUAL( eve::real(z_ss), spi);
  TTS_EQUAL( eve::imag(z_ss), so );

  TTS_EQUAL( eve::real(z_vd), w_t{0} );
  TTS_EQUAL( eve::imag(z_vd), w_t{0});

  TTS_EQUAL( eve::real(z_vs), wo );
  TTS_EQUAL( eve::imag(z_vs), wpi);

  TTS_EQUAL( eve::real(z_sv), wpi);
  TTS_EQUAL( eve::imag(z_sv), wo );

  TTS_EQUAL( eve::real(z_vv), wo );
  TTS_EQUAL( eve::imag(z_vv), wpi);
};

TTS_CASE_TPL("Check complex constructor from lambda", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using w_t = eve::wide<T>;

  auto fill_r = [](auto i, auto) { return T(1+i); };
  auto fill_i = [](auto i, auto) { return T(1)/(1+i); };
  auto fill   = [](auto i, auto) { return eve::complex<T>(T(1+i),T(1)/(1+i)); };

  eve::wide<eve::complex<T>> z_l(fill);
  eve::wide<eve::complex<T>> z_ll(fill_r, fill_i);
  eve::wide<eve::complex<T>> z_lc(fill_r, T{1.25});
  eve::wide<eve::complex<T>> z_cl(T{8.8},fill_i);

  TTS_EQUAL( eve::real(z_l)  , w_t(fill_r));
  TTS_EQUAL( eve::imag(z_l)  , w_t(fill_i));
  TTS_EQUAL( eve::real(z_ll) , w_t(fill_r));
  TTS_EQUAL( eve::imag(z_ll) , w_t(fill_i));
  TTS_EQUAL( eve::real(z_lc) , w_t(fill_r));
  TTS_EQUAL( eve::imag(z_lc) , w_t(1.25));
  TTS_EQUAL( eve::real(z_cl) , w_t(8.8));
  TTS_EQUAL( eve::imag(z_cl) , w_t(fill_i));
};

TTS_CASE_TPL("Check complex copy/assignment", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using w_t = eve::wide<T>;
  auto spi  = eve::pi(eve::as<T>{});
  auto so   = T{1};
  auto wpi  = w_t(spi);
  auto wo   = w_t(so);

  eve::complex<T>             z_s{spi,so};
  auto                        z_sc{z_s};
  eve::complex<T>             z_sa;
  z_sa = z_s;

  eve::wide<eve::complex<T>>  z_v{wo,wpi};
  auto                        z_vc{z_v};
  eve::wide<eve::complex<T>>  z_va;
  z_va = z_v;

  TTS_EQUAL ( z_sc, z_s );
  TTS_EQUAL ( z_sa, z_s );
  TTS_EQUAL ( z_vc, z_v );
  TTS_EQUAL ( z_va, z_v );
};
