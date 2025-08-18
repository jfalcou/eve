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
TTS_CASE_TPL("Check return types of add", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::raw;
  using eve::veltkamp;

  // regular
  TTS_EXPR_IS(veltkamp(T()), (kumi::tuple<T, T>));
  TTS_EXPR_IS(veltkamp(v_t()), (kumi::tuple<v_t, v_t>));
};

//==================================================================================================
//==  veltkamp simd tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of veltkamp on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0, 10))
             )
  <typename T>(T const& a0)
{
  using eve::veltkamp;
  using eve::as;
  using eve::raw;
  using eve::detail::map;
  auto [s, r] = veltkamp(a0);
  TTS_EQUAL(s+r, a0);
};
