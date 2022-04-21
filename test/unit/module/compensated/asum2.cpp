/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <algorithm>
#include <eve/module/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of asum2"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::asum2(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::asum2(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::asum2(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::asum2(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::asum2(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::asum2(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::asum2(v_t(), v_t(), v_t()) , v_t);
};

//==================================================================================================
// asum2 tests
//==================================================================================================

EVE_TEST( "Check behavior of asum2 on all types full range"
        , eve::test::simd::ieee_reals
        , eve::test::generate (  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              )
        )
<typename T>(  T const& a0, T const& a1, T const& a2)
{
  using eve::asum2;
  using eve::detail::map;
  using eve::abs;
  using v_t = eve::element_type_t<T>;
  auto m = [](auto a, auto b, auto c)-> v_t {return abs(a)+abs(b)+abs(c); };
  auto s = [](auto a)                -> v_t {return eve::sign(a);  };
  TTS_ULP_EQUAL(asum2((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::pedantic(asum2)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::diff_1st(asum2)((a0), (a1), (a2)), map(s, a0), 2);
  TTS_ULP_EQUAL(eve::diff_2nd(asum2)((a0), (a1), (a2)), map(s, a1), 2);
  TTS_ULP_EQUAL(eve::diff_3rd(asum2)((a0), (a1), (a2)), map(s, a2), 2);
};
