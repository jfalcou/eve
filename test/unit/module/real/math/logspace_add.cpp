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
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/log.hpp>
#include <eve/function/logspace_add.hpp>
#include <eve/function/diff/logspace_add.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of logspace_add"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::logspace_add(T(), T())  , T);
  TTS_EXPR_IS( eve::logspace_add(v_t(), v_t()), v_t);
  TTS_EXPR_IS( eve::logspace_add(T(), v_t()), T);
  TTS_EXPR_IS( eve::logspace_add(v_t(), T()), T);
  TTS_EXPR_IS( eve::logspace_add(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::logspace_add(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::logspace_add(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::logspace_add(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::logspace_add(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::logspace_add(v_t(), T(), v_t()) , T);

  TTS_EXPR_IS( eve::logspace_add(v_t(), v_t(), v_t()) , v_t);
};

//==================================================================================================
// logspace_add  tests
//==================================================================================================
auto maxi = []<typename T>(eve::as_<T> const & tgt)
{
  return eve::valmax(tgt)/3;
};
EVE_TEST( "Check behavior of logspace_add on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(0.0, maxi)
                             , eve::test::randoms(0.0, maxi)
                             , eve::test::randoms(0.5, 2.0)
                             , eve::test::randoms(0.5, 2.0)
                             , eve::test::randoms(0.0, maxi)
                             , eve::test::randoms(0.5, 2.0)
                             )
        )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3, T const& a4, T const& a5)
{
  using eve::detail::map;

  auto la0 = eve::log(a0);
  auto la1 = eve::log(a1);
  auto la2 = eve::log(a2);
  auto la3 = eve::log(a3);
  TTS_ULP_EQUAL(eve::logspace_add(la0, la1)      , eve::log(a0+a1), 2);
  TTS_ULP_EQUAL(eve::logspace_add(la2, la3)      , eve::log(a2+a3), 2);
  TTS_ULP_EQUAL(eve::diff_1st(eve::logspace_add)(a0, a1), eve::rec(eve::inc(eve::exp(a1-a0))), 2);
  TTS_ULP_EQUAL(eve::diff_1st(eve::logspace_add)(a2, a3), eve::rec(eve::inc(eve::exp(a3-a2))), 2);
  TTS_ULP_EQUAL(eve::diff_2nd(eve::logspace_add)(a0, a1), eve::rec(eve::inc(eve::exp(a0-a1))), 2);
  TTS_ULP_EQUAL(eve::diff_2nd(eve::logspace_add)(a2, a3), eve::rec(eve::inc(eve::exp(a2-a3))), 2);
  auto la4 = eve::log(a4);
  auto la5 = eve::log(a5);
  TTS_ULP_EQUAL(eve::logspace_add(la0, la1, la4)      , eve::log(a0+a1+a4), 2);
  TTS_ULP_EQUAL(eve::logspace_add(la2, la3, la5)      , eve::log(a2+a3+a5), 2);
};
