//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/quaternion.hpp>
#include <complex>

// template < typename ...Cs> auto pipo(auto, Cs... )
// {
//   constexpr size_t N = sizeof...(Cs);
//   std::cout << "N = " << N << std::endl;
// }

TTS_CASE_WITH( "Check behavior of fam on wide quaternion"
             , eve::test::simd::ieee_reals
             ,tts::generate( tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           )
             )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3
             , T const& a4, T const& a5, T const& a6, T const& a7
             , T const& a8, T const& a9, T const& a10, T const& a11
              , T const& a12, T const& a13, T const& a14, T const& a15)
{
  using z_t = eve::as_quaternion_t<T>;
  z_t x{a0, a1, a2, a3};
  z_t q1{a4, a5, a6, a7};
  z_t q2{a8, a9, a10, a11};
  z_t q3{a12, a13, a14, a15};
  using e_t = eve::element_type_t<T>;
   auto tol = 100.0*eve::eps(eve::as<e_t>());
  TTS_RELATIVE_EQUAL(eve::horner(x, q1, q2, q3), (q1*x+q2)*x+q3, tol);
  TTS_RELATIVE_EQUAL(eve::horner(x, q1, q2),     q1*x+q2,tol);
  TTS_RELATIVE_EQUAL(eve::horner(x, q1),         q1, tol);


//   using c_t = eve::as_complex_t<T>;
//   c_t c1{a0, a1};
//   c_t xx{a2, a3};
//    TTS_RELATIVE_EQUAL(eve::horner(xx, c1),         c1, tol);


//   TTS_RELATIVE_EQUAL(eve::horner(a0, a1),         a1, tol);

//    pipo(x, q1);
//    pipo(x, q1, q2);
//    pipo(x, q1, q2, q3);
};
