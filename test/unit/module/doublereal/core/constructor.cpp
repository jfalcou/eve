//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/doublereal.hpp>

TTS_CASE_TPL( "Check doublereal constructor from constants", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using w_t = eve::wide<T>;
  auto spi  = T(3.1415926535897932384626433832795028841971693993751);
  auto so   = T(1.22464679914735317722606593227500105820974944592307e-16);
  auto wpi  = w_t(spi);
  auto wo   = w_t(so);

  eve::doublereal<T>             z_sd{};
  eve::doublereal<T>             z_s0{spi};
  eve::doublereal<T>             z_ss{spi,so};
  eve::wide<eve::doublereal<T>>  z_vd{};
  eve::wide<eve::doublereal<T>>  z_vs{wo,spi};
  eve::wide<eve::doublereal<T>>  z_sv{spi,wo};
  eve::wide<eve::doublereal<T>>  z_vv{wo,wpi};

  TTS_EQUAL( eve::high(z_sd), T{0}  );
  TTS_EQUAL( eve::low(z_sd), T{0} );

  TTS_EQUAL( eve::high(z_s0), spi  );
  TTS_EQUAL( eve::low(z_s0), T{0} );

  TTS_EQUAL( eve::high(z_ss), spi);
  TTS_EQUAL( eve::low(z_ss), so );

  TTS_EQUAL( eve::high(z_vd), w_t{0} );
  TTS_EQUAL( eve::low(z_vd), w_t{0});

  TTS_EQUAL( eve::high(z_vs), wo );
  TTS_EQUAL( eve::low(z_vs), wpi);

  TTS_EQUAL( eve::high(z_sv), wpi);
  TTS_EQUAL( eve::low(z_sv), wo );

  TTS_EQUAL( eve::high(z_vv), wo );
  TTS_EQUAL( eve::low(z_vv), wpi);
};

// TTS_CASE_TPL("Check doublereal constructor from lambda", eve::test::scalar::ieee_reals)
// <typename T>(tts::type<T>)
// {
//   using w_t = eve::wide<T>;

//   auto fill_r = [](auto i, auto) { return T(1+i); };
//   auto fill_i = [](auto i, auto) { return T(1)/(1+i); };
//   auto fill   = [](auto i, auto) { return eve::doublereal<T>(T(1+i),T(1)/(1+i)); };

//   eve::wide<eve::doublereal<T>> z_l(fill);
//   eve::wide<eve::doublereal<T>> z_ll(fill_r, fill_i);
//   eve::wide<eve::doublereal<T>> z_lc(fill_r, T{1.25});
//   eve::wide<eve::doublereal<T>> z_cl(T{8.8},fill_i);

//   TTS_EQUAL( eve::high(z_l)  , w_t(fill_r));
//   TTS_EQUAL( eve::low(z_l)  , w_t(fill_i));
//   TTS_EQUAL( eve::high(z_ll) , w_t(fill_r));
//   TTS_EQUAL( eve::low(z_ll) , w_t(fill_i));
//   TTS_EQUAL( eve::high(z_lc) , w_t(fill_r));
//   TTS_EQUAL( eve::low(z_lc) , w_t(1.25));
//   TTS_EQUAL( eve::high(z_cl) , w_t(8.8));
//   TTS_EQUAL( eve::low(z_cl) , w_t(fill_i));
// };

TTS_CASE_TPL("Check doublereal copy/assignment", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using w_t = eve::wide<T>;
  auto spi  = eve::pi(eve::as<T>{});
  auto so   = T{1};
  auto wpi  = w_t(spi);
  auto wo   = w_t(so);
  using doublereal_t = eve::doublereal<T>;
  using wdoublereal_t = eve::wide<eve::doublereal<T>>;
  int N = (sizeof(T) == 4) ? 40 :60;
  int64_t a(1ll << N);
  int64_t b(12);
  int64_t c(a+b);
  float f = 2.0f;
  double d = 2.0;
  double d1 = 1.23456789123456789;

  doublereal_t             z_s{spi,so};
  auto                   z_sc{z_s};
  doublereal_t             z_sa;
  z_sa = z_s;
  wdoublereal_t  z_v(eve::make_doublereal(wo,wpi));
  auto                   z_vc{z_v};
  wdoublereal_t  z_va;
  z_va = z_v;

  TTS_EQUAL ( z_sc, z_s );
  TTS_EQUAL ( z_sa, z_s );
  TTS_EQUAL ( z_vc, z_v );
  TTS_EQUAL ( z_va, z_v );

  {
    doublereal_t fi64(c);
    doublereal_t fd64 = eve::make_doublereal(T(a), T(b));
    doublereal_t doublerealf(f);
    doublereal_t doublereald(d);
    doublereal_t doublereal1d(d1);
    doublereal_t doublereal1f = eve::make_doublereal(T(float(d1)), T(d1-float(d1)));

    TTS_EQUAL ( fd64, fi64);
    TTS_EQUAL ( doublerealf,  doublereald);
    TTS_EQUAL ( doublereal1d, doublereal1f);
  }
  {
    wdoublereal_t fi64(c);
    wdoublereal_t fd64 = eve::make_doublereal(w_t(a), w_t(b));
    wdoublereal_t doublerealf(f);
    wdoublereal_t doublereald(d);
    wdoublereal_t doublereal1d(d1);
    wdoublereal_t doublereal1f = eve::make_doublereal(w_t(float(d1)), w_t(d1-float(d1)));
    TTS_EQUAL ( fd64, fi64);
    TTS_EQUAL ( doublerealf,  doublereald);
    TTS_EQUAL ( doublereal1d, doublereal1f);
  }
};
