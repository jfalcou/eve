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
#include <eve/module/algo.hpp>
#include <eve/module/complex.hpp>
#include <eve/concept/range.hpp>
#include <type_traits>

namespace eve::detail
{

  template<value T, value T1>
  EVE_FORCEINLINE constexpr auto
  totally_naive_fft_(EVE_SUPPORTS(cpu_), std::vector<T> const & a, T1 f, T1 s) noexcept
  requires (scalar_value<T1>)
  {
    EVE_ASSERT(eve::abs(s) == 1, "s must be one or minus one");
    using  c_t = complex<underlying_type_t<T>>;
    auto N =  a.size();
    std::vector<c_t> c(N);
    using i_t = decltype(N);
    s += s;
    s /= N;
    for (i_t w=0; w<N; ++w)
    {
      c_t t = zero(as<c_t>());
      for (i_t k=0; k<N; ++k)
      {
        t +=  a[k] * exp_ipi( s*k*T1(w) );
      }
      c[w] = f*t;
    }
    return c;
  }

  template<floating_ordered_value T>
  EVE_FORCEINLINE constexpr auto
  scalar_naive_fft_(EVE_SUPPORTS(cpu_), std::vector<T> const & a, T f, T s) noexcept
  requires (scalar_value<T>)
  {
    EVE_ASSERT(eve::abs(s) == 1, "s must be one or minus one");
    auto N =  a.size();
    using  c_t = complex<underlying_type_t<T>>;
    using i_t = decltype(N);
    s += s;
    s /= N;
    T step(0);
    std::vector<c_t> c(N);
    for (i_t w=0; w<N; ++w, step += s)
    {
      auto ramp = views::iota_with_step(T(0), step, N);
      auto m = [](auto z){ auto [a, e] = z;  return a*exp_ipi(e); };
      c[w] = f*algo::transform_reduce(views::zip(a, ramp), m, c_t(0));
    }
    return c;
  }


  template<value T, value T1>
  EVE_FORCEINLINE constexpr auto
  simd_naive_fft_(EVE_SUPPORTS(cpu_), eve::algo::soa_vector<complex<T>> const & a, T1 f, T1 s) noexcept
  requires (scalar_value<T> && scalar_value<T1>)
  {
    EVE_ASSERT(eve::abs(s) == 1, "s must be one or minus one");
    using c_t = complex<T>;
    auto N =  a.size();
    eve::algo::soa_vector<c_t> c(N);
    using i_t = decltype(N);
    s += s;
    s /= N;
    T1 step(0);
    for (i_t w=0; w<N; ++w, step += s)
    {
      auto ramp = views::iota_with_step(T1(0), step, N);
      auto m = [](auto z){ auto [a, e] = z;  return a*exp_ipi(e); };
      auto r = algo::transform_reduce(views::zip(a, ramp), m, c_t(0));
      c.set(w, r*f);
    }
    return c;
  }

}
