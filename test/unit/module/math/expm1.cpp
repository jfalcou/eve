//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of expm1", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::expm1(T()), T);
  TTS_EXPR_IS(eve::expm1(v_t()), v_t);
};

//==================================================================================================
// expm1  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of expm1 on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::minlog, eve::maxlog), tts::randoms(-1.0, 1.0)))
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::expm1(a0), map([](auto e) -> v_t { return std::expm1(e); }, a0), 30);
  TTS_ULP_EQUAL(eve::expm1(a1), map([](auto e) -> v_t { return std::expm1(e); }, a1), 2);

  TTS_ULP_EQUAL(
      eve::pedantic(eve::expm1)(a0), map([](auto e) -> v_t { return std::expm1(e); }, a0), 30);
  TTS_ULP_EQUAL(
      eve::pedantic(eve::expm1)(a1), map([](auto e) -> v_t { return std::expm1(e); }, a1), 2);
};

TTS_CASE_TPL("Check return types of expm1", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::expm1(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::expm1(eve::inf(eve::as<T>())), eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::expm1(eve::minf(eve::as<T>())), T(-1));
  }

  TTS_EXPECT(eve::all(eve::is_negative(eve::expm1(T(-0.)))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::expm1(T(0.)))));

  TTS_IEEE_EQUAL(eve::expm1(T(0)), T(0));
  TTS_IEEE_EQUAL(eve::expm1(T(-0.)), T(0));

  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(eve::expm1(T(1)), T(std::expm1(v_t(1))), 0.5);
  TTS_ULP_EQUAL(eve::expm1(T(-1)), T(std::expm1(v_t(-1))), 0.5);
};
