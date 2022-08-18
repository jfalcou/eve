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
TTS_CASE_TPL("Check return types of log", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::log(T()), T);
  TTS_EXPR_IS(eve::log(v_t()), v_t);
};

//==================================================================================================
// log  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of log on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::eps, eve::valmax), tts::randoms(0.5, 2.0)))
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::log(a0), map([](auto e) -> v_t { return std::log(e); }, a0), 2);
  TTS_ULP_EQUAL(eve::log(a1), map([](auto e) -> v_t { return std::log(e); }, a1), 2);
};

TTS_CASE_TPL("Check return types of log", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::log(eve::inf(eve::as<T>())), eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::log(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::log(eve::mone(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::log(T(0)), eve::minf(eve::as<T>()));
  }

  if constexpr( eve::platform::supports_denormals )
  {
    TTS_IEEE_EQUAL(eve::log(eve::mindenormal(eve::as<T>())),
                   T(std::log(eve::mindenormal(eve::as<v_t>()))));
  }

  TTS_IEEE_EQUAL(eve::log(T(1)), T(0));
  TTS_IEEE_EQUAL(eve::log(T(2)), T(std::log(v_t(2))));
  TTS_IEEE_EQUAL(eve::log(T(8)), T(std::log(v_t(8))));
  TTS_IEEE_EQUAL(eve::log(T(64)), T(std::log(v_t(64))));
};


//==================================================================================================
// Tests for masked log
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::log)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::log[mask](a0),
            eve::if_else(mask, eve::log(a0), a0));
};
