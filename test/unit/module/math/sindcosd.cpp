//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/function/cosd.hpp>
#include <eve/function/sind.hpp>
#include <eve/function/sindcosd.hpp>
#include <cmath>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of sindcosd"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::sindcosd(T())  , (kumi::tuple<T, T>));
  TTS_EXPR_IS( eve::sindcosd(v_t()), (kumi::tuple<v_t, v_t>));
};

//==================================================================================================
// sindcosd  tests
//==================================================================================================
auto mquarter_c  = []<typename T>(eve::as<T> const & ){  return T(-45); };
auto quarter_c   = []<typename T>(eve::as<T> const & ){  return T( 45); };
auto mhalf_c = []<typename T>(eve::as<T> const & ){  return T(-90 ); };
auto half_c  = []<typename T>(eve::as<T> const & ){  return T( 90 ); };
auto mmed   = []<typename T>(eve::as<T> const & ){  return T(-360); };
auto med    = []<typename T>(eve::as<T> const & ){  return T( 360); };

EVE_TEST( "Check behavior of sindcosd on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(mquarter_c, quarter_c)
                             , eve::test::randoms(mhalf_c, half_c)
                             , eve::test::randoms(mmed, med)
                             , eve::test::randoms(eve::valmin, eve::valmax))
                             )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::detail::map;
  using eve::sindcosd;
  using eve::diff;
  using v_t = eve::element_type_t<T>;
  auto refc = [](auto e) -> v_t { return eve::cosd(e); };
  auto refs = [](auto e) -> v_t { return eve::sind(e); };
  {
    auto [s, c] = eve::quarter_circle(sindcosd)(a0);
    TTS_ULP_EQUAL(s      , map(refs, a0), 2);
    TTS_ULP_EQUAL(c      , map(refc, a0), 2);
  }
  {
    auto [s, c] = eve::half_circle(sindcosd)(a0);
    TTS_ULP_EQUAL(s      , map(refs, a0), 2);
    TTS_ULP_EQUAL(c      , map(refc, a0), 2);
    auto [s1, c1] = eve::half_circle(sindcosd)(a1);
    TTS_ULP_EQUAL(s1      , map(refs, a1), 2);
    TTS_ULP_EQUAL(c1      , map(refc, a1), 30);
  }
  {
    auto [s, c] = sindcosd(a0);
    TTS_ULP_EQUAL(s      , map(refs, a0), 2);
    TTS_ULP_EQUAL(c      , map(refc, a0), 2);
    auto [s1, c1] = sindcosd(a1);
    TTS_ULP_EQUAL(s1      , map(refs, a1), 2);
    TTS_ULP_EQUAL(c1      , map(refc, a1), 30);
    auto [s2, c2] = sindcosd(a2);
    TTS_ULP_EQUAL(s2      , map(refs, a2), 51);
    TTS_ULP_EQUAL(c2      , map(refc, a2), 51);
    auto [s3, c3] = sindcosd(a3);
    TTS_ULP_EQUAL(s3      , map(refs, a3), 2);
    TTS_ULP_EQUAL(c3      , map(refc, a3), 2);
  }
};
