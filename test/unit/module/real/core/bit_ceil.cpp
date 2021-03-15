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
#include <eve/function/bit_ceil.hpp>
#include <bit>

//==================================================================================================
// Types tests
//==================================================================================================
auto  types_tests = []<typename T>(auto& runtime, bool verbose, auto const&, T)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::bit_ceil(T())  , T);
  TTS_EXPR_IS( eve::bit_ceil(v_t()), v_t);
};

EVE_TEST_BED( "Check return types of bit_ceil on wide"
            , eve::test::simd::all_types
            , eve::test::generate(eve::test::no_data)
            , types_tests
            );




//==================================================================================================
// bit_ceil signed tests
//==================================================================================================
auto simd_integral_tests = []<typename T>( auto& runtime, bool verbose, auto const&
                                , T const& a0
                                )
{
//  using v_t = eve::element_type_t<T>;
  TTS_EQUAL( eve::bit_ceil(a0), T([&](auto i, auto) { return std::bit_ceil(a0.get(i)); }));
};

//auto min = []< typename T>(eve::as_<T> const &){return eve::unsigned_value<T> ? 0: -10;};
auto max = []< typename T>(eve::as_<T> const &){return eve::valmax(eve::as<T>())/2; };
EVE_TEST_BED( "Check behavior of bit_ceil on wide"
            , eve::test::simd::unsigned_integers
            , eve::test::generate(eve::test::randoms(0, max))
            , simd_integral_tests
            );

// auto simd_signed_tests2 = []<typename T>( auto& runtime, bool verbose, auto const&
//                                 , T const& a0
//                                 )
// {
//   using v_t = eve::element_type_t<T>;
//   TTS_EQUAL( eve::saturated(eve::bit_ceil)(a0)
//            , (T( [&](auto i, auto) {
//                    auto z = a0.get(i);
//                    return (z > 0 ? v_t(z)
//                            : (z == eve::valmin(eve::as(v_t())) ? eve::valmax(eve::as(v_t())) : -z));
//                  }))
//              );
// };

// EVE_TEST_BED( "Check behavior of bit_ceil on wide"
//             , eve::test::simd::signed_types
//             , eve::test::generate (eve::test::randoms(eve::valmin, eve::valmax))
//             , simd_signed_tests2
//             );

// //==================================================================================================
// // bit_ceil unsigned tests
// //==================================================================================================

// auto simd_unsigned_tests = []<typename T>( auto& runtime, bool verbose, auto const&
//                                 , T const& a0
//                                 )
// {
//   TTS_EQUAL( eve::bit_ceil(a0), a0);
//   TTS_EQUAL( eve::saturated(eve::bit_ceil)(a0), a0);
// };

// EVE_TEST_BED( "Check behavior of bit_ceil on wide"
//             , eve::test::simd::unsigned_types
//             , eve::test::generate ( eve::test::randoms(0, eve::valmax))
//             , simd_unsigned_tests
//             );
