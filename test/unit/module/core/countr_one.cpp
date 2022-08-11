//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <bit>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of countr_one on wide", eve::test::simd::unsigned_integers)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::countr_one(T()), T);
  TTS_EXPR_IS(eve::countr_one(v_t()), v_t);
};

//==================================================================================================
// countr_one(simd) tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of countr_one(wide) on unsigned integral ",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, const M t)
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::countr_one(a0), map([](auto e) -> v_t { return std::countr_one(e); }, a0));
  TTS_EQUAL(eve::countr_one[t](a0), eve::if_else(t, eve::countr_one(a0), a0));
};
