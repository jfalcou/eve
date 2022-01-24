//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/math.hpp>
#include <eve/detail/hz_device.hpp>
#include <eve/module/special/regular/lrising_factorial.hpp>
#include <eve/module/special/pedantic/lrising_factorial.hpp>
#include <eve/module/special/regular/digamma.hpp>

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
