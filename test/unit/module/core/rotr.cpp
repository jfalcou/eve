//======================================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//======================================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <bit>

//======================================================================================================================
// Types tests
//======================================================================================================================
TTS_CASE_TPL("Check return types of rotr", eve::test::simd::unsigned_integers)
<typename T>(tts::type<T>)
{
  using eve::rotr;
  using v_t  = eve::element_type_t<T>;
  using u_t  = eve::as_integer_t<T, unsigned>;
  using i_t  = eve::as_integer_t<T, signed>;
  using su_t = eve::as_integer_t<v_t, unsigned>;
  using si_t = eve::as_integer_t<v_t, signed>;

  TTS_EXPR_IS(rotr(T(), u_t()), T);
  TTS_EXPR_IS(rotr(T(), i_t()), T);
  TTS_EXPR_IS(rotr(T(), su_t()), T);
  TTS_EXPR_IS(rotr(T(), si_t()), T);
  TTS_EXPR_IS(rotr(T(), std::int32_t()), T);

  TTS_EXPR_IS(rotr(v_t(), u_t()), T);
  TTS_EXPR_IS(rotr(v_t(), i_t()), T);
  TTS_EXPR_IS(rotr(v_t(), su_t()), v_t);
  TTS_EXPR_IS(rotr(v_t(), si_t()), v_t);
};

auto maxi = []<typename T>(eve::as<T> const&) { return sizeof(eve::element_type_t<T>) * 8 - 1; };

//======================================================================================================================
//== rotr  tests
//======================================================================================================================
TTS_CASE_WITH("Check behavior of rotr on wide",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(0, tts::constant(maxi))))
<typename T>(T a0, T a1)
{
  using eve::rotr;
  TTS_EQUAL(rotr(a0, 0u), a0);
  TTS_EQUAL(rotr(a0, eve::index<0>), a0);
  TTS_EQUAL(rotr(a0, 1u), map([](auto e) { return std::rotr(e, 1u); }, a0));
  TTS_EQUAL(rotr(a0, eve::index<4>), map([](auto e) { return std::rotr(e, 4u); }, a0));
  using v_t = eve::element_type_t<T>;
  a0        = eve::one(eve::as(a0));
  a1        = eve::iota(eve::as(a0));
  a1        = a1 % (sizeof(v_t) * 8);
  auto ua1  =  eve::convert(a1,  eve::int_from<T>());
  TTS_EQUAL(rotr(a0, a1), map([](auto e, auto f) -> v_t { return std::rotr(e, f); }, a0, a1));
  TTS_EQUAL(rotr(a0, ua1), map([](auto e, auto f) -> v_t { return std::rotr(e, f); }, a0, ua1));
};

//======================================================================================================================
// Tests for masked rotr
//======================================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::rotr)(eve::wide)",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,M const& mask)
{
  TTS_IEEE_EQUAL(eve::rotr[mask](a0, 2),eve::if_else(mask, eve::rotr(a0, 2), a0));
};
