//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/polynomial.hpp>

#include <cmath>
#include <list>
#include <vector>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of newton on wide", eve::test::simd::all_types

)
<typename T>(tts::type<T>)
{
  using v_t  = eve::element_type_t<T>;
  using rv_t = std::vector<v_t>;
  using rl_t = std::list<v_t>;
  TTS_EXPR_IS(eve::newton(T(), rv_t(), rv_t()), T);
  TTS_EXPR_IS(eve::newton(T(), rv_t(), rl_t()), T);
  TTS_EXPR_IS(eve::newton(T(), rl_t(), rl_t()), T);
};

//==================================================================================================
//== newton tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of newton on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::ramp(0)))
<typename T>(T const& a0)
{
  using eve::fma;
  using eve::newton;
  using eve::numeric;
  using eve::one;
  using eve::pedantic;
  using v_t = eve::element_type_t<T>;
  //============================================================================
  //== ranges
  //============================================================================
  std::vector<v_t>   tab0; // std does not want array of size 0
  std::array<v_t, 1> tab1 = {1};
  std::array<v_t, 2> tab2 = {1, 2};
  std::array<v_t, 3> tab3 = {1, 2, 3};

  TTS_EQUAL((newton)(a0, tab0, tab0), T(0));
  TTS_EQUAL((newton)(a0, tab1, tab0), T(1));
  TTS_EQUAL((newton)(a0, tab2, tab1), (fma)(a0 - 1, 1, 2));
  TTS_EQUAL((newton)(a0, tab3, tab2), (fma)(a0 - 2, (fma)(a0 - 1, 1, 2), 3));

  TTS_EQUAL(pedantic(newton)(a0, tab0, tab0), T(0));
  TTS_EQUAL(pedantic(newton)(a0, tab1, tab0), T(1));
  TTS_EQUAL(pedantic(newton)(a0, tab2, tab1), (fma)(a0 - 1, 1, 2));
  TTS_EQUAL(pedantic(newton)(a0, tab3, tab2), (fma)(a0 - 2, (fma)(a0 - 1, 1, 2), 3));

  TTS_EQUAL(numeric(newton)(a0, tab0, tab0), T(0));
  TTS_EQUAL(numeric(newton)(a0, tab1, tab0), T(1));
  TTS_EQUAL(numeric(newton)(a0, tab2, tab1), (fma)(a0 - 1, 1, 2));
  TTS_EQUAL(numeric(newton)(a0, tab3, tab2), (fma)(a0 - 2, (fma)(a0 - 1, 1, 2), 3));
};
