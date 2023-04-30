//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/transforms.hpp>
#include <eve/module/complex.hpp>
#include <vector>
#include <eve/module/algo.hpp>
#include <eve/concept/range.hpp>
#include <algorithm>

TTS_CASE_TPL("Check ifft with aos complex range", eve::test::simd::ieee_reals)
  <typename T>(tts::type<T>)
{
  if constexpr(std::same_as<eve::element_type_t<T>, double>&& eve::cardinal_v<T> == 1)
  {
    size_t N = 64;
    using e_t = eve::element_type_t<T>;
    using c_t = eve::complex<e_t>;
    std::vector<c_t> a(N), b(N), orig(N);
    auto fac = e_t(1);
    for(size_t i=0; i < N ; ++i) orig[i] = b[i] = a[i] = c_t(i+1, i+2);
    eve::aos(eve::naive_ft)(a, fac, e_t(1));  //inverse ft with s = 1
    eve::aos(eve::ifft)(eve::aos(eve::naive_ft), b, fac);  //inverse ft with swapping

    for(size_t i = 0; i < N; i++){
      TTS_ABSOLUTE_EQUAL(a[i], b[i], 20*eve::eps(eve::as<e_t>()));
    }
  }
};


TTS_CASE_TPL("Check ifft with two ranges", eve::test::simd::ieee_reals)
  <typename T>(tts::type<T>)
{
  if constexpr(std::same_as<eve::element_type_t<T>, double> && eve::cardinal_v<T> == 1)
  {
    size_t N = 64;
    using e_t = eve::element_type_t<T>;
    std::vector<e_t> ar(N), br(N), origr(N), ai(N), bi(N), origi(N);
    for(size_t i=0; i < N ; ++i){
      origr[i] = br[i] = ar[i] = i+1;
      origi[i] = bi[i] = ai[i] = i+2;
    }
    auto fac = e_t(1);
    eve::aos(eve::naive_ft)(ar, ai, fac, e_t(1));    //inverse ft with s = 1
    eve::ifft(eve::aos(eve::naive_ft), br, bi,fac);  //inverse ft with swapping

    for(size_t i = 0; i < N; i++){
      TTS_ABSOLUTE_EQUAL(ar[i], br[i], 1000*eve::eps(eve::as<e_t>()));
      TTS_ABSOLUTE_EQUAL(ai[i], bi[i], 1000*eve::eps(eve::as<e_t>()));
    }
  }
};
