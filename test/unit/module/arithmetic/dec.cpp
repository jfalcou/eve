//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of dec"
            , eve::test::simd::all_types
            )
<typename T>(eve::as<T>)
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
// dec(simd)  tests
//==================================================================================================
auto valminp1 = []< typename T>(eve::as<T> const &){return eve::inc(eve::valmin(eve::as(eve::element_type_t<T>())));};

EVE_TEST( "Check behavior of dec(wide) and dec[cond](wide)"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::randoms(valminp1, eve::valmax))
        )
<typename T>(T const& a0 )
{
  using v_t = eve::element_type_t<T>;
  using eve::diff;
  TTS_EQUAL( eve::dec(a0), map([](auto e) ->v_t{ return v_t(e-1); }, a0));
  TTS_EQUAL( eve::dec[a0 > 64](a0), map([](auto e) ->v_t{ return v_t((e > 64) ?e-1 : e); }, a0));
  bool z = (a0.get(0) > 64);
  TTS_EQUAL( eve::dec[z](a0), map([&](auto e) ->v_t{ return v_t((z) ?e-1 : e); }, a0));
  if constexpr(eve::floating_real_value<T>)
    TTS_EQUAL( diff(eve::dec)(a0), eve::one(eve::as(a0)));

};

EVE_TEST( "Check behavior of saturated(dec)(wide) on integral types"
        , eve::test::simd::integers
        , eve::test::generate(eve::test::randoms(eve::valmin, valminp1))
        )
<typename T>(T const& a0 )
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL( eve::saturated(eve::dec)(a0), map([](auto e) ->v_t {
                                                 return v_t(e == eve::valmin(eve::as(e)) ? e : e-1); }, a0));
  TTS_EQUAL( eve::saturated(eve::dec[a0 > 64])(a0)
           , map([](auto e) ->v_t{ return v_t((e > 64
                                               && e != eve::valmin(eve::as(e)) ? e-1 : e)); }, a0));
  bool z = (a0.get(0) > 64);
   TTS_EQUAL( eve::saturated(eve::dec[z])(a0)
           , map([&](auto e) ->v_t{ return v_t((z
                                               && e != eve::valmin(eve::as(e)) ? e-1 : e)); }, a0));
 };


EVE_TEST( "Check behavior of saturated(dec)(wide) on integral types"
        , eve::test::simd::integers
        , eve::test::generate(eve::test::randoms(eve::valmin, valminp1))
        )
<typename T>(T const& a0 )
{
  using v_t = typename T::value_type;
  for (int i = 0; i != T::size(); ++i) {
    auto a = a0.get(i);
    TTS_EQUAL( eve::saturated(eve::dec)(a), v_t(a == eve::valmin(eve::as(a)) ? a : a-1));
  }
};
