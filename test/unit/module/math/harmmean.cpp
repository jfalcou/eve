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
TTS_CASE_TPL("Check return types of harmmean", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  // regular
  TTS_EXPR_IS(eve::harmmean(T(), T()), T);
  TTS_EXPR_IS(eve::harmmean(T(), v_t()), T);
  TTS_EXPR_IS(eve::harmmean(v_t(), T()), T);
  TTS_EXPR_IS(eve::harmmean(v_t(), v_t()), v_t);

  // multi
  TTS_EXPR_IS(eve::harmmean(T(), T(), T()), T);
  TTS_EXPR_IS(eve::harmmean(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::harmmean(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::harmmean(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::harmmean(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::harmmean(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::harmmean(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
//== harmmean tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of harmmean(wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-100, 100),
                            tts::randoms(-100, 100),
                            tts::randoms(-100, 100)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::harmmean;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(harmmean(a0, a1),
                tts::map( [](auto e, auto f) -> v_t {return (2/(1/e+1/f));}, a0, a1),
                2);
  auto f3 = [](auto e, auto f, auto g)  -> v_t{ return 3/(1/e+1/f+1/g);};
  TTS_ULP_EQUAL(harmmean(a0, a1, a2), tts::map(f3, a0, a1, a2), 30);
  TTS_ULP_EQUAL(harmmean[eve::pedantic](a0, a1, a2), tts::map(f3, a0, a1, a2), 30);
  TTS_ULP_EQUAL(harmmean(kumi::tuple{a0, a1, a2}), tts::map(f3, a0, a1, a2), 30);
  using v_t =  eve::element_type_t<T>;
  auto t = [](auto){ return v_t(1.5); };
  constexpr auto s = 3*T::size()/2;
  auto tup = kumi::generate<s>(t);
  TTS_RELATIVE_EQUAL(harmmean(tup),v_t(1.5), 1.0e-3);
};


//==================================================================================================
// Tests for masked harmmean
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::harmmean)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         T const& a1,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::harmmean[mask](a0, a1),
            eve::if_else(mask, eve::harmmean(a0, a1), a0));
};

TTS_CASE_WITH("Check behavior of harmmean kahan on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(1, eve::valmax),
                            tts::randoms(1, eve::valmax),
                            tts::randoms(1, eve::valmax)))
<typename T>(T const& a0, T const& a1,  T const&a2)
{
  using eve::harmmean;
  using eve::widen;
  using eve::kahan;
  using eve::as;
  if constexpr(sizeof(eve::element_type_t<T>) < 8)
    TTS_ULP_EQUAL(harmmean[kahan](a0, a1, a2), eve::downgrade(harmmean[widen](a0, a1, a2)), 5.0);

};
