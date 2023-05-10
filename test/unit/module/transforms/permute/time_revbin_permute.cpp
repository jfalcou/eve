//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"
#include <eve/module/transforms.hpp>
#include <eve/module/transforms/detail/pr.hpp>
#include <chrono>

template <typename T, eve::decorator D>
void timeit(std::string const & title, D const &, auto start, auto maxi = 16 )
{

  using e_t = T;
  using c_t = eve::complex<e_t>;
  std::int32_t j = start;
  std::int32_t max = maxi;
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
    eve::revbin_permute(a);
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
  //   std::cout << "ratio       | ";
  //   for(std::int32_t i=0; i < max; ++i) std::cout << std::setw(10) << ratios[i] << " | ";
  //   std::cout << "\n";
}

TTS_CASE_TPL("Check revbin_permute", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( eve::cardinal_v<T> == 1)
  {
    using e_t = eve::element_type_t<T>;
    timeit<e_t>("revbin_permute", eve::aos_type{}, 2,  8);
    timeit<e_t>("revbin_permute", eve::aos_type{}, 64, 8);
    timeit<e_t>("revbin_permute", eve::aos_type{}, 16384, 8);
    std::string sep(116, '-');
    std::cout << sep << std::endl;
    TTS_EQUAL(0, 0);
  }
};
