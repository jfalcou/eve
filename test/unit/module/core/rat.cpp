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
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::rat(scalar)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using t_t = decltype(eve::zip(std::declval<T>(),std::declval<T>()));

  TTS_EXPR_IS(eve::rat(T())         , t_t);
  TTS_EXPR_IS(eve::rat(T(), T())    , t_t);
  TTS_EXPR_IS(eve::rat(T(), v_t())  , t_t);
  TTS_EXPR_IS(eve::rat(v_t(), v_t()), (kumi::tuple<v_t, v_t>));
};

//==================================================================================================
// Tests for eve::rat
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::rat(simd)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::ramp(1.0)))
<typename T>(T const& a0)
{
  using v_t   = eve::element_type_t<T>;
  auto [n, d] = eve::rat(a0 / 37);
  TTS_EQUAL(n, eve::detail::map([](auto e) -> v_t { return e; }, a0));
  TTS_EQUAL(d, T(37));
};
