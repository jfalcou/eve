//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of nthroot"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  TTS_EXPR_IS( eve::nthroot(T(), T())  , T);
  TTS_EXPR_IS( eve::nthroot(v_t(), i_t()), v_t);
  TTS_EXPR_IS( eve::nthroot(v_t(), int()), v_t);
  TTS_EXPR_IS( eve::nthroot(T(), i_t()), T);
  TTS_EXPR_IS( eve::nthroot(T(), int()), T);
//  TTS_EXPR_IS( eve::nthroot(v_t(), T()), T);
};

//==================================================================================================
// nthroot  tests
//==================================================================================================
EVE_TEST( "Check behavior of nthroot on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(-100.0,  100.0)
                             , eve::test::randoms(0, eve::valmax)
                             , eve::test::as_integer(eve::test::randoms(1, 5))
                             , eve::test::as_integer(eve::test::randoms(1, 10))
                             )
        )
  <typename T, typename U>(T const& a0, T const& a1, U const& a2, U const& a3)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::nthroot(a0, U(2)*a2+U(1)), map([](auto e, auto f) -> v_t { return std::pow(std::abs(e), eve::rec(2.0*f+1.0))*eve::sign(e); }, a0, a2), 100);
  TTS_ULP_EQUAL(eve::nthroot(a1, a3)          , map([](auto e, auto f) -> v_t { return std::pow(e, eve::rec(double(f))); }, a1, a3), 100);
  TTS_ULP_EQUAL(eve::diff_1st(eve::nthroot)(a0, U(2)*a2+U(1)), eve::nthroot(a0, U(2)*a2+U(1))/(eve::convert(U(2)*a2+U(1), eve::as<v_t>())*a0), 2);
  TTS_ULP_EQUAL(eve::diff_1st(eve::nthroot)(a1, a3),           eve::nthroot(a1, a3)/(eve::convert(a3, eve::as<v_t>())*a1), 2);
};


EVE_TEST_TYPES( "Check return types of nthroot"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  TTS_ULP_EQUAL(eve::nthroot(T(0), T(-1)), eve::inf(eve::as<T>()), 0);
  TTS_ULP_EQUAL(eve::nthroot(-T(0), T(-2)), eve::nan(eve::as<T>()), 0);
  TTS_ULP_EQUAL(eve::nthroot(T(0), T(-2)), eve::inf(eve::as<T>()), 0);
  TTS_ULP_EQUAL(eve::nthroot(T(0),  2),  T(0), 0);
  TTS_ULP_EQUAL(eve::nthroot(-T(0), 2),  eve::nan(eve::as<T>()), 0);
  TTS_ULP_EQUAL(eve::nthroot(eve::inf(eve::as<T>()), T(4) ),  eve::inf(eve::as<T>()), 0);
  TTS_ULP_EQUAL(eve::nthroot(eve::inf(eve::as<T>()), T(-4) ),  T( 0 ), 0);
  TTS_ULP_EQUAL(eve::nthroot(eve::minf(eve::as<T>()), T(4) ),  eve::nan(eve::as<T>()), 0);
  TTS_ULP_EQUAL(eve::nthroot(eve::minf(eve::as<T>()), T(3) ),  eve::minf(eve::as<T>()), 0);
  TTS_ULP_EQUAL(eve::nthroot(T(64), 3),  T(4), 0.5);
  TTS_EQUAL(eve::nthroot(T(8),-3), T(0.5));
  TTS_EQUAL(eve::nthroot(T(8),3) , T(2)    );
  TTS_EQUAL(eve::nthroot(T(8),3u), T(2)    );
};
