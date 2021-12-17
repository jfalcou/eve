//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/derivative.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/function/pedantic/lrising_factorial.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/digamma.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/raw.hpp>

namespace eve::detail
{
  template<int N, real_value I, floating_real_value T, typename D>
  auto lrising_factorial_(EVE_SUPPORTS(cpu_), decorated<diff_<N>(D)> const &
             , I a, T x) noexcept
  {
    using elt_t = element_type_t<T>;
    using r_t = as_wide_t<elt_t, cardinal_t<I>>;
    auto aa = convert(a, as(elt_t()));
    if constexpr(N == 1)
    {
      return digamma(aa+x) - digamma(aa);
    }
    else if constexpr(N == 2)
    {
      return digamma(aa+x);
    }
    else
      return zero(as<r_t>());
  }

  template<int N, real_value I, floating_real_value T>
  auto lrising_factorial_(EVE_SUPPORTS(cpu_), diff_type<N> const &
             , I a, T x) noexcept
  {
    using elt_t = element_type_t<T>;
    using r_t = as_wide_t<elt_t, cardinal_t<I>>;
    auto aa = convert(a, as(elt_t()));
    if constexpr(N == 1)
    {
      return digamma(aa+x) - digamma(aa);
    }
    else if constexpr(N == 2)
    {
      return digamma(aa+x);
    }
    else
      return zero(as<r_t>());
  }

}
