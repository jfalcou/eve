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
TTS_CASE_TPL("Check return types of shr", eve::test::simd::unsigned_integers)
<typename T>(tts::type<T>)
{
  using v_t  = eve::element_type_t<T>;
  using i_t  = eve::as_integer_t<T, signed>;
  using u_t  = eve::as_integer_t<T, unsigned>;
  using vi_t = eve::as_integer_t<v_t, signed>;
  using vu_t = eve::as_integer_t<v_t, unsigned>;

  // regular
  TTS_EXPR_IS(eve::shr(T(), T()), T);
  TTS_EXPR_IS(eve::shr(T(), v_t()), T);
  TTS_EXPR_IS(eve::shr(v_t(), T()), T);
  TTS_EXPR_IS(eve::shr(v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::shr(T(), i_t()), T);
  TTS_EXPR_IS(eve::shr(T(), u_t()), T);
  TTS_EXPR_IS(eve::shr(v_t(), i_t()), T);
  TTS_EXPR_IS(eve::shr(v_t(), u_t()), T);
  TTS_EXPR_IS(eve::shr(T(), vi_t()), T);
  TTS_EXPR_IS(eve::shr(T(), vu_t()), T);
  TTS_EXPR_IS(eve::shr(v_t(), vi_t()), v_t);
  TTS_EXPR_IS(eve::shr(v_t(), vu_t()), v_t);
};

//==================================================================================================
// shr tests
//==================================================================================================
auto shift_max = []<typename T>(eve::as<T> const&)
{ return sizeof(eve::element_type_t<T>) * 8 - 1; };

TTS_CASE_WITH("Check behavior of shr on integral types",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(0u, tts::constant(shift_max))))
<typename T>(T const& a0, T const& a1)
{
  using eve::saturated;
  using eve::shr;
  TTS_EQUAL(shr(a0, a1), T([&](auto i, auto) { return shr(a0.get(i), a1.get(i)); }));
};

TTS_CASE_WITH("Check behavior of shr with scalar shift on integral types",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(0u, tts::constant(shift_max))))
<typename T, typename I>(T const& a0, I a1)
{
  using eve::saturated;
  using eve::shr;
  auto val = a1.get(0);
  TTS_EQUAL(shr(a0, val), T([&](auto i, auto) { return shr(a0.get(i), val); }));
};


//==================================================================================================
// Tests for masked shr
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::shr)(eve::wide)",
              eve::test::simd::integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::shr[mask](a0, 2),
            eve::if_else(mask, eve::shr(a0, 2), a0));
};
