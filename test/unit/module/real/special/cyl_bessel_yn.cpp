//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/cyl_bessel_yn.hpp>
#include <eve/function/prev.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>
#include <boost/math/special_functions/bessel.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of cyl_bessel_yn"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using I_t = eve::wide<i_t, eve::cardinal_t<T>>;
  TTS_EXPR_IS( eve::cyl_bessel_yn(T(), T())  ,  T);
  TTS_EXPR_IS( eve::cyl_bessel_yn(v_t(),v_t()), v_t);
  TTS_EXPR_IS( eve::cyl_bessel_yn(i_t(),T()),   T);
  TTS_EXPR_IS( eve::cyl_bessel_yn(I_t(),T()),   T);
  TTS_EXPR_IS( eve::cyl_bessel_yn(i_t(),v_t()), v_t);
  TTS_EXPR_IS( eve::cyl_bessel_yn(I_t(),v_t()), T);
};

//==================================================================================================
//== integral orders
//==================================================================================================
EVE_TEST( "Check behavior of cyl_bessel_yn on wide with integral order"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::ramp(0), eve::test::randoms(0.0, 20000.0))
        )
  <typename T>(T , T )
{
  using v_t = eve::element_type_t<T>;

  auto eve__cyl_bessel_yn =  [](auto n, auto x) { return eve::cyl_bessel_yn(n, x); };
  auto std__cyl_bessel_yn =  [](auto n, auto x)->v_t { return boost::math::cyl_neumann(n, x); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__cyl_bessel_yn(0, eve::minf(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_yn(2, eve::inf(eve::as<v_t>())), v_t(0), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_yn(3, eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
  }
  //scalar large x
  TTS_ULP_EQUAL(eve__cyl_bessel_yn(3, v_t(1500)), std__cyl_bessel_yn(3, v_t(1500)), 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_yn(2, v_t(500)), std__cyl_bessel_yn(2, v_t(500)), 2.0);
  //scalar forward
  TTS_ULP_EQUAL(eve__cyl_bessel_yn(0, v_t(10)), std__cyl_bessel_yn(0, v_t(10))  , 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_yn(1, v_t(5)),  std__cyl_bessel_yn(1, v_t(5))   , 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_yn(2, v_t(10)), std__cyl_bessel_yn(2, v_t(10))  , 20.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_yn(3, v_t(5)),  std__cyl_bessel_yn(3, v_t(5))   , 20.0);
  //scalar serie
//  TTS_ULP_EQUAL(eve__cyl_bessel_yn(2, v_t(0.1)), std__cyl_bessel_yn(2, v_t(0.1))  , 2.0);
// TTS_ULP_EQUAL(eve__cyl_bessel_yn(3, v_t(0.2)),  std__cyl_bessel_yn(3, v_t(0.2))   , 2.0);
  //scalar besseljy
  TTS_ULP_EQUAL(eve__cyl_bessel_yn(10, v_t(8)), std__cyl_bessel_yn(10, v_t(8))  , 2.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_yn(10, v_t(8)),  std__cyl_bessel_yn(10, v_t(8))   , 2.0);

// //  if constexpr( eve::platform::supports_invalids )
// //   {
// //     TTS_ULP_EQUAL(eve__cyl_bessel_yn(0, eve::minf(eve::as<T>())), eve::zero(eve::as<T>()), 0);
// //     TTS_ULP_EQUAL(eve__cyl_bessel_yn(2, eve::inf(eve::as<T>())), T(0), 0);
// //     TTS_ULP_EQUAL(eve__cyl_bessel_yn(3, eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
// //   }
// //   //scalar large x
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(3, T(1500)),  T(std__cyl_bessel_yn(3, v_t(1500))),  2.0);
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(2, T(500)),   T(std__cyl_bessel_yn(2, v_t(500))),   2.0);
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(-3, T(1500)), T(std__cyl_bessel_yn(-3, v_t(1500))), 2.0);
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(-2, T(500)),  T(std__cyl_bessel_yn(-2, v_t(500))),  2.0);
// //   //scalar forward
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(2, T(10)),    T(std__cyl_bessel_yn(2, v_t(10)))   , 2.0);
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(3, T(5)),     T(std__cyl_bessel_yn(3, v_t(5)))    , 2.0);
// //   //scalar serie
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(2, T(0.1)),   T(std__cyl_bessel_yn(2, v_t(0.1)))  , 2.0);
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(3, T(0.2)),   T(std__cyl_bessel_yn(3, v_t(0.2)))  , 2.0);
// //   //scalar besseljy
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(10, T(8)),   T(std__cyl_bessel_yn(10, v_t(8)))   , 2.0);
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(10, T(8)),   T(std__cyl_bessel_yn(10, v_t(8)))   , 2.0);

