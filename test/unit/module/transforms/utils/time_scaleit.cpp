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

template <eve::detail::range  R, typename T>
EVE_FORCEINLINE void ref_scaleit(R& f, T fac)
{
  if (fac != eve::one(eve::as(fac)))
  {
    auto n = std::size(f);
    using i_t = decltype(n);
    for (i_t i=0; i < n; ++i)
    {
      f[i]*= fac;
    }
  }
}


template <typename T, eve::decorator D>
void timeit(std::string const & title, D const &, auto start, auto maxi = 16 )
{

  using e_t = T;
  std::int32_t j = start;
  std::int32_t max = maxi;
  std::cout << "duration for " << title;
  std::cout << ",  type being " << tts::typename_<e_t> << std::endl;
  std::vector<double> simd_durations(max);
  std::vector<double> scal_durations(max);
  std::vector<double> ratios(max);
  std::vector<std::int32_t> size(max);
  for(std::int32_t i=0; i < max; ++i)
  {
    auto data = [j](){
      if constexpr(std::same_as<D, eve::aos_type>){
        std::vector<e_t> a(j);
        for(std::int32_t i=0; i < j; ++i) {a[i] = i+1; }
        return a;
      }
      else if constexpr(std::same_as<D, eve::soa_type>){
        eve::algo::soa_vector<e_t> a(j, e_t(1));
        for(std::int32_t i=0; i < j; ++i) {a.set(i, i+1); }
        return a;
      }
    };

    [[maybe_unused]] auto a = data();
    using namespace std::literals;
    auto tic =  std::chrono::steady_clock::now();
    eve::scaleit(a, e_t(3.5));
    auto toc =  std::chrono::steady_clock::now()-tic;
    simd_durations[i] = std::chrono::duration<double>(toc).count()*1000;
     tic =  std::chrono::steady_clock::now();
    ref_scaleit(a, e_t(3.5));
     toc =  std::chrono::steady_clock::now()-tic;
    scal_durations[i] = std::chrono::duration<double>(toc).count()*1000;
    size[i] = j;
    j <<= 1;
  }
  for(std::int32_t i=0; i < max; ++i) ratios[i] = scal_durations[i]/simd_durations[i];
  std::cout << std::left;
  std::cout << "size        | ";
  for(std::int32_t i=0; i < max; ++i) std::cout << std::setw(10) << size[i] << " | ";
  std::cout << "\n";
  std::cout << "scalar   ms | ";
  for(std::int32_t i=0; i < max; ++i) std::cout << std::setw(10) << scal_durations[i] << " | ";
   std::cout << "\n";
  std::cout << "simd     ms | ";
  for(std::int32_t i=0; i < max; ++i) std::cout << std::setw(10) << simd_durations[i] << " | ";
  std::cout << "\n";
  std::cout << "ratio       | ";
  for(std::int32_t i=0; i < max; ++i) std::cout << std::setw(10) << ratios[i] << " | ";
  std::cout << "\n";
}

TTS_CASE_TPL("Check ht_ft_cv", eve::test::simd::ieee_reals)
  <typename T>(tts::type<T>)
{
  if constexpr( eve::cardinal_v<T> == 1)
  {
    using e_t = eve::element_type_t<T>;
    timeit<e_t>("ht_ft_cv", eve::aos_type{}, 2,  8);
    timeit<e_t>("ht_ft_cv", eve::aos_type{}, 512, 8);
    timeit<e_t>("ht_ft_cv", eve::aos_type{}, 131072, 8);
    std::string sep(116, '-');
    std::cout << sep << std::endl;
    TTS_EQUAL(0, 0);
  }
};
