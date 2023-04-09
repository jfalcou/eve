//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"
#include "../complex/measures.hpp"
//#include <eve/module/fft.hpp>
#include <eve/module/complex.hpp>
#include <vector>
#include <eve/module/algo.hpp>
#include <eve/concept/range.hpp>
#include <algorithm>

template<typename F, eve::detail::range R, eve::scalar_value T>
  void ifft( F const & fft
           , R & f
           , T const & fac) noexcept
{
  auto conjmuli = [fac]<typename C>(C x){
    auto  [r, i] = x; return  C(i, r)*fac;
  };
  std::transform(f.data(), f.data()+f.size(), f.data(), conjmuli);
  fft(f, fac);
}

TTS_CASE_TPL("Check revbin_permute", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr(std::same_as<eve::element_type_t<T>, float>)
  {
    auto pr = [](auto name, auto v){
      std::cout << name << " = (";
      for(size_t i=0; i < v.size() ; ++i) std::cout << v[i] << " ";
      std::cout << ")\n";
    };

    auto pipo_fft =  [](auto &f , auto){
      for(size_t i = 0; i < f.size(); ++i) f[i]+= f[i];
    };
    using c_t = eve::complex<eve::element_type_t<T>>;
    int n = 10;
    std::vector<c_t> v(n), w(n);
    for(float i=0; i < n ; i+= 1){
      v[i] = c_t(i/2, i*2);
      w[i] = c_t(i*2, i/2);
    }
    pr("v ", v);
    std::cout << " =============================== " << n<< std::endl;
    ifft(pipo_fft, v, 1.0f);
    pr("v  ", v);
    std::cout << " ------------------------------- " << std::endl;
//    for(int i = 0; i < n; i++) TTS_EQUAL(v[i], w[i]);
  }
};
