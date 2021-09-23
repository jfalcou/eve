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
#include <eve/constant/invpi.hpp>
#include <eve/function/sind.hpp>
#include <eve/function/diff/sind.hpp>
#include <eve/function/deginrad.hpp>
#include <cmath>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
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
auto mrest  = []<typename T>(eve::as<T> const & ){  return T(-45); };
auto rest   = []<typename T>(eve::as<T> const & ){  return T( 45); };
auto msmall = []<typename T>(eve::as<T> const & ){  return T(-90 ); };
auto small  = []<typename T>(eve::as<T> const & ){  return T( 90 ); };
auto mmed   = []<typename T>(eve::as<T> const & ){  return -5000; };
auto med    = []<typename T>(eve::as<T> const & ){  return  5000; };

EVE_TEST( "Check behavior of sind on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(mrest, rest)
                             , eve::test::randoms(msmall, small)
                             , eve::test::randoms(mmed, med))
        )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::detail::map;
  using eve::sind;
  using eve::diff;
  using eve::deginrad;
  using v_t = eve::element_type_t<T>;
  auto ref = [](auto e) -> v_t { return boost::math::sin_pi(e/180.0l); };

  TTS_ULP_EQUAL(eve::restricted(sind)(a0)      , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::small(sind)(a0)           , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::small(sind)(a1)           , map(ref, a1), 30);
  TTS_ULP_EQUAL(eve::medium(sind)(a0)          , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::medium(sind)(a1)          , map(ref, a1), 30);
  TTS_ULP_EQUAL(eve::medium(sind)(a2)          , map(ref, a2), 1024);
  TTS_ULP_EQUAL(eve::big(sind)(a0)             , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::big(sind)(a1)             , map(ref, a1), 30);
  TTS_ULP_EQUAL(eve::big(sind)(a2)             , map(ref, a2), 1024);
  TTS_ULP_EQUAL(sind(a0)                       , map(ref, a0), 2);
  TTS_ULP_EQUAL(sind(a1)                       , map(ref, a1), 30);
  TTS_ULP_EQUAL(sind(a2)                       , map(ref, a2), 1024);
  auto dinr = 1.7453292519943295769236907684886127134428718885417e-2l;

  TTS_ULP_EQUAL(diff(sind)(a0), map([dinr](auto e) -> v_t { return  dinr*boost::math::cos_pi(e/180.0l); }, a0), 2);
};

EVE_TEST_TYPES( "Check return types of sind"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  TTS_ULP_EQUAL(eve::big(eve::sind)( T(1)    ) , T(1.745240643728351281941897851631619247225272030714e-2)  , 4.0);
  TTS_ULP_EQUAL(eve::big(eve::sind)(-T(1)    ) , T(-1.745240643728351281941897851631619247225272030714e-2) , 4.0);
  TTS_ULP_EQUAL(eve::big(eve::sind)( T(45.0) ) , T(0.70710678118654752440084436210484903928483593768847)   , 4.0);
  TTS_ULP_EQUAL(eve::big(eve::sind)(-T(45.0) ) , T(-0.70710678118654752440084436210484903928483593768847)  , 4.0);
  TTS_ULP_EQUAL(eve::big(eve::sind)( T(500.0)) , T(0.64278760968653932632264340990726343290755988420567)   , 4.0);
  TTS_ULP_EQUAL(eve::big(eve::sind)(-T(500.0)) , T(-0.64278760968653932632264340990726343290755988420567)  , 4.0);
  TTS_ULP_EQUAL(eve::sind( T(1)    ) , T(1.745240643728351281941897851631619247225272030714e-2)  , 4.0);
  TTS_ULP_EQUAL(eve::sind(-T(1)    ) , T(-1.745240643728351281941897851631619247225272030714e-2) , 4.0);
  TTS_ULP_EQUAL(eve::sind( T(45.0) ) , T(0.70710678118654752440084436210484903928483593768847)   , 4.0);
  TTS_ULP_EQUAL(eve::sind(-T(45.0) ) , T(-0.70710678118654752440084436210484903928483593768847)  , 4.0);
  TTS_ULP_EQUAL(eve::sind( T(500.0)) , T(0.64278760968653932632264340990726343290755988420567)   , 4.0);
  TTS_ULP_EQUAL(eve::sind(-T(500.0)) , T(-0.64278760968653932632264340990726343290755988420567)  , 4.0);
};
