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
TTS_CASE_TPL("Check return types of coshsinh", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::sinhcosh(T()), (eve::wide<kumi::tuple<v_t,v_t>,typename T::cardinal_type>));
  TTS_EXPR_IS(eve::sinhcosh(v_t()), (kumi::tuple<v_t, v_t>));
};

//==================================================================================================
// coshsinh  tests
//==================================================================================================
auto maxi = []<typename T>(eve::as<T> const&)
{
  using v_t = eve::element_type_t<T>;
  v_t ovl   = eve::ieee_constant<0x1.62e42fefa39efp+9, 0x1.6181480p+6f>(eve::as<v_t>{});  // 709.782712893384// 88.376251220703125f,
  return T(ovl);
};

auto mini = []<typename T>(eve::as<T> const& tgt) { return -maxi(tgt); };

TTS_CASE_WITH("Check behavior of cos on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(tts::constant(mini), tts::constant(maxi))))
<typename T>(T const& a0)
{
  using eve::sinhcosh;

  using v_t   = eve::element_type_t<T>;
  auto refc   = [](auto e) -> v_t { return std::cosh(e); };
  auto refs   = [](auto e) -> v_t { return std::sinh(e); };
  auto [s, c] = sinhcosh(a0);
  TTS_ULP_EQUAL(s, tts::map(refs, a0), 2);
  TTS_ULP_EQUAL(c, tts::map(refc, a0), 2);
};
