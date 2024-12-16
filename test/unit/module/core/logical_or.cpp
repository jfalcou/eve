//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "unit/module/core/logical_test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::logical_or(scalar)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  logical_test_scalar_return_type<T>(logical_or);
};

TTS_CASE_TPL("Check return types of eve::logical_or(simd)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  logical_test_simd_return_type<T>(logical_or);
};

//==================================================================================================
//== Tests for eve::logical_or
//==================================================================================================
TTS_CASE("Check behavior of eve::logical_or(bool)")
{
  TTS_EQUAL(logical_or(true, true), true);
  TTS_EQUAL(logical_or(true, false), true);
  TTS_EQUAL(logical_or(false, true), true);
  TTS_EQUAL(logical_or(false, false), false);
};

TTS_CASE_TPL("Check behavior of eve::logical_or(invalid)", tts::cartesian_square<eve::test::scalar::all_types>)
<typename T, typename U>(tts::type<kumi::tuple<T, U>>)
{
  logical_test_compile_reject<T, U>(logical_or);
};

TTS_CASE_WITH("Check behavior of eve::logical_or(simd)",
              eve::test::simd::all_types,
              tts::generate(tts::logicals(0, 3), tts::logicals(1, 2), tts::randoms(0, 2)))
<typename M, typename T>(M const& l0, M const& l1, T const& a0)
{
  TTS_EQUAL(eve::logical_or(l0, true), eve::true_(eve::as<M>()));
  TTS_EQUAL(eve::logical_or(true, l1), eve::true_(eve::as<M>()));
  TTS_EQUAL(eve::logical_or(false, l1), l1);
  TTS_EQUAL(eve::logical_or(l0, false), l0);

  logical_test_simd<M, T>(logical_or, [](auto e, auto f) { return e || f; }, l0, l1, a0);
};
