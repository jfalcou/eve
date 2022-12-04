//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special/pedantic/lrising_factorial.hpp>
#include <eve/module/special/regular/signgam.hpp>

namespace eve::detail
{

template<real_value I, floating_real_value T>
EVE_FORCEINLINE auto
rising_factorial_(EVE_SUPPORTS(cpu_), pedantic_type const&, I a, T x) noexcept
{
  if constexpr( std::is_integral_v<element_type_t<I>> )
    return pedantic(rising_factorial)(convert(a, as(element_type_t<T>())), x);
  else
  {
    using r_t = common_value_t<T, I>;
    return pedantic(rising_factorial)(r_t(a), r_t(x));
  }
}

template<floating_real_value T>
EVE_FORCEINLINE auto
rising_factorial_(EVE_SUPPORTS(cpu_), pedantic_type const&, T a, T x) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto sgnrf = [](auto a, auto x)
    {
      auto sga   = if_else(is_flint(a), one, signgam(a));
      auto sgapx = if_else(is_flint(a + x), one, signgam(a + x));
      return sga * sgapx;
    };
    auto lrn = pedantic(lrising_factorial)(a, x);
    return exp(lrn) * sgnrf(a, x);
  }
  else return apply_over(pedantic(rising_factorial), a, x);
}
}
