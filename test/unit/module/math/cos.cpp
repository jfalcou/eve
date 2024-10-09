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
#include <eve/module/math/detail/constant/rempio2_limits.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of cos", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::cos(T()), T);
  TTS_EXPR_IS(eve::cos(v_t()), v_t);
};

//==================================================================================================
// cos  tests
//==================================================================================================
auto mquarter_c = []<typename T>(eve::as<T> const& tgt) { return -eve::pio_4(tgt); };
auto quarter_c  = []<typename T>(eve::as<T> const& tgt) { return  eve::pio_4(tgt); };
auto mhalf_c    = []<typename T>(eve::as<T> const& tgt) { return -eve::pio_2(tgt); };
auto half_c     = []<typename T>(eve::as<T> const& tgt) { return  eve::pio_2(tgt); };
auto mfull_c    = []<typename T>(eve::as<T> const& tgt) { return -eve::pi(tgt); };
auto full_c     = []<typename T>(eve::as<T> const& tgt) { return  eve::pi(tgt); };
auto mmed       = []<typename T>(eve::as<T> const& tgt) { return -eve::Rempio2_limit[eve::medium](tgt); };
auto med        = []<typename T>(eve::as<T> const& tgt) { return  eve::Rempio2_limit[eve::medium](tgt); };

TTS_CASE_WITH("Check behavior of cos on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(tts::constant(mquarter_c), tts::constant(quarter_c)),
                            tts::randoms(tts::constant(mhalf_c), tts::constant(half_c)),
                            tts::randoms(tts::constant(mfull_c), tts::constant(full_c)),
                            tts::randoms(tts::constant(mmed), tts::constant(med)),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3, T const& a4)
{
  using eve::cos;

  using v_t = eve::element_type_t<T>;
  auto ref  = [](auto e) -> v_t { return std::cos(e); };
  TTS_ULP_EQUAL(cos[eve::quarter_circle](a0), tts::map(ref, a0), 2);
  TTS_ULP_EQUAL(cos[eve::half_circle](a0), tts::map(ref, a0), 2);
  TTS_ULP_EQUAL(cos[eve::half_circle](a1), tts::map(ref, a1), 2);
  TTS_ULP_EQUAL(cos[eve::full_circle](a0), tts::map(ref, a0), 2);
  TTS_ULP_EQUAL(cos[eve::full_circle](a1), tts::map(ref, a1), 2);
  TTS_ULP_EQUAL(cos[eve::full_circle](a2), tts::map(ref, a2), 2);
  TTS_ULP_EQUAL(cos(a0), tts::map(ref, a0), 2);
  TTS_ULP_EQUAL(cos(a1), tts::map(ref, a1), 2);
  TTS_ULP_EQUAL(cos(a2), tts::map(ref, a2), 2);
  TTS_ULP_EQUAL(cos(a3), tts::map(ref, a3), 2);
  TTS_ULP_EQUAL(cos(a4), tts::map(ref, a4), 2);
};


//==================================================================================================
// Tests for masked cos
//==================================================================================================
// TTS_CASE_WITH("Check behavior of eve::masked(eve::cos)(eve::wide)",
//               eve::test::simd::ieee_reals,
//               tts::generate(tts::randoms(eve::valmin, eve::valmax),
//               tts::logicals(0, 3)))
// <typename T, typename M>(T const& a0,
//                          M const& mask)
// {
//   TTS_IEEE_EQUAL(eve::cos[mask](a0),
//             eve::if_else(mask, eve::cos(a0), a0));
// };
