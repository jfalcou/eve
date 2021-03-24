/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/half.hpp>
#include <eve/function/geommean.hpp>
#include <eve/function/pedantic/geommean.hpp>
#include <eve/function/diff/geommean.hpp>
#include <numeric>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of geommean"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  //regular
  TTS_EXPR_IS( eve::geommean(T(), T()  ) , T);
  TTS_EXPR_IS( eve::geommean(T(), v_t()) , T);
  TTS_EXPR_IS( eve::geommean(v_t(), T()) , T);
  TTS_EXPR_IS( eve::geommean(v_t(), v_t()) , v_t);

//   //multi is not writen yet but will be
//   if constexpr(eve::floating_real_value<T>)
//   {
//     TTS_EXPR_IS( eve::geommean(T(), T(), T()  )  , T);
//     TTS_EXPR_IS( eve::geommean(T(), v_t(), T())  , T);
//     TTS_EXPR_IS( eve::geommean(v_t(), T(), T())  , T);
//     TTS_EXPR_IS( eve::geommean(T(), T(), v_t() ) , T);
//     TTS_EXPR_IS( eve::geommean(v_t(), v_t(), T()) , T);
//     TTS_EXPR_IS( eve::geommean(v_t(), T(), v_t()) , T);
//     TTS_EXPR_IS( eve::geommean(v_t(), v_t(), v_t()) , v_t);
//   }
};

//==================================================================================================
// geommean tests
//==================================================================================================
EVE_TEST( "Check behavior of geommean on real types"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::ramp(10), eve::test::ramp(100))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using eve::geommean;
  TTS_ULP_EQUAL( geommean(a0, a1), T([&](auto i, auto) { return std::sqrt(a0.get(i))*std::sqrt(a1.get(i)); }), 0.5);
  TTS_ULP_EQUAL( eve::pedantic(geommean)(a0, a1), T([&](auto i, auto) { return std::sqrt(a0.get(i))*std::sqrt(a1.get(i)); }), 0.5);
  TTS_ULP_EQUAL( eve::diff_2nd(geommean)(a0, a1), T([&](auto i, auto) { return std::sqrt(a0.get(i))/std::sqrt(a1.get(i))/2; }), 0.5);
  TTS_ULP_EQUAL( eve::diff_1st(geommean)(a0, a1), T([&](auto i, auto) { return std::sqrt(a1.get(i))/std::sqrt(a0.get(i))/2; }), 0.5);
};
