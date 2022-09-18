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
#include <eve/module/core.hpp>
#include <complex>

template < typename T >
auto cv(std::complex < T > sc)
{
  return eve::complex<T>(sc.real(), sc.imag());
}

TTS_CASE_WITH ( "Check behavior of lbeta on wide"
              , eve::test::simd::ieee_reals
              , tts::generate ( tts::randoms(0.1, 10)
                              , tts::randoms(0.1, 10)
                              , tts::randoms(0.1, 10)
                              , tts::randoms(0.1, 10)
                              )
              )
<typename T>(T const& a0, T const& a1, T const& , T const&  )
{
  using z_t = eve::as_complex_t<T>;
  using e_t = typename T::value_type;
  auto a = z_t(a0, a1);

  TTS_ULP_EQUAL( eve::lbeta(a, T(3))   , eve::lbeta(a, e_t(3)),  10);
  TTS_ULP_EQUAL( eve::lbeta(a, T(2))   , eve::lbeta(a, e_t(2)),  10);
  TTS_ULP_EQUAL( eve::lbeta(a, T(-2))   , eve::lbeta(a, e_t(-2)),  10);
};
