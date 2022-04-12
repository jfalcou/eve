//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/polynomial.hpp>
#include <cmath>
#include <array>
#include <vector>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of reverse_horner on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  TTS_EXPR_IS( eve::reverse_horner(T(), T())  , T);
  TTS_EXPR_IS( eve::reverse_horner(T(), T(), T())  , T);
  TTS_EXPR_IS( eve::reverse_horner(T(), T(), T())  , T);
  TTS_EXPR_IS( eve::reverse_horner(T(), v_t(), v_t())  , T);
  TTS_EXPR_IS( eve::reverse_horner(T(), v_t(), int())  , T);
  TTS_EXPR_IS( eve::reverse_horner(T(), v_t(), i_t())  , T);
  TTS_EXPR_IS( eve::reverse_horner(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
//== reverse_horner tests
//==================================================================================================
EVE_TEST( "Check behavior of reverse_horner on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::ramp(0))
        )
<typename T>(T const& a0)
{
  using eve::reverse_horner;
  using eve::fma;
  using eve::pedantic;
  using eve::numeric;
  using eve::one;
  using v_t = eve::element_type_t<T>;
  //============================================================================
  //== variadic
  //============================================================================

  TTS_EQUAL(reverse_horner(a0, 0), T(0));
  TTS_EQUAL(reverse_horner(a0, 1), T(1));
  TTS_EQUAL(reverse_horner(a0, 2, 1), fma(a0, 1, 2));
  TTS_EQUAL(reverse_horner(a0, 3, 2, 1), fma(a0, fma(a0, 1, 2), 3));

  TTS_EQUAL(pedantic(reverse_horner)(a0, 0), T(0));
  TTS_EQUAL(pedantic(reverse_horner)(a0, 1), T(1));
  TTS_EQUAL(pedantic(reverse_horner)(a0, 2, 1), pedantic(fma)(a0, 1, 2));
  TTS_EQUAL(pedantic(reverse_horner)(a0, 3, 2, 1), pedantic(fma)(a0, pedantic(fma)(a0, 1, 2), 3));

  TTS_EQUAL(numeric(reverse_horner)(a0, 0), T(0));
  TTS_EQUAL(numeric(reverse_horner)(a0, 1), T(1));
  TTS_EQUAL(numeric(reverse_horner)(a0, 2, 1), numeric(fma)(a0, 1, 2));
  TTS_EQUAL(numeric(reverse_horner)(a0, 3, 2, 1), numeric(fma)(a0, numeric(fma)(a0, 1, 2), 3));

  {
    //============================================================================
    //== ranges
    //============================================================================
    std::vector<v_t> tab0; // std does not want array of size 0
    std::array<v_t, 1> tab1 = {1};
    std::array<v_t, 2> tab2 = {2, 1};
    std::array<v_t, 3> tab3 = {3, 2, 1};


    TTS_EQUAL((reverse_horner)(a0, tab0), T(0));
    TTS_EQUAL((reverse_horner)(a0, tab1), T(1));
    TTS_EQUAL((reverse_horner)(a0, tab2), (fma)(a0, 1, 2));
    TTS_EQUAL((reverse_horner)(a0, tab3), (fma)(a0, (fma)(a0, 1, 2), 3));

    TTS_EQUAL(pedantic(reverse_horner)(a0, tab0), T(0));
    TTS_EQUAL(pedantic(reverse_horner)(a0, tab1), T(1));
    TTS_EQUAL(pedantic(reverse_horner)(a0, tab2), (fma)(a0, 1, 2));
    TTS_EQUAL(pedantic(reverse_horner)(a0, tab3), (fma)(a0, (fma)(a0, 1, 2), 3));

    TTS_EQUAL(numeric(reverse_horner)(a0, tab0), T(0));
    TTS_EQUAL(numeric(reverse_horner)(a0, tab1), T(1));
    TTS_EQUAL(numeric(reverse_horner)(a0, tab2), (fma)(a0, 1, 2));
    TTS_EQUAL(numeric(reverse_horner)(a0, tab3), (fma)(a0, (fma)(a0, 1, 2), 3));
  }
};
