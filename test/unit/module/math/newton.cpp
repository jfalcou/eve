//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
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
// TTS_CASE_TPL("Check return types of newton on wide", eve::test::simd::all_types

// )
// <typename T>(tts::type<T>)
// {
//   using v_t  = eve::element_type_t<T>;
//   using rv_t = std::vector<v_t>;
//   using rl_t = std::list<v_t>;
//   TTS_EXPR_IS(eve::newton(T(), rv_t(), rv_t()), T);
//   TTS_EXPR_IS(eve::newton(T(), rv_t(), rl_t()), T);
//   TTS_EXPR_IS(eve::newton(T(), rl_t(), rl_t()), T);
// };

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

  //============================================================================
  //== variadic
  //============================================================================

  TTS_EQUAL((newton)(a0), T(0));
  TTS_EQUAL((newton)(a0, 1), T(1));
  TTS_EQUAL((newton)(a0, 1, 2, 1), (fma)(a0 - 1, 1, 2));
  TTS_EQUAL((newton)(a0, 1, 2, 3, 1, 2), (fma)(a0 - 2, (fma)(a0 - 1, 1, 2), 3));


  //============================================================================
  //== tuples
  //============================================================================
  auto tup0 = kumi::tuple{};
  auto tup1 = kumi::tuple{1};
  auto tup2 = kumi::tuple{1, 2};
  auto tup3 = kumi::tuple{1, 2, 3};

  TTS_EQUAL((newton)(a0, tup0, tup0), T(0));
  TTS_EQUAL((newton)(a0, tup1, tup0), T(1));
  TTS_EQUAL((newton)(a0, tup2, tup1), (fma)(a0 - 1, 1, 2));
  TTS_EQUAL((newton)(a0, tup3, tup2), (fma)(a0 - 2, (fma)(a0 - 1, 1, 2), 3));

  TTS_EQUAL(newton[pedantic](a0, tup0, tup0), T(0));
  TTS_EQUAL(newton[pedantic](a0, tup1, tup0), T(1));
  TTS_EQUAL(newton[pedantic](a0, tup2, tup1), (fma)(a0 - 1, 1, 2));
  TTS_EQUAL(newton[pedantic](a0, tup3, tup2), (fma)(a0 - 2, (fma)(a0 - 1, 1, 2), 3));
};
