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
#include <eve/function/all.hpp>
#include <eve/function/exp_int.hpp>
#include <eve/function/diff/exp_int.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <type_traits>
#include <cmath>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/platform.hpp>
#include <boost/math/special_functions/expint.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of exp_int"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
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
EVE_TEST( "Check behavior of exp_int on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(0.0, 10.0))
        )
<typename T>(T const& a0 )
{
  using v_t = eve::element_type_t<T>;
  using eve::exp_int;
  using eve::as;
  for(int i=1; i < 4 ; ++i)
  {
    TTS_ULP_EQUAL( exp_int(i, a0),  map([i](auto e){return boost::math::expint(i, e);}, a0), 5);
    auto dexp_int = [i](auto e){return v_t( -boost::math::expint(i-1, e));};
    TTS_ULP_EQUAL( eve::diff(exp_int)(i, a0),  map(dexp_int, a0), 5);
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
    TTS_ULP_EQUAL(exp_int(T(i), T(10)) , T(boost::math::expint(i, 10.0)), 1.5);
  }
  for(int i=1; i < 4 ; ++i)
  {
    TTS_ULP_EQUAL(exp_int(i, T(0))  , eve::rec(T(i-1)), 0.5);
    TTS_ULP_EQUAL(exp_int(i, T(0.5)), T(boost::math::expint(i, 0.5)), 32.0);
    TTS_ULP_EQUAL(exp_int(i, T(1))  , T(boost::math::expint(i, 1.0)), 32.0);
    TTS_ULP_EQUAL(exp_int(i, T(10)) , T(boost::math::expint(i, 10.0)), 1.5);
  }
  using elt_t =  eve::element_type_t<T>;

  TTS_ULP_EQUAL(exp_int(elt_t(2.0), elt_t(0.5)), (boost::math::expint(elt_t(2), elt_t(0.5))), 16.0);
  TTS_ULP_EQUAL(exp_int(elt_t(6000), elt_t(0.5)), (boost::math::expint(elt_t(6000), elt_t(0.5))), 4.0);
};
