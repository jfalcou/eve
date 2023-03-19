//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"

#include <eve/module/fft.hpp>
#include <array>

TTS_CASE_WITH ( "Check behavior of abs on scalar"
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

  for(size_t i = 0; i <  N ; ++i) a[i] = i;
  using c_t = eve::complex<e_t>;
  TTS_EQUAL(0, 0);
  std::vector<c_t> c = eve::fft(a, e_t(1.0), e_t(-1));

  std::cout << "a =  (";
  for(size_t i=0; i < N ; ++i)
  {
    std::cout << a[i] << " ";
  }
  std::cout << ")" << std::endl;
  std::cout << "c =  (";
  for(size_t i=0; i < N ; ++i)
  {
    std::cout << c[i] << " ";
  }
  std::cout << ")" << std::endl;

  std::vector<c_t> d = eve::fft(c, e_t(1)/N, e_t(1));
  std::cout << "d =  (";
  for(size_t i=0; i < N ; ++i)
  {
    std::cout << d[i] << " ";
  }
  std::cout << ")" << std::endl;

};
