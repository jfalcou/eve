//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/function/reverse_horner.hpp>
#include <eve/function/numeric/reverse_horner.hpp>
#include <eve/function/pedantic/reverse_horner.hpp>
#include <eve/logical.hpp>
#include <type_traits>
#include <cmath>
#include <array>
#include <vector>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of reverse_horner on wide"
        , eve::test::simd::all_types

        )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
// using i_t = eve::as_integer_t<v_t>;
  TTS_EXPR_IS( eve::reverse_horner(T(), T())  , T);
  TTS_EXPR_IS( eve::reverse_horner(T(), T(), T())  , T);
  TTS_EXPR_IS( eve::reverse_horner(T(), T(), T())  , T);
  TTS_EXPR_IS( eve::reverse_horner(T(), v_t(), v_t())  , T);
//   TTS_EXPR_IS( eve::reverse_horner(T(), v_t(), int())  , T);
//   TTS_EXPR_IS( eve::reverse_horner(T(), v_t(), i_t())  , T);
   TTS_EXPR_IS( eve::reverse_horner(v_t(), v_t(), v_t()), v_t);
//   TTS_EXPR_IS( eve::reverse_horner(T(), eve::one, T())  , T);
//   TTS_EXPR_IS( eve::reverse_horner(T(), eve::one, T(), T())  , T);
//   TTS_EXPR_IS( eve::reverse_horner(T(), eve::one, v_t(), v_t())  , T);
//   TTS_EXPR_IS( eve::reverse_horner(T(), eve::one, v_t(), int())  , T);
//   TTS_EXPR_IS( eve::reverse_horner(T(), eve::one, v_t(), i_t())  , T);
//   TTS_EXPR_IS( eve::reverse_horner(v_t(), eve::one, v_t(), v_t()), v_t);
};

//==================================================================================================
//== reverse_horner tests
//==================================================================================================
EVE_TEST( "Check behavior of reverse_horner on wide"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::ramp(0))
        )
