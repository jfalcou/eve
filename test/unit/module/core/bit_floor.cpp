//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <bit>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of bit_floor on unsigned wide", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::bit_floor(T()), T);
  TTS_EXPR_IS(eve::bit_floor(v_t()), v_t);
};

//==================================================================================================
// bit_floor simd tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of bit_floor(wide) on unsigned integral types",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::randoms(0, +50), tts::logicals(0, 3)))
<typename T, typename U>(T const& a0, U const& t)
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::bit_floor(a0), map([](auto e) { return v_t(std::bit_floor(e)); }, a0));
  TTS_EQUAL(eve::bit_floor[t](a0), eve::if_else(t, eve::bit_floor(a0), a0));
};
