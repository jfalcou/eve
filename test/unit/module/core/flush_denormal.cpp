//==================================================================================================
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
TTS_CASE_TPL("Check return types of flush_denormal", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::flush_denormal(T())  , T  );
  TTS_EXPR_IS(eve::flush_denormal(v_t()), v_t);
};

//==================================================================================================
// Denormals go to zero, everything else is left alone
//==================================================================================================
TTS_CASE_TPL("Check behavior of flush_denormal on the values it targets", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  auto cases = tts::limits(tts::type<T>{});

  TTS_EQUAL(eve::flush_denormal(eve::mindenormal(as<T>()))    , T(0));
  TTS_EQUAL(eve::flush_denormal(-eve::mindenormal(as<T>()))   , T(0));
  TTS_EQUAL(eve::flush_denormal(eve::smallestposval(as<T>())) , eve::smallestposval(as<T>()));
  TTS_EQUAL(eve::flush_denormal(T(0))                         , T(0));
  TTS_EQUAL(eve::flush_denormal(T(1))                         , T(1));
  TTS_EQUAL(eve::flush_denormal(T(-1))                        , T(-1));
  TTS_IEEE_EQUAL(eve::flush_denormal(cases.nan)  , cases.nan);
  TTS_IEEE_EQUAL(eve::flush_denormal(cases.inf)  , cases.inf);
  TTS_IEEE_EQUAL(eve::flush_denormal(cases.minf) , cases.minf);
};

//==================================================================================================
// Normal values pass through untouched
//==================================================================================================
TTS_CASE_WITH("Check that flush_denormal leaves normal values alone",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-100.0, 100.0)))
<typename T>(T const& a0)
{
  TTS_IEEE_EQUAL(eve::flush_denormal(a0), a0);
};

//==================================================================================================
// masked flush_denormal
//==================================================================================================
TTS_CASE_WITH("Check behavior of flush_denormal[mask]",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-100.0, 100.0), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  TTS_IEEE_EQUAL(eve::flush_denormal[mask](a0), eve::if_else(mask, eve::flush_denormal(a0), a0));
};
