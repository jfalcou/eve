//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/gcd.hpp>
#include <eve/logical.hpp>
#include <cmath>



//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::gcd"
              , eve::test::simd::all_types)
<typename T>(eve::as_<T>)
{
  TTS_EXPR_IS(eve::gcd(T(), T()), T);
};

auto mini = []< typename T>(eve::as_<T> const &){return eve::valmin(eve::as<T>())+1; };

EVE_TEST( "Check corner-cases behavior of eve::gcd on wide"
        , eve::test::simd::integers
        , eve::test::generate ( eve::test::randoms(mini, eve::valmax)
                              , eve::test::randoms(mini, eve::valmax)
                              )
         )
  <typename T>(const T & a0,  const T & a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::gcd(a0, a1)      , map([](auto e, auto f) -> v_t { return std::gcd(e, f); }, a0, a1) );
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
EVE_TEST_TYPES( "Check  behavior of eve::gcd on wide peculiar cases"
        , eve::test::simd::all_types

         )
  <typename T>(eve::as_<T>)
{
  using eve::as;
  using eve::gcd;

  if constexpr( eve::floating_value<T> )
  {
    TTS_ULP_EQUAL(gcd(T(2), eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(gcd(T(2), eve::inf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(gcd(T(3), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(gcd(T(3.3), T(2)),  eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::to_nearest(gcd)(T(3.6), T(2)),  T(2), 0);
    TTS_ULP_EQUAL(eve::downward(gcd)(T(3.6), T(2)), T(1), 0);
  }

  TTS_ULP_EQUAL(gcd(T(10), T(5)), T(5), 0);
  TTS_ULP_EQUAL(gcd(T(6), T(2)), T(2), 0);
  TTS_ULP_EQUAL(gcd(T(36), T(45)), T(9), 0);
  TTS_ULP_EQUAL(gcd(T(1), T(0)), T(1), 0);
  TTS_ULP_EQUAL(gcd(T(0), T(0)), T(0), 0);
  TTS_ULP_EQUAL(gcd(T(0), T(1)), T(1), 0);
};
