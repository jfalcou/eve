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

EVE_TEST_TYPES( "Check return types of sph_bessel_j1"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::sph_bessel_j1(T(0)), T);
  TTS_EXPR_IS(eve::sph_bessel_j1(v_t(0)), v_t);
};

 EVE_TEST( "Check behavior of sph_bessel_j1 on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(0.0, 5.5),
                              eve::test::randoms(5.5, 9.5),
                              eve::test::randoms(9.5, 60.0))
         )
   <typename T>(T const& a0, T const& a1, T const& a2)
{
  using v_t = eve::element_type_t<T>;
  auto eve__sph_bessel_j1 =  [](auto x) { return eve::sph_bessel_j1(x); };
#if defined(__cpp_lib_math_special_functions)
  auto std__sph_bessel_j1 =  [](auto x)->v_t { return std::sph_bessel(v_t(1), x); };
#else
  auto std__sph_bessel_j1 =  [](auto x)->v_t { return boost::math::sph_bessel(double(1), double(x)); };
#endif

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__sph_bessel_j1(eve::inf(eve::as<v_t>())), eve::inf(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__sph_bessel_j1(eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__sph_bessel_j1(eve::inf(eve::as< T>())),  eve::inf(eve::as< T>()), 0);
    TTS_ULP_EQUAL(eve__sph_bessel_j1(eve::nan(eve::as< T>())), eve::nan(eve::as< T>()), 0);
  }
  TTS_IEEE_EQUAL(eve__sph_bessel_j1(v_t(-1)), eve::nan(eve::as<v_t>()));
  TTS_ULP_EQUAL(eve__sph_bessel_j1(v_t(500)), std__sph_bessel_j1(v_t(500)), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j1(v_t(10)), std__sph_bessel_j1(v_t(10))  , 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j1(v_t(5)),  std__sph_bessel_j1(v_t(5))   , 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j1(v_t(2)),  std__sph_bessel_j1(v_t(2))   , 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j1(v_t(1.5)),std__sph_bessel_j1(v_t(1.5)) , 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j1(v_t(0.5)),std__sph_bessel_j1(v_t(0.5)) , 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j1(v_t(1)),  std__sph_bessel_j1(v_t(1))   , 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j1(v_t(0)),  eve::zero(eve::as<v_t>()), 0.0);

  TTS_IEEE_EQUAL(eve__sph_bessel_j1(T(-1)), eve::nan(eve::as<T>()));
  TTS_ULP_EQUAL(eve__sph_bessel_j1( T(500)),  T(std__sph_bessel_j1(v_t(500)) ), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j1( T(10)) ,  T(std__sph_bessel_j1( v_t(10)) ), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j1( T(5))  ,  T(std__sph_bessel_j1( v_t(5))  ), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j1( T(2))  ,  T(std__sph_bessel_j1( v_t(2))  ), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j1( T(1.5)),  T(std__sph_bessel_j1( v_t(1.5))), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j1( T(0.5)),  T(std__sph_bessel_j1( v_t(0.5))), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j1( T(1))  ,  T(std__sph_bessel_j1( v_t(1))  ), 6.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j1( T(0))  , eve::zero(eve::as< T>()), 0.0);


  TTS_ULP_EQUAL(eve__sph_bessel_j1(a0), map(std__sph_bessel_j1, a0), 10.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j1(a1), map(std__sph_bessel_j1, a1), 10.0);
  TTS_ULP_EQUAL(eve__sph_bessel_j1(a2), map(std__sph_bessel_j1, a2), 10.0);

};


// EVE_TEST( "Check behavior of sph_bessel_j1 on wide with negative non integral order"
//         , eve::test::simd::ieee_reals
//         , eve::test::generate(eve::test::randoms(0.0, 60.0))
//         )
//   <typename T>(T a0 )
// {
//   using v_t = eve::element_type_t<T>;
//   auto eve__diff_bessel_j1 =  [](auto x) { return eve::diff(eve::sph_bessel_j1)(x); };
//   auto std__diff_bessel_j1 =  [](auto x)->v_t { return boost::math::sph_bessel_i_prime(double(0), double(x)); };
//   TTS_RELATIVE_EQUAL(eve__diff_bessel_j1(a0),   map(std__diff_bessel_j1, a0)   , 1.0e-3);

// };
