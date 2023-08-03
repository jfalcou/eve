//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"

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
              tts::generate( tts::randoms(-10.0, +10.0)
                            , tts::randoms(-10.0, +10.0)
                            , tts::randoms(-10.0, +10.0)
                            , tts::randoms(-10.0, +10.0)
                            , tts::randoms(-10.0, +10.0)
                            , tts::randoms(-10.0, +10.0)
                            , tts::randoms(-10.0, +10.0)
                            , tts::randoms(-10.0, +10.0)
                            )
             )
  <typename T>(T const& a0,T const& a1,T const& a2,T const& a3
              ,T const& a4,T const& a5,T const& a6,T const& a7)
{
  using eve::fma;
  using eve::newton;
  using eve::numeric;
  using eve::one;
  using eve::pedantic;
  using c_t  = eve::as_complex_t<T>;
  c_t x(a0, a1);
  c_t c1(a2, a3);
  c_t c2(a4, a5);
  c_t c3(a6, a7);
  //============================================================================
  //== ranges
  //============================================================================
  std::vector<c_t> tab0;
  std::vector<c_t> tab1{c1};
  std::vector<c_t> tab2{c1, c2};
  std::vector<c_t> tab3{c1, c2, c3};
  TTS_RELATIVE_EQUAL((newton)(x, tab0, tab0), c_t(0), 0.0001);
  TTS_RELATIVE_EQUAL((newton)(x, tab1, tab0), c1, 0.0001);
  TTS_RELATIVE_EQUAL((newton)(x, tab2, tab1), (c1*(x-c1)+c2), 0.0001);
  TTS_RELATIVE_EQUAL((newton)(x, tab3, tab2), (c1*(x-c1)+c2)*(x-c2)+c3, 0.0001);

  TTS_RELATIVE_EQUAL(pedantic(newton)(x, tab0, tab0),  c_t(0), 0.0001);
  TTS_RELATIVE_EQUAL(pedantic(newton)(x, tab1, tab0),  c1, 0.0001);
  TTS_RELATIVE_EQUAL(pedantic(newton)(x, tab2, tab1),  (c1*(x-c1)+c2), 0.0001);
  TTS_RELATIVE_EQUAL(pedantic(newton)(x, tab3, tab2),  (c1*(x-c1)+c2)*(x-c2)+c3, 0.0001);

  TTS_RELATIVE_EQUAL(numeric(newton)(x, tab0, tab0),  c_t(0), 0.0001);
  TTS_RELATIVE_EQUAL(numeric(newton)(x, tab1, tab0),  c1, 0.0001);
  TTS_RELATIVE_EQUAL(numeric(newton)(x, tab2, tab1),  (c1*(x-c1)+c2), 0.0001);
  TTS_RELATIVE_EQUAL(numeric(newton)(x, tab3, tab2),  (c1*(x-c1)+c2)*(x-c2)+c3, 0.0001);


  //============================================================================
  //== tuples
  //============================================================================
  auto tup0 = kumi::tuple{};
  auto tup1 = kumi::tuple{c1};
  auto tup2 = kumi::tuple{c1, c2};
  auto tup3 = kumi::tuple{c1, c2, c3};

  TTS_RELATIVE_EQUAL((newton)(x, tup0, tup0), c_t(0), 0.0001);
  TTS_RELATIVE_EQUAL((newton)(x, tup1, tup0), c1, 0.0001);
  TTS_RELATIVE_EQUAL((newton)(x, tup2, tup1), (c1*(x-c1)+c2), 0.0001);
  TTS_RELATIVE_EQUAL((newton)(x, tup3, tup2), (c1*(x-c1)+c2)*(x-c2)+c3, 0.0001);

  TTS_RELATIVE_EQUAL(pedantic(newton)(x, tup0, tup0), c_t(0), 0.0001);
  TTS_RELATIVE_EQUAL(pedantic(newton)(x, tup1, tup0), c1, 0.0001);
  TTS_RELATIVE_EQUAL(pedantic(newton)(x, tup2, tup1), (c1*(x-c1)+c2), 0.0001);
  TTS_RELATIVE_EQUAL(pedantic(newton)(x, tup3, tup2), (c1*(x-c1)+c2)*(x-c2)+c3, 0.0001);

  TTS_RELATIVE_EQUAL(numeric(newton)(x, tup0, tup0), c_t(0), 0.0001);
  TTS_RELATIVE_EQUAL(numeric(newton)(x, tup1, tup0), c1, 0.0001);
  TTS_RELATIVE_EQUAL(numeric(newton)(x, tup2, tup1), (c1*(x-c1)+c2), 0.0001);
  TTS_RELATIVE_EQUAL(numeric(newton)(x, tup3, tup2), (c1*(x-c1)+c2)*(x-c2)+c3, 0.0001);
};
