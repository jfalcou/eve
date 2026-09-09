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
TTS_CASE_TPL("Check return types of acscpi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::acscpi(T()), T);
  TTS_EXPR_IS(eve::acscpi(v_t()), v_t);
};

//==================================================================================================
// acscpi  tests
//==================================================================================================
// acscpi is asin of a reciprocal, and armv7 NEON has no division: the estimate's error reaches asin.
constexpr bool   rec_is_estimated = (eve::current_api >= eve::neon) && !(eve::current_api >= eve::asimd);
constexpr double acscpi_tolerance   = rec_is_estimated ? 8.0 : 2.0;

TTS_CASE_WITH("Check behavior of acscpi on wide",
              eve::test::simd::ieee_reals,
              tts::randoms(1.0, 100.0),
                            tts::randoms(1.0, 1e20),
                            tts::randoms(-1e20, -1.0),
                            tts::randoms(-100.0, -1.0))
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using v_t = eve::element_type_t<T>;

  auto sacscpi = [](auto e) -> v_t { return static_cast<v_t>(eve::radinpi(std_asin(1 / e))); };
  TTS_ULP_EQUAL(eve::acscpi(a0), tts::map(sacscpi, a0), acscpi_tolerance);

  TTS_ULP_EQUAL(eve::acscpi(a1), tts::map(sacscpi, a1), acscpi_tolerance);

  TTS_ULP_EQUAL(eve::acscpi(a2), tts::map(sacscpi, a2), acscpi_tolerance);

  TTS_ULP_EQUAL(eve::acscpi(a3), tts::map(sacscpi, a3), acscpi_tolerance);
};


//==================================================================================================
// Tests for masked acscpi
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::acscpi)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::acscpi[mask](a0),
            eve::if_else(mask, eve::acscpi(a0), a0));
};
