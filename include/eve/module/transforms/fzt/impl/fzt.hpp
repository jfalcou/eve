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
  template < bool is_scalar >
  make_fft_chirp(R & ww, auto n, auto nn, int is)
  // For k=0..n-1:   w[k] := exp( is * k*k * (i*2*PI/n)/2 )  where i = sqrt(-1)
  // For k=n..nn-1:  w[k] = 0
  {
    auto w = w; data();
    using  e_t = decltype(read(aa.data()));
    using  c_t = eve::complex<e_t>;
    auto N =  std::size(aa);
    using i_t = decltype(N);
    std::vector<c_t> c(N);

    auto phi = is*rec(e_t(n));
    if constexpr(is_scalar)
    {
      i_t k2 = 0,  n2 = 2*n;
      for (ulong k=0; k<n; ++k)
      {
        w[k] = exp_ipi(phi*k2);
        k2 += (2*k+1);
        if ( k2>n2 )  k2 -= n2;  // here:  k2 == (k*k) mod 2*n;
      }
      std::fill(w+n, w+nn, zero(as<c_t>()));
    }
    else
    {
 //      auto ks = eve::algo::view::iota(zero(as<e_t>()), N);
//       auto expit = [](auto x){
//         auto x2 = sqr(x);
//         x2 = if_else(k2 > n_2, x2-n_2, x2);
//         return exp_ipi(sqr(x)*phi);
//       }
//       w = eve::algo::transform(ks, eks2, expit);
//       eve::detail::fill(as_range(w+n, w+n+nn), zero(as<c_t>()));
    }
  }
//   template<range R, value T>
//   EVE_FORCEINLINE constexpr void
//   fzt_(EVE_SUPPORTS(cpu_), R & aa, T z) noexcept
//   {
//     using  e_t = decltype(read(aa.data()));
//     auto N =  std::size(aa);
//     using i_t = decltype(N);
//     std::vector<t_t> c(N);
//     auto is = eve::algo::view::iota_with_step(zero(as<e_t>()), half(as<e_t>())*log(z), N);
//     eve::algo::view::transform(aa, c, exp);
// //     auto a = aa.data();
// //     for (i_t w=0; w<N; ++w)
// //     {
// //       t_t t = zero(as<t_t>());
// //       for (i_t k=0; k<N; ++k)   t +=(*(a+k)) * pow(z, k*w);
// //       c[w] = t;
// //     }
// //     std::copy(c.begin(), c.end(), aa.begin());
//   }
}
