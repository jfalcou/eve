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
TTS_CASE_TPL("Check return types of secd", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::secd(T()), T);
  TTS_EXPR_IS(eve::secd(v_t()), v_t);
};

//==================================================================================================
// secd  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of secd on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-45, 45),
                            tts::randoms(-90, 90),
                            tts::randoms(-5000, 5000)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::secd;
  using eve::detail::map;

  using eve::deginrad;
  using v_t = eve::element_type_t<T>;
  auto ref  = [](auto e) -> v_t { return 1.0l / eve::cospi(double(e / 180.0l)); };

  TTS_ULP_EQUAL(eve::quarter_circle(secd)(a0), map(ref, a0), 4);
  TTS_ULP_EQUAL(eve::half_circle(secd)(a0), map(ref, a0), 4);
  TTS_ULP_EQUAL(eve::half_circle(secd)(a1), map(ref, a1), 4);
  TTS_ULP_EQUAL(secd(a0), map(ref, a0), 4);
  TTS_ULP_EQUAL(secd(a1), map(ref, a1), 4);
  TTS_ULP_EQUAL(secd(a2), map(ref, a2), 512);
};

TTS_CASE_TPL("Check return types of secd", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::secd(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::secd(eve::inf(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::secd(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()));
  }

  TTS_IEEE_EQUAL(eve::secd(T(0)), T(1));
  TTS_IEEE_EQUAL(eve::secd(T(-0.)), T(1));
};


//==================================================================================================
// Tests for masked secd
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::secd)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::secd[mask](a0),
            eve::if_else(mask, eve::secd(a0), a0));
};
