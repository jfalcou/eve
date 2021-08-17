//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/exp10.hpp>
#include <eve/function/pow.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N>
  EVE_FORCEINLINE constexpr T exp10_(EVE_SUPPORTS(cpu_)
                                   , diff_type<1> const &
                                   , T x
                                   , N n) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      using elt_t = element_type_t<T>;
      auto constexpr l10 = elt_t(2.302585092994045684017);
      return exp10(x)*pow(l10, n);
    }
    else
      return apply_over(diff_1st(exp10), x, n);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T exp10_(EVE_SUPPORTS(cpu_)
                                    , diff_type<1> const &
                                    , T x) noexcept
  {
    using elt_t = element_type_t<T>;
    auto constexpr l10 = elt_t(2.302585092994045684017);
    return exp10(x)*l10;
  }
}
