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
#include <boost/math/special_functions/expint.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of exp_int"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using I_t = eve::as_integer_t<T>;

  TTS_EXPR_IS( eve::exp_int(T(), T())  ,   T);
  TTS_EXPR_IS( eve::exp_int(v_t(),v_t()), v_t);
  TTS_EXPR_IS( eve::exp_int(i_t(),T()),   T);
  TTS_EXPR_IS( eve::exp_int(I_t(),T()),   T);
  TTS_EXPR_IS( eve::exp_int(I_t(),v_t()), T);
  TTS_EXPR_IS( eve::exp_int(i_t(),v_t()), v_t);
};

//==================================================================================================
// exp_int  tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of exp_int on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(0.0, 10.0))
        )
<typename T>(T const& a0 )
{
  using eve::exp_int;
  using eve::as;
  for(int i=1; i < 4 ; ++i)
  {
    TTS_ULP_EQUAL( exp_int(i, a0),  map([i](auto e){return boost::math::expint(i, e);}, a0), 16);
  }

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(exp_int(T(1), eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(exp_int(T(1), eve::inf(eve::as<T>()))   , T(0) );
  }

  for(int i=1; i < 4 ; ++i)
  {
    TTS_ULP_EQUAL(exp_int(T(i), T(0))  , eve::rec(T(i-1)), 0.5);
    TTS_ULP_EQUAL(exp_int(T(i), T(0.5)), T(boost::math::expint(i, 0.5)), 32.0);
    TTS_ULP_EQUAL(exp_int(T(i), T(1))  , T(boost::math::expint(i, 1.0)), 32.0);
    TTS_ULP_EQUAL(exp_int(T(i), T(10)) , T(boost::math::expint(i, 10.0)), 32.0);
  }
  for(int i=1; i < 4 ; ++i)
  {
    TTS_ULP_EQUAL(exp_int(i, T(0))  , eve::rec(T(i-1)), 0.5);
    TTS_ULP_EQUAL(exp_int(i, T(0.5)), T(boost::math::expint(i, 0.5)), 32.0);
    TTS_ULP_EQUAL(exp_int(i, T(1))  , T(boost::math::expint(i, 1.0)), 32.0);
    TTS_ULP_EQUAL(exp_int(i, T(10)) , T(boost::math::expint(i, 10.0)), 32.0);
  }
  using elt_t =  eve::element_type_t<T>;

  TTS_ULP_EQUAL(exp_int(elt_t(2.0), elt_t(0.5)), (boost::math::expint(elt_t(2), elt_t(0.5))), 16.0);
  TTS_ULP_EQUAL(exp_int(elt_t(6000), elt_t(0.5)), (boost::math::expint(elt_t(6000), elt_t(0.5))), 4.0);
};
