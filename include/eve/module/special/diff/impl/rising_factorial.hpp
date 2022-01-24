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
#include <eve/module/special/pedantic/rising_factorial.hpp>
#include <eve/module/special/diff/lrising_factorial.hpp>
#include <eve/module/special/regular/digamma.hpp>

namespace eve::detail
{
  template<int N, real_simd_value I, floating_real_value T>
  auto rising_factorial_(EVE_SUPPORTS(cpu_), decorated<diff_<N>(pedantic_)> const &
             , I a, T x) noexcept
  {
    using elt_t = element_type_t<T>;
    using r_t = as_wide_t<elt_t, cardinal_t<I>>;
    auto aa = convert(a, as(elt_t()));
    if constexpr(N <= 2)
    {
      auto tmp = pedantic(rising_factorial)(aa, x);
      return diff_type<N>()(lrising_factorial)(aa, x)*tmp;
    }
    else
      return zero(as<r_t>());
  }

  template<int N, real_scalar_value I, floating_real_value T, typename D>
  auto rising_factorial_(EVE_SUPPORTS(cpu_), decorated<diff_<N>(D)> const &
             , I a, T x) noexcept
  {
    if constexpr(N <= 2)
    {
      auto tmp = pedantic(rising_factorial)(T(a), x);
      return diff_type<N>()(lrising_factorial)(T(a), x)*tmp;
    }
    else
      return zero(as<T>());
  }

  template<int N, real_value I, floating_real_value T>
  auto rising_factorial_(EVE_SUPPORTS(cpu_)
                        , diff_type<N> const & d
                        , I a, T x) noexcept
  {
    using elt_t = element_type_t<T>;
    using r_t = as_wide_t<elt_t, cardinal_t<I>>;
    auto aa = convert(a, as(elt_t()));
    if constexpr(N <= 2)
    {
      auto tmp = rising_factorial(aa, x);
      return lrising_factorial(d, aa, x)*tmp;
    }
    else
      return zero(as<r_t>());
  }
}
