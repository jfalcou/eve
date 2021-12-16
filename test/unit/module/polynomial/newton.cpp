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
#include <eve/function/newton.hpp>
#include <eve/function/numeric/newton.hpp>
#include <eve/function/pedantic/newton.hpp>
#include <eve/logical.hpp>
#include <type_traits>
#include <cmath>
#include <list>
#include <vector>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of newton on wide"
        , eve::test::simd::all_types

        )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using rv_t = std::vector<v_t>;
  using rl_t = std::list<v_t>;
  TTS_EXPR_IS( eve::newton(T(), rv_t(), rv_t())  , T);
  TTS_EXPR_IS( eve::newton(T(), rv_t(), rl_t())  , T);
  TTS_EXPR_IS( eve::newton(T(), rl_t(), rl_t())  , T);

  TTS_EXPR_IS( eve::newton(T(), std::begin(rv_t()), std::end(rv_t()), std::begin(rv_t())), T);
};

//==================================================================================================
//== newton tests
//==================================================================================================
EVE_TEST( "Check behavior of newton on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::ramp(0))
        )
<typename T>(T const& a0)
{
  using eve::newton;
  using eve::fma;
  using eve::pedantic;
  using eve::numeric;
  using eve::one;
  using v_t = eve::element_type_t<T>;
  {
    //============================================================================
    //== ranges
    //============================================================================
    std::vector<v_t> tab0; // std does not want array of size 0
    std::array<v_t, 1> tab1 = {1};
    std::array<v_t, 2> tab2 = {1, 2};
    std::array<v_t, 3> tab3 = {1, 2, 3};


    TTS_EQUAL((newton)(a0, tab0, tab0), T(0));
    TTS_EQUAL((newton)(a0, tab1, tab0), T(1));
    TTS_EQUAL((newton)(a0, tab2, tab1), (fma)(a0-1, 1, 2));
    TTS_EQUAL((newton)(a0, tab3, tab2), (fma)(a0-2, (fma)(a0-1, 1, 2), 3));

    TTS_EQUAL(pedantic(newton)(a0, tab0, tab0), T(0));
    TTS_EQUAL(pedantic(newton)(a0, tab1, tab0), T(1));
    TTS_EQUAL(pedantic(newton)(a0, tab2, tab1), (fma)(a0-1, 1, 2));
    TTS_EQUAL(pedantic(newton)(a0, tab3, tab2), (fma)(a0-2, (fma)(a0-1, 1, 2), 3));

    TTS_EQUAL(numeric(newton)(a0, tab0, tab0), T(0));
    TTS_EQUAL(numeric(newton)(a0, tab1, tab0), T(1));
    TTS_EQUAL(numeric(newton)(a0, tab2, tab1), (fma)(a0-1, 1, 2));
    TTS_EQUAL(numeric(newton)(a0, tab3, tab2), (fma)(a0-2, (fma)(a0-1, 1, 2), 3));
  }
  {
    //============================================================================
    //== iterators
    //============================================================================
    std::vector<v_t> tab0; // std does not want array of size 0
    std::array<v_t, 1> tab1 = {1};
    std::array<v_t, 2> tab2 = {1, 2};
    std::array<v_t, 3> tab3 = {1, 2, 3};

    TTS_EQUAL((newton)(a0, &tab0[0], &tab0[0], &tab0[0]), T(0));
    TTS_EQUAL((newton)(a0, &tab1[0], &tab1[1], &tab0[0]), T(1));
    TTS_EQUAL((newton)(a0, &tab2[0], &tab2[2], &tab1[0]), (fma)(a0-1, 1, 2));
    TTS_EQUAL((newton)(a0, tab3.begin(), tab3.end(), tab2.begin()), (fma)(a0-2, (fma)(a0-1, 1, 2), 3));

    TTS_EQUAL(pedantic(newton)(a0, &tab0[0], &tab0[0], &tab0[0]), T(0));
    TTS_EQUAL(pedantic(newton)(a0, &tab1[0], &tab1[1], &tab0[0]), T(1));
    TTS_EQUAL(pedantic(newton)(a0, &tab2[0], &tab2[2], &tab1[0]), (fma)(a0-1, 1, 2));
    TTS_EQUAL(pedantic(newton)(a0, tab3.begin(), tab3.end(), tab2.begin()), (fma)(a0-2, (fma)(a0-1, 1, 2), 3));

    TTS_EQUAL(numeric(newton)(a0, &tab0[0], &tab0[0], &tab0[0]), T(0));
    TTS_EQUAL(numeric(newton)(a0, &tab1[0], &tab1[1], &tab0[0]), T(1));
    TTS_EQUAL(numeric(newton)(a0, &tab2[0], &tab2[2], &tab1[0]), (fma)(a0-1, 1, 2));
    TTS_EQUAL(numeric(newton)(a0, tab3.begin(), tab3.end(), tab2.begin()), (fma)(a0-2, (fma)(a0-1, 1, 2), 3));
  }
};


