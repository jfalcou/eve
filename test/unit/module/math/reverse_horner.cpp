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

#include <array>
#include <vector>
#include <span>

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
    auto tab1 = eve::coefficients{1};
    auto tab2 = eve::coefficients{2, 1};
    auto tab3 = eve::coefficients{3, 2, 1};

    TTS_EQUAL((reverse_horner)(a0, tab1), T(1));
    TTS_EQUAL((reverse_horner)(a0, tab2), (fma)(a0, 1, 2));
    TTS_EQUAL((reverse_horner)(a0, tab3), (fma)(a0, (fma)(a0, 1, 2), 3));


    TTS_EQUAL(reverse_horner[pedantic](a0, tab1), T(1));
    TTS_EQUAL(reverse_horner[pedantic](a0, tab2), (fma)(a0, 1, 2));
    TTS_EQUAL(reverse_horner[pedantic](a0, tab3), (fma)(a0, (fma)(a0, 1, 2), 3));
  }


  //============================================================================
  //== ranges
  //============================================================================
  {
    using v_t = std::vector<T>;
    auto vec1 = v_t{T(1)};
    auto vec2 = v_t{T(2), T(1)};
    auto vec3 = v_t{T(3), T(2), T(1)};

    TTS_EQUAL(reverse_horner(a0, vec1), T(1));
    TTS_EQUAL(reverse_horner(a0, vec2), fma(a0, 1, 2));
    TTS_EQUAL(reverse_horner(a0, vec3), fma(a0, fma(a0, 1, 2), 3));

    TTS_EQUAL(reverse_horner[pedantic](a0, vec1), T(1));
    TTS_EQUAL(reverse_horner[pedantic](a0, vec2), fma[pedantic](a0, 1, 2));
    TTS_EQUAL(reverse_horner[pedantic](a0, vec3), fma[pedantic](a0, fma[pedantic](a0, 1, 2), 3));
  }
  {
    auto arr1 = std::array<T,1>{T(1)};
    auto arr2 = std::array<T,2>{T(2), T(1)};
    auto arr3 = std::array<T,3>{T(3), T(2), T(1)};

    TTS_EQUAL(reverse_horner(a0, arr1), T(1));
    TTS_EQUAL(reverse_horner(a0, arr2), fma(a0, 1, 2));
    TTS_EQUAL(reverse_horner(a0, arr3), fma(a0, fma(a0, 1, 2), 3));

    TTS_EQUAL(reverse_horner[pedantic](a0, arr1), T(1));
    TTS_EQUAL(reverse_horner[pedantic](a0, arr2), fma[pedantic](a0, 1, 2));
    TTS_EQUAL(reverse_horner[pedantic](a0, arr3), fma[pedantic](a0, fma[pedantic](a0, 1, 2), 3));
  }
  {
    auto arr1 = std::array<T,1>{T(1)};
    auto arr2 = std::array<T,2>{T(2), T(1)};
    auto arr3 = std::array<T,3>{T(3), T(2), T(1)};

    TTS_EQUAL(reverse_horner(a0, std::span(arr1)), T(1));
    TTS_EQUAL(reverse_horner(a0, std::span(arr2)), fma(a0, 1, 2));
    TTS_EQUAL(reverse_horner(a0, std::span(arr3)), fma(a0, fma(a0, 1, 2), 3));

    TTS_EQUAL(reverse_horner[pedantic](a0, std::span(arr1)), T(1));
    TTS_EQUAL(reverse_horner[pedantic](a0, std::span(arr2)), fma[pedantic](a0, 1, 2));
    TTS_EQUAL(reverse_horner[pedantic](a0, std::span(arr3)), fma[pedantic](a0, fma[pedantic](a0, 1, 2), 3));
  }
 };
