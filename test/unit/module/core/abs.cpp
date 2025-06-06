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

//==================================================================================================
// Specific generator - valmin or valmin+1 if T is signed
//==================================================================================================
auto minimal = tts::constant(
    []<typename T>(eve::as<T> const& tgt)
    {
      constexpr auto sign = std::is_signed_v<T> ? 1 : 0;
      return eve::valmin(tgt) + sign;
    });

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::abs", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::abs(T()), T);
  TTS_EXPR_IS(eve::abs[eve::logical<T>()](T()), T);
  TTS_EXPR_IS(eve::abs[eve::logical<v_t>()](T()), T);
  TTS_EXPR_IS(eve::abs[bool()](T()), T);

  TTS_EXPR_IS(eve::abs[eve::saturated](T()), T);
  TTS_EXPR_IS(eve::abs[eve::saturated][eve::logical<T>()](T()), T);
  TTS_EXPR_IS(eve::abs[eve::saturated][eve::logical<v_t>()](T()), T);
  TTS_EXPR_IS(eve::abs[eve::saturated][bool()](T()), T);

  TTS_EXPR_IS(eve::abs(v_t()), v_t);
  TTS_EXPR_IS(eve::abs[eve::logical<v_t>()](v_t()), v_t);
  TTS_EXPR_IS(eve::abs[bool()](v_t()), v_t);

  TTS_EXPR_IS(eve::abs[eve::saturated](v_t()), v_t);
  TTS_EXPR_IS(eve::abs[eve::saturated][eve::logical<v_t>()](v_t()), v_t);
  TTS_EXPR_IS(eve::abs[eve::saturated][bool()](v_t()), v_t);
};

//==================================================================================================
// Tests for eve::abs
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::abs(eve::wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::abs(a0), tts::map([](auto e) -> v_t { return e > 0 ? e : -e; }, a0));
  TTS_EQUAL(eve::abs[mask](a0), eve::if_else(mask, eve::abs(a0), a0));
};

//==================================================================================================
// Tests for eve::abs[eve::saturated]
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::abs[eve::saturated](eve::wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( std::is_signed_v<v_t> )
  {
    TTS_EQUAL(eve::abs[eve::saturated](a0),
              tts::map([](auto e)
                  { return e == eve::valmin(eve::as(e)) ? eve::valmax(eve::as(e)) : eve::abs(e); },
                  a0));
  }
  else { TTS_EQUAL(eve::abs[eve::saturated](a0), a0); }

  TTS_EQUAL(eve::abs[eve::saturated][mask](a0),eve::if_else(mask, eve::abs[eve::saturated](a0), a0));
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL("Check corner-cases behavior of eve::abs variants on wide", eve::test::simd::all_types)
<typename T>(tts::type<T> tgt)
{
  auto cases = tts::limits(tgt);

  if constexpr( eve::floating_value<T> )
  {
    TTS_IEEE_EQUAL(eve::abs(cases.nan), cases.nan);
    TTS_IEEE_EQUAL(eve::abs(cases.minf), cases.inf);
    TTS_EQUAL(eve::abs(cases.mzero), T(0));
    TTS_EQUAL(eve::abs(cases.valmin), cases.valmax);
    TTS_EQUAL(eve::abs(cases.valmax), cases.valmax);

    TTS_IEEE_EQUAL(eve::abs[eve::saturated](cases.nan), cases.nan);
    TTS_IEEE_EQUAL(eve::abs[eve::saturated](cases.minf), cases.inf);
    TTS_EQUAL(eve::abs[eve::saturated](cases.mzero), T(0));
    TTS_EQUAL(eve::abs[eve::saturated](cases.valmin), cases.valmax);
    TTS_EQUAL(eve::abs[eve::saturated](cases.valmax), cases.valmax);
  }
  else
  {
     TTS_EQUAL(eve::abs(cases.valmax), cases.valmax);

     if constexpr( eve::signed_value<T> )
       TTS_EQUAL(eve::abs[eve::saturated](cases.valmin), cases.valmax);

     if constexpr( eve::unsigned_value<T> )
       TTS_EQUAL(eve::abs[eve::saturated](cases.valmin), cases.valmin);

     TTS_EQUAL(eve::abs[eve::saturated](cases.valmax), cases.valmax);
  }
};
