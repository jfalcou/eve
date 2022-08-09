//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <bit>
//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::popcount(simd)", eve::test::simd::unsigned_integers)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::popcount(T()), T);
  TTS_EXPR_IS(eve::popcount(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::popcount
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::popcount(simd)",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const&)
{
  using eve::detail::map;
  using i_t  = eve::as_integer_t<T, unsigned>;
  using vi_t = eve::element_type_t<i_t>;

  TTS_EQUAL(eve::popcount(a0), map([](vi_t e) -> vi_t { return std::popcount(e); }, a0));
  //  TTS_EQUAL(eve::popcount[t](a0), eve::if_else(t, eve::popcount(a0), a0));
};
