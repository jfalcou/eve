//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of arithmetic operators on wide", eve::test::simd::all_types)
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( T()    + T()   , T);
  TTS_EXPR_IS( T()    - T()   , T);
  TTS_EXPR_IS( T()    * T()   , T);
  TTS_EXPR_IS( T()    / T()   , T);
  TTS_EXPR_IS( T()    + v_t() , T);
  TTS_EXPR_IS( v_t()  + T()   , T);
  TTS_EXPR_IS( T()    - v_t() , T);
  TTS_EXPR_IS( v_t()  - T()   , T);
  TTS_EXPR_IS( T()    * v_t() , T);
  TTS_EXPR_IS( v_t()  * T()   , T);
  TTS_EXPR_IS( T()    / v_t() , T);
  TTS_EXPR_IS( v_t()  / T()   , T);

  if constexpr( eve::integral_value<T> )
  {
    TTS_EXPR_IS( T() % T(), T);
    TTS_EXPR_IS( v_t()% T(), T);
    TTS_EXPR_IS( T() % v_t(), T);
  }
};

//==================================================================================================
// wide (*) wide tests
//==================================================================================================
EVE_TEST( "Check behavior of arithmetic operators on wide"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms( 5, 50  )
                              , eve::test::randoms( 1, 100 )
                              , eve::test::randoms( 5, 50  )
                              )
        )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  TTS_EQUAL( (a0 + a2), T([&](auto i, auto) { return a0.get(i) + a2.get(i); }));
  TTS_EQUAL( (a0 - a2), T([&](auto i, auto) { return a0.get(i) - a2.get(i); }));
  TTS_EQUAL( (a0 * a2), T([&](auto i, auto) { return a0.get(i) * a2.get(i); }));
  TTS_ULP_EQUAL( (a0 / a1), T([&](auto i, auto) { return a0.get(i) / a1.get(i); }), 1);

  if constexpr( eve::integral_value<T> )
  {
    TTS_EQUAL( (a0 % a1), T([&](auto i, auto) { return a0.get(i) % a1.get(i); }) );
  }
};

//==================================================================================================
// wide ++/-- tests
//==================================================================================================
EVE_TEST( "Check behavior of pre/post increment/decrement operators on wide"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms( 5, 50  )
                              , eve::test::randoms( 1, 100 )
                              , eve::test::randoms( 5, 50  )
                              )
        )
<typename T>(T, T a1, T)
{
  {
    auto d0 = a1;
    auto post_inc  = d0++;
    TTS_EQUAL( post_inc , a1);
    TTS_EQUAL( d0       , a1 + 1);
  }

  {
    auto d0 = a1;
    auto pre_inc  = ++d0;
    TTS_EQUAL( pre_inc, a1 + 1);
    TTS_EQUAL( d0     , a1 + 1);
  }

  {
    auto d0 = a1;
    auto post_dec  = d0--;
    TTS_EQUAL( post_dec , a1);
    TTS_EQUAL( d0       , a1 - 1);
  }

  {
    auto d0 = a1;
    auto pre_dec  = --d0;
    TTS_EQUAL( pre_dec, a1 - 1);
    TTS_EQUAL( d0     , a1 - 1);
  }
};

//==================================================================================================
// scalar (*) wide tests
//==================================================================================================
EVE_TEST( "Check behavior of arithmetic operators on wide and scalar"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms( 5, 50  )
                              , eve::test::randoms( 1, 100 )
                              , eve::test::randoms( 5, 50  )
                              )
        )
<typename T>(T const& a0, T const& a1, T const& v)
{
  auto s = v.get(0);

  TTS_EQUAL( (a0 + s), T([&](auto i, auto) { return a0.get(i) + s; }) );
  TTS_EQUAL( (a0 - s), T([&](auto i, auto) { return a0.get(i) - s; }) );
  TTS_EQUAL( (s - a0), T([&](auto i, auto) { return s - a0.get(i); }) );
  TTS_EQUAL( (a0 * s), T([&](auto i, auto) { return a0.get(i) * s; }) );
  TTS_ULP_EQUAL( (a0 / s), T([&](auto i, auto) { return a0.get(i) / s; }), 1 );
  TTS_ULP_EQUAL( (s / a1), T([&](auto i, auto) { return s / a1.get(i); }), 1 );

  if constexpr( eve::integral_value<T> )
  {
    TTS_EQUAL( (a0 % s), T([&](auto i, auto) { return a0.get(i) % s; }));
    TTS_EQUAL( (s % a1), T([&](auto i, auto) { return s % a1.get(i); }));
  }
};
