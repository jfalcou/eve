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
TTS_CASE_TPL("Check return types of cos", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::sinpicospi(T()), (eve::wide<kumi::tuple<v_t, v_t>, T::size()>));
  TTS_EXPR_IS(eve::sinpicospi(v_t()), (kumi::tuple<v_t, v_t>));
};

//==================================================================================================
// cos  tests
//==================================================================================================
// unit.math.sinpicospi fails with cl 19.52.37029 x64 /std:c++20 /Od /Ob0 /RTC1 /MDd /EHsc /W3 /WX /Zc:preprocessor -DEVE_NO_FORCEINLINE (x86 SSE2); only used by the test case commented out below
// constexpr auto mmed = []<typename T>(eve::as<T> const& tgt)
// { return -eve::Rempio2_limit[eve::medium](tgt) * eve::inv_pi(tgt); };
// unit.math.sinpicospi fails with cl 19.52.37029 x64 /std:c++20 /Od /Ob0 /RTC1 /MDd /EHsc /W3 /WX /Zc:preprocessor -DEVE_NO_FORCEINLINE (x86 SSE2); only used by the test case commented out below
// constexpr auto med = []<typename T>(eve::as<T> const& tgt)
// { return eve::Rempio2_limit[eve::medium](tgt) * eve::inv_pi(tgt); };

// unit.math.sinpicospi fails with cl 19.52.37029 x64 /std:c++20 /Od /Ob0 /RTC1 /MDd /EHsc /W3 /WX /Zc:preprocessor -DEVE_NO_FORCEINLINE (x86 SSE2); passes with cl 19.51 and clang-cl 22
// TTS_CASE_WITH("Check behavior of cos on wide",
//               eve::test::simd::ieee_reals,
//               tts::randoms(-0.25, 0.25),
//                             tts::randoms(-0.5, 0.5),
//                             tts::randoms(tts::constant(mmed), tts::constant(med)),
//                             tts::randoms(eve::valmin, eve::valmax))
// <typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
// {
//   using eve::sinpicospi;
//
//   using v_t = eve::element_type_t<T>;
//   auto refc = [](auto e) -> v_t { return eve::cospi(e); };
//   auto refs = [](auto e) -> v_t { return eve::sinpi(e); };
//   {
//     auto [s, c] =  sinpicospi[eve::quarter_circle](a0);
//     TTS_ULP_EQUAL(s, tts::map(refs, a0), 2);
//     TTS_ULP_EQUAL(c, tts::map(refc, a0), 2);
//   }
//   {
//     auto [s, c] = sinpicospi(a0);
//     TTS_ULP_EQUAL(s, tts::map(refs, a0), 2);
//     TTS_ULP_EQUAL(c, tts::map(refc, a0), 2);
//     auto [s1, c1] = sinpicospi(a1);
//     TTS_ULP_EQUAL(s1, tts::map(refs, a1), 2);
//     TTS_ULP_EQUAL(c1, tts::map(refc, a1), 2);
//     auto [s2, c2] = sinpicospi(a2);
//     TTS_ULP_EQUAL(s2, tts::map(refs, a2), 2);
//     TTS_ULP_EQUAL(c2, tts::map(refc, a2), 2);
//     auto [s3, c3] = sinpicospi(a3);
//     TTS_ULP_EQUAL(s3, tts::map(refs, a3), 2);
//     TTS_ULP_EQUAL(c3, tts::map(refc, a3), 2);
//   }
// };
