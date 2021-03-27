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
#include <eve/function/dec.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/diff/dec.hpp>
#include <eve/function/saturated/dec.hpp>
#include <eve/logical.hpp>
#include <type_traits>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST( "Check return types of dec"
            , eve::test::simd::all_types
            , eve::test::generate(eve::test::no_data)
            )
<typename T>(T)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::dec(T())  , T);
  TTS_EXPR_IS( eve::dec(v_t()), v_t);
  TTS_EXPR_IS( eve::dec[eve::logical<T>()](T())  , T);
  TTS_EXPR_IS( eve::dec[eve::logical<T>()](v_t()), T);
  TTS_EXPR_IS( eve::dec[eve::logical<v_t>()](T())  , T);
  TTS_EXPR_IS( eve::dec[eve::logical<v_t>()](v_t()), v_t);
  TTS_EXPR_IS( eve::dec[bool()](T())  , T);
  TTS_EXPR_IS( eve::dec[bool()](v_t()), v_t);


  TTS_EXPR_IS( eve::saturated(eve::dec)(T())  , T);
  TTS_EXPR_IS( eve::saturated(eve::dec)(v_t()), v_t);
  TTS_EXPR_IS( eve::saturated(eve::dec[eve::logical<T>()])(T())  , T);
  TTS_EXPR_IS( eve::saturated(eve::dec[eve::logical<T>()])(v_t()), T);
  TTS_EXPR_IS( eve::saturated(eve::dec[eve::logical<v_t>()])(T())  , T);
  TTS_EXPR_IS( eve::saturated(eve::dec[eve::logical<v_t>()])(v_t()), v_t);
  TTS_EXPR_IS( eve::saturated(eve::dec[bool()])(T())  , T);
  TTS_EXPR_IS( eve::saturated(eve::dec[bool()])(v_t()), v_t);

  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::diff(eve::dec)(T())  , T);
    TTS_EXPR_IS( eve::diff(eve::dec)(v_t()), v_t);
  }
};



//==================================================================================================
// dec  tests
//==================================================================================================
auto valminp1 = []< typename T>(eve::as_<T> const &){return eve::inc(eve::valmin(eve::as(eve::element_type_t<T>())));};

EVE_TEST( "Check behavior of dec on signed wide"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::randoms(valminp1, eve::valmax))
        )
<typename T>(T const& a0 )
{
  TTS_EQUAL( eve::dec(a0), T([&](auto i, auto) { return a0.get(i)-1; }));
};

EVE_TEST( "Check behavior of saturated dec on integral wide"
        , eve::test::simd::integers
        , eve::test::generate(eve::test::randoms(eve::valmin, valminp1))
        )
<typename T>(T const& a0 )
{
  TTS_EQUAL( eve::saturated(eve::dec)(a0), T([&](auto i, auto) { auto x = a0.get(i);
                                               return x == eve::valmin(eve::as(x)) ? x : x-1; }));
};
