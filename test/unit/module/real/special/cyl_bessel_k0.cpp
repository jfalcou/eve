//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/cyl_bessel_k0.hpp>
#include <eve/function/diff/cyl_bessel_k0.hpp>
#include <eve/function/prev.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>
#include <boost/math/special_functions/bessel.hpp>
#include <boost/math/special_functions/bessel_prime.hpp>

EVE_TEST_TYPES( "Check return types of cyl_bessel_k0"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::cyl_bessel_k0(T(0)), T);
  TTS_EXPR_IS(eve::cyl_bessel_k0(v_t(0)), v_t);
};

 EVE_TEST( "Check behavior of cyl_bessel_k0 on wide"
        , eve::test::simd::ieee_reals
         , eve::test::generate( eve::test::randoms(0.0, 0.5)
                              , eve::test::randoms(0.5, 1.5)
                              , eve::test::randoms(1.5, 500.0))
         )
   <typename T>(T const& a0, T const& a1, T const& a2)
{
  using v_t = eve::element_type_t<T>;

  auto eve__cyl_bessel_k0 =  [](auto x) { return eve::cyl_bessel_k0(x); };
  auto std__cyl_bessel_k0 =  [](auto x)->v_t { return std::cyl_bessel_k(v_t(0), x); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__cyl_bessel_k0(eve::inf(eve::as<v_t>())), eve::zero(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_k0(eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_k0(eve::zero(eve::as<v_t>())), eve::inf(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_k0(eve::inf(eve::as<T>())),  eve::zero(eve::as< T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_k0(eve::nan(eve::as< T>())), eve::nan(eve::as< T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_k0(eve::zero(eve::as<T>())),  eve::inf(eve::as< T>()), 0);
  }
  TTS_IEEE_EQUAL(eve__cyl_bessel_k0(v_t(-1)), eve::nan(eve::as<v_t>()));
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(v_t(500)), std__cyl_bessel_k0(v_t(500)), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(v_t(10)), std__cyl_bessel_k0(v_t(10))  , 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(v_t(5)),  std__cyl_bessel_k0(v_t(5))   , 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(v_t(2)),  std__cyl_bessel_k0(v_t(2))   , 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(v_t(1.5)),std__cyl_bessel_k0(v_t(1.5)) , 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(v_t(0.5)),std__cyl_bessel_k0(v_t(0.5)) , 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(v_t(0.05)),std__cyl_bessel_k0(v_t(0.05)) , 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(v_t(1)),  std__cyl_bessel_k0(v_t(1))   , 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(v_t(0)),  eve::inf(eve::as<v_t>()), 0.0);

  TTS_IEEE_EQUAL(eve__cyl_bessel_k0(T(-1)), eve::nan(eve::as<T>()));
  TTS_ULP_EQUAL(eve__cyl_bessel_k0( T(500)),  T(std__cyl_bessel_k0(v_t(500)) ), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0( T(10)) ,  T(std__cyl_bessel_k0( v_t(10)) ), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0( T(5))  ,  T(std__cyl_bessel_k0( v_t(5))  ), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0( T(2))  ,  T(std__cyl_bessel_k0( v_t(2))  ), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0( T(1.5)),  T(std__cyl_bessel_k0( v_t(1.5))), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0( T(0.5)),  T(std__cyl_bessel_k0( v_t(0.5))), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0( T(1))  ,  T(std__cyl_bessel_k0( v_t(1))  ), 6.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0( T(0))  , eve::inf(eve::as<T>()), 0.0);


  TTS_ULP_EQUAL(eve__cyl_bessel_k0(a0), map(std__cyl_bessel_k0, a0), 10.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_k0(a1), map(std__cyl_bessel_k0, a1), 10.0);
  TTS_RELATIVE_EQUAL(eve__cyl_bessel_k0(a2), map(std__cyl_bessel_k0, a2), 0.001);
};

EVE_TEST( "Check behavior of cyl_bessel_k0 on wide with negative non integral order"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(0.0, 60.0))
        )
  <typename T>(T a0 )
{
  using v_t = eve::element_type_t<T>;
  auto eve__diff_bessel_k0 =  [](auto x) { return eve::diff(eve::cyl_bessel_k0)(x); };
  auto std__diff_bessel_k0 =  [](auto x)->v_t { return boost::math::cyl_bessel_k_prime(0, x); };
  TTS_RELATIVE_EQUAL(eve__diff_bessel_k0(a0),   map(std__diff_bessel_k0, a0)   , 1.0e-3);

};
