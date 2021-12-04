//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/cyl_bessel_in.hpp>
#include <eve/function/diff/cyl_bessel_in.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>
#include <boost/math/special_functions/bessel.hpp>
#include <boost/math/special_functions/bessel_prime.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of cyl_bessel_in"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
 using i_t = eve::as_integer_t<v_t>;
 using I_t = eve::wide<i_t, eve::cardinal_t<T>>;
  TTS_EXPR_IS( eve::cyl_bessel_in(T(), T())  ,  T);
  TTS_EXPR_IS( eve::cyl_bessel_in(v_t(),v_t()), v_t);
  TTS_EXPR_IS( eve::cyl_bessel_in(i_t(),T()),   T);
  TTS_EXPR_IS( eve::cyl_bessel_in(I_t(),T()),   T);
  TTS_EXPR_IS( eve::cyl_bessel_in(i_t(),v_t()), v_t);
  TTS_EXPR_IS( eve::cyl_bessel_in(I_t(),v_t()), T);
};

//==================================================================================================
//== integral orders
//==================================================================================================
EVE_TEST( "Check behavior of cyl_bessel_in on wide with integral order"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::ramp(0),
                              eve::test::randoms(0.0, 10.0))
        )
  <typename T>(T n , T a0)
{
  using v_t = eve::element_type_t<T>;
  auto eve__cyl_bessel_in =  [](auto n, auto x) { return eve::cyl_bessel_in(n, x); };
#if defined(__cpp_lib_math_special_functions)
  auto std__cyl_bessel_in =  [](auto n, auto x)->v_t { return std::cyl_bessel_i(n, x); };
#else
  auto std__cyl_bessel_in =  [](auto n, auto x)->v_t { return boost::math::cyl_bessel_i(double(n), double(x)); };
#endif
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__cyl_bessel_in(0, eve::minf(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_in(2, eve::inf(eve::as<v_t>())), eve::inf(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_in(3, eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
  }
  //scalar large x
  TTS_ULP_EQUAL(eve__cyl_bessel_in(3, v_t(1500)), std__cyl_bessel_in(3, v_t(1500)), 5.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(2, v_t(500)), std__cyl_bessel_in(2, v_t(500)), 5.0);
  //scalar forward
  TTS_ULP_EQUAL(eve__cyl_bessel_in(0, v_t(10)), std__cyl_bessel_in(0, v_t(10))  , 5.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(1, v_t(5)),  std__cyl_bessel_in(1, v_t(5))   , 5.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(2, v_t(10)), std__cyl_bessel_in(2, v_t(10))  , 35.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(3, v_t(5)),  std__cyl_bessel_in(3, v_t(5))   , 35.0);
  //scalar small
  TTS_ULP_EQUAL(eve__cyl_bessel_in(0, v_t(0.1)), std__cyl_bessel_in(0, v_t(0.1))  , 5.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(1, v_t(0.2)),  std__cyl_bessel_in(1, v_t(0.2))   , 5.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(2, v_t(0.1)), std__cyl_bessel_in(2, v_t(0.1))  , 5.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(3, v_t(0.2)),  std__cyl_bessel_in(3, v_t(0.2))   , 5.0);
  //scalar medium
  TTS_ULP_EQUAL(eve__cyl_bessel_in(10, v_t(8)), std__cyl_bessel_in(10, v_t(8))  , 5.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(20, v_t(8)), std__cyl_bessel_in(20, v_t(8))   , 5.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(2 , v_t(1.9010021686554)), std__cyl_bessel_in(2, v_t(1.9010021686554))   , 15.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(2,  v_t(244.708321520116)), std__cyl_bessel_in(2, v_t(244.708321520116)) , 15.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(3,  v_t(517.048069608611)), std__cyl_bessel_in(3,  v_t(517.048069608611)), 15.0);

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__cyl_bessel_in(0, eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_in(2, eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_in(3, eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }
  //simd large x
  TTS_ULP_EQUAL(eve__cyl_bessel_in(3, T(1500)),  T(std__cyl_bessel_in(3, v_t(1500))),  5.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(2, T(500)),   T(std__cyl_bessel_in(2, v_t(500))),   5.0);
  //simd forward
  TTS_ULP_EQUAL(eve__cyl_bessel_in(2, T(10)),    T(std__cyl_bessel_in(2, v_t(10)))   , 35.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(3, T(5)),     T(std__cyl_bessel_in(3, v_t(5)))    , 35.0);
  //simd small
  TTS_ULP_EQUAL(eve__cyl_bessel_in(0, T(0.1)),   T(std__cyl_bessel_in(0, v_t(0.1)))  , 5.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(1, T(0.2)),   T(std__cyl_bessel_in(1, v_t(0.2)))  , 5.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(2, T(0.1)),   T(std__cyl_bessel_in(2, v_t(0.1)))  , 5.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(3, T(0.2)),   T(std__cyl_bessel_in(3, v_t(0.2)))  , 5.0);
  //simd medium
  TTS_ULP_EQUAL(eve__cyl_bessel_in(10, T(8)),   T(std__cyl_bessel_in(10, v_t(8)))   , 7.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(20, T(8)),   T(std__cyl_bessel_in(20, v_t(8)))   , 5.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(2 , T(1.9010021686554)), T(std__cyl_bessel_in(2, v_t(1.9010021686554)))   , 15.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(2,  T(244.708321520116)),T(std__cyl_bessel_in(2, v_t(244.708321520116))) , 15.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(3,  T(517.048069608611)),T(std__cyl_bessel_in(3,  v_t(517.048069608611))), 15.0);



  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__cyl_bessel_in(T(0), eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_in(T(2), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_in(T(3), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }
  // large x
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(3), T(1500)),  T(std__cyl_bessel_in(3, v_t(1500))),  5.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(2), T(500)),   T(std__cyl_bessel_in(2, v_t(500))),   5.0);
  // forward
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(2), T(10)),    T(std__cyl_bessel_in(2, v_t(10)))   , 35.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(3), T(5)),     T(std__cyl_bessel_in(3, v_t(5)))    , 35.0);
  // serie
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(2), T(0.1)),   T(std__cyl_bessel_in(2, v_t(0.1)))  , 5.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(3), T(0.2)),   T(std__cyl_bessel_in(3, v_t(0.2)))  , 5.0);
  // besseljy
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(10), T(8)),   T(std__cyl_bessel_in(10, v_t(8)))   , 7.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(20), T(8)),   T(std__cyl_bessel_in(20, v_t(8)))   , 5.0);

  using i_t = eve::as_integer_t<v_t>;
  using I_t = eve::wide<i_t, eve::cardinal_t<T>>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__cyl_bessel_in(I_t(0), eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_in(I_t(2), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_in(I_t(3), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }
  // large x
  TTS_ULP_EQUAL(eve__cyl_bessel_in(I_t(3), T(1500)),  T(std__cyl_bessel_in(3, v_t(1500))),  5.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(I_t(2), T(500)),   T(std__cyl_bessel_in(2, v_t(500))),   5.0);
  // forward
  TTS_ULP_EQUAL(eve__cyl_bessel_in(I_t(2), T(10)),    T(std__cyl_bessel_in(2, v_t(10)))   , 35.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(I_t(3), T(5)),     T(std__cyl_bessel_in(3, v_t(5)))    , 35.0);
  // serie
  TTS_ULP_EQUAL(eve__cyl_bessel_in(I_t(2), T(0.1)),   T(std__cyl_bessel_in(2, v_t(0.1)))  , 5.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(I_t(3), T(0.2)),   T(std__cyl_bessel_in(3, v_t(0.2)))  , 5.0);
  // besseljy
  TTS_ULP_EQUAL(eve__cyl_bessel_in(I_t(10), T(8)),   T(std__cyl_bessel_in(10, v_t(8)))   , 7.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(I_t(20), T(8)),   T(std__cyl_bessel_in(20, v_t(8)))   , 5.0);

  TTS_ULP_EQUAL(map(eve__cyl_bessel_in, n, a0),   map(std__cyl_bessel_in, n, a0)   , 60.0);
};

//==================================================================================================
//== non integral orders
//==================================================================================================
EVE_TEST( "Check behavior of cyl_bessel_in on wide with non integral order"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(0.0, 10.0)
                             , eve::test::randoms(0.0, 10.0))
        )
  <typename T>(T n, T a0 )
{
  using v_t = eve::element_type_t<T>;

  auto eve__cyl_bessel_in =  [](auto n, auto x) { return eve::cyl_bessel_in(n, x); };
#if defined(__cpp_lib_math_special_functions)
  auto std__cyl_bessel_in =  [](auto n, auto x)->v_t { return std::cyl_bessel_i(n, x); };
#else
  auto std__cyl_bessel_in =  [](auto n, auto x)->v_t { return boost::math::cyl_bessel_i(double(n), double(x)); };
#endif

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__cyl_bessel_in(T(0.5), eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_in(T(2.5), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_in(T(3.5), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }
  // large x
  TTS_ULP_EQUAL(eve__cyl_bessel_in(v_t(3.5), v_t(1500)),  std__cyl_bessel_in(v_t(3.5), v_t(1500)),  10.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(v_t(2.5), v_t(500)),   std__cyl_bessel_in(v_t(2.5), v_t(500)),   10.0);
  // forward
  TTS_ULP_EQUAL(eve__cyl_bessel_in(v_t(2.5), v_t(10)),    std__cyl_bessel_in(v_t(2.5), v_t(10))   , 10.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(v_t(3.5), v_t(5)),     std__cyl_bessel_in(v_t(3.5), v_t(5))    , 10.0);
  // serie
  TTS_ULP_EQUAL(eve__cyl_bessel_in(v_t(2.5), v_t(0.1)),   std__cyl_bessel_in(v_t(2.5), v_t(0.1))  , 10.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(v_t(3.5), v_t(0.2)),   std__cyl_bessel_in(v_t(3.5), v_t(0.2))  , 10.0);
  // besseljy
  TTS_ULP_EQUAL(eve__cyl_bessel_in(v_t(10.5), v_t(8)),    std__cyl_bessel_in(v_t(10.5), v_t(8))   , 10.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(v_t(10.5), v_t(8)),    std__cyl_bessel_in(v_t(10.5), v_t(8))   , 10.0);

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__cyl_bessel_in(T(0.5), eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_in(T(2.5), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_in(T(3.5), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }
  // large x
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(3.5), T(700)),  T(std__cyl_bessel_in(v_t(3.5), v_t(700))),  10.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(2.5), T(500)),   T(std__cyl_bessel_in(v_t(2.5), v_t(500))),   10.0);
  // forward
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(2.5), T(10)),    T(std__cyl_bessel_in(v_t(2.5), v_t(10)))   , 310.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(3.5), T(5)),     T(std__cyl_bessel_in(v_t(3.5), v_t(5)))    , 310.0);
  // serie
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(2.5), T(0.1)),   T(std__cyl_bessel_in(v_t(2.5), v_t(0.1)))  , 10.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(3.5), T(0.2)),   T(std__cyl_bessel_in(v_t(3.5), v_t(0.2)))  , 10.0);
  // besseljy
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(10.5), T(8)),   T(std__cyl_bessel_in(v_t(10.5), v_t(8)))   , 10.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(10.5), T(8)),   T(std__cyl_bessel_in(v_t(10.5), v_t(8)))   , 10.0);

  TTS_RELATIVE_EQUAL(eve__cyl_bessel_in(n, a0),   map(std__cyl_bessel_in, n, a0)   , 1.0e-3);
};


