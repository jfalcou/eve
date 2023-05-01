//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/transforms/detail/pr.hpp>
#include <eve/module/algo.hpp>
#include <eve/module/complex.hpp>
#include <eve/module/transforms.hpp>
#include <vector>
#include <chrono>

template < typename T> void
slow_ht(auto f, size_t n, T fac)
// (slow) Hartley transform.
{
  using e_t = T;
  std::vector<e_t> res(n);
  const double ph0 = 2.0/e_t(n);
  for (size_t w=0; w<n; ++w)
  {
    T t=0.0;
    for (size_t k=0; k<n; ++k)
    {
      auto [s, c] = eve::sinpicospi(ph0*k*w);
      t += ((c+s)*f[k]);
    }
    res[w] = fac*t*eve::invsqrt_2(eve::as(fac));
  }
  std::copy(&res[0], &res[n], f);
}


TTS_CASE_TPL("Check naive_ht on aos", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr(std::same_as<eve::element_type_t<T>, double> && eve::cardinal_v<T> == 1)
  {
    size_t N = 8;
    std::cout << tts::typename_<T> << std::endl; ;
    using e_t = typename T::value_type;
//    e_t invsqrt2 = eve::invsqrt_2(eve::as<e_t>());
    std::vector<e_t> a(N), ref(N), orig(N);
    for(size_t i=0; i < N ; ++i) orig[i] = ref[i] = a[i] = i+1;
    pr("a", a.data(), 8);
    eve::aos(eve::naive_ht)(a, e_t(1.0));
    pr("a", a.data(), 8);
    pr("ref", ref.data(), 8);
    slow_ht(&ref[0], 8, e_t(1.0));
    pr("ref", ref.data(), 8);
    for(size_t i=0; i <N ; ++i){
      TTS_ABSOLUTE_EQUAL(a[i],ref[i], 100*eve::eps(eve::as<e_t>()));
    }
    eve::aos(eve::naive_ht)(a, e_t(2)/(N)); //inverse ht
    for(size_t i=0; i <N ; ++i){
      TTS_ABSOLUTE_EQUAL(a[i],orig[i], 100*eve::eps(eve::as<e_t>()));
    }
  }
};

// TTS_CASE_TPL("Check naive_ht on soa", eve::test::simd::ieee_reals)
// <typename T>(tts::type<T>)
// {
//   if constexpr(std::same_as<eve::element_type_t<T>, double>&& eve::cardinal_v<T> == 1)
//   {
//     size_t N = 8;
//     std::cout << tts::typename_<T> << std::endl; ;
//     using e_t = typename T::value_type;
//     using c_t = eve::complex<e_t>;
//     eve::algo::soa_vector<c_t> a(N), orig(N);
//     for(size_t i=0; i < N ; ++i){
//       a.set(i, c_t(i+1, i+2));
//       orig.set(i, a.get(i));
//     }
//     eve::soa(eve::naive_ht)(a, e_t(1.0));
//     eve::soa(eve::naive_ht)(a, e_t(2)/N);//inverse fft
//     for(size_t i=0; i < N ; ++i)
//       TTS_ABSOLUTE_EQUAL(a.get(i), orig.get(i), 10*eve::eps(eve::as<e_t>()));
//   }
// };


TTS_CASE_TPL("Check naive_ht on aos pair", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr(std::same_as<eve::element_type_t<T>, double> && eve::cardinal_v<T> == 1)
  {
    size_t N = 8;
    std::cout << tts::typename_<T> << std::endl; ;
    using e_t = typename T::value_type;
    std::vector<e_t> ar(N), ai(N), origr(N), origi(N), refr(N), refi(N);
    for(size_t i=0; i < N ; ++i){ refr[i] = origr[i] = ar[i] = e_t(i)+1; refi[i] = origi[i] = ai[i] = e_t(1);}
    eve::aos(eve::naive_ht)(ar, ai, e_t(1.0));
    slow_ht(&refr[0], 8, e_t(1.0));
    slow_ht(&refi[0], 8, e_t(1.0));
    for(size_t i=0; i <N ; ++i){
      TTS_ABSOLUTE_EQUAL(ar[i],refr[i], 100*eve::eps(eve::as<e_t>()));
      TTS_ABSOLUTE_EQUAL(ai[i],refi[i], 100*eve::eps(eve::as<e_t>()));
    }
    eve::aos(eve::naive_ht)(ar, ai, e_t(2)/N); //inverse ht
    for(size_t i=0; i <N ; ++i){
      TTS_ABSOLUTE_EQUAL(ar[i],origr[i], 100*eve::eps(eve::as<e_t>()));
      TTS_ABSOLUTE_EQUAL(ai[i],origi[i], 100*eve::eps(eve::as<e_t>()));
    }
  }
};
