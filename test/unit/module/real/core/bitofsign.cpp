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
#include <eve/constant/signmask.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/logical.hpp>
#include <type_traits>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST( "Check return types of bitofsign"
            , eve::test::simd::all_types
            , eve::test::generate(eve::test::no_data)
            )
<typename T>(T)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::bitofsign(T())  , T);
  TTS_EXPR_IS( eve::bitofsign(v_t()), v_t);
  TTS_EXPR_IS( eve::bitofsign[eve::logical<T>()](T())  , T);
  TTS_EXPR_IS( eve::bitofsign[eve::logical<T>()](v_t()), T);
  TTS_EXPR_IS( eve::bitofsign[eve::logical<v_t>()](T())  , T);
  TTS_EXPR_IS( eve::bitofsign[eve::logical<v_t>()](v_t()), v_t);
  TTS_EXPR_IS( eve::bitofsign[bool()](T())  , T);
  TTS_EXPR_IS( eve::bitofsign[bool()](v_t()), v_t);
};



//==================================================================================================
// bitofsign  tests
//==================================================================================================
EVE_TEST( "Check behavior of bitofsign on wide"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0 )
{
  TTS_EQUAL( eve::bitofsign(a0), T([&](auto i, auto) { auto x = a0.get(i); return eve::bit_and(x, eve::signmask(eve::as(x))); }));
};

// EVE_TEST( "Check behavior of saturated(bitofsign) on signed integral wide"
//         , eve::test::simd::signed_integers
//         , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
//         )
// <typename T>(T const& a0 )
// {
//   using eve::as;
//   TTS_EQUAL( eve::bitofsign(a0), T([&](auto i, auto) { auto a0i = a0.get(i); return a0i == eve::valmin(as(a0i)) ? eve::valmax(as(a0i)) : std::bitofsign(a0i); }));
// };


//==================================================================================================
// bitofsign unsigned tests
//==================================================================================================
// EVE_TEST( "Check behavior of bitofsign on unsigned wide"
//             , eve::test::simd::unsigned_types
//             , eve::test::generate ( eve::test::randoms(0, eve::valmax))
//             )
// <typename T>(T const& a0 )
// {
//   TTS_EQUAL( eve::bitofsign(a0), a0);
//   TTS_EQUAL( eve::saturated(eve::bitofsign)(a0), a0);
// };
