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

template <eve::detail::range  R>
EVE_FORCEINLINE void ref_ht_ft_cv(R& fr, R& fi, int sign = 1)
{
  auto n = std::size(fr);
  using i_t = decltype(n);
  using e_t =  std::remove_reference_t<decltype(fr[0])>;
  for (i_t i=1, j=n-1;  i<j;  i++, j--)
  {
    e_t q, r, s, t;
    if (sign > 0)
    {
      eve::detail::sd(fr[i], fr[j], q, r);
      eve::detail::sd(fi[i], fi[j], s, t);
    }
    else
    {
      eve::detail::sd(fr[j], fr[i], q, r);
      eve::detail::sd(fi[j], fi[i], s, t);
    }
    eve::detail::hsd(q, t, fr[j], fr[i]);
    eve::detail::hsd(s, r, fi[i], fi[j]);
  }
}


template <typename T>
void timeit(std::string const & title, auto start, auto maxi = 16 )
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
    std::vector<e_t> ar(j), ai(j);
    for(std::int32_t i=0; i < j; ++i) {ar[i] = i+1; ai[i] = i+2;}
    using namespace std::literals;
    auto tic =  std::chrono::steady_clock::now();
    ref_ht_ft_cv(ar, ai);
    auto toc =  std::chrono::steady_clock::now()-tic;
    scal_durations[i] = std::chrono::duration<double>(toc).count()*1000;
    tic =  std::chrono::steady_clock::now();
    eve::ht_ft_cv(ar, ai);
    toc =  std::chrono::steady_clock::now()-tic;
    simd_durations[i] = std::chrono::duration<double>(toc).count()*1000;
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
    timeit<e_t>("ht_ft_cv", 2,  8);
    timeit<e_t>("ht_ft_cv", 512, 8);
    timeit<e_t>("ht_ft_cv", 131072, 8);
    std::string sep(116, '-');
    std::cout << sep << std::endl;
    TTS_EQUAL(0, 0);
  }
};
