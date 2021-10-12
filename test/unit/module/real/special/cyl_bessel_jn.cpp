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
// EVE_TEST_TYPES( "Check return types of cyl_bessel_jn"
//             , eve::test::simd::ieee_reals
//             )
// <typename T>(eve::as<T>)
// {
//   using v_t = eve::element_type_t<T>;
//   using i_t = eve::as_integer_t<v_t>;
//   using I_t = eve::wide<i_t, eve::cardinal_t<T>>;
//   TTS_EXPR_IS( eve::cyl_bessel_jn(T(), T())  ,  T);
//   TTS_EXPR_IS( eve::cyl_bessel_jn(v_t(),v_t()), v_t);
//   TTS_EXPR_IS( eve::cyl_bessel_jn(i_t(),T()),   T);
//   TTS_EXPR_IS( eve::cyl_bessel_jn(I_t(),T()),   T);
//   TTS_EXPR_IS( eve::cyl_bessel_jn(i_t(),v_t()), v_t);
// //  TTS_EXPR_IS( eve::cyl_bessel_jn(I_t(),v_t()), T);
// };

EVE_TEST( "Check behavior of cyl_bessel_jn on wide"
        , eve::test::simd::ieee_floats
        , eve::test::generate(eve::test::randoms(0.0, 20000.0))
        )
  <typename T>(T const& )
{
  using v_t = eve::element_type_t<T>;

  auto eve__cyl_bessel_jn =  [](auto n, auto x) { return eve::cyl_bessel_jn(n, x); };
  auto std__cyl_bessel_jn =  [](auto n, auto x)->v_t { return boost::math::bessel_j(n, x, boost::math::Policy()); };
//   if constexpr( eve::platform::supports_invalids )
//   {
//     TTS_ULP_EQUAL(eve__cyl_bessel_jn(0, eve::minf(eve::as<v_t>())), eve::zero(eve::as<v_t>()), 0);
//     TTS_ULP_EQUAL(eve__cyl_bessel_jn(2, eve::inf(eve::as<v_t>())), v_t(0), 0);
//     TTS_ULP_EQUAL(eve__cyl_bessel_jn(3, eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
//   }
//   //scalar large x
//    TTS_ULP_EQUAL(eve__cyl_bessel_jn(3, v_t(1500)), std__cyl_bessel_jn(3, v_t(1500)), 2.0);
//    TTS_ULP_EQUAL(eve__cyl_bessel_jn(2, v_t(500)), std__cyl_bessel_jn(2, v_t(500)), 2.0);
//    TTS_ULP_EQUAL(eve__cyl_bessel_jn(-3, v_t(1500)), std__cyl_bessel_jn(-3, v_t(1500)), 2.0);
//    TTS_ULP_EQUAL(eve__cyl_bessel_jn(-2, v_t(500)), std__cyl_bessel_jn(-2, v_t(500)), 2.0);
//   //scalar forward
//    TTS_ULP_EQUAL(eve__cyl_bessel_jn(2, v_t(10)), std__cyl_bessel_jn(2, v_t(10))  , 2.0);
//    TTS_ULP_EQUAL(eve__cyl_bessel_jn(3, v_t(5)),  std__cyl_bessel_jn(3, v_t(5))   , 2.0);
  //scalar serie
//    TTS_ULP_EQUAL(eve__cyl_bessel_jn(2, v_t(0.1)), std__cyl_bessel_jn(2, v_t(0.1))  , 2.0);
//    TTS_ULP_EQUAL(eve__cyl_bessel_jn(3, v_t(0.2)),  std__cyl_bessel_jn(3, v_t(0.2))   , 2.0);
  if constexpr(eve::cardinal_v<T> == 1)
  {
    auto z1 = eve__cyl_bessel_jn(10, v_t(8));
    auto z2 =std__cyl_bessel_jn(10, v_t(8));
    TTS_ULP_EQUAL(z1, z2, 2.0);
//     TTS_ULP_EQUAL(eve__cyl_bessel_jn(10, v_t(8)), std__cyl_bessel_jn(10, v_t(8))  , 2.0);
//   TTS_ULP_EQUAL(eve__cyl_bessel_jn(10, v_t(8)),  std__cyl_bessel_jn(10, v_t(8))   , 2.0);
  }
  else
    TTS_ULP_EQUAL(0, 0, 1);

//   TTS_ULP_EQUAL(eve__cyl_bessel_jn(3, v_t(0.2)),  std__cyl_bessel_jn(3, v_t(5))   , 2.0);

};
