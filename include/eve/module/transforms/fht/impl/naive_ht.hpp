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
    auto [c, s] = sinpicospi(x);
    return (c+s)*invsqrt_2(as(x));
  }

  template<eve::algo::relaxed_range R, floating_ordered_value T>
  EVE_FORCEINLINE constexpr void
  naive_ht_(EVE_SUPPORTS(cpu_), R & a, T f) noexcept
  requires(!eve::algo::is_soa_vector_v<R>)
  {
    using  t_t = decltype(read(a.data()));
    auto N =  std::size(a);
    using i_t = decltype(N);
    std::vector<t_t> c(N);

    auto phi0 = T(2)/N;
    for (i_t w=0; w<N; ++w)
    {
      auto z = phi0*w;
      t_t t = zero(as(phi0));
      for (i_t k=0; k<N; ++k)   t += *(a.data()+k)* eve::detail::cas( k*z );
      c[w] = f*t;
    }
    std::copy(c.begin(), c.end(), a.begin());
  }

  template<eve::algo::relaxed_range R, floating_ordered_value T>
  EVE_FORCEINLINE constexpr void
  naive_ht_(EVE_SUPPORTS(cpu_), R & a, T f) noexcept
  requires(eve::algo::is_soa_vector_v<R>)
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

  template<eve::algo::relaxed_range R, floating_scalar_value T>
  EVE_FORCEINLINE constexpr void
  naive_ht_(EVE_SUPPORTS(cpu_), R & ar, R & ai, T f) noexcept
  {
    naive_ht(ar, f);
    naive_ht(ai, f);
  }

}
