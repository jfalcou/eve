//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/diff/inc.hpp>
#include <eve/function/saturated/inc.hpp>
#include <eve/logical.hpp>
#include <type_traits>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST( "Check return types of inc"
            , eve::test::simd::all_types
            , eve::test::generate(eve::test::no_data)
            )
<typename T>(T)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::inc(T())  , T);
  TTS_EXPR_IS( eve::inc(v_t()), v_t);
  TTS_EXPR_IS( eve::inc[eve::logical<T>()](T())  , T);
  TTS_EXPR_IS( eve::inc[eve::logical<T>()](v_t()), T);
  TTS_EXPR_IS( eve::inc[eve::logical<v_t>()](T())  , T);
  TTS_EXPR_IS( eve::inc[eve::logical<v_t>()](v_t()), v_t);
  TTS_EXPR_IS( eve::inc[bool()](T())  , T);
  TTS_EXPR_IS( eve::inc[bool()](v_t()), v_t);


  TTS_EXPR_IS( eve::saturated(eve::inc)(T())  , T);
  TTS_EXPR_IS( eve::saturated(eve::inc)(v_t()), v_t);
  TTS_EXPR_IS( eve::saturated(eve::inc[eve::logical<T>()])(T())  , T);
  TTS_EXPR_IS( eve::saturated(eve::inc[eve::logical<T>()])(v_t()), T);
  TTS_EXPR_IS( eve::saturated(eve::inc[eve::logical<v_t>()])(T())  , T);
  TTS_EXPR_IS( eve::saturated(eve::inc[eve::logical<v_t>()])(v_t()), v_t);
  TTS_EXPR_IS( eve::saturated(eve::inc[bool()])(T())  , T);
  TTS_EXPR_IS( eve::saturated(eve::inc[bool()])(v_t()), v_t);

  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::diff(eve::inc)(T())  , T);
    TTS_EXPR_IS( eve::diff(eve::inc)(v_t()), v_t);
  }
};



//==================================================================================================
// inc  tests
//==================================================================================================
auto valmaxm1 = []< typename T>(eve::as_<T> const &){return eve::dec(eve::valmax(eve::as(eve::element_type_t<T>())));};

EVE_TEST( "Check behavior of inc on signed wide"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::randoms(eve::valmin, valmaxm1))
        )
<typename T>(T const& a0 )
{
  TTS_EQUAL( eve::inc(a0), T([&](auto i, auto) { return a0.get(i)+1; }));
};

EVE_TEST( "Check behavior of saturated inc on integral wide"
        , eve::test::simd::integers
        , eve::test::generate(eve::test::randoms(valmaxm1, eve::valmax))
        )
<typename T>(T const& a0 )
{
  TTS_EQUAL( eve::saturated(eve::inc)(a0), T([&](auto i, auto) { auto x = a0.get(i);
                                               return x == eve::valmax(eve::as(x)) ? x : x+1; }));
};
