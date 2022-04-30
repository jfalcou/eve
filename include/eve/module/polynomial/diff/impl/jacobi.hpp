//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/polynomial/regular/jacobi.hpp>


namespace eve::detail
{

  template<real_value N, floating_value T, floating_value U, floating_value V>
  EVE_FORCEINLINE constexpr auto jacobi_(EVE_SUPPORTS(cpu_)
                                        , diff_type<1> const &
                                        , N const & n
                                        , U const & alpha
                                        , V const & beta
                                        , T const &x) noexcept
  {
    using f_t = common_compatible_t<T, U, V>;
    using r_t = std::conditional_t<scalar_value<f_t> && scalar_value<N>, f_t, as_wide_t<f_t, cardinal_t<N>>>;
    auto nn(to_<r_t>(n));
    return (alpha + beta + inc(nn))*r_t(0.5)*jacobi(dec(n), inc(alpha), inc(beta), x);
  }

  template<real_value N, floating_value T, floating_value U, floating_value V>
  EVE_FORCEINLINE constexpr T jacobi_(EVE_SUPPORTS(cpu_)
                                     , diff_type<1> const &
                                     , N const & n
                                     , U const & alpha
                                     , V const & beta
                                     , T const &x
                                     , size_t k) noexcept
  {
    using f_t = common_compatible_t<T, U, V>;
    using r_t = std::conditional_t<scalar_value<f_t> && scalar_value<N>, f_t, as_wide_t<f_t, cardinal_t<N>>>;
    r_t scale(1);
    auto nn(to_<r_t>(n));
    r_t apbpn = alpha+beta+nn;
    for(size_t j = 1; j <= k; ++j) scale *= average(apbpn, r_t(j));
   auto j = jacobi(nn-k, alpha+k, beta+k, x);
   return j*scale;
//    return scale*jacobi(nn,    alpha,    beta,    x);
//   return scale*jacobi(nn-k, alpha+k, beta+k, x);
  }
}
