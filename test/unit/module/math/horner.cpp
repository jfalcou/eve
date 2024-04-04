//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of horner on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  TTS_EXPR_IS(eve::horner(T(), T()), T);
  TTS_EXPR_IS(eve::horner(T(), T(), T()), T);
  TTS_EXPR_IS(eve::horner(T(), T(), T()), T);
  TTS_EXPR_IS(eve::horner(T(), v_t(), v_t()), T);
  TTS_EXPR_IS(eve::horner(T(), v_t(), int()), T);
  TTS_EXPR_IS(eve::horner(T(), v_t(), i_t()), T);
  TTS_EXPR_IS(eve::horner(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
//== horner tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of horner on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10.0, 10.0))
             )
<typename T>(T const& a0)
{
  using eve::fma;
  using eve::horner;
  using eve::pedantic;

  TTS_EQUAL(horner(a0, 0), T(0));
  TTS_EQUAL(horner(a0, 1), T(1));
  TTS_EQUAL(horner(a0, 1, 2), fma(a0, 1, 2));
  TTS_EQUAL(horner(a0, 1, 2, 3), fma(a0, fma(a0, 1, 2), 3));

  TTS_EQUAL(horner[pedantic](a0, 0), T(0));
  TTS_EQUAL(horner[pedantic](a0, 1), T(1));
  TTS_EQUAL(horner[pedantic](a0, 1, 2), fma[pedantic](a0, 1, 2));
  TTS_EQUAL(horner[pedantic](a0, 1, 2, 3), fma[pedantic](a0, fma[pedantic](a0, 1, 2), 3));

  //============================================================================
  //== tuples
  //============================================================================
  auto tab1 = kumi::tuple{1};
  auto tab2 = kumi::tuple{1, 2};
  auto tab3 = kumi::tuple{1, 2, 3};

  TTS_EQUAL(horner(a0, tab1), T(1));
  TTS_EQUAL(horner(a0, tab2), fma(a0, 1, 2));
  TTS_EQUAL(horner(a0, tab3), fma(a0, fma(a0, 1, 2), 3));

  TTS_EQUAL(horner[pedantic](a0, tab1), T(1));
  TTS_EQUAL(horner[pedantic](a0, tab2), fma[pedantic](a0, 1, 2));
  TTS_EQUAL(horner[pedantic](a0, tab3), fma[pedantic](a0, fma[pedantic](a0, 1, 2), 3));
};