<typename T>(T const& a0)
{
  using eve::reverse_horner;
  using eve::fma;
  using eve::pedantic;
  using eve::numeric;
  using eve::one;
//  using v_t = eve::element_type_t<T>;
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

  //============================================================================
  //== variadic with leading one
  //============================================================================
  TTS_EQUAL(reverse_horner(a0, one), T(1));
  TTS_EQUAL(reverse_horner(a0, one, 2), fma(a0, 1, 2));
  TTS_EQUAL(reverse_horner(a0, one, 3, 2), fma(a0, fma(a0, 1, 2), 3));

  TTS_EQUAL(pedantic(reverse_horner)(a0, 0), T(0));
  TTS_EQUAL(pedantic(reverse_horner)(a0, one), T(1));
  TTS_EQUAL(pedantic(reverse_horner)(a0, one, 2), pedantic(fma)(a0, 1, 2));
  TTS_EQUAL(pedantic(reverse_horner)(a0, one, 3, 2), pedantic(fma)(a0, pedantic(fma)(a0, 1, 2), 3));

  TTS_EQUAL(numeric(reverse_horner)(a0, 0), T(0));
  TTS_EQUAL(numeric(reverse_horner)(a0, one), T(1));
  TTS_EQUAL(numeric(reverse_horner)(a0, one, 2), numeric(fma)(a0, 1, 2));
  TTS_EQUAL(numeric(reverse_horner)(a0, one, 3, 2), numeric(fma)(a0, numeric(fma)(a0, 1, 2), 3));

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
  {
    //============================================================================
    //== ranges + leading coefficient one
    //============================================================================
    std::vector<v_t> tab1 = {};// std does not want array of size 0
    std::array<v_t, 1> tab2 = {2};
    std::array<v_t, 2> tab3 = {3, 2};

    TTS_EQUAL((reverse_horner)(a0, one, tab1), T(1));
    TTS_EQUAL((reverse_horner)(a0, one, tab2), (fma)(a0, 1, 2));
    TTS_EQUAL((reverse_horner)(a0, one, tab3), (fma)(a0, (fma)(a0, 1, 2), 3));

    TTS_EQUAL(numeric(reverse_horner)(a0, one, tab1), T(1));
    TTS_EQUAL(numeric(reverse_horner)(a0, one, tab2), (fma)(a0, 1, 2));
    TTS_EQUAL(numeric(reverse_horner)(a0, one, tab3), (fma)(a0, (fma)(a0, 1, 2), 3));

    TTS_EQUAL(pedantic(reverse_horner)(a0, one, tab1), T(1));
    TTS_EQUAL(pedantic(reverse_horner)(a0, one, tab2), (fma)(a0, 1, 2));
    TTS_EQUAL(pedantic(reverse_horner)(a0, one, tab3), (fma)(a0, (fma)(a0, 1, 2), 3));

    TTS_EQUAL(reverse_horner(a0, one), T(1));
    TTS_EQUAL(reverse_horner(a0, one, 2), fma(a0, 1, 2));
    TTS_EQUAL(reverse_horner(a0, one, 2, 3), fma(a0, fma(a0, 1, 2), 3));

    TTS_EQUAL(pedantic(reverse_horner)(a0, one), T(1));
    TTS_EQUAL(pedantic(reverse_horner)(a0, one, 2), pedantic(fma)(a0, 1, 2));
    TTS_EQUAL(pedantic(reverse_horner)(a0, one, 2, 3), pedantic(fma)(a0, pedantic(fma)(a0, 1, 2), 3));

    TTS_EQUAL(numeric(reverse_horner)(a0, one), T(1));
    TTS_EQUAL(numeric(reverse_horner)(a0, one, 2), numeric(fma)(a0, 1, 2));
    TTS_EQUAL(numeric(reverse_horner)(a0, one, 2, 3), numeric(fma)(a0, numeric(fma)(a0, 1, 2), 3));

  }
  {
    //============================================================================
    //== iterators
    //============================================================================
    std::vector<v_t> tab0; // std does not want array of size 0
    std::array<v_t, 1> tab1 = {1};
    std::array<v_t, 2> tab2 = {2, 1};
    std::array<v_t, 3> tab3 = {3, 2, 1};

    TTS_EQUAL((reverse_horner)(a0, &tab0[0], &tab0[0]), T(0));
    TTS_EQUAL((reverse_horner)(a0, &tab1[0], &tab1[1]), T(1));
    TTS_EQUAL((reverse_horner)(a0, &tab2[0], &tab2[2]), (fma)(a0, 1, 2));
    TTS_EQUAL((reverse_horner)(a0, tab3.begin(), tab3.end()), (fma)(a0, (fma)(a0, 1, 2), 3));

    TTS_EQUAL(pedantic(reverse_horner)(a0, &tab0[0], &tab0[0]), T(0));
    TTS_EQUAL(pedantic(reverse_horner)(a0, &tab1[0], &tab1[1]), T(1));
    TTS_EQUAL(pedantic(reverse_horner)(a0, &tab2[0], &tab2[2]), (fma)(a0, 1, 2));
    TTS_EQUAL(pedantic(reverse_horner)(a0, tab3.begin(), tab3.end()), (fma)(a0, (fma)(a0, 1, 2), 3));

    TTS_EQUAL(numeric(reverse_horner)(a0, &tab0[0], &tab0[0]), T(0));
    TTS_EQUAL(numeric(reverse_horner)(a0, &tab1[0], &tab1[1]), T(1));
    TTS_EQUAL(numeric(reverse_horner)(a0, &tab2[0], &tab2[2]), (fma)(a0, 1, 2));
    TTS_EQUAL(numeric(reverse_horner)(a0, tab3.begin(), tab3.end()), (fma)(a0, (fma)(a0, 1, 2), 3));
  }
  {
    //============================================================================
    //== iterators with leading one
    //============================================================================
    std::vector<v_t> tab1 = {};// std does not want array of size 0
    std::array<v_t, 1> tab2 = {2};
    std::array<v_t, 2> tab3 = {3, 2};


    TTS_EQUAL((reverse_horner)(a0, one, &tab1[0], &tab1[0]), T(1));
    TTS_EQUAL((reverse_horner)(a0, one, &tab2[0], &tab2[1]), (fma)(a0, 1, 2));
    TTS_EQUAL((reverse_horner)(a0, one, tab3.begin(), tab3.end()), (fma)(a0, (fma)(a0, 1, 2), 3));

    TTS_EQUAL(pedantic(reverse_horner)(a0, one, &tab1[0], &tab1[0]), T(1));
    TTS_EQUAL(pedantic(reverse_horner)(a0, one, &tab2[0], &tab2[1]), (fma)(a0, 1, 2));
    TTS_EQUAL(pedantic(reverse_horner)(a0, one, tab3.begin(), tab3.end()), (fma)(a0, (fma)(a0, 1, 2), 3));

    TTS_EQUAL(numeric(reverse_horner)(a0, one, &tab1[0], &tab1[0]), T(1));
    TTS_EQUAL(numeric(reverse_horner)(a0, one, &tab2[0], &tab2[1]), (fma)(a0, 1, 2));
    TTS_EQUAL(numeric(reverse_horner)(a0, one, tab3.begin(), tab3.end()), (fma)(a0, (fma)(a0, 1, 2), 3));

  }

};
