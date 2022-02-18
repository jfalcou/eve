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
#include <eve/detail/diff_div.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of sph_bessel_jn"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using I_t = eve::wide<i_t, eve::cardinal_t<T>>;
  TTS_EXPR_IS( eve::sph_bessel_jn(T(), T())  ,  T);
  TTS_EXPR_IS( eve::sph_bessel_jn(v_t(),v_t()), v_t);
  TTS_EXPR_IS( eve::sph_bessel_jn(i_t(),T()),   T);
  TTS_EXPR_IS( eve::sph_bessel_jn(I_t(),T()),   T);
  TTS_EXPR_IS( eve::sph_bessel_jn(i_t(),v_t()), v_t);
//  TTS_EXPR_IS( eve::sph_bessel_jn(I_t(),v_t()), T);
 };

//==================================================================================================
//== integral orders
//==================================================================================================
EVE_TEST( "Check behavior of sph_bessel_jn on wide with integral order"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::ramp(0), eve::test::randoms(0.0, 20000.0))
        )
  <typename T>(T n, T a0)
{
  using v_t = eve::element_type_t<T>;
  auto eve__sph_bessel_jn =  [](auto n, auto x) { return eve::sph_bessel_jn(n, x); };
  auto std__sph_bessel_jn =  [](auto n, auto x)->v_t { return boost::math::sph_bessel(unsigned(n), double(x)); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__sph_bessel_jn(2, eve::inf(eve::as<v_t>())), v_t(0), 0);
    TTS_ULP_EQUAL(eve__sph_bessel_jn(3, eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
  }

  TTS_ULP_EQUAL(eve__sph_bessel_jn(3, v_t(1500)), std__sph_bessel_jn(3u, v_t(1500)), 2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(2, v_t(500)), std__sph_bessel_jn(2u, v_t(500)), 2.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(2, v_t(10)), std__sph_bessel_jn(2u, v_t(10))  , 4.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(3, v_t(5)),  std__sph_bessel_jn(3u, v_t(5))   , 2.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(2, v_t(0.1)), std__sph_bessel_jn(2u, v_t(0.1))  , 2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(3, v_t(0.2)),  std__sph_bessel_jn(3u, v_t(0.2))   , 2.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(10, v_t(8)), std__sph_bessel_jn(10u, v_t(8))  , 2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(10, v_t(8)),  std__sph_bessel_jn(10u, v_t(8))   , 2.0);

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__sph_bessel_jn(2, eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve__sph_bessel_jn(3, eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

  TTS_ULP_EQUAL(eve__sph_bessel_jn(3, T(1500)),  T(std__sph_bessel_jn(3u, v_t(1500))),  2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(2, T(500)),   T(std__sph_bessel_jn(2u, v_t(500))),   2.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(2, T(10)),    T(std__sph_bessel_jn(2u, v_t(10)))   , 4.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(3, T(5)),     T(std__sph_bessel_jn(3u, v_t(5)))    , 2.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(2, T(0.1)),   T(std__sph_bessel_jn(2u, v_t(0.1)))  , 2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(3, T(0.2)),   T(std__sph_bessel_jn(3u, v_t(0.2)))  , 2.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(10, T(8)),   T(std__sph_bessel_jn(10u, v_t(8)))   , 2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(10, T(8)),   T(std__sph_bessel_jn(10u, v_t(8)))   , 2.0);

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__sph_bessel_jn(T(2), eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve__sph_bessel_jn(T(3), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

  TTS_ULP_EQUAL(eve__sph_bessel_jn(T(3), T(1500)),  T(std__sph_bessel_jn(3u, v_t(1500))),  2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(T(2), T(500)),   T(std__sph_bessel_jn(2u, v_t(500))),   2.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(T(2), T(10)),    T(std__sph_bessel_jn(2u, v_t(10)))   , 4.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(T(3), T(5)),     T(std__sph_bessel_jn(3u, v_t(5)))    , 2.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(T(2), T(0.1)),   T(std__sph_bessel_jn(2u, v_t(0.1)))  , 2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(T(3), T(0.2)),   T(std__sph_bessel_jn(3u, v_t(0.2)))  , 2.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(T(10), T(8)),   T(std__sph_bessel_jn(10u, v_t(8)))   , 2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(T(10), T(8)),   T(std__sph_bessel_jn(10u, v_t(8)))   , 2.0);

  using i_t = eve::as_integer_t<v_t>;
  using I_t = eve::wide<i_t, eve::cardinal_t<T>>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__sph_bessel_jn(I_t(2), eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve__sph_bessel_jn(I_t(3), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

  TTS_ULP_EQUAL(eve__sph_bessel_jn(I_t(3), T(1500)),  T(std__sph_bessel_jn(3u, v_t(1500))),  2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(I_t(2), T(500)),   T(std__sph_bessel_jn(2u, v_t(500))),   2.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(I_t(2), T(10)),    T(std__sph_bessel_jn(2u, v_t(10)))   , 4.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(I_t(3), T(5)),     T(std__sph_bessel_jn(3u, v_t(5)))    , 2.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(I_t(2), T(0.1)),   T(std__sph_bessel_jn(2u, v_t(0.1)))  , 2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(I_t(3), T(0.2)),   T(std__sph_bessel_jn(3u, v_t(0.2)))  , 2.0);

  TTS_ULP_EQUAL(eve__sph_bessel_jn(I_t(10), T(8)),   T(std__sph_bessel_jn(10u, v_t(8)))   , 2.0);
  TTS_ULP_EQUAL(eve__sph_bessel_jn(I_t(10), T(8)),   T(std__sph_bessel_jn(10u, v_t(8)))   , 2.0);

  TTS_RELATIVE_EQUAL(eve__sph_bessel_jn(n, a0),   map(std__sph_bessel_jn, n, a0)   , 0.0035);
};


EVE_TEST( "Check behavior of diff(sph_bessel_j1) on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(1.0, 10.0))
        )
  <typename T>(T a0 )
{
  auto eve__diff_bessel_jn =  [](auto n, auto x) { return eve::diff(eve::sph_bessel_jn)(n, x); };
  auto j3 = [](auto x){ return eve::sph_bessel_jn(3, x); };
  auto df = [j3](auto x){return eve::detail::centered_diffdiv(j3, x); };

  TTS_RELATIVE_EQUAL(eve__diff_bessel_jn(3, a0),   df(a0), 1.0e-2);
  TTS_RELATIVE_EQUAL(eve__diff_bessel_jn(1, a0),   eve::diff(eve::sph_bessel_j1)(a0), 1.0e-2);
};
