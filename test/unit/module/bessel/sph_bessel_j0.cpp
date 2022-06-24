//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/bessel.hpp>
#include <boost/math/special_functions/bessel.hpp>
#include <boost/math/special_functions/bessel_prime.hpp>


EVE_TEST_TYPES( "Check return types of sph_bessel_j0"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::sph_bessel_j0(T(0)), T);
  TTS_EXPR_IS(eve::sph_bessel_j0(v_t(0)), v_t);
};

 EVE_TEST( "Check behavior of sph_bessel_j0 on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(0.0, 5.5),
                              eve::test::randoms(5.5, 9.5),
                              eve::test::randoms(9.5, 60.0))
         )
   <typename T>(T const& a0, T const& a1, T const& a2)
{
  using v_t = eve::element_type_t<T>;
  auto eve__sph_bessel_j0 =  [](auto x) { return eve::sph_bessel_j0(x); };
  auto std__sph_bessel_j0 =  [](auto x)->v_t { return boost::math::sph_bessel(0u, double(x)); };

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__sph_bessel_j0(eve::inf(eve::as<v_t>())), eve::zero(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__sph_bessel_j0(eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__sph_bessel_j0(eve::inf(eve::as< T>())),  eve::zero(eve::as< T>()), 0);
    TTS_ULP_EQUAL(eve__sph_bessel_j0(eve::nan(eve::as< T>())), eve::nan(eve::as< T>()), 0);
  }
  TTS_ULP_EQUAL(eve__sph_bessel_j0(v_t(500)), std__sph_bessel_j0(v_t(500)), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j0(v_t(10)), std__sph_bessel_j0(v_t(10))  , 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j0(v_t(5)),  std__sph_bessel_j0(v_t(5))   , 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j0(v_t(2)),  std__sph_bessel_j0(v_t(2))   , 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j0(v_t(1.5)),std__sph_bessel_j0(v_t(1.5)) , 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j0(v_t(0.5)),std__sph_bessel_j0(v_t(0.5)) , 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j0(v_t(1)),  std__sph_bessel_j0(v_t(1))   , 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j0(v_t(0)),  eve::one(eve::as<v_t>()), 0.0);

  TTS_ULP_EQUAL(eve__sph_bessel_j0( T(500)),  T(std__sph_bessel_j0(v_t(500)) ), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j0( T(10)) ,  T(std__sph_bessel_j0( v_t(10)) ), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j0( T(5))  ,  T(std__sph_bessel_j0( v_t(5))  ), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j0( T(2))  ,  T(std__sph_bessel_j0( v_t(2))  ), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j0( T(1.5)),  T(std__sph_bessel_j0( v_t(1.5))), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j0( T(0.5)),  T(std__sph_bessel_j0( v_t(0.5))), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j0( T(1))  ,  T(std__sph_bessel_j0( v_t(1))  ), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j0( T(0))  , eve::one(eve::as< T>()), 0.0);


  TTS_ULP_EQUAL(eve__sph_bessel_j0(a0), map(std__sph_bessel_j0, a0), 10.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j0(a1), map(std__sph_bessel_j0, a1), 10.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j0(a2), map(std__sph_bessel_j0, a2), 10.0);

};
