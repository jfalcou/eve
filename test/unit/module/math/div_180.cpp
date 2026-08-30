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

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of div_180", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::div_180(T())  , T  );
  TTS_EXPR_IS(eve::div_180(v_t()), v_t);
};

//==================================================================================================
// div_180 divides by 180, more accurately than the plain division does
//==================================================================================================
TTS_CASE_WITH("Check behavior of div_180",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1000.0, 1000.0)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(eve::div_180(a0), tts::map([](auto e) -> v_t { return e / 180; }, a0), 0.5);
};

//==================================================================================================
// The corner cases the double-double split is there for
//==================================================================================================
TTS_CASE_TPL("Check limits of div_180", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  auto cases = tts::limits(tts::type<T>{});

  TTS_EQUAL(eve::div_180(T(0))    , T(0));
  TTS_EQUAL(eve::div_180(T(-0.0)) , T(-0.0));
  TTS_EQUAL(eve::div_180(T(180))  , T(1));
  TTS_EQUAL(eve::div_180(T(-180)) , T(-1));
  TTS_EQUAL(eve::div_180(T(360))  , T(2));
  TTS_IEEE_EQUAL(eve::div_180(cases.nan) , cases.nan);
  TTS_IEEE_EQUAL(eve::div_180(cases.inf) , cases.inf);
  TTS_IEEE_EQUAL(eve::div_180(cases.minf), cases.minf);
};

//==================================================================================================
// masked div_180
//==================================================================================================
TTS_CASE_WITH("Check behavior of div_180[mask]",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1000.0, 1000.0), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  TTS_IEEE_EQUAL(eve::div_180[mask](a0), eve::if_else(mask, eve::div_180(a0), a0));
};
