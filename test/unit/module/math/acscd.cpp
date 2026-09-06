//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "std_proxy.hpp"
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of acscd", eve::test::simd::ieee_reals_wf16)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::acscd(T()), T);
  TTS_EXPR_IS(eve::acscd(v_t()), v_t);
};

//==================================================================================================
// acscd  tests
//==================================================================================================
// acscd is asin of a reciprocal, and NEON has no division instruction below asimd, where eve builds
// one from a vrecpe estimate. The reciprocal then carries an error the arcsine passes on. Measured
// worst, 1 where division is an instruction, 3 on the armv7 job.
constexpr bool   rec_is_estimated = (eve::current_api >= eve::neon) && !(eve::current_api >= eve::asimd);
constexpr double acscd_tolerance   = rec_is_estimated ? 8.0 : 2.0;

TTS_CASE_WITH("Check behavior of acscd on wide",
              eve::test::simd::ieee_reals_wf16,
              tts::randoms(1.0, 100.0),
                            tts::randoms(1.0, 1e20),
                            tts::randoms(-1e20, -1.0),
                            tts::randoms(-100.0, -1.0))
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using v_t = eve::element_type_t<T>;

  auto sacscd = [](auto e) -> v_t { return static_cast<v_t>(eve::radindeg(std_asin(1 / e))); };
  TTS_ULP_EQUAL(eve::acscd(a0), tts::map(sacscd, a0), acscd_tolerance);

  TTS_ULP_EQUAL(eve::acscd(a1), tts::map(sacscd, a1), acscd_tolerance);

  TTS_ULP_EQUAL(eve::acscd(a2), tts::map(sacscd, a2), acscd_tolerance);

  TTS_ULP_EQUAL(eve::acscd(a3), tts::map(sacscd, a3), acscd_tolerance);
};


//==================================================================================================
// Tests for masked acscd
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::acscd)(eve::wide)",
              eve::test::simd::ieee_reals_wf16,
              tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::acscd[mask](a0),
            eve::if_else(mask, eve::acscd(a0), a0));
};
