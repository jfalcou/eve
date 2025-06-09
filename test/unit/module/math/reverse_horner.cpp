//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/polynomial.hpp>

#include <array>
#include <cmath>
#include <vector>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of reverse_horner on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  TTS_EXPR_IS(eve::reverse_horner(T(), T()), T);
  TTS_EXPR_IS(eve::reverse_horner(T(), T(), T()), T);
  TTS_EXPR_IS(eve::reverse_horner(T(), T(), T()), T);
  TTS_EXPR_IS(eve::reverse_horner(T(), v_t(), v_t()), T);
  TTS_EXPR_IS(eve::reverse_horner(T(), int(), v_t()), T);
  TTS_EXPR_IS(eve::reverse_horner(T(), v_t(), i_t()), T);
  TTS_EXPR_IS(eve::reverse_horner(T(), v_t(), v_t()), T);
  TTS_EXPR_IS(eve::reverse_horner(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
//== reverse_horner tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of reverse_horner on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::ramp(0)))
<typename T>(T const& a0)
{
  using eve::fma;
  using eve::numeric;
  using eve::one;
  using eve::pedantic;
  using eve::reverse_horner;
  //============================================================================
  //== variadic
  //============================================================================

  TTS_EQUAL(reverse_horner(a0, 0), T(0));
  TTS_EQUAL(reverse_horner(a0, 1), T(1));
  TTS_EQUAL(reverse_horner(a0, 2, 1), fma(a0, 1, 2));
  TTS_EQUAL(reverse_horner(a0, 3, 2, 1), fma(a0, fma(a0, 1, 2), 3));

  TTS_EQUAL(reverse_horner[pedantic](a0, 0), T(0));
  TTS_EQUAL(reverse_horner[pedantic](a0, 1), T(1));
  TTS_EQUAL(reverse_horner[pedantic](a0, 2, 1), fma[pedantic](a0, 1, 2));
  TTS_EQUAL(reverse_horner[pedantic](a0, 3, 2, 1), fma[pedantic](a0, fma[pedantic](a0, 1, 2), 3));


  {
    //============================================================================
    //== tuples
    //============================================================================
    auto tab0 = eve::coefficients{};
    auto tab1 = eve::coefficients{1};
    auto tab2 = eve::coefficients{2, 1};
    auto tab3 = eve::coefficients{3, 2, 1};

    TTS_EQUAL((reverse_horner)(a0, tab0), T(0));
    TTS_EQUAL((reverse_horner)(a0, tab1), T(1));
    TTS_EQUAL((reverse_horner)(a0, tab2), (fma)(a0, 1, 2));
    TTS_EQUAL((reverse_horner)(a0, tab3), (fma)(a0, (fma)(a0, 1, 2), 3));

    TTS_EQUAL(reverse_horner[pedantic](a0, tab0), T(0));
    TTS_EQUAL(reverse_horner[pedantic](a0, tab1), T(1));
    TTS_EQUAL(reverse_horner[pedantic](a0, tab2), (fma)(a0, 1, 2));
    TTS_EQUAL(reverse_horner[pedantic](a0, tab3), (fma)(a0, (fma)(a0, 1, 2), 3));
  }


 };
