//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/algo.hpp>
#include <eve/module/complex.hpp>
#include <eve/module/transforms.hpp>
#include <vector>
#include <chrono>
#include <eve/concept/range.hpp>


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


TTS_CASE_TPL("Check ft_ht_cv on aos", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr(std::same_as<eve::element_type_t<T>, double>&& eve::cardinal_v<T> == 1)
  {
    [[maybe_unused]] auto pr = [](auto name, auto v,  size_t max = 16){
      auto m = (v.size() > max) ? max: v.size();
      std::cout << name << " = (";
      for(size_t i=0; i < m ; ++i) std::cout << v[i] << " ";
      if (v.size() > max+1) std::cout << "... " << v[v.size()-1];
      else if (v.size() > max) std::cout << v[v.size()-1];
      std::cout << ")\n";
    };
    size_t ldn = 11;
    size_t N = 1 << ldn;
    using e_t = eve::element_type_t<T>;
    {
      {
        std::vector<e_t> f0(N), f1(N);
        for(size_t i=0; i < N ; ++i){ f0[i] = f1[i] = i+0.5; };
        ref_scaleit (f0,  e_t(3.5));
        eve::scaleit(f1, e_t(3.5));
        for(size_t i=0; i < N ; ++i){
          TTS_EQUAL(f1[i], f0[i]);
          TTS_EQUAL(f1[i], f0[i]);
        };
      }
    }
  }
};
