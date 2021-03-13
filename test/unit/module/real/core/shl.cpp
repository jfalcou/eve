/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/shl.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
auto types_tests = []<typename T>(auto& runtime, bool verbose, auto const&, T)
{
  using v_t  = eve::element_type_t<T>;
  using i_t  = eve::as_integer_t<T, signed>;
  using u_t  = eve::as_integer_t<T, unsigned>;
  using vi_t = eve::as_integer_t<v_t, signed>;
  using vu_t = eve::as_integer_t<v_t, unsigned>;

  //regular
  TTS_EXPR_IS( eve::shl(T(), T()  ) , T);
  TTS_EXPR_IS( eve::shl(T(), v_t()) , T);
  TTS_EXPR_IS( eve::shl(v_t(), T()) , T);
  TTS_EXPR_IS( eve::shl(v_t(), v_t()) , v_t);
  TTS_EXPR_IS( eve::shl(T(), i_t()  ) , T);
  TTS_EXPR_IS( eve::shl(T(), u_t()) , T);
  TTS_EXPR_IS( eve::shl(v_t(), i_t()) , T);
  TTS_EXPR_IS( eve::shl(v_t(), u_t()) , T);
  TTS_EXPR_IS( eve::shl(T(), vi_t()  ) , T);
  TTS_EXPR_IS( eve::shl(T(), vu_t()) , T);
  TTS_EXPR_IS( eve::shl(v_t(), vi_t()) , v_t);
  TTS_EXPR_IS( eve::shl(v_t(), vu_t()) , v_t);

};

EVE_TEST_BED( "Check return types of shl"
            , eve::test::simd::unsigned_types
            , eve::test::generate(eve::test::no_data)
            , types_tests
            );

//==================================================================================================
// shl tests
//==================================================================================================
auto simd_tests = []<typename T>( auto& runtime, bool verbose, auto const&
                                , T const& a0, T const& a1
                                )
{
  using eve::shl;
  using eve::saturated;
  TTS_EQUAL( shl(a0, a1), T([&](auto i, auto) { return shl(a0.get(i), a1.get(i)); }));

};

auto shift_max = []< typename T>(eve::as_<T> const &){return sizeof(eve::element_type_t<T>)*8-1;};

EVE_TEST_BED( "Check behavior of shl on integral types"
            , eve::test::simd::unsigned_types
            , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                                  , eve::test::randoms(0u, shift_max)
                                  )
            , simd_tests
            );



// //==================================================================================================
// // conditional shl tests
// //==================================================================================================
// auto simd_tests_if = []<typename T>( auto& runtime, bool verbose, auto const&
//                                 , T const& a0, T const& a1, T const& a2
//                                 )
// {
//   using eve::shl;
//   using eve::saturated;

//   TTS_EQUAL( shl[a2 > T(64)](a0, a1), T([&](auto i, auto) {return a2.get(i) > 64 ? shl(a0.get(i), a1.get(i)) :a0.get(i) ; }));
//   TTS_EQUAL( saturated(shl[a2 > T(64)])(a0, a1), T([&](auto i, auto) { return  a2.get(i) > 64 ? saturated(shl)(a0.get(i), a1.get(i)):a0.get(i); }));
// };

// EVE_TEST_BED( "Check behavior of shl on signed types"
//             , eve::test::simd::signed_types
//             , eve::test::generate ( eve::test::randoms(-128, 127)
//                                   , eve::test::randoms(-128, 127)
//                                   , eve::test::randoms(-128, 127)
//                                   )
//             , simd_tests_if
//             );

// EVE_TEST_BED( "Check behavior of shl on unsigned types"
//             , eve::test::simd::unsigned_types
//             , eve::test::generate ( eve::test::randoms(0, 127)
//                                   , eve::test::randoms(0, 127)
//                                   , eve::test::randoms(0, 127)
//                                   )
//             , simd_tests
//             );
