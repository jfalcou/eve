//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/gamma_pinv.hpp>
#include <type_traits>
#include <cmath>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <boost/math/special_functions/gamma.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of gamma_pinv"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::gamma_pinv(T(), T())  , T);
  TTS_EXPR_IS( eve::gamma_pinv(T(), v_t()), T);
  TTS_EXPR_IS( eve::gamma_pinv(v_t(), T()), T);
  TTS_EXPR_IS( eve::gamma_pinv(v_t(), v_t()), v_t);
};

//==================================================================================================
// gamma_pinv  tests
//==================================================================================================
EVE_TEST( "Check behavior of gamma_pinv on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(0.0, 1.0)
                             , eve::test::randoms(0.0, 100.0))
        )
<typename T>(T const& a0, T const& a1 )
{
  using v_t = eve::element_type_t<T>;
  using eve::gamma_pinv;
  TTS_ULP_EQUAL( eve::gamma_pinv(a0, a1),  map([&](auto e, auto f) -> v_t{ return boost::math::gamma_p_inv(f, e); }, a0, a1), 33);

  auto bggpi =  [](auto e, auto f){return boost::math::gamma_p_inv(f, e); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(gamma_pinv(eve::nan(eve::as<T>()), T(1))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(gamma_pinv(eve::inf(eve::as<T>()), T(1))  , eve::nan(eve::as<T>()) );
  }
  TTS_ULP_EQUAL(gamma_pinv(T(0.1), T(0.75))   , T(bggpi(v_t(0.1), v_t(0.75)))     , 20);
  TTS_ULP_EQUAL(gamma_pinv(T(0.75), T(0.75))  , T(bggpi(v_t(0.75), v_t(0.75)))    , 20);
  TTS_ULP_EQUAL(gamma_pinv(T(0.1), T(0.1))    , T(bggpi(v_t(0.1), v_t(0.1)))      , 20);
  TTS_ULP_EQUAL(gamma_pinv(T(0.25), T(0.75))  , T(bggpi(v_t(0.25), v_t(0.75)))    , 20);
  TTS_ULP_EQUAL(gamma_pinv(T(0.25), T(0.25))  , T(bggpi(v_t(0.25), v_t(0.25)))    , 20);
  TTS_ULP_EQUAL(gamma_pinv(T(0.75), T(0.25))  , T(bggpi(v_t(0.75), v_t(0.25)))    , 20);
  TTS_ULP_EQUAL(gamma_pinv(T(0.25), T(2.0))   , T(bggpi(v_t(0.25), v_t(2.0)))     , 20);
  TTS_ULP_EQUAL(gamma_pinv(T(0.25), T(2.25))  , T(bggpi(v_t(0.25), v_t(2.25)))    , 20);
  TTS_ULP_EQUAL(gamma_pinv(T(0.75), T(2.25))  , T(bggpi(v_t(0.75), v_t(2.25)))    , 20);

};
