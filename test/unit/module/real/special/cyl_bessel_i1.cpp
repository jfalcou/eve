//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/cyl_bessel_i1.hpp>
#include <eve/function/prev.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>
#include <boost/math/special_functions/bessel.hpp>

EVE_TEST_TYPES( "Check return types of cyl_bessel_i1"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::cyl_bessel_i1(T(0)), T);
  TTS_EXPR_IS(eve::cyl_bessel_i1(v_t(0)), v_t);
};

 EVE_TEST( "Check behavior of cyl_bessel_i1 on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(0.0, 5.5),
                              eve::test::randoms(5.5, 9.5),
                              eve::test::randoms(9.5, 500.0),
                              eve::test::randoms(500.0, 1000.0)
                             )
         )
   <typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using v_t = eve::element_type_t<T>;

  auto eve__cyl_bessel_i1 =  [](auto x) { return eve::cyl_bessel_i1(x); };
  auto std__cyl_bessel_i1 =  [](auto x)->v_t { return std::cyl_bessel_i(v_t(1), x); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__cyl_bessel_i1(eve::inf(eve::as<v_t>())), eve::inf(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_i1(eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_i1(eve::inf(eve::as< T>())),  eve::inf(eve::as< T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_i1(eve::nan(eve::as< T>())), eve::nan(eve::as< T>()), 0);
  }
  TTS_IEEE_EQUAL(eve__cyl_bessel_i1(v_t(-1)), eve::nan(eve::as<v_t>()));
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(v_t(500)), std__cyl_bessel_i1(v_t(500)), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(v_t(10)), std__cyl_bessel_i1(v_t(10))  , 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(v_t(5)),  std__cyl_bessel_i1(v_t(5))   , 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(v_t(2)),  std__cyl_bessel_i1(v_t(2))   , 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(v_t(1.5)),std__cyl_bessel_i1(v_t(1.5)) , 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(v_t(0.5)),std__cyl_bessel_i1(v_t(0.5)) , 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(v_t(1)),  std__cyl_bessel_i1(v_t(1))   , 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(v_t(0)),  eve::zero(eve::as<v_t>()), 0.0);

  TTS_IEEE_EQUAL(eve__cyl_bessel_i1(T(-1)), eve::nan(eve::as<T>()));
  TTS_ULP_EQUAL(eve__cyl_bessel_i1( T(500)),  T(std__cyl_bessel_i1(v_t(500)) ), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1( T(10)) ,  T(std__cyl_bessel_i1( v_t(10)) ), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1( T(5))  ,  T(std__cyl_bessel_i1( v_t(5))  ), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1( T(2))  ,  T(std__cyl_bessel_i1( v_t(2))  ), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1( T(1.5)),  T(std__cyl_bessel_i1( v_t(1.5))), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1( T(0.5)),  T(std__cyl_bessel_i1( v_t(0.5))), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1( T(1))  ,  T(std__cyl_bessel_i1( v_t(1))  ), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1( T(0))  , eve::zero(eve::as< T>()), 0.0);


  TTS_ULP_EQUAL(eve__cyl_bessel_i1(a0), map(std__cyl_bessel_i1, a0), 10.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(a1), map(std__cyl_bessel_i1, a1), 10.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(a2), map(std__cyl_bessel_i1, a2), 10.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_i1(a3), map(std__cyl_bessel_i1, a3), 10.0);
};
