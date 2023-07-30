//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/complex.hpp>
#include <complex>

// template < typename ...Cs> auto pipo(auto, Cs... )
// {
//   constexpr size_t N = sizeof...(Cs);
//   std::cout << "N = " << N << std::endl;
// }

TTS_CASE_WITH( "Check behavior of fam on wide complex"
             , eve::test::simd::ieee_reals
             ,tts::generate( tts::randoms(-10, 10)
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
             , T const& a4, T const& a5, T const& a6, T const& a7)
{
  using z_t = eve::as_complex_t<T>;
  z_t x {a0, a1};
  z_t c1{a2, a3};
  z_t c2{a4, a5};
  z_t c3{a6, a7};
  auto tol = 0.001;
  TTS_RELATIVE_EQUAL(eve::horner(x, c1, c2, c3), (c1*x+c2)*x+c3, tol);
  TTS_RELATIVE_EQUAL(eve::horner(x, c1, c2),     c1*x+c2,tol);
  TTS_RELATIVE_EQUAL(eve::horner(x, c1),         c1, tol);
};
