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
#include <eve/module/complex.hpp>
#include <vector>
#include <eve/module/algo.hpp>
#include <eve/concept/range.hpp>
#include <algorithm>

TTS_CASE_TPL("Check ifft", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr(std::same_as<eve::element_type_t<T>, float>&& eve::cardinal_v<T> == 1)
  {
    using e_t = eve::element_type_t<T>;
    using c_t = eve::complex<e_t>;
    int n = 10;
    {
      auto pipo_fft =  [](auto &f , auto){
        for(size_t n=0; n < std::size(f) ; ++n){ auto [r, i] = f[n]; f[n] = c_t(i, -r);}
      };
      auto pr = [](auto name, auto v){
        std::cout << name << " = (";
        for(size_t i=0; i < v.size() ; ++i) std::cout << v[i] << " ";
        std::cout << ")\n";
      };
      std::vector<c_t> v(n), w(n);
      for(float i=0; i < n ; i+= 1){
        v[i] = c_t(i/2, i*2);
        w[i] = c_t(-i*2, i/2);
      }
      pr("v avant", v);
      pr("w      ", w);
      eve::aos(eve::ifft)(pipo_fft, v, 1.0f);
      pr("v apres", v);
      for(int i = 0; i < n; i++) TTS_EQUAL(v[i], w[i]);
    }

    {
      auto pr = [](auto name, auto v){
        std::cout << name << " = (";
        for(size_t i=0; i < v.size() ; ++i) std::cout << v.get(i) << " ";
        std::cout << ")\n";
      };
      auto pipo_fft =  [](auto &f, auto){  //do nothing
        for(size_t n=0; n < std::size(f) ; ++n){ auto [r, i] = f.get(n); f.set(n, c_t(i, -r));}
      };
      eve::algo::soa_vector<c_t> v(n), w(n);
      for(float i=0; i < n ; i+= 1){
        v.set(i, c_t(i/2, i*2));
        w.set(i, c_t(-i*2, i/2));
      }
      pr("v avant", v);
      pr("w      ", w);
      eve::soa(eve::ifft)(pipo_fft, v, 1.0f);
      pr("v apres", v);
      for(int i = 0; i < n; i++) TTS_EQUAL(v.get(i), w.get(i));
    }

    {
      auto pr = [](auto name, auto vr, auto vi){
        std::cout << name << " = (";
        for(size_t i=0; i < vr.size() ; ++i) std::cout << vr[i] << "+" << vi[i] << "i ";
        std::cout << ")\n";
      };
      auto pipo_fft =  [](auto&fr, auto &fi, auto){//do nothing
        for(size_t n=0; n < std::size(fr) ; ++n){ auto t = fr[n]; fr[n] = fi[n]; fi[n] = -t; }

      };
      std::vector<e_t> vr(n), wr(n), vi(n), wi(n);
      for(float i=0; i < n ; i+= 1){
        vr[i] = i/2;
        vi[i] = i*2;
        wr[i] = i/2;
        wi[i] = -2*i;
     }
      pr("v avant", vr, vi);
      pr("w      ", wr, wi);
      eve::ifft(pipo_fft, vr, vi, 1.0f);
      pr("v apres", vr, vi);
      for(int i = 0; i < n; i++){
        TTS_EQUAL(vr[i], wr[i]);
        TTS_EQUAL(vi[i], wi[i]);
      }
    }
  }
};
