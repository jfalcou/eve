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
TTS_CASE_TPL("Check return types of acsc", eve::test::simd::ieee_reals_wf16)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::acsc(T()), T);
  TTS_EXPR_IS(eve::acsc(v_t()), v_t);
};

//==================================================================================================
// acsc  tests
//==================================================================================================
// acsc is asin of a reciprocal, and NEON has no division instruction below asimd, where eve builds
// one from a vrecpe estimate. The reciprocal then carries an error the arcsine passes on. Measured
// worst, 1 where division is an instruction, 3 on the armv7 job.
constexpr bool   rec_is_estimated = (eve::current_api >= eve::neon) && !(eve::current_api >= eve::asimd);
constexpr double acsc_tolerance   = rec_is_estimated ? 8.0 : 2.0;

TTS_CASE_WITH("Check behavior of acsc on wide",
              eve::test::simd::ieee_reals_wf16,
              tts::randoms(1.0, 100.0),
                            tts::randoms(1.0, 1e20),
                            tts::randoms(-1e20, -1.0),
                            tts::randoms(-100.0, -1.0))
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using v_t = eve::element_type_t<T>;

  auto sacsc = [](auto e) -> v_t { return static_cast<v_t>(std_asin(1 / e)); };
  TTS_ULP_EQUAL(eve::acsc(a0), tts::map(sacsc, a0), acsc_tolerance);

  TTS_ULP_EQUAL(eve::acsc(a1), tts::map(sacsc, a1), acsc_tolerance);

  TTS_ULP_EQUAL(eve::acsc(a2), tts::map(sacsc, a2), acsc_tolerance);

  TTS_ULP_EQUAL(eve::acsc(a3), tts::map(sacsc, a3), acsc_tolerance);
};


//==================================================================================================
// Tests for masked acsc
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::acsc)(eve::wide)",
              eve::test::simd::ieee_reals_wf16,
              tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::acsc[mask](a0),
            eve::if_else(mask, eve::acsc(a0), a0));
};

TTS_CASE_WITH("Check behavior of acsc on wide",
              eve::test::simd::ieee_reals,
              tts::randoms(1, 100), tts::randoms(-100, -1))
<typename T>(T const& a0, T const& a1)
{
   using eve::raw;
   auto prec = tts::prec<T>(0.005, 0.005);
   TTS_RELATIVE_EQUAL(eve::acsc(a0), eve::acsc[raw](a0), prec);
   TTS_RELATIVE_EQUAL(eve::acsc(a1), eve::acsc[raw](a1), prec);
   using eve::fast;
   auto prec1 = tts::prec<T>(0.00007, 0.00007);
   TTS_RELATIVE_EQUAL(eve::acsc(a0), eve::acsc[fast](a0), prec1);
   TTS_RELATIVE_EQUAL(eve::acsc(a1), eve::acsc[fast](a1), prec1);

};
