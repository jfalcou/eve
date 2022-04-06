/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <algorithm>
#include <eve/module/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
// EVE_TEST_TYPES( "Check return types of sum_of_prod"
//               , eve::test::simd::ieee_reals
//               )
// <typename T>(eve::as<T>)
// {
//   using v_t = eve::element_type_t<T>;

//   TTS_EXPR_IS( eve::sum_of_prod(T(), T(), T(), T()  )  , T);
//   TTS_EXPR_IS( eve::sum_of_prod(T(), v_t(), T(), T())  , T);
//   TTS_EXPR_IS( eve::sum_of_prod(v_t(), T(), T(), T())  , T);
//   TTS_EXPR_IS( eve::sum_of_prod(T(), T(), v_t(), T() ) , T);
//   TTS_EXPR_IS( eve::sum_of_prod(v_t(), v_t(), T(), T()) , T);
//   TTS_EXPR_IS( eve::sum_of_prod(v_t(), T(), v_t(), T()) , T);
//   TTS_EXPR_IS( eve::sum_of_prod(v_t(), v_t(), v_t(), v_t()) , v_t);

// };

// //==================================================================================================
// // sum_of_prod tests
// //==================================================================================================


// EVE_TEST( "Check precision behavior of sum_of_prod on real types"
//         , eve::test::simd::ieee_reals
//         , eve::test::generate (  eve::test::randoms(-10, 10)
//                               ,  eve::test::randoms(-10, 10)
//                               ,  eve::test::randoms(-10, 10)
//                               ,  eve::test::randoms(-10, 10)
//                               )
//         )
// <typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
// {
//   using eve::sum_of_prod;
//   TTS_ULP_EQUAL ( sum_of_prod(a0,a1,a2,a3), a0*a1+a2*a3 , 10);
//   TTS_ULP_EQUAL ( eve::diff_1st(sum_of_prod)(a0,a1,a2,a3), a1 , 10);
//   TTS_ULP_EQUAL ( eve::diff_2nd(sum_of_prod)(a0,a1,a2,a3), a0 , 10);
//   TTS_ULP_EQUAL ( eve::diff_3rd(sum_of_prod)(a0,a1,a2,a3), a3 , 10);
//   TTS_ULP_EQUAL ( eve::diff_nth<4>(sum_of_prod)(a0,a1,a2,a3), a2 , 10);
// };

//==================================================================================================
// sum_of_prod full N-parameters
//==================================================================================================
EVE_TEST( "Check behavior of sum_of_prod on all types full range"
        , eve::test::simd::ieee_reals
        , eve::test::generate (  eve::test::randoms(-10, 10)
                              ,  eve::test::randoms(-10, 10)
                              ,  eve::test::randoms(-10, 10)
                              ,  eve::test::randoms(-10, 10)
                              ,  eve::test::randoms(-10, 10)
                              ,  eve::test::randoms(-10, 10)
                              ,  eve::test::randoms(-10, 10)
                              ,  eve::test::randoms(-10, 10)                              )
        )
  <typename T>(  T const& a0, T const& a1, T const& a2, T const& a3
              ,  T const& a4, T const& a5, T const& a6, T const& a7)
{
  using eve::as;
  using eve::sum_of_prod;

  TTS_ULP_EQUAL(sum_of_prod(a0, a1, a2, a3, a4, a5, a6, a7), a0*a1+a2*a3+a4*a5+a6*a7, 20);
  TTS_ULP_EQUAL(eve::diff_1st(sum_of_prod)(a0,a1,a2,a3,a4,a5,a6,a7),a1,0);
  TTS_ULP_EQUAL(eve::diff_2nd(sum_of_prod)(a0,a1,a2,a3,a4,a5,a6,a7),a0,0);
  TTS_ULP_EQUAL(eve::diff_3rd(sum_of_prod)(a0,a1,a2,a3,a4,a5,a6,a7),a3,0);
  TTS_ULP_EQUAL(eve::diff_nth<4>(sum_of_prod)(a0,a1,a2,a3,a4,a5,a6,a7),a2,0);
  TTS_ULP_EQUAL(eve::diff_nth<5>(sum_of_prod)(a0,a1,a2,a3,a4,a5,a6,a7),a5,0);
  TTS_ULP_EQUAL(eve::diff_nth<6>(sum_of_prod)(a0,a1,a2,a3,a4,a5,a6,a7),a4,0);
  TTS_ULP_EQUAL(eve::diff_nth<7>(sum_of_prod)(a0,a1,a2,a3,a4,a5,a6,a7),a7,0);
  TTS_ULP_EQUAL(eve::diff_nth<8>(sum_of_prod)(a0,a1,a2,a3,a4,a5,a6,a7),a6,0);
};
