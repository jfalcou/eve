//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/quaternion.hpp>

TTS_CASE_TPL( "Check quaternion constructor from constants", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using w_t = eve::wide<T>;
  auto spi  = eve::pi(eve::as<T>{});
  auto so   = T{1};
  auto wpi  = w_t(spi);
  auto wo   = w_t(so);

  eve::quaternion<T>             z_sd{};
  eve::quaternion<T>             z_s0{spi};
  eve::quaternion<T>             z_ss{spi,so, so, so};
  eve::wide<eve::quaternion<T>>  z_vd{};
  eve::wide<eve::quaternion<T>>  z_vs{wo,spi,spi,spi};
  eve::wide<eve::quaternion<T>>  z_sv{spi,wo,wo,wo};
  eve::wide<eve::quaternion<T>>  z_vv{wo,wpi,wpi,wpi};
  auto a = kumi::make_tuple(wpi,wpi,wpi);
  eve::wide<eve::quaternion<T>> z_ra =  eve::to_quaternion(wo,a);

  TTS_EQUAL( eve::real(z_sd), T{0}  );
  TTS_EQUAL( eve::ipart(z_sd), T{0} );
  TTS_EQUAL( eve::jpart(z_sd), T{0} );
  TTS_EQUAL( eve::kpart(z_sd), T{0} );

  TTS_EQUAL( eve::real(z_s0), spi  );
  TTS_EQUAL( eve::ipart(z_s0), T{0} );
  TTS_EQUAL( eve::jpart(z_s0), T{0} );
  TTS_EQUAL( eve::kpart(z_s0), T{0} );

  TTS_EQUAL( eve::real(z_ss), spi);
  TTS_EQUAL( eve::ipart(z_ss), so );
  TTS_EQUAL( eve::jpart(z_ss), so );
  TTS_EQUAL( eve::kpart(z_ss), so );

  TTS_EQUAL( eve::real(z_vd), w_t{0} );
  TTS_EQUAL( eve::ipart(z_vd), w_t{0});
  TTS_EQUAL( eve::jpart(z_vd), w_t{0} );
  TTS_EQUAL( eve::kpart(z_vd), w_t{0} );

  TTS_EQUAL( eve::real(z_vs), wo );
  TTS_EQUAL( eve::ipart(z_vs), wpi);
  TTS_EQUAL( eve::jpart(z_vs), wpi);
  TTS_EQUAL( eve::kpart(z_vs), wpi);

  TTS_EQUAL( eve::real(z_sv), wpi);
  TTS_EQUAL( eve::ipart(z_sv), wo );
  TTS_EQUAL( eve::jpart(z_sv), wo);
  TTS_EQUAL( eve::kpart(z_sv), wo);

  TTS_EQUAL( eve::real(z_vv), wo );
  TTS_EQUAL( eve::ipart(z_vv), wpi);
  TTS_EQUAL( eve::jpart(z_vv), wpi);
  TTS_EQUAL( eve::kpart(z_vv), wpi);

  TTS_EQUAL( eve::real(z_ra), wo );
  TTS_EQUAL( eve::ipart(z_ra), wpi);
  TTS_EQUAL( eve::jpart(z_ra), wpi);
  TTS_EQUAL( eve::kpart(z_ra), wpi);
};

TTS_CASE_TPL("Check quaternion constructor from lambda", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using w_t = eve::wide<T>;

  auto fill_r = [](auto i, auto) { return T(1+i); };
  auto fill_i = [](auto i, auto) { return T(1)/(1+i); };
  auto fill_j = [](auto i, auto) { return T(i); };
  auto fill_k = [](auto  , auto) { return T(1); };
  auto fill   = [](auto i, auto) { return eve::quaternion<T>(T(1+i),T(1)/(1+i),T(i),T(1)); };

  eve::wide<eve::quaternion<T>> z_l(fill);
  eve::wide<eve::quaternion<T>> z_ll(fill_r, fill_i, fill_j, fill_k);
  eve::wide<eve::quaternion<T>> z_lc(fill_r, T{1.25}, T{2.25}, T{3.25});
  eve::wide<eve::quaternion<T>> z_cl(T{8.8},fill_i, T(1.0), fill_k);

  TTS_EQUAL( eve::real(z_l)  , w_t(fill_r));
  TTS_EQUAL( eve::ipart(z_l)  , w_t(fill_i));
  TTS_EQUAL( eve::jpart(z_l)  , w_t(fill_j));
  TTS_EQUAL( eve::kpart(z_l)  , w_t(fill_k));

  TTS_EQUAL( eve::real(z_ll) , w_t(fill_r));
  TTS_EQUAL( eve::ipart(z_ll) , w_t(fill_i));
  TTS_EQUAL( eve::jpart(z_ll) , w_t(fill_j));
  TTS_EQUAL( eve::kpart(z_ll) , w_t(fill_k));

  TTS_EQUAL( eve::real(z_lc) , w_t(fill_r));
  TTS_EQUAL( eve::ipart(z_lc) , w_t(1.25));
  TTS_EQUAL( eve::jpart(z_lc) , w_t(2.25));
  TTS_EQUAL( eve::kpart(z_lc) , w_t(3.25));

  TTS_EQUAL( eve::real(z_cl) , w_t(8.8));
  TTS_EQUAL( eve::ipart(z_cl) , w_t(fill_i));
  TTS_EQUAL( eve::jpart(z_cl) , w_t(1.0));
  TTS_EQUAL( eve::kpart(z_cl) , w_t(fill_k));
};

 TTS_CASE_TPL("Check quaternion copy/assignment", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using w_t = eve::wide<T>;
  auto spi  = eve::pi(eve::as<T>{});
  auto so   = T{1};
  auto wpi  = w_t(spi);
  auto wo   = w_t(so);

  eve::quaternion<T>             z_s{spi,so, so, so};
  auto                           z_sc{z_s};
  eve::quaternion<T>             z_sa;
  z_sa = z_s;

  eve::wide<eve::quaternion<T>>  z_v{wo,wpi, wpi, wpi};
  auto                           z_vc{z_v};
  eve::wide<eve::quaternion<T>>  z_va;
  z_va = z_v;

  TTS_EQUAL ( z_sc, z_s );
  TTS_EQUAL ( z_sa, z_s );
  TTS_EQUAL ( z_vc, z_v );
  TTS_EQUAL ( z_va, z_v );
};
