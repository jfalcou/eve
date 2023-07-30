//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/polynomial.hpp>
#include <eve/module/complex.hpp>

#include <cmath>
#include <list>
#include <vector>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of newton on wide", eve::test::simd::ieee_reals

)
<typename T>(tts::type<T>)
{
  using c_t  = eve::as_complex_t<T>;
  using v_t  = eve::complex<eve::element_type_t<T>>;
  using rv_t = std::vector<v_t>;
  using rl_t = std::list<v_t>;
  TTS_EXPR_IS(eve::newton(T(), rv_t(), rv_t()), c_t);
  TTS_EXPR_IS(eve::newton(T(), rv_t(), rl_t()), c_t);
  TTS_EXPR_IS(eve::newton(T(), rl_t(), rl_t()), c_t);
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
  using c_t  = eve::as_complex_t<T>; //eve::element_type_t<T>>;
  //============================================================================
  //== ranges
  //============================================================================
  std::vector<c_t> tab0;
  std::vector<c_t> tab1{c_t(1)};
  std::vector<c_t> tab2{c_t(1), c_t(2)};
  std::vector<c_t> tab3{c_t(1), c_t(2), c_t(3)};

  TTS_EQUAL((newton)(c_t(a0), tab0, tab0), c_t(0));
  TTS_EQUAL((newton)(c_t(a0), tab1, tab0), c_t(1));
  TTS_EQUAL((newton)(c_t(a0), tab2, tab1), c_t((fma)(a0 - 1, 1, 2)));
  TTS_EQUAL((newton)(c_t(a0), tab3, tab2), c_t((fma)(a0 - 2, (fma)(a0 - 1, 1, 2), 3)));

  TTS_EQUAL(pedantic(newton)(a0, tab0, tab0), c_t(0));
  TTS_EQUAL(pedantic(newton)(a0, tab1, tab0), c_t(1));
  TTS_EQUAL(pedantic(newton)(a0, tab2, tab1), c_t((fma)(a0 - 1, 1, 2)));
  TTS_EQUAL(pedantic(newton)(a0, tab3, tab2), c_t((fma)(a0 - 2, (fma)(a0 - 1, 1, 2), 3)));

  TTS_EQUAL(numeric(newton)(a0, tab0, tab0), c_t(0));
  TTS_EQUAL(numeric(newton)(a0, tab1, tab0), c_t(1));
  TTS_EQUAL(numeric(newton)(a0, tab2, tab1), c_t((fma)(a0 - 1, 1, 2)));
  TTS_EQUAL(numeric(newton)(a0, tab3, tab2), c_t((fma)(a0 - 2, (fma)(a0 - 1, 1, 2), 3)));


  //============================================================================
  //== tuples
  //============================================================================
  auto tup0 = kumi::tuple{};
  auto tup1 = kumi::tuple{c_t(1)};
  auto tup2 = kumi::tuple{c_t(1), c_t(2)};
  auto tup3 = kumi::tuple{c_t(1), c_t(2), c_t(3)};

  TTS_EQUAL((newton)(c_t(a0), tup0, tup0), c_t(0));
  TTS_EQUAL((newton)(a0, tup1, tup0), c_t(1));
  TTS_EQUAL((newton)(a0, tup2, tup1), c_t((fma)(a0 - 1, 1, 2)));
  TTS_EQUAL((newton)(a0, tup3, tup2), c_t((fma)(a0 - 2, (fma)(a0 - 1, 1, 2), 3)));

  TTS_EQUAL(pedantic(newton)(c_t(a0), tup0, tup0), c_t(0));
  TTS_EQUAL(pedantic(newton)(a0, tup1, tup0), c_t(1));
  TTS_EQUAL(pedantic(newton)(a0, tup2, tup1), c_t((fma)(a0 - 1, 1, 2)));
  TTS_EQUAL(pedantic(newton)(a0, tup3, tup2), c_t((fma)(a0 - 2, (fma)(a0 - 1, 1, 2), 3)));

  TTS_EQUAL(numeric(newton)(c_t(a0), tup0, tup0), c_t(0));
  TTS_EQUAL(numeric(newton)(a0, tup1, tup0), c_t(1));
  TTS_EQUAL(numeric(newton)(a0, tup2, tup1), c_t((fma)(a0 - 1, 1, 2)));
  TTS_EQUAL(numeric(newton)(a0, tup3, tup2), c_t((fma)(a0 - 2, (fma)(a0 - 1, 1, 2), 3)));
};
