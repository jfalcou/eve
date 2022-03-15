//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of cos"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::rempio2(T())  , (kumi::tuple<T, T>));
  TTS_EXPR_IS( eve::rempio2(v_t()), (kumi::tuple<v_t, v_t>));
};

//==================================================================================================
// cos  tests
//==================================================================================================
auto mhalf_c  = []<typename T>(eve::as<T> const & tgt){  return -eve::pio_4(tgt); };
auto half_c   = []<typename T>(eve::as<T> const & tgt){  return  eve::pio_4(tgt); };
auto mhalf_c = []<typename T>(eve::as<T> const & tgt){  return -eve::pio_2(tgt); };
auto half_c  = []<typename T>(eve::as<T> const & tgt){  return  eve::pio_2(tgt); };
auto mmed   = []<typename T>(eve::as<T> const & tgt){  return -eve::detail::Rempio2_limit(eve::medium_type(), tgt); };
auto med    = []<typename T>(eve::as<T> const & tgt){  return  eve::detail::Rempio2_limit(eve::medium_type(), tgt); };

EVE_TEST( "Check behavior of cos on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(mquarter_c, quarter_c)
                             , eve::test::randoms(mhalf_c, half_c)
                             , eve::test::randoms(mmed, med)
                             , eve::test::randoms(eve::valmin, eve::valmax))
                             )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::detail::map;
  using eve::rempio2;
  using eve::diff;
  using v_t = eve::element_type_t<T>;
  auto [sn0, sx0, sdx0] = eve::rem_pio2(a0);
  auto [sn1, sx1, sdx1] = eve::rem_pio2(a1);
  auto [sn2, sx2, sdx2] = eve::rem_pio2(a2);
  auto [sn3, sx3, sdx3] = eve::rem_pio2(a3);
  {
    auto [n0, x0, dx0] = eve::quarter_circle(rempio2)(a0);
    TTS_ULP_EQUAL(n0      , sn0, 2);
    TTS_ULP_EQUAL(x0      , sx0, 2);
    TTS_ULP_EQUAL(dx0     , sdx0, 2);
  }
  {
    auto [n0, x0, dx0] = eve::half_circle(rempio2)(a0);
    TTS_ULP_EQUAL(n0      , sn0, 2);
    TTS_ULP_EQUAL(x0      , sx0, 2);
    TTS_ULP_EQUAL(dx0     , sdx0, 2);
    auto [n1, x1, dx1] = eve::half_circle(rempio2)(a1);
    TTS_ULP_EQUAL(n1      , sn1, 2);
    TTS_ULP_EQUAL(x1      , sx1, 2);
    TTS_ULP_EQUAL(dx1     , sdx1, 2);
  }
  {
    auto [n0, x0, dx0] = eve::rempio2(a0);
    TTS_ULP_EQUAL(n0      , sn0, 2);
    TTS_ULP_EQUAL(x0      , sx0, 2);
    TTS_ULP_EQUAL(dx0     , sdx0, 2);
    auto [n1, x1, dx1] = eve::rempio2(a1);
    TTS_ULP_EQUAL(n1      , sn1, 2);
    TTS_ULP_EQUAL(x1      , sx1, 2);
    TTS_ULP_EQUAL(dx1     , sdx1, 2);
    auto [n2, x2, dx2] = eve::rempio2(a2);
    TTS_ULP_EQUAL(n2      , sn2, 2);
    TTS_ULP_EQUAL(x2      , sx2, 2);
    TTS_ULP_EQUAL(dx2     , sdx2, 2);
    auto [n3, x3, dx3] = eve::rempio2(a3);
    TTS_ULP_EQUAL(n3      , sn3, 2);
    TTS_ULP_EQUAL(x3      , sx3, 2);
    TTS_ULP_EQUAL(dx3     , sdx3, 2);
  }
};
