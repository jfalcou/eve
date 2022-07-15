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
TTS_CASE_TPL("Check return types of eve::gcd", eve::test::simd::all_types)
<typename T>(tts::type<T>) { TTS_EXPR_IS(eve::gcd(T(), T()), T); };

auto mini = tts::constant([]<typename T>(eve::as<T> const&)
                          { return eve::inc(eve::valmin(eve::as<T>())); });

TTS_CASE_WITH("Check corner-cases behavior of eve::gcd on wide",
              eve::test::simd::integers,
              tts::generate(tts::randoms(mini, eve::valmax), tts::randoms(mini, eve::valmax)))
<typename T>(const T& a0, const T& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::gcd(a0, a1), map([](auto e, auto f) -> v_t { return std::gcd(e, f); }, a0, a1));
};

//==================================================================================================
//=== Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL("Check  behavior of eve::gcd on wide peculiar cases", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::gcd;

  TTS_ULP_EQUAL(gcd(T(10), T(5)), T(5), 0);
  TTS_ULP_EQUAL(gcd(T(6), T(2)), T(2), 0);
  TTS_ULP_EQUAL(gcd(T(36), T(45)), T(9), 0);
  TTS_ULP_EQUAL(gcd(T(1), T(0)), T(1), 0);
  TTS_ULP_EQUAL(gcd(T(0), T(0)), T(0), 0);
  TTS_ULP_EQUAL(gcd(T(0), T(1)), T(1), 0);
};
