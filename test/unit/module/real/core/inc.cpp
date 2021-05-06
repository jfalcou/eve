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
#include <eve/function/diff/inc.hpp>
#include <eve/function/saturated/inc.hpp>
#include <eve/logical.hpp>
#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of inc"
            , eve::test::simd::all_types
            )
<typename T>(eve::as_<T>)
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
// inc(simd)  tests
//==================================================================================================
auto valminp1 = []< typename T>(eve::as_<T> const &){return eve::inc(eve::valmin(eve::as(eve::element_type_t<T>())));};

EVE_TEST( "Check behavior of inc(wide) and inc[cond](wide)"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::randoms(valminp1, eve::valmax))
        )
<typename T>(T const& a0 )
{
  using v_t = eve::element_type_t<T>;
  using eve::diff;
  TTS_EQUAL( eve::inc(a0), map([](auto e) ->v_t{ return v_t(e+1); }, a0));
  TTS_EQUAL( eve::inc[a0 > 64](a0), map([](auto e) ->v_t{ return v_t((e > 64) ?e+1 : e); }, a0));
  bool z = (a0.get(0) > 64);
  TTS_EQUAL( eve::inc[z](a0), map([&](auto e) ->v_t{ return v_t((z) ?e+1 : e); }, a0));
  if constexpr(eve::floating_real_value<T>)
    TTS_EQUAL( diff(eve::inc)(a0), eve::one(eve::as(a0)));

};

EVE_TEST( "Check behavior of saturated(inc)(wide) on integral types"
        , eve::test::simd::integers
        , eve::test::generate(eve::test::randoms(eve::valmin, valminp1))
        )
<typename T>(T const& a0 )
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL( eve::saturated(eve::inc)(a0), map([](auto e) ->v_t {
                                                 return v_t(e == eve::valmax(eve::as(e)) ? e : e+1); }, a0));
  TTS_EQUAL( eve::saturated(eve::inc[a0 > 64])(a0)
           , map([](auto e) ->v_t{ return v_t((e > 64
                                               && e != eve::valmin(eve::as(e)) ? e+1 : e)); }, a0));
  bool z = (a0.get(0) > 64);
   TTS_EQUAL( eve::saturated(eve::inc[z])(a0)
           , map([&](auto e) ->v_t{ return v_t((z
                                               && e != eve::valmin(eve::as(e)) ? e+1 : e)); }, a0));
 };


EVE_TEST( "Check behavior of saturated(inc)(wide) on integral types"
        , eve::test::simd::integers
        , eve::test::generate(eve::test::randoms(eve::valmin, valminp1))
        )
<typename T>(T const& a0 )
{
  using v_t = typename T::value_type;
  for (auto a : a0)
  TTS_EQUAL( eve::saturated(eve::inc)(a), v_t(a == eve::valmax(eve::as(a)) ? a : a+1));
};
