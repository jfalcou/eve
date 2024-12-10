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
TTS_CASE_TPL("Check return types of eve::logical_xor(scalar)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  logical_test_scalar_return_type<T>(eve::logical_xor);
};

TTS_CASE_TPL("Check return types of eve::logical_xor(simd)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  logical_test_simd_return_type<T>(eve::logical_xor);
};

//==================================================================================================
//== Tests for eve::logical_xor
//==================================================================================================
TTS_CASE("Check behavior of eve::logical_xor(bool)")
{
  TTS_EQUAL(eve::logical_xor(true, true), false);
  TTS_EQUAL(eve::logical_xor(true, false), true);
  TTS_EQUAL(eve::logical_xor(false, true), true);
  TTS_EQUAL(eve::logical_xor(false, false), false);
};

TTS_CASE_TPL("Check behavior of eve::logical_xor(invalid)", tts::cartesian_square<eve::test::scalar::all_types>)
<typename T, typename U>(tts::type<kumi::tuple<T, U>>)
{
  logical_test_compile_reject<T, U>(eve::logical_xor);
};

TTS_CASE_WITH("Check behavior of eve::logical_xor(logical<wide>)",
              eve::test::simd::all_types,
              tts::generate(tts::logicals(0, 3), tts::logicals(1, 2), tts::randoms(0, 2)))
<typename M, typename T>(M const& l0, [[maybe_unused]] M const& l1, [[maybe_unused]] T const& a0)
{
  using l_t = eve::element_type_t<M>;

  TTS_EQUAL(eve::logical_xor(l0, true), tts::map([](auto e) -> l_t { return !e; }, l0));
  TTS_EQUAL(eve::logical_xor(true, l1), tts::map([](auto e) -> l_t { return !e; }, l1));
  TTS_EQUAL(eve::logical_xor(false, l1), l1);
  TTS_EQUAL(eve::logical_xor(l0, false), l0);

  logical_test_simd<M, T>(eve::logical_xor, [](auto e, auto f) { return e != f; }, l0, l1, a0);
};
