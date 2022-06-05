//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of logspace_sub"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::logspace_sub(T(), T())  , T);
  TTS_EXPR_IS( eve::logspace_sub(v_t(), v_t()), v_t);
  TTS_EXPR_IS( eve::logspace_sub(T(), v_t()), T);
  TTS_EXPR_IS( eve::logspace_sub(v_t(), T()), T);

  TTS_EXPR_IS( eve::logspace_sub(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::logspace_sub(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::logspace_sub(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::logspace_sub(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::logspace_sub(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::logspace_sub(v_t(), T(), v_t()) , T);

  TTS_EXPR_IS( eve::logspace_sub(v_t(), v_t(), v_t()) , v_t);
};

//==================================================================================================
// logspace_sub  tests
//==================================================================================================
EVE_TEST( "Check behavior of logspace_sub on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(0.0, eve::valmax)
                             , eve::test::randoms(0.0, eve::valmax)
                             , eve::test::randoms(0.5, 2.0)
                             , eve::test::randoms(0.5, 2.0)
                             , eve::test::randoms(0.0, eve::valmax)
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
  TTS_ULP_EQUAL(eve::logspace_sub(la0, la1)      , eve::log(a0-a1), 2);
  TTS_ULP_EQUAL(eve::logspace_sub(la2, la3)      , eve::log(a2-a3), 10);
  
  
  
  
  auto la4 = eve::log(a4);
  auto la5 = eve::log(a5);
  TTS_ULP_EQUAL(eve::logspace_sub(la0, la1, la4)      , eve::log(a0-a1-a4), 2);
  TTS_ULP_EQUAL(eve::logspace_sub(la2, la3, la5)      , eve::log(a2-a3-a5), 2);
};
