//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/bessel.hpp>

TTS_CASE_TPL("Check return types of airy_ai", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t  = eve::element_type_t<T>;
  using kv_t = kumi::tuple<v_t, v_t>;
  using kT   = eve::wide<kv_t, typename T::cardinal_type>;
  TTS_EXPR_IS(eve::airy(T(0)), kT);
  TTS_EXPR_IS(eve::airy(v_t(0)), kv_t);
};

TTS_CASE_WITH ( "Check behavior of airy on wide"
              , eve::test::simd::ieee_reals
              , tts::generate(tts::randoms(-20.0, 0.0), tts::randoms(0.0, 20.0))
              )
<typename T>(T a0, T a1)
{
  auto [ai0, bi0] = eve::airy(a0);
  TTS_IEEE_EQUAL(ai0, eve::airy_ai(a0));
  TTS_IEEE_EQUAL(bi0, eve::airy_bi(a0));

  auto [ai1, bi1] = eve::airy(a1);
  TTS_IEEE_EQUAL(ai1, eve::airy_ai(a1));
  TTS_IEEE_EQUAL(bi1, eve::airy_bi(a1));
};
