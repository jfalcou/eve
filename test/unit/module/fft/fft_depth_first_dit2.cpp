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


TTS_CASE_WITH ( "Check behavior of dit2 simd on scalar"
              , tts::bunch<eve::test::scalar::ieee_reals>
              , tts::generate(tts::randoms(-1.0, +1.0)
                             , tts::randoms(-1.0, +1.0))
              )
<typename T>(T const& , T const&  )
{
  size_t N = 1024;
  using e_t = typename T::value_type;
  using c_t = eve::complex<e_t>;

  std::vector<c_t> a(N);
  for(size_t i=0; i < N ; ++i) a[i] =  c_t(i+1, 1);
  eve::fft_df2(a, e_t(1.0), e_t(-1));
  std::cout << "a =  (";
  for(size_t i=0; i < N; ++i) std::cout << a[i] << ",  ";
  std::cout << ")\n";

  std::vector<c_t> ascal(N);
  for(size_t i=0; i < N ; ++i) ascal[i] =  c_t(i+1, 1);
  eve::fft_dt2(ascal, e_t(1.0), e_t(-1));
  std::cout << "ascal =  (";
  for(size_t i=0; i < N; ++i) std::cout << ascal[i] << ",  ";
  std::cout << ")\n";



//   eve::algo::soa_vector<c_t> a(N);
//   for(size_t i=0; i < N ; ++i) a.set(i, c_t(i+1, 1));

//   eve::fft_df2(a, e_t(1.0), e_t(-1));
//   std::cout << "asimd =  (";
//   for(size_t i=0; i < N; ++i) std::cout << a.get(i) << ",  ";
//   std::cout << ")\n";


//   std::vector<c_t> ascal(N);
//   for(size_t i=0; i < N ; ++i) ascal[i] =  c_t(i+1, 1);
//   eve::fft_df2(ascal, e_t(1.0), e_t(-1));
//   std::cout << "ascal =  (";
//   for(size_t i=0; i < N; ++i) std::cout << ascal[i] << ",  ";
//   std::cout << ")\n";


  for(size_t i=0; i < N; ++i){
    std::cout << "i = " << i << " -> " << a[i] << " = ?   " << ascal[i] << std::endl;
    TTS_ULP_EQUAL(a[i], ascal[i], 33000) << "i = " << i << "\n";
  }
};
