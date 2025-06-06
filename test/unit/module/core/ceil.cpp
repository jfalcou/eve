//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <cmath>

#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of ceil", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::ceil(T()), T);
  TTS_EXPR_IS(eve::ceil(v_t()), v_t);

  if constexpr( eve::floating_value<T> )
  {
    TTS_EXPR_IS(eve::ceil(T(), eve::as<int>()), eve::as_integer_t<T>);
    TTS_EXPR_IS(eve::ceil(v_t(), eve::as<int>()), eve::as_integer_t<v_t>);
    TTS_EXPR_IS(eve::ceil(T(), eve::as<unsigned int>()), (eve::as_integer_t<T, unsigned>));
    TTS_EXPR_IS(eve::ceil(v_t(), eve::as<unsigned int>()), (eve::as_integer_t<v_t, unsigned>));
    TTS_EXPR_IS(eve::ceil[eve::almost](T()), T);
    TTS_EXPR_IS(eve::ceil[eve::almost](v_t()), v_t);
  }
};

//==================================================================================================
// almost tests
//==================================================================================================
TTS_CASE_TPL("Check  with specific values", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  TTS_EQUAL(eve::ceil(T(-1)), T(-1));
  TTS_EQUAL(eve::ceil(T(-2)), T(-2));
  TTS_EQUAL(eve::ceil(T(0)), T(0));
  TTS_EQUAL(eve::ceil(T(1)), T(1));
  TTS_EQUAL(eve::ceil(T(2)), T(2));

  TTS_EQUAL(eve::ceil(T(-1.3)), T(-1));
  TTS_EQUAL(eve::ceil(T(-1.5)), T(-1));
  TTS_EQUAL(eve::ceil(T(-1.6)), T(-1));
  TTS_EQUAL(eve::ceil(T(1.3)), T(2));
  TTS_EQUAL(eve::ceil(T(1.5)), T(2));
  TTS_EQUAL(eve::ceil(T(1.6)), T(2));

  TTS_EQUAL(eve::ceil[eve::almost](T(-1)), T(-1));
  TTS_EQUAL(eve::ceil[eve::almost](T(-2)), T(-2));
  TTS_EQUAL(eve::ceil[eve::almost](T(0)), T(0));
  TTS_EQUAL(eve::ceil[eve::almost](T(1)), T(1));
  TTS_EQUAL(eve::ceil[eve::almost](T(2)), T(2));

  TTS_EQUAL(eve::ceil[eve::almost](T(-1.3)), T(-1));
  TTS_EQUAL(eve::ceil[eve::almost](T(-1.5)), T(-1));
  TTS_EQUAL(eve::ceil[eve::almost](T(-1.6)), T(-1));
  TTS_EQUAL(eve::ceil[eve::almost](T(1.3)), T(2));
  TTS_EQUAL(eve::ceil[eve::almost](T(1.5)), T(2));
  TTS_EQUAL(eve::ceil[eve::almost](T(1.6)), T(2));
  TTS_EQUAL(eve::ceil[eve::almost](eve::eps(eve::as<T>())), T(0));
  TTS_EQUAL(eve::ceil[eve::almost](2 * eve::eps(eve::as<T>())), T(0));
  TTS_EQUAL(eve::ceil[eve::almost](3 * eve::eps(eve::as<T>())), T(0));
  TTS_EQUAL(eve::ceil[eve::almost](4 * eve::eps(eve::as<T>())), T(1));
};

//==================================================================================================
// ceil(simd)  tests
//==================================================================================================
auto min =
    tts::constant([]<typename T>(eve::as<T> const&) { return eve::signed_value<T> ? -50 : 0; });
TTS_CASE_WITH("Check behavior of ceil(wide))",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(min, +50)))
<typename T>(T const& a0)
{
  using wi_t  = eve::as_integer_t<T>;
  using uwi_t = eve::as_integer_t<T, unsigned>;
  using v_t   = eve::element_type_t<T>;
  using i_t   = eve::as_integer_t<v_t>;
  using ui_t  = eve::as_integer_t<v_t, unsigned>;
  if constexpr( eve::floating_value<T> )
  {
    TTS_EQUAL(eve::ceil(a0), tts::map([&](auto e) -> v_t { return v_t(std::ceil(e)); }, a0));

    TTS_EQUAL(eve::ceil(a0, eve::as<int>()),
              wi_t([&](auto i, auto) { return i_t(std::ceil(a0.get(i))); }));
    TTS_EQUAL(eve::ceil(eve::abs(a0), eve::as<unsigned int>()),
              uwi_t([&](auto i, auto) { return ui_t(std::ceil(std::abs(a0.get(i)))); }));
  }
  else { TTS_EQUAL(eve::ceil(a0), a0); }
};


//==================================================================================================
// Tests for masked ceil
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::ceil)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::ceil[mask](a0),
            eve::if_else(mask, eve::ceil(a0), a0));
};