//==================================================================================================
//== newton(scalar) tests
//==================================================================================================
EVE_TEST( "Check behavior of newton on scalar"
        , eve::test::scalar::all_types
        , eve::test::generate(eve::test::randoms(0, 127))
        )
<typename T>(T const& a)
{
  using eve::newton;
  using eve::fma;
  using eve::pedantic;
  using eve::numeric;
  using eve::one;
  using v_t = typename T::value_type;
  for( auto a0 :a)
  {
    {
      //============================================================================
      //== ranges
      //============================================================================
      std::vector<v_t> tab0; // std does not want array of size 0
      std::array<v_t, 1> tab1 = {1};
      std::array<v_t, 2> tab2 = {1, 2};
      std::array<v_t, 3> tab3 = {1, 2, 3};


      TTS_EQUAL((newton)(a0, tab0, tab0), v_t(0));
      TTS_EQUAL((newton)(a0, tab1, tab0), v_t(1));
      TTS_EQUAL((newton)(a0, tab2, tab1), (fma)(v_t(a0-1), v_t(1), v_t(2)));
      TTS_EQUAL((newton)(a0, tab3, tab2), (fma)(v_t(a0-2), (fma)(v_t(a0-1), v_t(1), v_t(2)), v_t(3)));

      TTS_EQUAL(pedantic(newton)(a0, tab0, tab0), v_t(0));
      TTS_EQUAL(pedantic(newton)(a0, tab1, tab0), v_t(1));
      TTS_EQUAL(pedantic(newton)(a0, tab2, tab1), (fma)(v_t(a0-1), v_t(1), v_t(2)));
      TTS_EQUAL(pedantic(newton)(a0, tab3, tab2), (fma)(v_t(a0-2), (fma)(v_t(a0-1), v_t(1), v_t(2)), v_t(3)));

      TTS_EQUAL(numeric(newton)(a0, tab0, tab0), v_t(0));
      TTS_EQUAL(numeric(newton)(a0, tab1, tab0), v_t(1));
      TTS_EQUAL(numeric(newton)(a0, tab2, tab1), (fma)(v_t(a0-1), v_t(1), v_t(2)));
      TTS_EQUAL(numeric(newton)(a0, tab3, tab2), (fma)(v_t(a0-2), (fma)(v_t(a0-1), v_t(1), v_t(2)), v_t(3)));
    }
    {
      //============================================================================
      //== iterators
      //============================================================================
      std::vector<v_t> tab0; // std does not want array of size 0
      std::array<v_t, 1> tab1 = {v_t(1)};
      std::array<v_t, 2> tab2 = {v_t(1), v_t(2)};
      std::array<v_t, 3> tab3 = {v_t(1), v_t(2), v_t(3)};

      TTS_EQUAL((newton)(a0, &tab0[0], &tab0[0], &tab0[0]), v_t(0));
      TTS_EQUAL((newton)(a0, &tab1[0], &tab1[1], &tab1[0]), v_t(1));
      TTS_EQUAL((newton)(a0, &tab2[0], &tab2[2], &tab2[0]), (fma)(v_t(a0-1), v_t(1), v_t(2)));
      TTS_EQUAL((newton)(a0, tab3.begin(), tab3.end(), tab2.begin()), (fma)(v_t(a0-2), (fma)(v_t(a0-1), v_t(1), v_t(2)), v_t(3)));

      TTS_EQUAL(pedantic(newton)(a0, &tab0[0], &tab0[0], &tab0[0]), v_t(0));
      TTS_EQUAL(pedantic(newton)(a0, &tab1[0], &tab1[1], &tab1[0]), v_t(1));
      TTS_EQUAL(pedantic(newton)(a0, &tab2[0], &tab2[2], &tab2[0]), (fma)(v_t(a0-1), v_t(1), v_t(2)));
      TTS_EQUAL(pedantic(newton)(a0, tab3.begin(), tab3.end(), tab2.begin()), (fma)(v_t(a0-2), (fma)(v_t(a0-1), v_t(1), v_t(2)), v_t(3)));

      TTS_EQUAL(numeric(newton)(a0, &tab0[0], &tab0[0], &tab0[0]), v_t(0));
      TTS_EQUAL(numeric(newton)(a0, &tab1[0], &tab1[1], &tab1[0]), v_t(1));
      TTS_EQUAL(numeric(newton)(a0, &tab2[0], &tab2[2], &tab2[0]), (fma)(v_t(a0-1), v_t(1), v_t(2)));
      TTS_EQUAL(numeric(newton)(a0, tab3.begin(), tab3.end(), tab2.begin()), (fma)(v_t(a0-2), (fma)(v_t(a0-1), v_t(1), v_t(2)), v_t(3)));
    }
  }
};
