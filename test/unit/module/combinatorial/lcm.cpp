//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/combinatorial.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::lcm", eve::test::simd::all_types)
<typename T>(tts::type<T>) { TTS_EXPR_IS(eve::lcm(T(), T()), T); };

auto maxi = tts::constant([]<typename T>(eve::as<T> const&)
                          { return eve::min(eve::valmax(eve::as<T>()), T(10000)); });

TTS_CASE_WITH("Check corner-cases behavior of eve::lcm on wide",
              eve::test::simd::integers,
              tts::generate(tts::randoms(1, maxi), tts::randoms(1, maxi)))
<typename T>(const T& a0, const T& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::lcm(a0, a1), map([](auto e, auto f) -> v_t { return std::lcm(e, f); }, a0, a1));
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL("Check  behavior of eve::lcm on wide peculiar cases", eve::test::simd::all_types

)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::lcm;

  TTS_EQUAL(eve::lcm(T(22), T(10)), T(110));
  TTS_EQUAL(eve::lcm(T(7), T(5)), T(35));
  TTS_EQUAL(eve::lcm(T(0), T(1)), T(std::lcm((0), (1))));
  TTS_EQUAL(eve::lcm(T(1), T(0)), T(std::lcm((1), (0))));
};
