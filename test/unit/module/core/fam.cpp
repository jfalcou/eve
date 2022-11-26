/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of fam", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::fam(T(), T(), T()), T);
  TTS_EXPR_IS(eve::fam(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::fam(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::fam(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::fam(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::fam(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::fam(v_t(), v_t(), v_t()), v_t);

  if constexpr( eve::floating_value<T> )
  {
    using wi_t = eve::as_wide_t<int, eve::cardinal_t<T>>;
    TTS_EXPR_IS(eve::fam(T(), int(), int()), T);
    TTS_EXPR_IS(eve::fam(T(), v_t(), int()), T);
    TTS_EXPR_IS(eve::fam(v_t(), int(), T()), T);
    TTS_EXPR_IS(eve::fam(int(), T(), int()), T);
    TTS_EXPR_IS(eve::fam(wi_t(), int(), int()), wi_t);
    TTS_EXPR_IS(eve::fam(char(), wi_t(), int()), wi_t);
  }
};

//==================================================================================================
// fam tests
//==================================================================================================
auto onepmileps =
    tts::constant([]<typename U>(eve::as<U>)
                  { return (eve::inc(1000 * eve::eps(eve::as(eve::element_type_t<U>())))); });

auto onemmileps =
    tts::constant([]<typename U>(eve::as<U>)
                  { return (eve::oneminus(1000 * eve::eps(eve::as(eve::element_type_t<U>())))); });

TTS_CASE_WITH("Check precision behavior of fam on real types",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(onemmileps, onepmileps),
                            tts::randoms(onemmileps, onepmileps)))
<typename T>(T const& a0, T const& a1)
{
  using eve::fam;
  using eve::fma;
  using eve::detail::map;
  TTS_IEEE_EQUAL(eve::pedantic(fam)(-eve::one(eve::as<T>()), a0, a1),
                 eve::pedantic(fma)(a0, a1, -eve::one(eve::as<T>())));
};

//==================================================================================================
//== fam full range tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of fam on all types full range",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::as;
  using eve::fam;
  using eve::fma;
  using eve::detail::map;

  TTS_ULP_EQUAL(fam(a0, a1, a2), fma(a1, a2, a0), 0.5);
  TTS_IEEE_EQUAL(eve::pedantic(fam)(a0, a1, a2), eve::pedantic(fma)(a1, a2, a0));
  TTS_IEEE_EQUAL(eve::numeric(fam)(a0, a1, a2), eve::pedantic(fma)(a1, a2, a0));
};

//==================================================================================================
//== fam masked
//==================================================================================================
TTS_CASE_WITH("Check behavior of fam on all types full range",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const& t)
{
  using eve::as;
  using eve::fam;

  TTS_IEEE_EQUAL(fam[t](a0, a1, a2), eve::if_else(t, fam[t](a0, a1, a2), a0));
};
