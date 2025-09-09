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
TTS_CASE_TPL("Check return types of mean_value", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::welford;
  using v_t = eve::element_type_t<T>;
  using wf_t = eve::detail::wf<T>;
  // regular
  TTS_EXPR_IS(eve::mean_value(T(), T()), T);
  TTS_EXPR_IS(eve::mean_value(T(), v_t()), T);
  TTS_EXPR_IS(eve::mean_value(v_t(), T()), T);
  TTS_EXPR_IS(eve::mean_value(v_t(), v_t()), v_t);

  // multi
  if constexpr( eve::floating_value<T> )
  {
    TTS_EXPR_IS(eve::mean_value(T(), T(), T()), T);
    TTS_EXPR_IS(eve::mean_value(T(), v_t(), T()), T);
    TTS_EXPR_IS(eve::mean_value(v_t(), T(), T()), T);
    TTS_EXPR_IS(eve::mean_value(T(), T(), v_t()), T);
    TTS_EXPR_IS(eve::mean_value(v_t(), v_t(), T()), T);
    TTS_EXPR_IS(eve::mean_value(v_t(), T(), v_t()), T);

    TTS_EXPR_IS(eve::mean_value(v_t(), v_t(), v_t()), v_t);
  }

  // welford

  // regular
  TTS_EXPR_IS(eve::mean_value[welford](T(), T()), wf_t);
  TTS_EXPR_IS(eve::mean_value[welford](T(), v_t()), wf_t);
  TTS_EXPR_IS(eve::mean_value[welford](v_t(), T()), wf_t);
  TTS_EXPR_IS(eve::mean_value[welford](v_t(), v_t()), eve::detail::wf<v_t>);

  // multi
  if constexpr( eve::floating_value<T> )
  {
    TTS_EXPR_IS(eve::mean_value[welford](T(), T(), T()), wf_t);
    TTS_EXPR_IS(eve::mean_value[welford](T(), v_t(), T()), wf_t);
    TTS_EXPR_IS(eve::mean_value[welford](v_t(), T(), T()), wf_t);
    TTS_EXPR_IS(eve::mean_value[welford](T(), T(), v_t()), wf_t);
    TTS_EXPR_IS(eve::mean_value[welford](v_t(), v_t(), T()), wf_t);
    TTS_EXPR_IS(eve::mean_value[welford](v_t(), T(), v_t()), wf_t);

    TTS_EXPR_IS(eve::mean_value[welford](v_t(), v_t(), v_t()), eve::detail::wf<v_t>);
  }
};

//==================================================================================================
//== mean_value[welford] tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of mean_value[welford](wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.)))
<typename T>(T  a0, T  a1, T  a2)
{
  using eve::welford;
  using eve::mean_value;
  TTS_ULP_EQUAL(mean_value[welford](a0, a1).avg_, (a0+a1)/2, 0.5);
  TTS_ULP_EQUAL(mean_value[welford](a0, a1, a2).avg_,(a0+a1+a2)/3, 1.0);
  TTS_ULP_EQUAL(mean_value(a0, a1), (a0+a1)/2, 0.5);
  TTS_ULP_EQUAL(mean_value(a0, a1, a2),(a0+a1+a2)/3, 1.0);
};

TTS_CASE_WITH("Check behavior of mean_value(wide integers)",
              eve::test::simd::integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           , tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1)
{
  using eve::mean_value;
  using v_t = eve::element_type_t<T>;
  auto wr = T(mean_value(a0, a1));
  TTS_ULP_EQUAL(wr, tts::map([](auto e, auto f) -> v_t { return std::midpoint(e, f); }, a0, a1), 2);
  TTS_EXPECT(eve::all(wr <= mean_value[eve::upper](a0, a1)));
  TTS_EXPECT(eve::all(wr >= mean_value[eve::lower](a0, a1)));
};

//==================================================================================================
//==  conditional mean_value[welford] tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of  mean_value[welford][cond](wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0, 127), tts::randoms(0, 127), tts::randoms(0, 127)))
  <typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::mean_value;
  using eve::welford;
  using eve::kahan;
  TTS_ULP_EQUAL(
    mean_value[welford][a2 > T(64)](a0, a1).avg_,
    mean_value[kahan][a2 > T(64)](a0, a1), 0.5);
};


//==================================================================================================
//=== Tests for masked mean_value[welford]
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::mean_value[welford])(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& ,
                         T const& ,
                         M const& mask)
{
  T a0(25.0);
  T a1(35.0);
  std::cout <<eve::mean_value[eve::welford](a0, a1).avg_<< std::endl;
  std::cout << eve::detail::wf(a0).avg_<< std::endl;
  std::cout << a0                 << std::endl;
  std::cout <<mask<< std::endl;
  std::cout << eve::if_else(mask, eve::mean_value[eve::welford](a0, a1).avg_, a0) << std::endl;
  TTS_ULP_EQUAL(eve::mean_value[mask][eve::welford](a0, a1).avg_,
                 eve::if_else(mask, eve::mean_value[eve::kahan](a0, a1), a0), 0.5);
  TTS_ULP_EQUAL(eve::mean_value[mask](a0, a1),
                 eve::if_else(mask, eve::mean_value[eve::kahan](a0, a1), a0), 0.5);
};

//==================================================================================================
//===  Tests for lower upper  mean_value[welford]
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::upper(eve::mean_value[welford])(eve::wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax))
              )
<typename T>(T const& a0, T const& a1)
{
  using eve::mean_value;
  using eve::lower;
  using eve::upper;
  using eve::strict;
  TTS_EXPECT(eve::all(eve::mean_value(a0, a1) <= eve::mean_value[eve::upper](a0, a1)));
  TTS_EXPECT(eve::all(eve::inc(eve::mean_value(a0, a1)) >=eve::mean_value[eve::upper](a0, a1)));
  T  w0{0.1};
  T  w1{0.12f};
  TTS_EXPECT(eve::all(mean_value[upper](w0, w1)  >=  mean_value(w0, w1)));
  TTS_EXPECT(eve::all(mean_value[lower](w0, -w1) <= mean_value(w0, -w1)));
  if constexpr (eve::floating_value<T>)
  {
    TTS_EXPECT(eve::all(mean_value[strict][upper](w0, w1)  >  mean_value(w0, w1)));
    TTS_EXPECT(eve::all(mean_value[strict][upper](w0, w1)  >= mean_value(w0, w1)));
    TTS_EXPECT(eve::all(mean_value[strict][lower](w0, -w1) <  mean_value(w0, -w1)));
    TTS_EXPECT(eve::all(mean_value[strict][upper](w0, w1)  >= mean_value[upper](w0, w1)));
    TTS_EXPECT(eve::all(mean_value[strict][lower](w0, -w1) <= mean_value[lower](w0, -w1)));
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
  using eve::mean_value;
  using eve::welford;
  using eve::as;
  if constexpr(sizeof(eve::element_type_t<T>) < 8)
  {
    TTS_ULP_EQUAL(mean_value[kahan](a0, a1, a2), eve::downgrade(mean_value[widen](a0, a1, a2)), 0.5);
    TTS_ULP_EQUAL(mean_value[welford](a0, a1, a2).avg_, eve::downgrade(mean_value[widen](a0, a1, a2)), 0.5);
    TTS_ULP_EQUAL(mean_value[welford](a0, a1, a2).avg_, mean_value[kahan](a0, a1, a2), 0.5);
  }

};
