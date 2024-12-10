//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "unit/module/core/logical_ops.hpp"

#include <eve/module/core.hpp>

using namespace eve;

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::logical_and(scalar)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  logical_test_scalar_return_type<T>(logical_and);
};

TTS_CASE_TPL("Check return types of eve::logical_and(simd)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  logical_test_simd_return_type<T>(logical_and);
};

//==================================================================================================
//== Tests for eve::logical_and
//==================================================================================================
TTS_CASE("Check behavior of eve::logical_and(bool)")
{
  TTS_EQUAL(logical_and(true, true), true);
  TTS_EQUAL(logical_and(true, false), false);
  TTS_EQUAL(logical_and(false, true), false);
  TTS_EQUAL(logical_and(false, false), false);
};

TTS_CASE_TPL("Check behavior of eve::logical_and(invalid)", tts::cartesian_square<eve::test::scalar::all_types>)
<typename T, typename U>(tts::type<kumi::tuple<T, U>>)
{
  logical_test_compile_reject<T, U>(logical_and);
};

TTS_CASE_WITH("Check behavior of eve::logical_and(logical<wide>)",
              eve::test::simd::all_types,
              tts::generate(tts::logicals(0, 3), tts::logicals(1, 2), tts::randoms(0, 2)))
<typename M, typename T>(M const& l0, [[maybe_unused]] M const& l1, [[maybe_unused]] T const& a0)
{
  TTS_EQUAL(eve::logical_and(l0, true), l0);
  TTS_EQUAL(eve::logical_and(true, l1), l1);
  TTS_EQUAL(eve::logical_and(l0, true), l0);
  TTS_EQUAL(eve::logical_and(l0, false), eve::false_(eve::as<M>()));

  logical_test_simd<M, T>(logical_and, [](auto e, auto f) { return e && f; }, l0, l1, a0);
};
