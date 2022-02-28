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
EVE_TEST_TYPES( "Check return types of cscd"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::cscd(T())  , T);
  TTS_EXPR_IS( eve::cscd(v_t()), v_t);
};

//==================================================================================================
// cscd  tests
//==================================================================================================
auto mquarter_c  = []<typename T>(eve::as<T> const & ){  return T(-45); };
auto quarter_c   = []<typename T>(eve::as<T> const & ){  return T( 45); };
auto mhalf_c = []<typename T>(eve::as<T> const & ){  return T(-90 ); };
auto half_c  = []<typename T>(eve::as<T> const & ){  return T( 90 ); };
auto mmed   = []<typename T>(eve::as<T> const & ){  return -5000; };
auto med    = []<typename T>(eve::as<T> const & ){  return  5000; };

EVE_TEST( "Check behavior of cscd on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(mquarter_c, quarter_c)
                             , eve::test::randoms(mhalf_c, half_c)
                             , eve::test::randoms(mmed, med))
                             )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::detail::map;
  using eve::cscd;
  using eve::diff;
  using eve::deginrad;
  using v_t = eve::element_type_t<T>;
  auto ref = [](auto e) -> v_t { auto d = eve::sind(e);return d ? 1.0/d : eve::nan(eve::as(e)); };
  TTS_ULP_EQUAL(eve::quarter_circle(cscd)(a0)  , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(cscd)(a0)     , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(cscd)(a1)     , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::cscd(a0)                  , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::cscd(a1)                  , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::cscd(a2)                  , map(ref, a2), 2);
  auto dinr = 1.7453292519943295769236907684886127134428718885417e-2l;

  TTS_ULP_EQUAL(diff(cscd)(a0), map([dinr](auto e) -> v_t { return  -dinr*cscd(e)*eve::cotd(e); }, a0), 2);
};
