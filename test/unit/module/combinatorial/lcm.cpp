//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/combinatorial.hpp>
#include <cmath>



//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::lcm"
              , eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  TTS_EXPR_IS(eve::lcm(T(), T()), T);
};


EVE_TEST( "Check corner-cases behavior of eve::lcm on wide"
        , eve::test::simd::integers
        , eve::test::generate ( eve::test::randoms(1, eve::sqrtvalmax)
                              , eve::test::randoms(1, eve::sqrtvalmax)
                              )
         )
  <typename T>(const T & a0,  const T & a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::lcm(a0, a1)      , map([](auto e, auto f) -> v_t { return std::lcm(e, f); }, a0, a1) );
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
EVE_TEST_TYPES( "Check  behavior of eve::lcm on wide peculiar cases"
        , eve::test::simd::all_types

         )
  <typename T>(eve::as<T>)
{
  using eve::as;
  using eve::lcm;

  TTS_EQUAL(eve::lcm(T(22), T( 10)) , T(110));
  TTS_EQUAL(eve::lcm(T(7), T( 5)) , T(35));
  TTS_EQUAL(eve::lcm(T(0), T(1)), T(std::lcm((0), (1))) );
  TTS_EQUAL(eve::lcm(T(1), T(0)), T(std::lcm((1), (0))) );
};
