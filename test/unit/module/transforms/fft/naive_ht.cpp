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

TTS_CASE_TPL("Check naive_ht on aos", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr(std::same_as<eve::element_type_t<T>, double> && eve::cardinal_v<T> == 1)
  {
    size_t N = 8;
    std::cout << tts::typename_<T> << std::endl; ;
    using e_t = typename T::value_type;
//    e_t invsqrt2 = eve::invsqrt_2(eve::as<e_t>());
    std::vector<e_t> a(N), orig(N);
    std::vector<e_t> ref = {25.45584412271571, 4.0, 0, -1.656854249492381, -2.8284271247461903, -4, -5.6568542494923806, -9.656854249492381};
    for(size_t i=0; i < N ; ++i) orig[i] = a[i] = i+1;
    pr("a", a.data(), 8);
    eve::aos(eve::naive_ht)(a, e_t(1.0));
    pr("a", a.data(), 8);
    for(size_t i=0; i <N ; ++i){
      TTS_ABSOLUTE_EQUAL(a[i],ref[i], 10*eve::eps(eve::as<e_t>()));
    }
    eve::aos(eve::naive_ht)(a, e_t(2)/(N)); //inverse ht
    for(size_t i=0; i <N ; ++i){
      TTS_ABSOLUTE_EQUAL(a[i],orig[i], 10*eve::eps(eve::as<e_t>()));
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
    std::vector<e_t> ar(N), ai(N), origr(N), origi(N);
    std::vector<e_t> refr = {25.45584412271571, 4.0, 0, -1.656854249492381, -2.8284271247461903, -4, -5.6568542494923806, -9.656854249492381};
    std::vector<e_t> refi = {5.6568542494923815, 0, 0, 0, 0, 0, 0, 0};
    for(size_t i=0; i < N ; ++i){ origr[i] = ar[i] = e_t(i)+1; origi[i] = ai[i] = e_t(1);}
    eve::aos(eve::naive_ht)(ar, ai, e_t(1.0));
    for(size_t i=0; i <N ; ++i){
      TTS_ABSOLUTE_EQUAL(ar[i],refr[i], 10*eve::eps(eve::as<e_t>()));
      TTS_ABSOLUTE_EQUAL(ai[i],refi[i], 10*eve::eps(eve::as<e_t>()));
    }
    eve::aos(eve::naive_ht)(ar, ai, e_t(2)/N); //inverse ht
    for(size_t i=0; i <N ; ++i){
      TTS_ABSOLUTE_EQUAL(ar[i],origr[i], 10*eve::eps(eve::as<e_t>()));
      TTS_ABSOLUTE_EQUAL(ai[i],origi[i], 10*eve::eps(eve::as<e_t>()));
    }
  }
};
