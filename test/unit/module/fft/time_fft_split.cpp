//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"
#include "../complex/measures.hpp"
#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>
#include <eve/module/complex.hpp>
#include <eve/module/fft.hpp>
#include <vector>
#include <chrono>
#include <string>
#include <iomanip>

template <typename F, typename T, eve::decorator D>
void timeit(std::string const & title, F const & fft, D const &, T fac, int max = 16)
{

  using e_t = T;
  using c_t = eve::complex<e_t>;
  std::int32_t j = 512;
  std::cout << "duration for " << title;
  std::cout << ",  type being " << tts::typename_<e_t> << std::endl;
  std::vector<double> durations(max);
  std::vector<double> ratios(max);
  std::vector<std::int32_t> size(max);
  for(std::int32_t i=0; i < max; ++i)
  {
    j <<= 1;
    auto data = [j](){
      if constexpr(std::same_as<D, eve::aos_type>){
        std::vector<c_t> a(j, c_t(1, 2));
        for(std::int32_t i=0; i < j; ++i) a[i] = c_t(i, i+1);
        return a;
      }
      else if constexpr(std::same_as<D, eve::soa_type>){
        eve::algo::soa_vector<c_t> a(j, c_t(1, 2));
        for(std::int32_t i=0; i < j; ++i) a.set(i, c_t(i, i+1));
        return a;
      }
    };

    [[maybe_unused]] auto a = data();
    using namespace std::literals;
    auto tic =  std::chrono::steady_clock::now();
    fft(a, fac);
//    std::cout << eve::read(a.begin()) << std::endl;
    auto toc =  std::chrono::steady_clock::now()-tic;
    durations[i] = std::chrono::duration<double>(toc).count()*1000;
    size[i] = j;
  }
  ratios[0] = 1;
  for(std::int32_t i=1; i < max; ++i) ratios[i] = durations[i]/durations[i-1];
  std::cout << std::left;
  std::cout << "size        | ";
  for(std::int32_t i=0; i < max; ++i) std::cout << std::setw(10) << size[i] << " | ";
  std::cout << "\n";
  std::cout << "duration ms | ";
  for(std::int32_t i=0; i < max; ++i) std::cout << std::setw(10) << durations[i] << " | ";
  std::cout << "\n";
  std::cout << "ratio       | ";
  for(std::int32_t i=0; i < max; ++i) std::cout << std::setw(10) << ratios[i] << " | ";
  std::cout << "\n";

}

TTS_CASE_TPL("Check naive_fft", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  if(eve::cardinal_v<T> == 1)
  {
    using e_t = eve::element_type_t<T>;
    timeit("eve::aos(eve::fft_split)", eve::aos(eve::fft_split), eve::aos_type{}, e_t(1.0), 10);
    timeit("eve::soa(eve::fft_split)", eve::soa(eve::fft_split), eve::soa_type{}, e_t(1.0), 10);
    std::cout << "==========================================================================================================================" << std::endl;
  }
  TTS_EQUAL(0, 0);
  return 0;
};
