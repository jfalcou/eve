//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cyl_bessel_j0.hpp>
#include <eve/function/prev.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>
#include <boost/math/special_functions/bessel.hpp>

EVE_TEST_TYPES( "Check return types of cyl_bessel_j0"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::cyl_bessel_j0(T(0)), T);
  TTS_EXPR_IS(eve::cyl_bessel_j0(v_t(0)), v_t);
};

 EVE_TEST( "Check behavior of cyl_bessel_j0 on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(0.0, 20000.0))
         )
   <typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;

  auto eve__cyl_bessel_j0 =  [](auto x) { return eve::cyl_bessel_j0(x); };
  auto std__cyl_bessel_j0 =  [](auto x)->v_t { return boost::math::cyl_bessel_j(v_t(0), x); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__cyl_bessel_j0(eve::minf(eve::as<v_t>())), eve::zero(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_j0(eve::inf(eve::as<v_t>())), v_t(0), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_j0(eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_j0(eve::minf(eve::as< T>())), eve::zero(eve::as< T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_j0(eve::inf(eve::as< T>())),  T(0), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_j0(eve::nan(eve::as< T>())), eve::nan(eve::as< T>()), 0);
  }
  TTS_ULP_EQUAL(eve__cyl_bessel_j0(v_t(1500)), std__cyl_bessel_j0(v_t(1500)), 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_j0(v_t(500)), std__cyl_bessel_j0(v_t(500)), 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_j0(v_t(10)), std__cyl_bessel_j0(v_t(10))  , 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_j0(v_t(5)),  std__cyl_bessel_j0(v_t(5))   , 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_j0(v_t(2)),  std__cyl_bessel_j0(v_t(2))   , 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_j0(v_t(1.5)),std__cyl_bessel_j0(v_t(1.5)) , 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_j0(v_t(0.5)),std__cyl_bessel_j0(v_t(0.5)) , 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_j0(v_t(1)),  std__cyl_bessel_j0(v_t(1))   , 2.5);
  TTS_ULP_EQUAL(eve__cyl_bessel_j0(v_t(0)),  eve::one(eve::as<v_t>()), 0.0);

  TTS_ULP_EQUAL(eve__cyl_bessel_j0( T(1500)), T(std__cyl_bessel_j0(v_t(1500))), 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_j0( T(500)),  T(std__cyl_bessel_j0(v_t(500)) ), 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_j0( T(10)) ,  T(std__cyl_bessel_j0( v_t(10)) ), 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_j0( T(5))  ,  T(std__cyl_bessel_j0( v_t(5))  ), 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_j0( T(2))  ,  T(std__cyl_bessel_j0( v_t(2))  ), 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_j0( T(1.5)),  T(std__cyl_bessel_j0( v_t(1.5))), 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_j0( T(0.5)),  T(std__cyl_bessel_j0( v_t(0.5))), 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_j0( T(1))  ,  T(std__cyl_bessel_j0( v_t(1))  ), 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_j0( T(0))  , eve::one(eve::as< T>()), 0.0);


  TTS_ULP_EQUAL(eve__cyl_bessel_j0(a0), map(std__cyl_bessel_j0, a0), 5.0);
};
