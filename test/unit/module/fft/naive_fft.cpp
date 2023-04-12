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
#include <vector>
#include <chrono>

TTS_CASE_TPL("Check naive_fft on aos", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr(std::same_as<eve::element_type_t<T>, double>&& eve::cardinal_v<T> == 1)
  {
//     auto pr = [](auto name, auto v){
//       std::cout << name << " = (";
//       for(size_t i=0; i < v.size() ; ++i) std::cout << v[i] << " ";
//       std::cout << ")\n";
//     };
    size_t N = 1024;
    std::cout << tts::typename_<T> << std::endl; ;
    using e_t = typename T::value_type;
    using c_t = eve::complex<e_t>;
    std::vector<c_t> a(N), orig(N);
    for(size_t i=0; i < N ; ++i) orig[i] = a[i] = c_t(i+1, i+2);
//    pr("a avant", a);
    auto tic =  std::chrono::steady_clock::now();
    eve::aos(eve::naive_fft)(a, e_t(1.0));
    auto toc =  std::chrono::steady_clock::now();
    using namespace std::literals;
    std::cout << "duration naive_fft aos wih n = " << N <<" -> "<< (toc-tic)<< "\n" << std::endl;
//    pr("a apres", a);
    eve::aos(eve::ifft)(eve::aos(eve::naive_fft), a, e_t(1)/N);
//    pr("a apres ifft", a);

    for(int i=0; i < ssize(a) ; ++i) TTS_ULP_EQUAL(a[i], orig[i], 10000);
  }
};

TTS_CASE_TPL("Check naive_fft on soa", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr(std::same_as<eve::element_type_t<T>, double>&& eve::cardinal_v<T> == 1)
  {
//     auto pr = [](auto name, auto v){
//       std::cout << name << " = (";
//       for(size_t i=0; i < v.size() ; ++i) std::cout << v.get(i) << " ";
//       std::cout << ")\n";
//     };
    size_t N = 1024;
    std::cout << tts::typename_<T> << std::endl; ;
    using e_t = typename T::value_type;
    using c_t = eve::complex<e_t>;
    eve::algo::soa_vector<c_t> a(N), orig(N);
    for(size_t i=0; i < N ; ++i){
      a.set(i, c_t(i+1, i+2));
      orig.set(i, a.get(i));
    }
//    pr("a avant", a);
    auto tic =  std::chrono::steady_clock::now();
    eve::soa(eve::naive_fft)(a, e_t(1.0));
    auto toc =  std::chrono::steady_clock::now();
    using namespace std::literals;
    std::cout << "duration naive_fft aos wih n = " << N <<" -> "<< (toc-tic) << "\n" << std::endl;
//    pr("a apres", a);
    eve::soa(eve::ifft)(eve::soa(eve::naive_fft), a, e_t(1)/N);
//    pr("a apres ifft", a);

    for(int i=0; i < ssize(a) ; ++i) TTS_ULP_EQUAL(a.get(i), orig.get(i), 10000);
  }
};
