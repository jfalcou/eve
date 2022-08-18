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
TTS_CASE_TPL("Check return types of bit_shl", eve::test::simd::unsigned_integers)
<typename T>(tts::type<T>)
{
  using v_t  = eve::element_type_t<T>;
  using i_t  = eve::as_integer_t<T, signed>;
  using u_t  = eve::as_integer_t<T, unsigned>;
  using vi_t = eve::as_integer_t<v_t, signed>;
  using vu_t = eve::as_integer_t<v_t, unsigned>;

  // regular
  TTS_EXPR_IS(eve::bit_shl(T(), T()), T);
  TTS_EXPR_IS(eve::bit_shl(T(), v_t()), T);
  TTS_EXPR_IS(eve::bit_shl(v_t(), T()), T);
  TTS_EXPR_IS(eve::bit_shl(v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::bit_shl(T(), i_t()), T);
  TTS_EXPR_IS(eve::bit_shl(T(), u_t()), T);
  TTS_EXPR_IS(eve::bit_shl(v_t(), i_t()), T);
  TTS_EXPR_IS(eve::bit_shl(v_t(), u_t()), T);
  TTS_EXPR_IS(eve::bit_shl(T(), vi_t()), T);
  TTS_EXPR_IS(eve::bit_shl(T(), vu_t()), T);
  TTS_EXPR_IS(eve::bit_shl(v_t(), vi_t()), v_t);
  TTS_EXPR_IS(eve::bit_shl(v_t(), vu_t()), v_t);
};

//==================================================================================================
// wide tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of bit_shl(wide, wide)",
              eve::test::simd::integers,
              tts::generate(tts::randoms(-50, 50), tts::random_bits(), tts::logicals(0, 3)))
<typename T, typename I, typename L>(T a0, I a1, L test)
{
  using eve::bit_shl;
  using eve::detail::map;
  using v_t = typename T::value_type;
  TTS_EQUAL(bit_shl(a0, a1), map([](auto e, auto s) -> v_t { return e << s; }, a0, a1));
  TTS_EQUAL(bit_shl[test](a0, a1), eve::if_else(test, eve::bit_shl(a0, a1), a0));
};

TTS_CASE_WITH("Check behavior of bit_shl(wide, scalar)",
              eve::test::simd::integers,
              tts::generate(tts::randoms(-50, 50), tts::random_bits(), tts::logicals(0, 3)))
<typename T, typename I, typename L>(T a0, I s, L test)
{
  using eve::bit_shl;
  using eve::detail::map;
  auto val  = s.get(0);
  using v_t = typename T::value_type;
  TTS_EQUAL(bit_shl(a0, val), map([&](auto e) -> v_t { return e << val; }, a0));
  TTS_EQUAL(bit_shl[test](a0, val), eve::if_else(test, eve::bit_shl(a0, val), a0));
};

//==================================================================================================
// Tests for masked bit_shl
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::bit_shl)(eve::wide)",
              eve::test::simd::integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::bit_shl[mask](a0, 2),
            eve::if_else(mask, eve::bit_shl(a0, 2), a0));
};
