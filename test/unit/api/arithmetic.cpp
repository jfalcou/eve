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
auto types_tests = []<typename T>(auto& runtime, bool verbose, auto const&, T)
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

EVE_TEST_BED( "Check return types of arithmetic operators on wide"
            , eve::test::simd::all_types
            , eve::test::generate(eve::test::no_data)
            , types_tests
            );

//==================================================================================================
// wide (*) wide tests
//==================================================================================================
auto simd_tests = []<typename T>( auto& runtime, bool verbose, auto const&
                                , T const& a0, T const& a1, T const& a2
                                )
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

EVE_TEST_BED( "Check behavior of arithmetic operators on wide"
            , eve::test::simd::all_types
            , eve::test::generate ( eve::test::randoms(-50, 50  )
                                  , eve::test::randoms( 1 , 100 )
                                  , eve::test::randoms(-50, 50  )
                                  )
            , simd_tests
            );

//==================================================================================================
// wide ++/-- tests
//==================================================================================================
auto incdec_tests = []<typename T>( auto& runtime, bool verbose, auto const&
                                  , T, T a1, T
                                  )
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

EVE_TEST_BED( "Check behavior of pre/post increment/decrement operators on wide"
            , eve::test::simd::all_types
            , eve::test::generate ( eve::test::randoms(-50, 50  )
                                  , eve::test::randoms( 1 , 100 )
                                  , eve::test::randoms(-50, 50  )
                                  )
            , incdec_tests
            );

//==================================================================================================
// scalar (*) wide tests
//==================================================================================================
auto mixed_tests = []<typename T>( auto& runtime, bool verbose, auto const&
                                , T const& a0, T const& a1, T const&
                                )
{
  TTS_EQUAL( (a0 + 3), T([&](auto i, auto) { return a0.get(i) + 3; }) );
  TTS_EQUAL( (a0 - 3), T([&](auto i, auto) { return a0.get(i) - 3; }) );
  TTS_EQUAL( (3 - a0), T([&](auto i, auto) { return 3 - a0.get(i); }) );
  TTS_EQUAL( (a0 * 3), T([&](auto i, auto) { return a0.get(i) * 3; }) );
  TTS_ULP_EQUAL( (a0 / 3), T([&](auto i, auto) { return a0.get(i) / 3; }), 1 );
  TTS_ULP_EQUAL( (3 / a1), T([&](auto i, auto) { return 3 / a1.get(i); }), 1 );

  if constexpr( eve::integral_value<T> )
  {
    TTS_EQUAL( (a0 % 3), T([&](auto i, auto) { return a0.get(i) % 3; }));
    TTS_EQUAL( (3 % a1), T([&](auto i, auto) { return 3 % a1.get(i); }));
  }
};

EVE_TEST_BED( "Check behavior of arithmetic operators on wide and scalar"
            , eve::test::simd::all_types
            , eve::test::generate ( eve::test::randoms(-50, 50  )
                                  , eve::test::randoms( 1 , 100 )
                                  , eve::test::randoms(-50, 50  )
                                  )
            , mixed_tests
            );
