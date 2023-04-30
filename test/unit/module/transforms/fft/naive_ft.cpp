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

TTS_CASE_TPL("Check naive_ft on aos", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr(std::same_as<eve::element_type_t<T>, double> && eve::cardinal_v<T> == 1)
  {
    size_t N = 8;
    std::cout << tts::typename_<T> << std::endl; ;
    using e_t = typename T::value_type;
    using c_t = eve::complex<e_t>;
    std::vector<c_t> a(N), orig(N);
    std::vector<c_t> ref = {c_t(36, 44), c_t(-13.65685424949238, 5.6568542494923788), c_t(-8, 0), c_t(-5.6568542494923797, -2.3431457505076208)
                            , c_t(-4, -4), c_t(-2.3431457505076208, -5.6568542494923806), c_t(0, -8), c_t(5.6568542494923797, -13.656854249492378)
                             };
    for(size_t i=0; i < N ; ++i) orig[i] = a[i] = c_t(i+1, i+2);
    eve::aos(eve::naive_ft)(a, e_t(1.0), e_t(-1));
    for(size_t i=0; i <N ; ++i){
      TTS_ULP_EQUAL(          a[i],            ref[i] , 10000);
    }
    eve::aos(eve::naive_ft)(a, e_t(1)/N, e_t(1)); //inverse fft
    for(size_t i=0; i <N ; ++i){
      TTS_ULP_EQUAL(          a[i],            orig[i] , 10000);
    }
  }
};

TTS_CASE_TPL("Check naive_ft on soa", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr(std::same_as<eve::element_type_t<T>, double>&& eve::cardinal_v<T> == 1)
  {
    size_t N = 8;
    std::cout << tts::typename_<T> << std::endl; ;
    using e_t = typename T::value_type;
    using c_t = eve::complex<e_t>;
    eve::algo::soa_vector<c_t> a(N), orig(N);
    for(size_t i=0; i < N ; ++i){
      a.set(i, c_t(i+1, i+2));
      orig.set(i, a.get(i));
    }
    eve::soa(eve::naive_ft)(a, e_t(1.0), e_t(-1.0) );
    eve::soa(eve::naive_ft)(a, e_t(1)/N, e_t(1.0)  );//inverse fft
    for(size_t i=0; i < N ; ++i) TTS_ULP_EQUAL(a.get(i), orig.get(i), 10000);
  }
};


TTS_CASE_TPL("Check naive_ft on aos pair", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr(std::same_as<eve::element_type_t<T>, double> && eve::cardinal_v<T> == 1)
  {
    size_t N = 8;
    std::cout << tts::typename_<T> << std::endl; ;
    using e_t = typename T::value_type;
    std::vector<e_t> ar(N), ai(N), origr(N), origi(N);
    std::vector<e_t> refr = {36,-13.65685424949238, -8, -5.6568542494923797, -4, -2.3431457505076208, 0, 5.6568542494923797 };
    std::vector<e_t> refi = {44, 5.6568542494923788, 0, -2.3431457505076208, -4, -5.6568542494923806, -8, -13.656854249492378};
    for(size_t i=0; i < N ; ++i){ origr[i] = ar[i] = i+1; origi[i] = ai[i] =i+2;}
    eve::aos(eve::naive_ft)(ar, ai, e_t(1.0), e_t(-1));
    for(size_t i=0; i <N ; ++i){
      TTS_ULP_EQUAL(          ar[i],            refr[i] , 10000);
      TTS_ULP_EQUAL(          ai[i],            refi[i] , 10000);
    }
    eve::aos(eve::naive_ft)(ar, ai, e_t(1)/N, e_t(1)); //inverse fft
    for(size_t i=0; i <N ; ++i){
      TTS_ULP_EQUAL(          ar[i],            origr[i] , 10000);
      TTS_ULP_EQUAL(          ai[i],            origi[i] , 10000);
    }
  }
};
