//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"
#include "../complex/measures.hpp"
#include <eve/module/algo.hpp>
#include <eve/module/complex.hpp>
#include <eve/module/fft.hpp>


TTS_CASE_WITH ( "Check behavior of naive on scalar"
              , tts::bunch<eve::test::scalar::ieee_reals>
              , tts::generate(tts::randoms(-1.0, +1.0)
                             , tts::randoms(-1.0, +1.0))
              )
<typename T>(T const& , T const&  )
{
  size_t N = 11;
  std::cout << tts::typename_<T> << std::endl; ;
  using e_t = typename T::value_type;
  std::vector<e_t> a(N);
  for(size_t i=0; i < N ; ++i) a[i] = i+1;

  using c_t = eve::complex<e_t>;
  TTS_EQUAL(0, 0);
  std::vector<c_t> c = eve::naive_fft(a, e_t(1.0), e_t(-1));
  eve::algo::soa_vector<c_t> sc(N);

  for(size_t i=0; i < N; ++i) sc.set(i, c_t(c[i]));

  eve::algo::soa_vector<c_t> sd =  eve::naive_fft(sc, e_t(1.0)/N, e_t(1));
  for(size_t i=0; i < N; ++i)
  {
    TTS_ULP_EQUAL(eve::real(sd.get(i)), a[i], 200);
  }
};
