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
EVE_TEST_TYPES( "Check return types of sind"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::sind(T())  , T);
  TTS_EXPR_IS( eve::sind(v_t()), v_t);
};

//==================================================================================================
// sind  tests
//==================================================================================================
auto mquarter_c  = []<typename T>(eve::as<T> const & ){  return T(-45); };
auto quarter_c   = []<typename T>(eve::as<T> const & ){  return T( 45); };
auto mhalf_c = []<typename T>(eve::as<T> const & ){  return T(-90 ); };
auto half_c  = []<typename T>(eve::as<T> const & ){  return T( 90 ); };
auto mmed   = []<typename T>(eve::as<T> const & ){  return -5000; };
auto med    = []<typename T>(eve::as<T> const & ){  return  5000; };

EVE_TEST( "Check behavior of sind on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(mquarter_c, quarter_c)
                             , eve::test::randoms(mhalf_c, half_c)
                             , eve::test::randoms(mmed, med))
        )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::detail::map;
  using eve::sind;
  
  using eve::deginrad;
  using v_t = eve::element_type_t<T>;
  auto ref = [](auto e) -> v_t { return boost::math::sin_pi(e/180.0l); };

  TTS_ULP_EQUAL(eve::quarter_circle(sind)(a0)      , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(sind)(a0)           , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(sind)(a1)           , map(ref, a1), 30);
  TTS_ULP_EQUAL(sind(a0)                       , map(ref, a0), 2);
  TTS_ULP_EQUAL(sind(a1)                       , map(ref, a1), 30);
  TTS_ULP_EQUAL(sind(a2)                       , map(ref, a2), 1024);
};

EVE_TEST_TYPES( "Check return types of sind"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  TTS_ULP_EQUAL(eve::sind( T(1)    ) , T(1.745240643728351281941897851631619247225272030714e-2)  , 4.0);
  TTS_ULP_EQUAL(eve::sind(-T(1)    ) , T(-1.745240643728351281941897851631619247225272030714e-2) , 4.0);
  TTS_ULP_EQUAL(eve::sind( T(45.0) ) , T(0.70710678118654752440084436210484903928483593768847)   , 4.0);
  TTS_ULP_EQUAL(eve::sind(-T(45.0) ) , T(-0.70710678118654752440084436210484903928483593768847)  , 4.0);
  TTS_ULP_EQUAL(eve::sind( T(500.0)) , T(0.64278760968653932632264340990726343290755988420567)   , 4.0);
  TTS_ULP_EQUAL(eve::sind(-T(500.0)) , T(-0.64278760968653932632264340990726343290755988420567)  , 4.0);
};
