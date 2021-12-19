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
#include <eve/constant/nan.hpp>
#include <eve/constant/invpi.hpp>
#include <eve/function/cotd.hpp>
#include <eve/function/diff/cotd.hpp>
#include <eve/function/cscd.hpp>
#include <eve/function/cosd.hpp>
#include <eve/function/sind.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/deginrad.hpp>
#include <cmath>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of cotd"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::cotd(T())  , T);
  TTS_EXPR_IS( eve::cotd(v_t()), v_t);
};

//==================================================================================================
// cotd  tests
//==================================================================================================
auto mquarter_c  = []<typename T>(eve::as<T> const & ){  return T(-45); };
auto quarter_c  = []<typename T>(eve::as<T> const & ){  return T( 45); };
auto mhalf_c = []<typename T>(eve::as<T> const & ){  return T(-90 ); };
auto half_c  = []<typename T>(eve::as<T> const & ){  return T( 90 ); };
auto mmed   = []<typename T>(eve::as<T> const & ){  return -5000; };
auto med    = []<typename T>(eve::as<T> const & ){  return  5000; };

EVE_TEST( "Check behavior of cotd on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(mquarter_c, quarter_c)
                             , eve::test::randoms(mhalf_c, half_c)
                             , eve::test::randoms(mmed, med)
                             , eve::test::randoms(eve::valmin, eve::valmax))
                             )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::detail::map;
  using eve::cotd;
  using eve::diff;
  using eve::deginrad;
  using v_t = eve::element_type_t<T>;
  auto ref = [](auto e) -> v_t { auto d = eve::sind(e); return d ? eve::cosd(e)/eve::sind(e): eve::nan(eve::as(e)); };
  TTS_ULP_EQUAL(eve::quarter_circle(cotd)(a0)  , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(cotd)(a0)     , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(cotd)(a1)     , map(ref, a1), 40);
  TTS_ULP_EQUAL(eve::cotd(a0)                  , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::cotd(a1)                  , map(ref, a1), 40);
  TTS_ULP_EQUAL(eve::cotd(a2)                  , map(ref, a2), 1600);
  TTS_ULP_EQUAL(eve::cotd(a3)                  , map(ref, a3), 2);
  auto dinr = 1.7453292519943295769236907684886127134428718885417e-2l;

  TTS_ULP_EQUAL(diff(cotd)(a0), map([dinr](auto e) -> v_t { return  -dinr*eve::sqr(eve::cscd(e)); }, a0), 4);
};

EVE_TEST_TYPES( "Check corner cases of cotd"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using eve::cotd;
  TTS_ULP_EQUAL(cotd( T(  1))   , T(57.289961630759424687278147537112577980217522235144)    , 6);
  TTS_ULP_EQUAL(cotd(-T(  1))   , T(-57.289961630759424687278147537112577980217522235144)   , 6);
  TTS_ULP_EQUAL(cotd( T( 45))   , T(1)                                                      , 6);
  TTS_ULP_EQUAL(cotd(-T( 45))   , T(-1)                                                     , 6);
  TTS_ULP_EQUAL(cotd( T(500.0)) , T(-1.19175359259420995870530807186041933693070040770853)  , 6);
  TTS_ULP_EQUAL(cotd(-T(500.0)) , T(1.19175359259420995870530807186041933693070040770853)   , 6);



};
