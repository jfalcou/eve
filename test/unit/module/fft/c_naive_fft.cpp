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

TTS_CASE_WITH ( "Check behavior of naive_fft on scalar"
              , tts::bunch<eve::test::scalar::ieee_reals>
              , tts::generate(tts::randoms(-1.0, +1.0)
                             , tts::randoms(-1.0, +1.0))
              )
  <typename T>(T const& , T const&  )
{
//  size_t N = 4;
  using e_t = typename T::value_type;
  using c_t = eve::complex<e_t>;

  eve::algo::soa_vector<c_t> a{c_t(1, 1), c_t(2, -1), c_t(3, -2), c_t(4, 5)};

  TTS_EQUAL(0, 0);
  eve::algo::soa_vector<c_t> c = eve::naive_fft(a, e_t(1.0), e_t(-1));
  eve::algo::soa_vector<c_t> d = eve::naive_fft(c, e_t(1)/c.size(), e_t(1));
  for(size_t i=0; i < a.size() ; ++i)
  {
    TTS_ULP_EQUAL(a.get(i), d.get(i), 0.5);
  }

  std::cout << "a =  (";
  for(size_t i=0; i < a.size() ; ++i)
  {
    std::cout << a.get(i) << " ";
  }
  std::cout << ")" << std::endl;
  std::cout << "c =  (";
  for(size_t i=0; i < c.size() ; ++i)
  {
    std::cout << c.get(i) << " ";
  }
  std::cout << ")" << std::endl;

  std::cout << "d =  (";
  for(size_t i=0; i < d.size() ; ++i)
  {
    std::cout << d.get(i) << " ";
  }
  std::cout << ")" << std::endl;

};
