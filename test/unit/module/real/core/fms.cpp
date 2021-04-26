/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/pedantic/fms.hpp>
#include <eve/function/numeric/fms.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/round.hpp>
#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of fms"
              , eve::test::simd::all_types
              )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::fms(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::fms(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::fms(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::fms(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::fms(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::fms(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::fms(v_t(), v_t(), v_t()) , v_t);

  if constexpr(eve::floating_value<T>)
  {
    using wi_t = eve::as_wide_t<int, eve::cardinal_t<T>>;
    TTS_EXPR_IS( eve::fms(T(), int(), int()  )  , T);
    TTS_EXPR_IS( eve::fms(T(), v_t(), int())  , T);
    TTS_EXPR_IS( eve::fms(v_t(), int(), T())  , T);
    TTS_EXPR_IS( eve::fms(int(), T(), int())  , T);
    TTS_EXPR_IS( eve::fms(wi_t(), int(), int())  , wi_t);
    TTS_EXPR_IS( eve::fms(char(), wi_t(), int()), wi_t);
  }

};

//==================================================================================================
// fms tests
//==================================================================================================
auto onepmileps = []<typename U>(eve::as_<U>)
{
  return (eve::inc(1000*eve::eps(eve::as(eve::element_type_t<U>()))));
};

auto onemmileps = []<typename U>(eve::as_<U>)
{
  return (eve::oneminus(1000*eve::eps(eve::as(eve::element_type_t<U>()))));
};

EVE_TEST( "Check precision behavior of fms on real types"
        , eve::test::simd::ieee_reals
        , eve::test::generate (  eve::test::randoms(onemmileps, onepmileps)
                              ,  eve::test::randoms(onemmileps, onepmileps)
                              )
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::fms;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL ( eve::pedantic(fms)(a0, a1, eve::one(eve::as<T>()))
                , T([&](auto i , auto) { return eve::pedantic(fms)(a0.get(i), a1.get(i), v_t(1)); })
                , 2
                );
};

//==================================================================================================
// fms full range tests
//==================================================================================================
EVE_TEST( "Check behavior of fms on all types full range"
        , eve::test::simd::all_types
        , eve::test::generate (  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              )
        )
<typename T>(  T const& a0, T const& a1, T const& a2)
{
  using eve::fms;
  TTS_ULP_EQUAL(fms((a0), (a1), (a2)), T([&](auto i , auto) { return eve::pedantic(fms)((a0.get(i)), (a1.get(i)), (a2.get(i))); }), 2);
  TTS_ULP_EQUAL(eve::pedantic(fms)((a0), (a1), (a2)), T([&](auto i , auto) { return eve::pedantic(fms)((a0.get(i)), (a1.get(i)), (a2.get(i))); }), 2);
  TTS_ULP_EQUAL(eve::numeric(fms)((a0), (a1), (a2)), T([&](auto i , auto) { return eve::pedantic(fms)((a0.get(i)), (a1.get(i)), (a2.get(i))); }), 2);
};
