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
TTS_CASE_TPL("Check return types of eve::logical_andnot(scalar)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  logical_test_scalar_return_type<T>(eve::logical_andnot);
};

TTS_CASE_TPL("Check return types of eve::logical_andnot(simd)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  logical_test_simd_return_type<T>(eve::logical_andnot);
};

//==================================================================================================
//== Tests for eve::logical_andnot
//==================================================================================================
TTS_CASE("Check behavior of eve::logical_andnot(bool)")
{
  TTS_EQUAL(eve::logical_andnot(true, true), false);
  TTS_EQUAL(eve::logical_andnot(true, false), true);
  TTS_EQUAL(eve::logical_andnot(false, true), false);
  TTS_EQUAL(eve::logical_andnot(false, false), false);
};

TTS_CASE_TPL("Check behavior of eve::logical_andnot(invalid)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  logical_test_compile_reject<T>(eve::logical_andnot);
};

TTS_CASE_WITH("Check behavior of eve::logical_andnot(logical<wide>)",
              eve::test::simd::all_types,
              tts::generate(tts::logicals(0, 3), tts::logicals(1, 2), tts::randoms(0, 2)))
<typename M, typename T>(M const& l0, [[maybe_unused]] M const& l1, [[maybe_unused]] T const& a0)
{
  using l_t = eve::element_type_t<M>;

  TTS_EQUAL(eve::logical_andnot(l0, true), eve::false_(eve::as<M>()));
  TTS_EQUAL(eve::logical_andnot(true, l1), tts::map([](auto e) -> l_t { return !e; }, l1));
  TTS_EQUAL(eve::logical_andnot(false, l1), eve::false_(eve::as<M>()));
  TTS_EQUAL(eve::logical_andnot(l0, false), l0);

  logical_test_simd<M, T>(eve::logical_andnot, [](auto e, auto f) { return e && !f; }, l0, l1, a0);
};
