//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"
#include "../complex/measures.hpp"
#include <eve/module/fft.hpp>
#include <chrono>


TTS_CASE_TPL("Check revbin_permute", eve::test::simd::unsigned_integers)
<typename T>(tts::type<T>)
{
  if constexpr(std::same_as<eve::element_type_t<T>, std::uint8_t> && eve::cardinal_v<T> == 1)
  {
    auto pr = [](auto name, auto v){
      std::cout << name << " = (";
      for(size_t i=0; i < v.size() ; ++i) std::cout << eve::read(v.data()+i) << " ";
      std::cout << ")\n";
    };


    for(int n=32; n < 256; n <<= 1)
    {
      std::vector<int32_t> vi(n), orig(n);
      for(int i=0; i < n ; ++i) vi[i] = i;
      pr("vi ", vi);
      std::cout << " =============================== " << n<< std::endl;
      eve::aos(eve::revbin_permute)(vi);
      pr("vi  ", vi);
      eve::aos(eve::revbin_permute)(vi);
      pr("rvi ", vi);
      std::cout << " ------------------------------- " << std::endl;
      for(int i = 0; i < n; i++) TTS_EQUAL(vi[i], i);
    }

    using c_t =  eve::complex<float>;
    int n=32768;
    {
      std::vector<c_t> vi(n);
      auto tic =  std::chrono::steady_clock::now();
      eve::aos(eve::revbin_permute)(vi);
      auto toc =  std::chrono::steady_clock::now();
      std::cout << "duration = " << (toc-tic) << "\n" << std::endl;
      pr("vi  ", vi);
    }
    {
      eve::algo::soa_vector<c_t> vi(n);
      auto tic =  std::chrono::steady_clock::now();
      eve::soa(eve::revbin_permute)(vi);
      auto toc =  std::chrono::steady_clock::now();
      std::cout << "duration = " << (toc-tic) << "\n" << std::endl;
      pr("vi  ", vi);
    }

  }
};
