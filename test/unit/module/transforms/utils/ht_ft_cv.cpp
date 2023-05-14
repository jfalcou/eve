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

TTS_CASE_TPL("Check ft_ht_cv", eve::test::simd::ieee_reals)
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
    size_t ldn = 8;
    size_t N = 1 << ldn;
    using e_t = eve::element_type_t<T>;
    {
      {
        std::vector<e_t> fr0(N), fi0(N), fr1(N), fi1(N);
        for(size_t i=0; i < N ; ++i){ fr0[i] = fr1[i] = i+0.5; fi0[i] = fi1[i] = 4*N-2*i+1; };
        ref_ht_ft_cv (fr0, fi0, +1);
        eve::ht_ft_cv(fr1, fi1);
        for(size_t i=0; i < N ; ++i){
          TTS_EQUAL(fr1[i], fr0[i]);
          TTS_EQUAL(fi1[i], fi0[i]);
        };
      }
      {
        std::vector<e_t> fr0(N), fi0(N), fr1(N), fi1(N);
        for(size_t i=0; i < N ; ++i){ fr0[i] = fr1[i] = i+0.5; fi0[i] = fi1[i] = 4*N-2*i+1; };
        ref_ht_ft_cv (fr0, fi0, -1);
        eve::inv_ht_ft_cv(fr1, fi1);
        for(size_t i=0; i < N ; ++i){
          TTS_EQUAL(fr1[i], fr0[i]);
          TTS_EQUAL(fi1[i], fi0[i]);
        };
      }
    }
  }
};
