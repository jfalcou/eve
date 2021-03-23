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
#include <eve/function/fnms.hpp>
#include <eve/function/pedantic/fnms.hpp>
#include <eve/function/numeric/fnms.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/round.hpp>
#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of fnms"
            , eve::test::simd::all_types
  
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::fnms(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::fnms(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::fnms(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::fnms(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::fnms(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::fnms(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::fnms(v_t(), v_t(), v_t()) , v_t);
};

//==================================================================================================
//== fnms tests
//==================================================================================================

auto onepmileps = []< typename T>(eve::as_<T> const &){return (eve::inc(1000*eve::eps(eve::as(eve::element_type_t<T>())))) ;};
auto onemmileps = []< typename T>(eve::as_<T> const &){return (eve::oneminus(1000*eve::eps(eve::as(eve::element_type_t<T>())))) ;};

EVE_TEST( "Check precision behavior of fnms on real types"
        , eve::test::simd::ieee_reals
        , eve::test::generate (  eve::test::randoms(onemmileps, onepmileps)
                              ,  eve::test::randoms(onemmileps, onepmileps)
                              )
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::fnms;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL( eve::pedantic(fnms)(a0, a1, -eve::one(eve::as<T>())), T([&](auto i , auto) { return eve::pedantic(fnms)(a0.get(i), a1.get(i), v_t(-1)); }), 2);
};

//==================================================================================================
// fnms full range tests
//==================================================================================================
EVE_TEST( "Check behavior of fnms on all types full range"
        , eve::test::simd::all_types
        , eve::test::generate (  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              )
        )
<typename T>(  T const& a0, T const& a1, T const& a2)
{
  using eve::fnms;
  TTS_ULP_EQUAL(fnms((a0), (a1), (a2)), T([&](auto i , auto) { return eve::pedantic(fnms)((a0.get(i)), (a1.get(i)), (a2.get(i))); }), 2);
  TTS_ULP_EQUAL(eve::pedantic(fnms)((a0), (a1), (a2)), T([&](auto i , auto) { return eve::pedantic(fnms)((a0.get(i)), (a1.get(i)), (a2.get(i))); }), 2);
  TTS_ULP_EQUAL(eve::numeric(fnms)((a0), (a1), (a2)), T([&](auto i , auto) { return eve::pedantic(fnms)((a0.get(i)), (a1.get(i)), (a2.get(i))); }), 2);
};
