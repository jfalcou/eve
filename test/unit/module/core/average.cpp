//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <numeric>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of average", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::welford;
  using v_t = eve::element_type_t<T>;
  // regular
  TTS_EXPR_IS(eve::average(T(), T()), T);
  TTS_EXPR_IS(eve::average(T(), v_t()), T);
  TTS_EXPR_IS(eve::average(v_t(), T()), T);
  TTS_EXPR_IS(eve::average(v_t(), v_t()), v_t);

  // multi
  if constexpr( eve::floating_value<T> )
  {
    TTS_EXPR_IS(eve::average(T(), T(), T()), T);
    TTS_EXPR_IS(eve::average(T(), v_t(), T()), T);
    TTS_EXPR_IS(eve::average(v_t(), T(), T()), T);
    TTS_EXPR_IS(eve::average(T(), T(), v_t()), T);
    TTS_EXPR_IS(eve::average(v_t(), v_t(), T()), T);
    TTS_EXPR_IS(eve::average(v_t(), T(), v_t()), T);

    TTS_EXPR_IS(eve::average(v_t(), v_t(), v_t()), v_t);
  }
};

TTS_CASE_WITH("Check behavior of average(wide integers)",
              eve::test::simd::integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           , tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1)
{
  using eve::average;
  using v_t = eve::element_type_t<T>;
  auto wr = T(average(a0, a1));
  TTS_ULP_EQUAL(wr, tts::map([](auto e, auto f) -> v_t { return std::midpoint(e, f); }, a0, a1), 2);
  TTS_EXPECT(eve::all(wr <= average[eve::upper](a0, a1)));
  TTS_EXPECT(eve::all(wr >= average[eve::lower](a0, a1)));
};

//==================================================================================================
//==  conditional average tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of  average[welford][cond](wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0, 127), tts::randoms(0, 127), tts::randoms(0, 127)))
  <typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::average;
  using eve::welford;
  using eve::kahan;
  TTS_ULP_EQUAL(
    average[a2 > T(64)](a0, a1), eve::if_else(a2 > T(64), average(a0, a1), a0), 0.5);
};


//==================================================================================================
//=== Tests for masked average[welford]
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::average[welford])(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         T const& a1,
                         M const& mask)
{
  TTS_ULP_EQUAL(eve::average[mask](a0, a1),
                 eve::if_else(mask, eve::average(a0, a1), a0), 0.5);
};

//==================================================================================================
//===  Tests for lower upper  average
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::upper(eve::average[welford])(eve::wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax))
              )
<typename T>(T const& a0, T const& a1)
{
  using eve::average;
  using eve::lower;
  using eve::upper;
  using eve::strict;
  TTS_EXPECT(eve::all(eve::average(a0, a1) <= eve::average[eve::upper](a0, a1)));
  TTS_EXPECT(eve::all(eve::inc(eve::average(a0, a1)) >=eve::average[eve::upper](a0, a1)));
  T  w0{0.1};
  T  w1{0.12f};
  TTS_EXPECT(eve::all(average[upper](w0, w1)  >=  average(w0, w1)));
  TTS_EXPECT(eve::all(average[lower](w0, -w1) <= average(w0, -w1)));
  if constexpr (eve::floating_value<T>)
  {
    TTS_EXPECT(eve::all(average[strict][upper](w0, w1)  >  average(w0, w1)));
    TTS_EXPECT(eve::all(average[strict][upper](w0, w1)  >= average(w0, w1)));
    TTS_EXPECT(eve::all(average[strict][lower](w0, -w1) <  average(w0, -w1)));
    TTS_EXPECT(eve::all(average[strict][upper](w0, w1)  >= average[upper](w0, w1)));
    TTS_EXPECT(eve::all(average[strict][lower](w0, -w1) <= average[lower](w0, -w1)));
  }
};


TTS_CASE_WITH("Check behavior of average kahan on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1,  T const&a2)
{
  using eve::kahan;
  using eve::widen;
  using eve::average;
  using eve::welford;
  using eve::as;
  if constexpr(sizeof(eve::element_type_t<T>) < 8)
  {
    TTS_ULP_EQUAL(average[kahan](a0, a1, a2), eve::downgrade(average[widen](a0, a1, a2)), 0.5);
  }

};
