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
#include <eve/module/transforms/utils.hpp>
#include <type_traits>

namespace eve::detail
{

  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE constexpr void
  naive_ft_(EVE_SUPPORTS(cpu_), R & ar,  R & ai, T f, T s = -1) noexcept
  requires(!eve::algo::is_soa_vector_v<R>)
 {
    EVE_ASSERT(eve::abs(s) == 1, "sign must be one or minus one");
    EVE_ASSERT(std::size(ar) == std::size(ai), "ranges ar and ai must share the same size");
    using  c_t = eve::complex<T>;
    auto N =  std::size(ar);
    using i_t = decltype(N);
    std::vector<c_t> c(N);

    s *= T(2)/N;
    for (i_t w=0; w<N; ++w)
    {
      auto z = s*w;
      c_t t = zero(as<c_t>());
      for (i_t k=0; k<N; ++k)   t += c_t(ar[k], ai[k])*exp_ipi( k*z );
      c[w] = f*t;
    }

    for(size_t i=0; i < N; ++i)
    {
      kumi::tie(ar[i], ai[i]) = kumi::to_tuple(c[i]);
    }
  }

  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE constexpr void
  naive_ft_(EVE_SUPPORTS(cpu_), R & a, T f, T s = -1) noexcept
  requires(!eve::algo::is_soa_vector_v<R>)
  {
    EVE_ASSERT(eve::abs(s) == 1, "sign must be one or minus one");
    using  c_t = complex<underlying_type_t<T>>;
    auto N =  std::size(a);
    eve::algo::soa_vector<c_t> c(N);
    using i_t = decltype(N);

    s *= T(2)/N;
    for (i_t w=0; w<N; ++w)
    {
      auto z = s*w;
      c_t t = zero(as<c_t>());
      for (i_t k=0; k<N; ++k)   t = fam(t, a[k], exp_ipi( k*z ));
      c.set(w, f*t);
    }
    eve::algo::copy(c, a);
  }

  template<eve::algo::relaxed_range R, floating_scalar_value T>
  EVE_FORCEINLINE constexpr void
  naive_ft_(EVE_SUPPORTS(cpu_), R & a, T f, T s = -1) noexcept
  requires(eve::algo::is_soa_vector_v<R>)
  {
    EVE_ASSERT(eve::abs(s) == 1, "s must be one or minus one");
    using c_t = eve::complex<T>;
    auto N =  a.size();
    eve::algo::soa_vector<c_t> c(N);
    using i_t = decltype(N);
    s *= T(2)/N;
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

  template<typename U>
  inline void pr1(auto name,  U* vd,  auto nn, size_t max = 16u) noexcept {
    size_t n(nn);
    auto m = (n > max) ? max: n;
    std::cout << name << " = (" << std::setprecision(17);

    for(size_t i=0; i < m ; ++i) std::cout << "c_t(" << eve::real(vd[i]) << ", " << eve::imag(vd[i]) << "), "<< " ";
    if (n > max+1) std::cout << "... " << +vd[n-1];
    else if (n > max) std::cout << +vd[n-1];
    std::cout << ")\n";
  }
}
