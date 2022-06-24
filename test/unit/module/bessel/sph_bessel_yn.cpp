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


//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of sph_bessel_yn"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using I_t = eve::wide<i_t, eve::cardinal_t<T>>;
  TTS_EXPR_IS( eve::sph_bessel_yn(T(), T())  ,  T);
  TTS_EXPR_IS( eve::sph_bessel_yn(v_t(),v_t()), v_t);
  TTS_EXPR_IS( eve::sph_bessel_yn(i_t(),T()),   T);
  TTS_EXPR_IS( eve::sph_bessel_yn(I_t(),T()),   T);
  TTS_EXPR_IS( eve::sph_bessel_yn(i_t(),v_t()), v_t);
//  TTS_EXPR_IS( eve::sph_bessel_yn(I_t(),v_t()), T);
 };

//==================================================================================================
//== integral orders
//==================================================================================================
EVE_TEST( "Check behavior of sph_bessel_yn on wide with integral order"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::ramp(0), eve::test::randoms(0.0, 20000.0))
        )
  <typename T>(T n, T a0)
{
  using v_t = eve::element_type_t<T>;
  auto eve__sph_bessel_yn =  [](auto n, auto x) { return eve::sph_bessel_yn(n, x); };
  auto std__sph_bessel_yn =  [](auto n, auto x)->v_t { return boost::math::sph_neumann(unsigned(n), double(x)); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__sph_bessel_yn(2, eve::inf(eve::as<v_t>())), v_t(0), 0);
    TTS_ULP_EQUAL(eve__sph_bessel_yn(3, eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
  }

  TTS_ULP_EQUAL(eve__sph_bessel_yn(3, v_t(1500)), std__sph_bessel_yn(3u, v_t(1500)), 2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_yn(2, v_t(500)), std__sph_bessel_yn(2u, v_t(500)), 2.0);

  TTS_ULP_EQUAL(eve__sph_bessel_yn(2, v_t(10)), std__sph_bessel_yn(2u, v_t(10))  , 5.0);
  TTS_ULP_EQUAL(eve__sph_bessel_yn(3, v_t(5)),  std__sph_bessel_yn(3u, v_t(5))   , 40.0);

  TTS_ULP_EQUAL(eve__sph_bessel_yn(2, v_t(0.1)), std__sph_bessel_yn(2u, v_t(0.1))  , 2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_yn(3, v_t(0.2)),  std__sph_bessel_yn(3u, v_t(0.2))   , 2.0);

  TTS_ULP_EQUAL(eve__sph_bessel_yn(10, v_t(8)), std__sph_bessel_yn(10u, v_t(8))  , 2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_yn(10, v_t(8)),  std__sph_bessel_yn(10u, v_t(8))   , 2.0);

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__sph_bessel_yn(2, eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve__sph_bessel_yn(3, eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

  TTS_ULP_EQUAL(eve__sph_bessel_yn(3, T(1500)),  T(std__sph_bessel_yn(3u, v_t(1500))),  2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_yn(2, T(500)),   T(std__sph_bessel_yn(2u, v_t(500))),   2.0);

  TTS_ULP_EQUAL(eve__sph_bessel_yn(2, T(10)),    T(std__sph_bessel_yn(2u, v_t(10)))   , 5.0);
  TTS_ULP_EQUAL(eve__sph_bessel_yn(3, T(5)),     T(std__sph_bessel_yn(3u, v_t(5)))    , 40.0);

  TTS_ULP_EQUAL(eve__sph_bessel_yn(2, T(0.1)),   T(std__sph_bessel_yn(2u, v_t(0.1)))  , 2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_yn(3, T(0.2)),   T(std__sph_bessel_yn(3u, v_t(0.2)))  , 2.0);

  TTS_ULP_EQUAL(eve__sph_bessel_yn(10, T(8)),   T(std__sph_bessel_yn(10u, v_t(8)))   , 2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_yn(10, T(8)),   T(std__sph_bessel_yn(10u, v_t(8)))   , 2.0);

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__sph_bessel_yn(T(2), eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve__sph_bessel_yn(T(3), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

  TTS_ULP_EQUAL(eve__sph_bessel_yn(T(3), T(1500)),  T(std__sph_bessel_yn(3u, v_t(1500))),  2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_yn(T(2), T(500)),   T(std__sph_bessel_yn(2u, v_t(500))),   2.0);

  TTS_ULP_EQUAL(eve__sph_bessel_yn(T(2), T(10)),    T(std__sph_bessel_yn(2u, v_t(10)))   , 5.0);
  TTS_ULP_EQUAL(eve__sph_bessel_yn(T(3), T(5)),     T(std__sph_bessel_yn(3u, v_t(5)))    , 40.0);

  TTS_ULP_EQUAL(eve__sph_bessel_yn(T(2), T(0.1)),   T(std__sph_bessel_yn(2u, v_t(0.1)))  , 2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_yn(T(3), T(0.2)),   T(std__sph_bessel_yn(3u, v_t(0.2)))  , 2.0);

  TTS_ULP_EQUAL(eve__sph_bessel_yn(T(10), T(8)),   T(std__sph_bessel_yn(10u, v_t(8)))   , 2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_yn(T(10), T(8)),   T(std__sph_bessel_yn(10u, v_t(8)))   , 2.0);

  using i_t = eve::as_integer_t<v_t>;
  using I_t = eve::wide<i_t, eve::cardinal_t<T>>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__sph_bessel_yn(I_t(2), eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve__sph_bessel_yn(I_t(3), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

  TTS_ULP_EQUAL(eve__sph_bessel_yn(I_t(3), T(1500)),  T(std__sph_bessel_yn(3u, v_t(1500))),  2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_yn(I_t(2), T(500)),   T(std__sph_bessel_yn(2u, v_t(500))),   2.0);

  TTS_ULP_EQUAL(eve__sph_bessel_yn(I_t(2), T(10)),    T(std__sph_bessel_yn(2u, v_t(10)))   , 5.0);
  TTS_ULP_EQUAL(eve__sph_bessel_yn(I_t(3), T(5)),     T(std__sph_bessel_yn(3u, v_t(5)))    , 40.0);

  TTS_ULP_EQUAL(eve__sph_bessel_yn(I_t(2), T(0.1)),   T(std__sph_bessel_yn(2u, v_t(0.1)))  , 2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_yn(I_t(3), T(0.2)),   T(std__sph_bessel_yn(3u, v_t(0.2)))  , 2.0);

  TTS_ULP_EQUAL(eve__sph_bessel_yn(I_t(10), T(8)),   T(std__sph_bessel_yn(10u, v_t(8)))   , 2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_yn(I_t(10), T(8)),   T(std__sph_bessel_yn(10u, v_t(8)))   , 2.0);

  TTS_RELATIVE_EQUAL(eve__sph_bessel_yn(n, a0),   map(std__sph_bessel_yn, n, a0)   , 0.0025);
};

