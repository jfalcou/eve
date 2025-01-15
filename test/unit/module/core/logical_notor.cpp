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
TTS_CASE_TPL("Check return types of eve::logical_notor(scalar)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  logical_test_scalar_return_type<T>(eve::logical_notor);
};

TTS_CASE_TPL("Check return types of eve::logical_notor(simd)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  logical_test_simd_return_type<T>(eve::logical_notor);
};

//==================================================================================================
//== Tests for eve::logical_notor
//==================================================================================================
TTS_CASE("Check behavior of eve::logical_notor(bool)")
{
  TTS_EQUAL(eve::logical_notor(true, true), true);
  TTS_EQUAL(eve::logical_notor(true, false), false);
  TTS_EQUAL(eve::logical_notor(false, true), true);
  TTS_EQUAL(eve::logical_notor(false, false), true);
};

TTS_CASE_TPL("Check behavior of eve::logical_or(invalid)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  logical_test_compile_reject<T>(eve::logical_notor);
};

TTS_CASE_WITH("Check behavior of eve::logical_notor(simd)",
              eve::test::simd::all_types,
              tts::generate(tts::logicals(0, 3), tts::logicals(1, 2), tts::randoms(0, 2)))
<typename M, typename T>(M const& l0, M const& l1, T const& a0)
{
  using l_t = eve::element_type_t<M>;

  TTS_EQUAL(eve::logical_notor(l0, true), eve::true_(eve::as<M>()));
  TTS_EQUAL(eve::logical_notor(true, l1), l1);
  TTS_EQUAL(eve::logical_notor(false, l1), eve::true_(eve::as<M>()));
  TTS_EQUAL(eve::logical_notor(l0, false), tts::map([](auto e) -> l_t { return !e; }, l0));

  logical_test_simd<M, T>(eve::logical_notor, [](auto e, auto f) { return !e || f; }, l0, l1, a0);
};
