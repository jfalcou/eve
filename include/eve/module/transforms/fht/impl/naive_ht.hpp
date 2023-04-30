//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <vector>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/algo.hpp>
#include <eve/module/complex.hpp>
#include <eve/concept/range.hpp>
#include <eve/module/transforms/utils.hpp>
#include <type_traits>

namespace eve::detail
{

  EVE_FORCEINLINE auto cas(auto x)
  {
    return cospi(x+quarter(as(x)));
  }

  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE constexpr void
  naive_ht_(EVE_SUPPORTS(cpu_), aos_type const &, R & a, T f) noexcept
  {
    using  t_t = decltype(read(a.data()));
    auto N =  std::size(a);
    using i_t = decltype(N);
    std::vector<t_t> c(N);

    auto s = T(2)/N;
    for (i_t w=0; w<N; ++w)
    {
      auto z = s*w;
      t_t t = zero(as<t_t>());
      for (i_t k=0; k<N; ++k)   t += *(a.data()+k)* eve::detail::cas( k*z );
      c[w] = f*t;
    }
    std::copy(c.begin(), c.end(), a.begin());
  }

  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE constexpr void
  naive_ht_(EVE_SUPPORTS(cpu_), soa_type const &, R & a, T f) noexcept
  {
    using c_t = eve::complex<T>;
    auto N =  a.size();
    eve::algo::soa_vector<c_t> c(N);
    using i_t = decltype(N);
    auto s = T(2)/N;
    T step(s);
    for (i_t w=0; w<N; ++w, step += s)
    {
      auto ramp = views::iota_with_step(T(0), step, N);
      auto m = [](auto z){ auto [a, e] = z;  return cas(e); };
      auto r = algo::transform_reduce(views::zip(a, ramp), m, c_t(0));
      c.set(w, r*f);
    }
    eve::algo::copy(c, a);
  }

  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE constexpr void
  naive_ht_(EVE_SUPPORTS(cpu_), aos_type const &, R & ar, R & ai, T f) noexcept
  {
    aos(naive_ht)(ar, f);
    aos(naive_ht)(ai, f);
  }

}
