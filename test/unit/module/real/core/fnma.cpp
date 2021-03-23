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
#include <eve/function/fnma.hpp>
#include <eve/function/pedantic/fnma.hpp>
#include <eve/function/numeric/fnma.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/round.hpp>
#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of fnma"
            , eve::test::simd::all_types
  
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::fnma(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::fnma(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::fnma(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::fnma(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::fnma(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::fnma(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::fnma(v_t(), v_t(), v_t()) , v_t);
};

//==================================================================================================
//== fnma tests
//==================================================================================================

auto onepmileps = []< typename T>(eve::as_<T> const &){return (eve::inc(1000*eve::eps(eve::as(eve::element_type_t<T>())))) ;};
auto onemmileps = []< typename T>(eve::as_<T> const &){return (eve::oneminus(1000*eve::eps(eve::as(eve::element_type_t<T>())))) ;};

EVE_TEST( "Check precision behavior of fnma on real types"
        , eve::test::simd::ieee_reals
        , eve::test::generate (  eve::test::randoms(onemmileps, onepmileps)
                              ,  eve::test::randoms(onemmileps, onepmileps)
                              )
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::fnma;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL( eve::pedantic(fnma)(a0, a1, eve::one(eve::as<T>())), T([&](auto i , auto) { return eve::pedantic(fnma)(a0.get(i), a1.get(i), v_t(1)); }), 2);
};

//==================================================================================================
// fnma full range tests
//==================================================================================================
EVE_TEST( "Check behavior of fnma on all types full range"
        , eve::test::simd::all_types
        , eve::test::generate (  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              )
        )
<typename T>(  T const& a0, T const& a1, T const& a2)
{
  using eve::fnma;
  TTS_ULP_EQUAL(fnma((a0), (a1), (a2)), T([&](auto i , auto) { return eve::pedantic(fnma)((a0.get(i)), (a1.get(i)), (a2.get(i))); }), 2);
  TTS_ULP_EQUAL(eve::pedantic(fnma)((a0), (a1), (a2)), T([&](auto i , auto) { return eve::pedantic(fnma)((a0.get(i)), (a1.get(i)), (a2.get(i))); }), 2);
  TTS_ULP_EQUAL(eve::numeric(fnma)((a0), (a1), (a2)), T([&](auto i , auto) { return eve::pedantic(fnma)((a0.get(i)), (a1.get(i)), (a2.get(i))); }), 2);
};
