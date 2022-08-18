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
TTS_CASE_TPL("Check return types of sech", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::sech(T()), T);
  TTS_EXPR_IS(eve::sech(v_t()), v_t);
};

//==================================================================================================
// sech  tests
//==================================================================================================
auto maxi = []<typename T>(eve::as<T> const&)
{
  using v_t = eve::element_type_t<T>;
  v_t ovl   = eve::Ieee_constant<v_t, 0x42B0C0A4U, 0x40862E42FEFA39EFULL>(); // 88.376251220703125f,
                                                                             // 709.782712893384
  return T(ovl);
};
auto mini = []<typename T>(eve::as<T> const& tgt) { return -maxi(tgt); };

TTS_CASE_WITH("Check behavior of sech on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(tts::constant(mini), tts::constant(maxi)),
                            tts::randoms(-1.0, 1.0)))
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  using eve::cosh;
  using eve::sech;

  auto rel = std::is_same_v<v_t, float> ? 2e-5 : 1e-13;

  TTS_RELATIVE_EQUAL(sech(a0), map([](auto e) -> v_t { return 1 / std::cosh(e); }, a0), rel);
  TTS_RELATIVE_EQUAL(sech(a1), map([](auto e) -> v_t { return 1 / std::cosh(e); }, a1), rel);
};


//==================================================================================================
// Tests for masked sech
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::sech)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::sech[mask](a0),
            eve::if_else(mask, eve::sech(a0), a0));
};
