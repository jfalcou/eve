/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of bit_shr", eve::test::simd::unsigned_integers)
<typename T>(tts::type<T>)
{
  using v_t  = eve::element_type_t<T>;
  using i_t  = eve::as_integer_t<T, signed>;
  using u_t  = eve::as_integer_t<T, unsigned>;
  using vi_t = eve::as_integer_t<v_t, signed>;
  using vu_t = eve::as_integer_t<v_t, unsigned>;

  // regular
  TTS_EXPR_IS(eve::bit_shr(T(), T()), T);
  TTS_EXPR_IS(eve::bit_shr(T(), v_t()), T);
  TTS_EXPR_IS(eve::bit_shr(v_t(), T()), T);
  TTS_EXPR_IS(eve::bit_shr(v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::bit_shr(T(), i_t()), T);
  TTS_EXPR_IS(eve::bit_shr(T(), u_t()), T);
  TTS_EXPR_IS(eve::bit_shr(v_t(), i_t()), T);
  TTS_EXPR_IS(eve::bit_shr(v_t(), u_t()), T);
  TTS_EXPR_IS(eve::bit_shr(T(), vi_t()), T);
  TTS_EXPR_IS(eve::bit_shr(T(), vu_t()), T);
  TTS_EXPR_IS(eve::bit_shr(v_t(), vi_t()), v_t);
  TTS_EXPR_IS(eve::bit_shr(v_t(), vu_t()), v_t);
};

//==================================================================================================
// wide tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of shr(wide, wide)",
              eve::test::simd::integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::random_bits(), tts::logicals(0, 3)))
<typename T, typename I, typename L>(T a0, I a1, L test)
{
  using eve::bit_shr;
  using v_t = eve::element_type_t<T>;
  using u_t = eve::as_integer_t<v_t, unsigned>;
  TTS_EQUAL(bit_shr(a0, a1), tts::map([](auto e, auto s) -> v_t { return v_t(u_t(e) >> s); }, a0, a1));
  TTS_EQUAL(bit_shr[test](a0, a1), eve::if_else(test, eve::bit_shr(a0, a1), a0));
};

TTS_CASE_WITH("Check behavior of bit_shr(wide, integral constant)",
              eve::test::simd::integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3)))
<typename T, typename L>(T a0, L test)
{
  using eve::bit_shr;
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL(bit_shr(a0, eve::index<1>), tts::map([&](auto e) -> v_t { return eve::bit_shr(e, eve::index<1>); }, a0));
  TTS_EQUAL(bit_shr[test](a0, eve::index<1>), eve::if_else(test, eve::bit_shr(a0, eve::index<1>), a0));
};

TTS_CASE_WITH("Check behavior of shift(wide, scalar)",
              eve::test::simd::integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::random_bits(), tts::logicals(0, 3)))
<typename T, typename I, typename L>(T a0, I s, L test)
{
  using eve::bit_shr;
  auto val  = s.get(0);
  using v_t = eve::element_type_t<T>;
  using u_t = eve::as_integer_t<v_t, unsigned>;
  TTS_EQUAL(bit_shr(a0, val), tts::map([&](auto e) -> v_t { return v_t(u_t(e) >> val); }, a0));
  TTS_EQUAL(bit_shr[test](a0, val), eve::if_else(test, eve::bit_shr(a0, val), a0));
};


//==================================================================================================
// Tests for masked bit_shr
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::bit_shr[cx](eve::wide)",
              eve::test::simd::integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::bit_shr[mask](a0, 2),
            eve::if_else(mask, eve::bit_shr(a0, 2), a0));
};
