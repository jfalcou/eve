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
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::sqr", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::saturated;
  using eve::sqr;

  TTS_EXPR_IS(sqr(T()), T);
  TTS_EXPR_IS(sqr[eve::logical<T>()](T()), T);
  TTS_EXPR_IS(sqr[eve::logical<v_t>()](T()), T);
  TTS_EXPR_IS(sqr[bool()](T()), T);

  TTS_EXPR_IS(eve::sqr[saturated](T()), T);
  TTS_EXPR_IS(eve::sqr[saturated][eve::logical<T>()](T()), T);
  TTS_EXPR_IS(eve::sqr[saturated][eve::logical<v_t>()](T()), T);
  TTS_EXPR_IS(eve::sqr[saturated][bool()](T()), T);

  TTS_EXPR_IS(sqr(v_t()), v_t);
  TTS_EXPR_IS(sqr[eve::logical<v_t>()](v_t()), v_t);
  TTS_EXPR_IS(sqr[bool()](v_t()), v_t);

  TTS_EXPR_IS(eve::sqr[saturated](v_t()), v_t);
  TTS_EXPR_IS(eve::sqr[saturated][eve::logical<v_t>()](v_t()), v_t);
  TTS_EXPR_IS(eve::sqr[saturated][bool()](v_t()), v_t);
};

//==================================================================================================
// Tests for eve::sqr
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sqr(eve::wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  using eve::as;
  using eve::saturated;
  using eve::sqr;
  using eve::lower;
  using eve::upper;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(sqr(a0), map([](auto e) -> v_t { return e * e; }, a0));
  TTS_EQUAL(sqr(a0), a0*a0);
  TTS_EQUAL(sqr[lower](a0), mul[lower](a0, a0));
  TTS_EQUAL(sqr[upper](a0), mul[upper](a0, a0));
  TTS_EQUAL(sqr[mask](a0), eve::if_else(mask, eve::sqr(a0), a0));
  if constexpr( eve::integral_value<T> )
  {
    TTS_EQUAL(sqr[saturated](a0),
              map(
                  [](auto e) -> v_t {
                    return eve::abs[eve::saturated](e) > eve::sqrtvalmax(as(e)) ? eve::valmax(as(e))
                                                                           : e * e;
                  },
                  a0));
    TTS_EQUAL(sqr[saturated][mask](a0), eve::if_else(mask,sqr[saturated](a0), a0));

  }
};
