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
#include <eve/function/abs.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/diff/abs.hpp>
#include <eve/function/saturated/abs.hpp>
#include <eve/logical.hpp>
#include <type_traits>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
auto  types_tests = []<typename T>(auto& runtime, bool verbose, auto const&, T)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::abs(T())  , T);
  TTS_EXPR_IS( eve::abs(v_t()), v_t);
  TTS_EXPR_IS( eve::abs[eve::logical<T>()](T())  , T);
  TTS_EXPR_IS( eve::abs[eve::logical<T>()](v_t()), T);
  TTS_EXPR_IS( eve::abs[eve::logical<v_t>()](T())  , T);
  TTS_EXPR_IS( eve::abs[eve::logical<v_t>()](v_t()), v_t);
  TTS_EXPR_IS( eve::abs[bool()](T())  , T);
  TTS_EXPR_IS( eve::abs[bool()](v_t()), v_t);


  TTS_EXPR_IS( eve::saturated(eve::abs)(T())  , T);
  TTS_EXPR_IS( eve::saturated(eve::abs)(v_t()), v_t);
  TTS_EXPR_IS( eve::saturated(eve::abs[eve::logical<T>()])(T())  , T);
  TTS_EXPR_IS( eve::saturated(eve::abs[eve::logical<T>()])(v_t()), T);
  TTS_EXPR_IS( eve::saturated(eve::abs[eve::logical<v_t>()])(T())  , T);
  TTS_EXPR_IS( eve::saturated(eve::abs[eve::logical<v_t>()])(v_t()), v_t);
  TTS_EXPR_IS( eve::saturated(eve::abs[bool()])(T())  , T);
  TTS_EXPR_IS( eve::saturated(eve::abs[bool()])(v_t()), v_t);

  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::diff(eve::abs)(T())  , T);
    TTS_EXPR_IS( eve::diff(eve::abs)(v_t()), v_t);
  }
};

EVE_TEST_BED( "Check return types of abs on wide"
            , eve::test::simd::all_types
            , eve::test::generate(eve::test::no_data)
            , types_tests
            );




//==================================================================================================
// abs signed tests
//==================================================================================================
auto simd_signed_tests = []<typename T>( auto& runtime, bool verbose, auto const&
                                , T const& a0
                                )
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL( eve::abs(a0), T([&](auto i, auto) { return a0.get(i) > 0 ? v_t(a0.get(i)) : -v_t(a0.get(i)); }));
  if constexpr(eve::floating_real_value<T>)
    TTS_EQUAL( eve::diff(eve::abs)(a0)
             , (T([&](auto i, auto) {
                   auto z = a0.get(i); return (z > 0 ? v_t(1)
                                               : (z <  0) ? v_t(-1) : v_t(0));
                  }))
             );
};

auto valminp1 = []< typename T>(eve::as_<T> const &){return eve::inc(eve::valmin(eve::as(eve::element_type_t<T>())));};

EVE_TEST_BED( "Check behavior of abs on wide"
            , eve::test::simd::signed_types
            , eve::test::generate(eve::test::randoms(valminp1, eve::valmax))
            , simd_signed_tests
            );

auto simd_signed_tests2 = []<typename T>( auto& runtime, bool verbose, auto const&
                                , T const& a0
                                )
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL( eve::saturated(eve::abs)(a0)
           , (T( [&](auto i, auto) {
                   auto z = a0.get(i);
                   return (z > 0 ? v_t(z)
                           : (z == eve::valmin(eve::as(v_t())) ? eve::valmax(eve::as(v_t())) : -z));
                 }))
             );
};

EVE_TEST_BED( "Check behavior of abs on wide"
            , eve::test::simd::signed_types
            , eve::test::generate (eve::test::randoms(eve::valmin, eve::valmax))
            , simd_signed_tests2
            );

//==================================================================================================
// abs unsigned tests
//==================================================================================================

auto simd_unsigned_tests = []<typename T>( auto& runtime, bool verbose, auto const&
                                , T const& a0
                                )
{
  TTS_EQUAL( eve::abs(a0), a0);
  TTS_EQUAL( eve::saturated(eve::abs)(a0), a0);
};

EVE_TEST_BED( "Check behavior of abs on wide"
            , eve::test::simd::unsigned_types
            , eve::test::generate ( eve::test::randoms(0, eve::valmax))
            , simd_unsigned_tests
            );
