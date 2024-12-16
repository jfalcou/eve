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

using namespace eve;

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::logical_notand(scalar)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  logical_test_scalar_return_type<T>(eve::logical_notand);
};

TTS_CASE_TPL("Check return types of eve::logical_notand(simd)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  logical_test_simd_return_type<T>(eve::logical_notand);
};

//==================================================================================================
//== Tests for eve::logical_notand
//==================================================================================================
TTS_CASE("Check behavior of eve::logical_notand(bool)")
{
  TTS_EQUAL(eve::logical_notand(true, true), false);
  TTS_EQUAL(eve::logical_notand(true, false), false);
  TTS_EQUAL(eve::logical_notand(false, true), true);
  TTS_EQUAL(eve::logical_notand(false, false), false);
};

TTS_CASE_TPL("Check behavior of eve::logical_notand(invalid)", tts::cartesian_square<eve::test::scalar::all_types>)
<typename T, typename U>(tts::type<kumi::tuple<T, U>>)
{
  logical_test_compile_reject<T, U>(eve::logical_notand);
};

TTS_CASE_WITH("Check behavior of eve::logical_notand(logical<wide>)",
              eve::test::simd::all_types,
              tts::generate(tts::logicals(0, 3), tts::logicals(1, 2), tts::randoms(0, 2)))
<typename M, typename T>(M const& l0, [[maybe_unused]] M const& l1, [[maybe_unused]] T const& a0)
{
  using l_t = eve::element_type_t<M>;

  TTS_EQUAL(eve::logical_notand(l0, true), tts::map([](auto e) -> l_t { return !e; }, l0));
  TTS_EQUAL(eve::logical_notand(true, l1), eve::false_(eve::as<M>()));
  TTS_EQUAL(eve::logical_notand(false, l1), l1);
  TTS_EQUAL(eve::logical_notand(l0, false), eve::false_(eve::as<M>()));

  logical_test_simd<M, T>(eve::logical_notand, [](auto e, auto f) { return !e && f; }, l0, l1, a0);
};
