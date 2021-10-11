//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cyl_bessel_jn.hpp>
#include <eve/function/prev.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>
#include <boost/math/special_functions/bessel.hpp>

// //==================================================================================================
// // Types tests
// //==================================================================================================
EVE_TEST_TYPES( "Check return types of cyl_bessel_jn"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using I_t = eve::wide<i_t, eve::cardinal_t<T>>;
  TTS_EXPR_IS( eve::cyl_bessel_jn(T(), T())  ,  T);
  TTS_EXPR_IS( eve::cyl_bessel_jn(v_t(),v_t()), v_t);
  TTS_EXPR_IS( eve::cyl_bessel_jn(i_t(),T()),   T);
  TTS_EXPR_IS( eve::cyl_bessel_jn(I_t(),T()),   T);
  TTS_EXPR_IS( eve::cyl_bessel_jn(i_t(),v_t()), v_t);
//  TTS_EXPR_IS( eve::cyl_bessel_jn(I_t(),v_t()), T);
};

EVE_TEST( "Check behavior of cyl_bessel_jn on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(0.0, 20000.0))
        )
  <typename T>(T const& )
{
  using v_t = eve::element_type_t<T>;

  auto eve__cyl_bessel_jn =  [](auto n, auto x) { return eve::cyl_bessel_jn(n, x); };
  auto std__cyl_bessel_jn =  [](auto n, auto x)->v_t { return boost::math::cyl_bessel_j(n, x); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__cyl_bessel_jn(0, eve::minf(eve::as<v_t>())), eve::zero(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_jn(2, eve::inf(eve::as<v_t>())), v_t(0), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_jn(3, eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
//     TTS_ULP_EQUAL(eve__cyl_bessel_jn(eve::minf(eve::as< T>())), eve::zero(eve::as< T>()), 0);
//     TTS_ULP_EQUAL(eve__cyl_bessel_jn(eve::inf(eve::as< T>())),  T(0), 0);
//     TTS_ULP_EQUAL(eve__cyl_bessel_jn(eve::nan(eve::as< T>())), eve::nan(eve::as< T>()), 0);
  }
   TTS_ULP_EQUAL(eve__cyl_bessel_jn(3, v_t(1500)), std__cyl_bessel_jn(3, v_t(1500)), 2.0);
   TTS_ULP_EQUAL(eve__cyl_bessel_jn(2, v_t(500)), std__cyl_bessel_jn(2, v_t(500)), 2.0);
   TTS_ULP_EQUAL(eve__cyl_bessel_jn(-3, v_t(1500)), std__cyl_bessel_jn(3, v_t(1500)), 2.0);
   TTS_ULP_EQUAL(eve__cyl_bessel_jn(-2, v_t(500)), std__cyl_bessel_jn(2, v_t(500)), 2.0);
//   TTS_ULP_EQUAL(eve__cyl_bessel_jn(v_t(10)), std__cyl_bessel_jn(v_t(10))  , 2.0);
//   TTS_ULP_EQUAL(eve__cyl_bessel_jn(v_t(5)),  std__cyl_bessel_jn(v_t(5))   , 2.0);
//   TTS_ULP_EQUAL(eve__cyl_bessel_jn(v_t(2)),  std__cyl_bessel_jn(v_t(2))   , 2.0);
//   TTS_ULP_EQUAL(eve__cyl_bessel_jn(v_t(1.5)),std__cyl_bessel_jn(v_t(1.5)) , 2.0);
//   TTS_ULP_EQUAL(eve__cyl_bessel_jn(v_t(0.5)),std__cyl_bessel_jn(v_t(0.5)) , 2.0);
//   TTS_ULP_EQUAL(eve__cyl_bessel_jn(v_t(1)),  std__cyl_bessel_jn(v_t(1))   , 2.5);
//   TTS_ULP_EQUAL(eve__cyl_bessel_jn(v_t(0)),  eve::one(eve::as<v_t>()), 0.0);

//   TTS_ULP_EQUAL(eve__cyl_bessel_jn( T(1500)), T(std__cyl_bessel_jn(v_t(1500))), 2.0);
//   TTS_ULP_EQUAL(eve__cyl_bessel_jn( T(500)),  T(std__cyl_bessel_jn(v_t(500)) ), 2.0);
//   TTS_ULP_EQUAL(eve__cyl_bessel_jn( T(10)) ,  T(std__cyl_bessel_jn( v_t(10)) ), 2.0);
//   TTS_ULP_EQUAL(eve__cyl_bessel_jn( T(5))  ,  T(std__cyl_bessel_jn( v_t(5))  ), 2.0);
//   TTS_ULP_EQUAL(eve__cyl_bessel_jn( T(2))  ,  T(std__cyl_bessel_jn( v_t(2))  ), 2.0);
//   TTS_ULP_EQUAL(eve__cyl_bessel_jn( T(1.5)),  T(std__cyl_bessel_jn( v_t(1.5))), 2.0);
//   TTS_ULP_EQUAL(eve__cyl_bessel_jn( T(0.5)),  T(std__cyl_bessel_jn( v_t(0.5))), 2.0);
//   TTS_ULP_EQUAL(eve__cyl_bessel_jn( T(1))  ,  T(std__cyl_bessel_jn( v_t(1))  ), 2.0);
//   TTS_ULP_EQUAL(eve__cyl_bessel_jn( T(0))  , eve::one(eve::as< T>()), 0.0);


//   TTS_ULP_EQUAL(eve__cyl_bessel_jn(a0), map(std__cyl_bessel_jn, a0), 5.0);
};
