/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/pedantic/fma.hpp>
#include <eve/function/numeric/fma.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/round.hpp>
#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
// auto types_tests = []<typename T>(auto& runtime, bool verbose, auto const&, T)
// {
//   using v_t = eve::element_type_t<T>;

//   //multi
//   TTS_EXPR_IS( eve::fma(T(), T(), T()  )  , T);
//   TTS_EXPR_IS( eve::fma(T(), v_t(), T())  , T);
//   TTS_EXPR_IS( eve::fma(v_t(), T(), T())  , T);
//   TTS_EXPR_IS( eve::fma(T(), T(), v_t() ) , T);
//   TTS_EXPR_IS( eve::fma(v_t(), v_t(), T()) , T);
//   TTS_EXPR_IS( eve::fma(v_t(), T(), v_t()) , T);
//   TTS_EXPR_IS( eve::fma(v_t(), v_t(), v_t()) , v_t);
// };

// EVE_TEST_BED( "Check return types of fma"
//             , eve::test::simd::all_types
//             , eve::test::generate(eve::test::no_data)
//             , types_tests
//             );

//==================================================================================================
// fma tests
//==================================================================================================
// auto simd_tests = []<typename T>( auto& runtime, bool verbose, auto const&
//                                 , T const& a0, T const& a1
//                                 )
// {
//   using eve::fma;
//   using v_t = eve::element_type_t<T>;
//   TTS_ULP_EQUAL( eve::pedantic(fma)(a0, a1, -eve::one(eve::as<T>())), T([&](auto i , auto) { return eve::pedantic(fma)(a0.get(i), a1.get(i), v_t(-1)); }), 2);
// };

// auto onepmileps = []< typename T>(eve::as_<T> const &){return (eve::inc(1000*eve::eps(eve::as(eve::element_type_t<T>())))) ;};
// auto onemmileps = []< typename T>(eve::as_<T> const &){return (eve::oneminus(1000*eve::eps(eve::as(eve::element_type_t<T>())))) ;};

// EVE_TEST_BED( "Check behavior of fma on all types"
//             , eve::test::simd::ieee_reals
//             , eve::test::generate (  eve::test::randoms(onemmileps, onepmileps)
//                                   ,  eve::test::randoms(onemmileps, onepmileps)
//                                   )
//             , simd_tests
//             );


//==================================================================================================
// fma tests
//==================================================================================================
auto simd_tests = []<typename T>( auto& runtime, bool verbose, auto const&
                                        , T const& a0, T const& a1, T const& a2
                                        )
{
  using eve::fma;
  TTS_ULP_EQUAL(fma((a0), (a1), (a2)), T([&](auto i , auto) { return eve::pedantic(fma)((a0.get(i)), (a1.get(i)), (a2.get(i))); }), 2);
  TTS_ULP_EQUAL(eve::pedantic(fma)((a0), (a1), (a2)), T([&](auto i , auto) { return eve::pedantic(fma)((a0.get(i)), (a1.get(i)), (a2.get(i))); }), 2);
  TTS_ULP_EQUAL(eve::numeric(fma)((a0), (a1), (a2)), T([&](auto i , auto) { return eve::pedantic(fma)((a0.get(i)), (a1.get(i)), (a2.get(i))); }), 2);
};

EVE_TEST_BED( "Check behavior of fma on all types"
            , eve::test::simd::all_types
            , eve::test::generate (  eve::test::randoms(eve::valmin, eve::mone)
                                  ,  eve::test::randoms(eve::valmin, eve::mone)
                                  ,  eve::test::randoms(eve::valmin, eve::mone)
                                  )
            , simd_tests
            );

EVE_TEST_BED( "Check behavior of fma on all types"
            , eve::test::simd::all_types
            , eve::test::generate (  eve::test::randoms(eve::one, eve::valmax)
                                  ,  eve::test::randoms(eve::one, eve::valmax)
                                  ,  eve::test::randoms(eve::one, eve::valmax)
                                  )
            , simd_tests
            );
EVE_TEST_BED( "Check behavior of fma on all types"
            , eve::test::simd::all_types
            , eve::test::generate (  eve::test::randoms(eve::valmin, eve::valmax)
                                  ,  eve::test::randoms(eve::valmin, eve::valmax)
                                  ,  eve::test::randoms(eve::valmin, eve::valmax)
                                  )
            , simd_tests
            );
