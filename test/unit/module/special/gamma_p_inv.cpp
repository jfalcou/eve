//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/special.hpp>
#include <cmath>
#include <boost/math/special_functions/gamma.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of gamma_p_inv"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::gamma_p_inv(T(), T())  , T);
  TTS_EXPR_IS( eve::gamma_p_inv(T(), v_t()), T);
  TTS_EXPR_IS( eve::gamma_p_inv(v_t(), T()), T);
  TTS_EXPR_IS( eve::gamma_p_inv(v_t(), v_t()), v_t);
};

//==================================================================================================
// gamma_p_inv  tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of gamma_p_inv on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(0.0, 1.0)
                             , tts::randoms(0.0, 100.0))
        )
<typename T>(T const& a0, T const& a1 )
{
  using v_t = eve::element_type_t<T>;
  using eve::gamma_p_inv;
  TTS_ULP_EQUAL( eve::gamma_p_inv(a0, a1),  map([&](auto e, auto f) -> v_t{ return boost::math::gamma_p_inv(f, e); }, a0, a1), 33);

  auto bggpi =  [](auto e, auto f){return boost::math::gamma_p_inv(f, e); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(gamma_p_inv(eve::nan(eve::as<T>()), T(1))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(gamma_p_inv(eve::inf(eve::as<T>()), T(1))  , eve::nan(eve::as<T>()) );
  }
  TTS_ULP_EQUAL(gamma_p_inv(T(0.1), T(0.75))   , T(bggpi(v_t(0.1), v_t(0.75)))     , 20);
  TTS_ULP_EQUAL(gamma_p_inv(T(0.75), T(0.75))  , T(bggpi(v_t(0.75), v_t(0.75)))    , 20);
  TTS_ULP_EQUAL(gamma_p_inv(T(0.1), T(0.1))    , T(bggpi(v_t(0.1), v_t(0.1)))      , 20);
  TTS_ULP_EQUAL(gamma_p_inv(T(0.25), T(0.75))  , T(bggpi(v_t(0.25), v_t(0.75)))    , 20);
  TTS_ULP_EQUAL(gamma_p_inv(T(0.25), T(0.25))  , T(bggpi(v_t(0.25), v_t(0.25)))    , 20);
  TTS_ULP_EQUAL(gamma_p_inv(T(0.75), T(0.25))  , T(bggpi(v_t(0.75), v_t(0.25)))    , 20);
  TTS_ULP_EQUAL(gamma_p_inv(T(0.25), T(2.0))   , T(bggpi(v_t(0.25), v_t(2.0)))     , 20);
  TTS_ULP_EQUAL(gamma_p_inv(T(0.25), T(2.25))  , T(bggpi(v_t(0.25), v_t(2.25)))    , 20);
  TTS_ULP_EQUAL(gamma_p_inv(T(0.75), T(2.25))  , T(bggpi(v_t(0.75), v_t(2.25)))    , 20);

};
