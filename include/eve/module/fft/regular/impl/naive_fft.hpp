//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <vector>
#include <eve/module/complex.hpp>
#include <eve/concept/range.hpp>

namespace eve::detail
{

  template<value T, value T1>
  EVE_FORCEINLINE constexpr auto
  fft_(EVE_SUPPORTS(cpu_), std::vector<T> const & a, T1 s, T1 f) noexcept
  {
    using  c_t = complex<T>;
    auto N =  a.size();
    using i_t = decltype(N);
    std::vector<c_t> c(N);
    s += s;
    s /= N;
    for (i_t w=0; w<N; ++w)
    {
      c_t t = zero(as<c_t>());
      std::cout << tts::typename_<c_t> << std::endl;
      for (i_t k=0; k<N; ++k)
      {
        t +=  a[k] * exp_ipi( s*k*T1(w) );
      }
      c[w] = f*t;
    }
    return c;
  }

}
