//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of trunc", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::trunc(T()), T);
  TTS_EXPR_IS(eve::trunc(v_t()), v_t);
  TTS_EXPR_IS(eve::int_(eve::trunc)(T()), eve::as_integer_t<T>);
  TTS_EXPR_IS(eve::int_(eve::trunc)(v_t()), eve::as_integer_t<v_t>);
  TTS_EXPR_IS(eve::uint_(eve::trunc)(T()), (eve::as_integer_t<T, unsigned>));
  TTS_EXPR_IS(eve::uint_(eve::trunc)(v_t()), (eve::as_integer_t<v_t, unsigned>));

  if constexpr( eve::floating_ordered_value<T> )
  {
    TTS_EXPR_IS(eve::tolerant(eve::trunc)(T()), T);
    TTS_EXPR_IS(eve::tolerant(eve::trunc)(v_t()), v_t);
  }
};

//==================================================================================================
// tolerant tests
//==================================================================================================
TTS_CASE_TPL("Check  with nans and infs", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  TTS_EQUAL(eve::tolerant(eve::trunc)(eve::inc(-eve::eps(eve::as<T>()))), T(1));
  TTS_EQUAL(eve::tolerant(eve::trunc)(eve::inc(-2 * eve::eps(eve::as<T>()))), T(1));
  TTS_EQUAL(eve::tolerant(eve::trunc)(eve::inc(-3 * eve::eps(eve::as<T>()))), T(1));
  TTS_EQUAL(eve::tolerant(eve::trunc)(eve::inc(-4 * eve::eps(eve::as<T>()))), T(0));
  TTS_EQUAL(eve::tolerant(eve::trunc)(eve::dec(eve::eps(eve::as<T>()))), T(-1));
  TTS_EQUAL(eve::tolerant(eve::trunc)(eve::dec(2 * eve::eps(eve::as<T>()))), T(-1));
  TTS_EQUAL(eve::tolerant(eve::trunc)(eve::dec(3 * eve::eps(eve::as<T>()))), T(-1));
  TTS_EQUAL(eve::tolerant(eve::trunc)(eve::dec(4 * eve::eps(eve::as<T>()))), T(0));
};

//==================================================================================================
// trunc signed tests
//==================================================================================================
auto mini = []<typename T>(eve::as<T> const&) { return eve::signed_value<T> ? -50 : 0; };

TTS_CASE_WITH("Check behavior of trunc on wide",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(tts::constant(mini), +50)))
<typename T>(T const& a0)
{
  using wi_t  = eve::as_integer_t<T>;
  using uwi_t = eve::as_integer_t<T, unsigned>;
  using v_t   = eve::element_type_t<T>;
  using i_t   = eve::as_integer_t<v_t>;
  using ui_t  = eve::as_integer_t<v_t, unsigned>;
  if constexpr( eve::floating_ordered_value<T> )
  {
    TTS_EQUAL(eve::trunc(a0), T([&](auto i, auto) { return v_t(std::trunc(a0.get(i))); }));
    TTS_EQUAL(eve::int_(eve::trunc)(a0), wi_t([&](auto i, auto) { return i_t(a0.get(i)); }));
    TTS_EQUAL(eve::uint_(eve::trunc)(eve::abs(a0)),
              uwi_t([&](auto i, auto) { return ui_t(std::abs(a0.get(i))); }));
  }
  else { TTS_EQUAL(eve::trunc(a0), a0); }
};


//==================================================================================================
// Tests for masked trunc
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::trunc)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10000.0, 10000.0),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::trunc[mask](a0),
            eve::if_else(mask, eve::trunc(a0), a0));
};