// //   if constexpr( eve::platform::supports_invalids )
// //   {
// //     TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(0), eve::minf(eve::as<T>())), eve::zero(eve::as<T>()), 0);
// //     TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(2), eve::inf(eve::as<T>())), T(0), 0);
// //     TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(3), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
// //   }
// //   // large x
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(3), T(1500)),  T(std__cyl_bessel_yn(3, v_t(1500))),  2.0);
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(2), T(500)),   T(std__cyl_bessel_yn(2, v_t(500))),   2.0);
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(-3), T(1500)), T(std__cyl_bessel_yn(-3, v_t(1500))), 2.0);
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(-2), T(500)),  T(std__cyl_bessel_yn(-2, v_t(500))),  2.0);
// //   // forward
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(2), T(10)),    T(std__cyl_bessel_yn(2, v_t(10)))   , 2.0);
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(3), T(5)),     T(std__cyl_bessel_yn(3, v_t(5)))    , 2.0);
// //   // serie
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(2), T(0.1)),   T(std__cyl_bessel_yn(2, v_t(0.1)))  , 2.0);
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(3), T(0.2)),   T(std__cyl_bessel_yn(3, v_t(0.2)))  , 2.0);
// //   // besseljy
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(10), T(8)),   T(std__cyl_bessel_yn(10, v_t(8)))   , 2.0);
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(10), T(8)),   T(std__cyl_bessel_yn(10, v_t(8)))   , 2.0);

// //   using i_t = eve::as_integer_t<v_t>;
// //   using I_t = eve::wide<i_t, eve::cardinal_t<T>>;

// //   if constexpr( eve::platform::supports_invalids )
// //   {
// //     TTS_ULP_EQUAL(eve__cyl_bessel_yn(I_t(0), eve::minf(eve::as<T>())), eve::zero(eve::as<T>()), 0);
// //     TTS_ULP_EQUAL(eve__cyl_bessel_yn(I_t(2), eve::inf(eve::as<T>())), T(0), 0);
// //     TTS_ULP_EQUAL(eve__cyl_bessel_yn(I_t(3), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
// //   }
// //   // large x
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(I_t(3), T(1500)),  T(std__cyl_bessel_yn(3, v_t(1500))),  2.0);
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(I_t(2), T(500)),   T(std__cyl_bessel_yn(2, v_t(500))),   2.0);
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(I_t(-3), T(1500)), T(std__cyl_bessel_yn(-3, v_t(1500))), 2.0);
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(I_t(-2), T(500)),  T(std__cyl_bessel_yn(-2, v_t(500))),  2.0);
// //   // forward
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(I_t(2), T(10)),    T(std__cyl_bessel_yn(2, v_t(10)))   , 2.0);
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(I_t(3), T(5)),     T(std__cyl_bessel_yn(3, v_t(5)))    , 2.0);
// //   // serie
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(I_t(2), T(0.1)),   T(std__cyl_bessel_yn(2, v_t(0.1)))  , 2.0);
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(I_t(3), T(0.2)),   T(std__cyl_bessel_yn(3, v_t(0.2)))  , 2.0);
// //   // besseljy
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(I_t(10), T(8)),   T(std__cyl_bessel_yn(10, v_t(8)))   , 2.0);
// //   TTS_ULP_EQUAL(eve__cyl_bessel_yn(I_t(10), T(8)),   T(std__cyl_bessel_yn(10, v_t(8)))   , 2.0);

// //     TTS_RELATIVE_EQUAL(eve__cyl_bessel_yn(n, a0),   map(std__cyl_bessel_yn, n, a0)   , 0.0015);

 };

//==================================================================================================
//== non integral orders
//==================================================================================================
// EVE_TEST( "Check behavior of cyl_bessel_yn on wide with non integral order"
//         , eve::test::simd::ieee_reals
//         , eve::test::generate(eve::test::randoms(0.0, 10.0)
//         , eve::test::randoms(0.0, 2000.0))
//         )
//   <typename T>(T n, T a0 )
// {
//   using v_t = eve::element_type_t<T>;

//   auto eve__cyl_bessel_yn =  [](auto n, auto x) { return eve::cyl_bessel_yn(n, x); };
//   auto std__cyl_bessel_yn =  [](auto n, auto x)->v_t { return boost::math::cyl_neumann(n, x); };

//   if constexpr( eve::platform::supports_invalids )
//   {
//     TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(0.5), eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
//     TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(2.5), eve::inf(eve::as<T>())), T(0), 0);
//     TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(3.5), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
//   }
//   // large x
//   TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(3.5), T(1500)),  T(std__cyl_bessel_yn(v_t(3.5), v_t(1500))),  2.0);
//   TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(2.5), T(500)),   T(std__cyl_bessel_yn(v_t(2.5), v_t(500))),   2.0);
//   // forward
//   TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(2.5), T(10)),    T(std__cyl_bessel_yn(v_t(2.5), v_t(10)))   , 25.0);
//   TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(3.5), T(5)),     T(std__cyl_bessel_yn(v_t(3.5), v_t(5)))    , 25.0);
//   // serie
//   TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(2.5), T(0.1)),   T(std__cyl_bessel_yn(v_t(2.5), v_t(0.1)))  , 2.0);
//   TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(3.5), T(0.2)),   T(std__cyl_bessel_yn(v_t(3.5), v_t(0.2)))  , 2.5);
//   // besseljy
//   TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(10.5), T(8)),   T(std__cyl_bessel_yn(v_t(10.5), v_t(8)))   , 2.0);
//   TTS_ULP_EQUAL(eve__cyl_bessel_yn(T(10.5), T(8)),   T(std__cyl_bessel_yn(v_t(10.5), v_t(8)))   , 2.0);

//  TTS_RELATIVE_EQUAL(eve__cyl_bessel_yn(n, a0),   map(std__cyl_bessel_yn, n, a0)   , 0.001);
// };