EVE_TEST( "Check behavior of cyl_bessel_in on wide with negative non integral order"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(0.0, 10.0)
                             , eve::test::randoms(0.0, 60.0))
        )
  <typename T>(T n, T a0 )
{
  using v_t = eve::element_type_t<T>;

  auto eve__cyl_bessel_in =  [](auto n, auto x) { return eve::cyl_bessel_in(n, x); };
  auto std__cyl_bessel_in =  [](auto n, auto x)->v_t { return boost::math::cyl_bessel_i(double(n), double(x)); };

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__cyl_bessel_in(T(-0.5), eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_in(T(-2.5), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_in(T(-3.5), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }
  // large x
  TTS_ULP_EQUAL(eve__cyl_bessel_in(v_t(-3.5), v_t(1500)),  eve::inf(eve::as<v_t>()),  10.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(v_t(-2.5), v_t(60)),   std__cyl_bessel_in(v_t(-2.5), v_t(60)),   10.0);
  // forward
  TTS_ULP_EQUAL(eve__cyl_bessel_in(v_t(-2.5), v_t(10)),    std__cyl_bessel_in(v_t(-2.5), v_t(10))   , 10.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(v_t(-3.5), v_t(5)),     std__cyl_bessel_in(v_t(-3.5), v_t(5))    , 10.0);
  // serie
  TTS_ULP_EQUAL(eve__cyl_bessel_in(v_t(-2.5), v_t(0.1)),   std__cyl_bessel_in(v_t(-2.5), v_t(0.1))  , 10.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(v_t(-3.5), v_t(0.2)),   std__cyl_bessel_in(v_t(-3.5), v_t(0.2))  , 10.0);
  // besseljy
  TTS_ULP_EQUAL(eve__cyl_bessel_in(v_t(-10.5), v_t(8)),    std__cyl_bessel_in(v_t(-10.5), v_t(8))   , 10.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(v_t(-10.5), v_t(8)),    std__cyl_bessel_in(v_t(-10.5), v_t(8))   , 10.0);

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__cyl_bessel_in(T(-0.5), eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_in(T(-2.5), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_in(T(-3.5), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }
  // large x
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(-3.5), T(1500)),  eve::inf(eve::as<T>()),  10.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(-2.5), T(60)),   T(std__cyl_bessel_in(v_t(-2.5), v_t(60))),   10.0);
  // forward
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(-2.5), T(10)),    T(std__cyl_bessel_in(v_t(-2.5), v_t(10)))   , 310.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(-3.5), T(5)),     T(std__cyl_bessel_in(v_t(-3.5), v_t(5)))    , 310.0);
  // serie
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(-2.5), T(0.1)),   T(std__cyl_bessel_in(v_t(-2.5), v_t(0.1)))  , 10.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(-3.5), T(0.2)),   T(std__cyl_bessel_in(v_t(-3.5), v_t(0.2)))  , 10.0);
  // besseljy
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(-10.5), T(8)),   T(std__cyl_bessel_in(v_t(-10.5), v_t(8)))   , 10.0);
  TTS_ULP_EQUAL(eve__cyl_bessel_in(T(-10.5), T(8)),   T(std__cyl_bessel_in(v_t(-10.5), v_t(8)))   , 10.0);

  TTS_RELATIVE_EQUAL(eve__cyl_bessel_in(-n, a0),   map(std__cyl_bessel_in, -n, a0)   , 1.0e-3);
};

EVE_TEST( "Check behavior of diff of cyl_bessel_in on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(0.0, 10.0)
                             , eve::test::randoms(0.0, 10.0))
        )
  <typename T>(T n, T a0 )
{
  using v_t = eve::element_type_t<T>;
  auto eve__diff_bessel_in =  [](auto n, auto x) { return eve::diff(eve::cyl_bessel_in)(n, x); };
  auto std__diff_bessel_in =  [](auto n, auto x)->v_t { return boost::math::cyl_bessel_i_prime(double(n), double(x)); };
  TTS_RELATIVE_EQUAL(eve__diff_bessel_in(n, a0),   map(std__diff_bessel_in, n, a0)   , 1.0e-3);

};
