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
  TTS_EXPR_IS(eve::int_(eve::ceil)(T()), eve::as_integer_t<T>);
  TTS_EXPR_IS(eve::int_(eve::ceil)(v_t()), eve::as_integer_t<v_t>);
  TTS_EXPR_IS(eve::uint_(eve::ceil)(T()), (eve::as_integer_t<T, unsigned>));
  TTS_EXPR_IS(eve::uint_(eve::ceil)(v_t()), (eve::as_integer_t<v_t, unsigned>));

  if constexpr( eve::floating_value<T> )
  {
    TTS_EXPR_IS(eve::tolerant(eve::ceil)(T()), T);
    TTS_EXPR_IS(eve::tolerant(eve::ceil)(v_t()), v_t);
  }
};

//==================================================================================================
// tolerant tests
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

  TTS_EQUAL(eve::tolerant(eve::ceil)(T(-1)), T(-1));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(-2)), T(-2));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(0)), T(0));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(1)), T(1));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(2)), T(2));

  TTS_EQUAL(eve::tolerant(eve::ceil)(T(-1.3)), T(-1));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(-1.5)), T(-1));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(-1.6)), T(-1));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(1.3)), T(2));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(1.5)), T(2));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(1.6)), T(2));
  TTS_EQUAL(eve::tolerant(eve::ceil)(eve::eps(eve::as<T>())), T(0));
  TTS_EQUAL(eve::tolerant(eve::ceil)(2 * eve::eps(eve::as<T>())), T(0));
  TTS_EQUAL(eve::tolerant(eve::ceil)(3 * eve::eps(eve::as<T>())), T(0));
  TTS_EQUAL(eve::tolerant(eve::ceil)(4 * eve::eps(eve::as<T>())), T(1));
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
  using eve::detail::map;
  using wi_t  = eve::as_integer_t<T>;
  using uwi_t = eve::as_integer_t<T, unsigned>;
  using v_t   = eve::element_type_t<T>;
  using i_t   = eve::as_integer_t<v_t>;
  using ui_t  = eve::as_integer_t<v_t, unsigned>;
  if constexpr( eve::floating_value<T> )
  {
    TTS_EQUAL(eve::ceil(a0), map([&](auto e) -> v_t { return v_t(std::ceil(e)); }, a0));

    TTS_EQUAL(eve::int_(eve::ceil)(a0),
              wi_t([&](auto i, auto) { return i_t(std::ceil(a0.get(i))); }));
    TTS_EQUAL(eve::uint_(eve::ceil)(eve::abs(a0)),
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
