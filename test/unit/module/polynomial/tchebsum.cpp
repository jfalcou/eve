//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/polynomial.hpp>

#include <array>
#include <vector>
#include <span>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of tchebsum on wide", eve::test::simd::ieee_reals_wf16)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  TTS_EXPR_IS(eve::tchebsum(T(), T()), T);
  TTS_EXPR_IS(eve::tchebsum(T(), T(), T()), T);
  TTS_EXPR_IS(eve::tchebsum(T(), T(), T()), T);
  TTS_EXPR_IS(eve::tchebsum(T(), v_t(), v_t()), T);
  TTS_EXPR_IS(eve::tchebsum(T(), v_t(), int()), T);
  TTS_EXPR_IS(eve::tchebsum(T(), v_t(), i_t()), T);
  TTS_EXPR_IS(eve::tchebsum(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
//== tchebsum tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of tchebsum on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-3.0, 3.0))
             )
<typename T>(T const& a0)
{
  using eve::tchebsum;
  using eve::pedantic;
  using eve::widen;

  {
    auto t2 = 2*eve::sqr(a0)-1;

    TTS_EQUAL(tchebsum(a0, T(0)), T(0));
    TTS_EQUAL(tchebsum(a0, T(1)), T(0.5));
    TTS_EQUAL(tchebsum(a0, T(1), T(2)), T(0.5)+T(2)*a0);
    TTS_ULP_EQUAL(tchebsum(a0, T(1), T(2), T(3)), T(0.5)+T(2)*a0+T(3)*t2, 0.5);

    TTS_EQUAL(tchebsum[pedantic](a0, 0), T(0));
    TTS_EQUAL(tchebsum[pedantic](a0, 1), T(0.5));
    TTS_EQUAL(tchebsum[pedantic](a0, 1, 2),  T(0.5)+T(2)*a0);
    TTS_ULP_EQUAL(tchebsum[pedantic](a0, T(1), T(2), T(3)), T(0.5)+T(2)*a0+T(3)*t2, 2.0);
    TTS_ULP_EQUAL(tchebsum[widen](a0, T(1), T(2), T(3)), tchebsum(upgrade(a0), upgrade(T(1)), upgrade(T(2)), upgrade(T(3))), 0.5);
  }

  //============================================================================
  //== tuples
  //============================================================================
  auto tab0 = eve::coefficients{};
  auto tab1 = eve::coefficients{1};
  auto tab2 = eve::coefficients{1, 2};
  auto tab3 = eve::coefficients{1, 2, 3};

  TTS_EQUAL(tchebsum(a0, tab0), T(0));
  TTS_EQUAL(tchebsum(a0, tab1), T(0.5));
  TTS_EQUAL(tchebsum(a0, tab2), tchebsum(a0, 1, 2));
  TTS_EQUAL(tchebsum(a0, tab3), tchebsum(a0, 1, 2, 3));

  TTS_EQUAL(tchebsum[pedantic](a0, tab0), T(0));
  TTS_EQUAL(tchebsum[pedantic](a0, tab1), T(0.5));
  TTS_EQUAL(tchebsum[pedantic](a0, tab2), tchebsum[pedantic](a0, 1, 2));
  TTS_EQUAL(tchebsum[pedantic](a0, tab3), tchebsum[pedantic](a0, 1, 2, 3));
  TTS_ULP_EQUAL(tchebsum[widen](a0, tab3), tchebsum(upgrade(a0), upgrade(T(1)), upgrade(T(2)), upgrade(T(3))), 0.5);

  //============================================================================
  //== ranges
  //============================================================================
  {
    using v_t = std::vector<T>;
    auto vec1 = v_t{T(1)};
    auto vec2 = v_t{T(1), T(2)};
    auto vec3 = v_t{T(1), T(2), T(3)};

    TTS_EQUAL(tchebsum(a0, vec1), T(0.5));
    TTS_EQUAL(tchebsum(a0, vec2), tchebsum(a0, 1, 2));
    TTS_EQUAL(tchebsum(a0, vec3), tchebsum(a0, 1, 2, 3));

    TTS_EQUAL(tchebsum[pedantic](a0, vec1), T(0.5));
    TTS_EQUAL(tchebsum[pedantic](a0, vec2), tchebsum[pedantic](a0, 1, 2));
    TTS_EQUAL(tchebsum[pedantic](a0, vec3), tchebsum[pedantic](a0, 1, 2, 3));
    TTS_ULP_EQUAL(tchebsum[widen](a0, vec3), tchebsum(upgrade(a0), upgrade(T(1)), upgrade(T(2)), upgrade(T(3))), 0.5);
  }
  {
    auto arr1 = std::array<T,1>{T(1)};
    auto arr2 = std::array<T,2>{T(1), T(2)};
    auto arr3 = std::array<T,3>{T(1), T(2), T(3)};

    TTS_EQUAL(tchebsum(a0, arr1), T(0.5));
    TTS_EQUAL(tchebsum(a0, arr2), tchebsum(a0, 1, 2));
    TTS_EQUAL(tchebsum(a0, arr3), tchebsum(a0, 1, 2, 3));

    TTS_EQUAL(tchebsum[pedantic](a0, arr1),  T(0.5));
    TTS_EQUAL(tchebsum[pedantic](a0, arr2),  tchebsum[pedantic](a0, 1, 2));
    TTS_EQUAL(tchebsum[pedantic](a0, arr3),  tchebsum[pedantic](a0, 1, 2, 3));
    TTS_ULP_EQUAL(tchebsum[widen](a0, arr3), tchebsum(upgrade(a0), upgrade(T(1)), upgrade(T(2)), upgrade(T(3))), 0.5);
  }
  {
    auto arr1 = std::array<T,1>{T(1)};
    auto arr2 = std::array<T,2>{T(1), T(2)};
    auto arr3 = std::array<T,3>{T(1), T(2), T(3)};

    TTS_EQUAL(tchebsum(a0, std::span(arr1)),  T(0.5));
    TTS_EQUAL(tchebsum(a0, std::span(arr2)),  tchebsum(a0, 1, 2));
    TTS_EQUAL(tchebsum(a0, std::span(arr3)),  tchebsum(a0, 1, 2, 3));

    TTS_EQUAL(tchebsum[pedantic](a0, std::span(arr1)),  T(0.5));
    TTS_EQUAL(tchebsum[pedantic](a0, std::span(arr2)),  tchebsum[pedantic](a0, 1, 2));
    TTS_EQUAL(tchebsum[pedantic](a0, std::span(arr3)),  tchebsum[pedantic](a0, 1, 2, 3));
    TTS_ULP_EQUAL(tchebsum[widen](a0, std::span(arr3)), tchebsum(upgrade(a0), upgrade(T(1)), upgrade(T(2)), upgrade(T(3))), 0.5);
  }

};
