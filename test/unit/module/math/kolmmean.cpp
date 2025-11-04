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
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of kolmmean", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  auto f0 = eve::abs; //l1 mean
  // regular
  TTS_EXPR_IS(eve::kolmmean(f0, f0, T(), T()), T);
  TTS_EXPR_IS(eve::kolmmean(f0, f0,T(), v_t()), T);
  TTS_EXPR_IS(eve::kolmmean(f0, f0,v_t(), T()), T);
  TTS_EXPR_IS(eve::kolmmean(f0, f0,v_t(), v_t()), v_t);

  // multi
  TTS_EXPR_IS(eve::kolmmean(f0, f0,T(), T(), T()), T);
  TTS_EXPR_IS(eve::kolmmean(f0, f0,T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::kolmmean(f0, f0,v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::kolmmean(f0, f0,T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::kolmmean(f0, f0,v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::kolmmean(f0, f0,v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::kolmmean(f0, f0,v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
//== kolmmean tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of kolmmean(wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-100, 100),
                            tts::randoms(-100, 100),
                            tts::randoms(-100, 100)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::kolmmean;
  using v_t = eve::element_type_t<T>;
  auto f0 = eve::abs; //l1 mean
  auto h = [](auto ... e) -> v_t {return eve::average(eve::abs(e)...); };
  TTS_ULP_EQUAL(kolmmean(f0, f0, a0, a1), tts::map(h, a0, a1),2);
  TTS_ULP_EQUAL(kolmmean(f0, f0, a0, a1, a2), tts::map(h, a0, a1, a2), 30);
  TTS_ULP_EQUAL(kolmmean[eve::pedantic](f0, f0, a0, a1, a2), tts::map(h, a0, a1, a2), 30);
  TTS_ULP_EQUAL(kolmmean(f0, f0, kumi::tuple{a0, a1, a2}), tts::map(h, a0, a1, a2), 30);
  using v_t =  eve::element_type_t<T>;
  auto t = [](auto){ return v_t(1.5); };
  constexpr auto s = 3*T::size()/2;
  auto tup = kumi::generate<s>(t);
  TTS_RELATIVE_EQUAL(kolmmean(f0, f0, tup),v_t(1.5), 1.0e-3);
};


TTS_CASE_WITH("Check behavior of kolmmean kahan on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(1, eve::valmax),
                            tts::randoms(1, eve::valmax),
                            tts::randoms(1, eve::valmax)))
<typename T>(T const& a0, T const& a1,  T const&a2)
{
  using eve::kolmmean;
  using eve::widen;
  using eve::kahan;
  using eve::as;
  auto f0 = eve::abs; //l1 mean
  if constexpr(sizeof(eve::element_type_t<T>) < 8)
    TTS_ULP_EQUAL(kolmmean[kahan](f0, f0, a0, a1, a2), eve::downgrade(kolmmean[widen](f0, f0, a0, a1, a2)), 5.0);

};
