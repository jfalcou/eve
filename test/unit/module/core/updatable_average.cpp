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
  using wf_t = eve::detail::wf<T>;
  // regular
  TTS_EXPR_IS(eve::updatable_average(T(), T()), wf_t);
  TTS_EXPR_IS(eve::updatable_average(T(), v_t()), wf_t);
  TTS_EXPR_IS(eve::updatable_average(v_t(), T()), wf_t);
  TTS_EXPR_IS(eve::updatable_average(v_t(), v_t()), eve::detail::wf<v_t>);

  // multi
  if constexpr( eve::floating_value<T> )
  {
    TTS_EXPR_IS(eve::updatable_average(T(), T(), T()), wf_t);
    TTS_EXPR_IS(eve::updatable_average(T(), v_t(), T()), wf_t);
    TTS_EXPR_IS(eve::updatable_average(v_t(), T(), T()), wf_t);
    TTS_EXPR_IS(eve::updatable_average(T(), T(), v_t()), wf_t);
    TTS_EXPR_IS(eve::updatable_average(v_t(), v_t(), T()), wf_t);
    TTS_EXPR_IS(eve::updatable_average(v_t(), T(), v_t()), wf_t);

    TTS_EXPR_IS(eve::updatable_average(v_t(), v_t(), v_t()), eve::detail::wf<v_t>);
  }
};

//==================================================================================================
//== updatable_average tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of updatable_average(wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.)))
<typename T>(T  a0, T  a1, T  a2)
{
  using eve::welford;
  using eve::average;
  TTS_ULP_EQUAL(updatable_average(a0, a1).avg_, (a0+a1)/2, 0.5);
  TTS_ULP_EQUAL(updatable_average(a0, a1, a2).avg_,(a0+a1+a2)/3, 1.0);
};


//==================================================================================================
//==  conditional updatable_average tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of  updatable_average[cond](wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0, 127), tts::randoms(0, 127), tts::randoms(0, 127)))
  <typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::average;
  using eve::updatable_average;
  using eve::kahan;
  TTS_ULP_EQUAL(
    updatable_average[a2 > T(64)](a0, a1).avg_,
    average[kahan][a2 > T(64)](a0, a1), 0.5);
};


//==================================================================================================
//=== Tests for masked updatable_average
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::updatable_average)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         T const& a1,
                         M const& mask)
{
//   T a0(25.0);
//   T a1(35.0);
//   std::cout <<eve::average[eve::welford](a0, a1).avg_<< std::endl;
//   std::cout << eve::detail::wf(a0).avg_<< std::endl;
//   std::cout << a0                 << std::endl;
//   std::cout <<mask<< std::endl;
//   std::cout << eve::if_else(mask, eve::average[eve::welford](a0, a1).avg_, a0) << std::endl;
  TTS_ULP_EQUAL(eve::average[mask][eve::welford](a0, a1).avg_,
                 eve::if_else(mask, eve::average[eve::kahan](a0, a1), a0), 0.5);
  TTS_ULP_EQUAL(eve::average[mask](a0, a1),
                 eve::if_else(mask, eve::average[eve::kahan](a0, a1), a0), 0.5);
};

//==================================================================================================
//===  Tests for lower upper  updatable_average
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::upper(eve::updatable_average)(eve::wide)",
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


TTS_CASE_WITH("Check behavior of kahan kahan on wide",
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
    TTS_ULP_EQUAL(updatable_average(a0, a1, a2).avg_, eve::downgrade(average[widen](a0, a1, a2)), 0.5);
    TTS_ULP_EQUAL(updatable_average(a0, a1, a2).avg_, average[kahan](a0, a1, a2), 0.5);
  }

};
