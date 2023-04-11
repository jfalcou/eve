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
#include <eve/module/fft/utils.hpp>
#include <type_traits>

namespace eve::detail
{

  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE constexpr void
  naive_fft_(EVE_SUPPORTS(cpu_), aos_type const &, R & a, T f) noexcept
  requires(eve::is_complex_v<typename R::value_type>)
  {
//    EVE_ASSERT(eve::abs(s) == 1, "s must be one or minus one");
    using  c_t = complex<underlying_type_t<T>>;
    auto N =  a.size();
    std::vector<c_t> c(N);
    using i_t = decltype(N);

    auto s = T(-2)/N;
    for (i_t w=0; w<N; ++w)
    {
      auto z = s*w;
      c_t t = zero(as<c_t>());
      for (i_t k=0; k<N; ++k)   t = fam(t, a[k], exp_ipi( k*z ));
      c[w] = f*t;
    }
    std::copy(c.begin(), c.end(), a.begin());
  }

  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE constexpr void
  naive_fft_(EVE_SUPPORTS(cpu_), soa_type const &, R & a, T f) noexcept
  requires(eve::is_complex_v<typename R::value_type>)
  {
//    EVE_ASSERT(eve::abs(s) == 1, "s must be one or minus one");
    using c_t = eve::complex<T>;
    auto N =  a.size();
    eve::algo::soa_vector<c_t> c(N);
    using i_t = decltype(N);
    auto s = T(-2)/N;
    T step(0);
    for (i_t w=0; w<N; ++w, step += s)
    {
      auto ramp = views::iota_with_step(T(0), step, N);
      auto m = [](auto z){ auto [a, e] = z;  return a*exp_ipi(e); };
      auto r = algo::transform_reduce(views::zip(a, ramp), m, c_t(0));
      c.set(w, r*f);
    }
    eve::algo::copy(c, a);
  }

}
