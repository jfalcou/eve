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
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of secd"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::secd(T())  , T);
  TTS_EXPR_IS( eve::secd(v_t()), v_t);
};

//==================================================================================================
// secd  tests
//==================================================================================================
auto mquarter_c  = []<typename T>(eve::as<T> const & ){  return T(-45); };
auto quarter_c   = []<typename T>(eve::as<T> const & ){  return T( 45); };
auto mhalf_c = []<typename T>(eve::as<T> const & ){  return T(-90 ); };
auto half_c  = []<typename T>(eve::as<T> const & ){  return T( 90 ); };
auto mmed   = []<typename T>(eve::as<T> const & ){  return -5000; };
auto med    = []<typename T>(eve::as<T> const & ){  return  5000; };

EVE_TEST( "Check behavior of secd on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(mquarter_c, quarter_c)
                             , eve::test::randoms(mhalf_c, half_c)
                             , eve::test::randoms(mmed, med))
        )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::detail::map;
  using eve::secd;
  using eve::diff;
  using eve::deginrad;
  using v_t = eve::element_type_t<T>;
  auto ref = [](auto e) -> v_t { return 1.0l/boost::math::cos_pi(e/180.0l); };

  TTS_ULP_EQUAL(eve::quarter_circle(secd)(a0)      , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(secd)(a0)           , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(secd)(a1)           , map(ref, a1), 50);
  TTS_ULP_EQUAL(secd(a0)                       , map(ref, a0), 2);
  TTS_ULP_EQUAL(secd(a1)                       , map(ref, a1), 50);
  TTS_ULP_EQUAL(secd(a2)                       , map(ref, a2), 800);
  auto dinr = 1.7453292519943295769236907684886127134428718885417e-2l;

  TTS_ULP_EQUAL(diff(secd)(a0), map([dinr](auto e) -> v_t { return  dinr*eve::secd(e)*eve::tand(e); }, a0), 2);
};

EVE_TEST_TYPES( "Check return types of secd"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::secd(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::secd(eve::inf(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::secd(eve::minf(eve::as<T>())) , eve::nan(eve::as<T>()) );
  }

  TTS_IEEE_EQUAL(eve::secd(T( 0 )) , T(1));
  TTS_IEEE_EQUAL(eve::secd(T(-0.)) , T(1));

};
