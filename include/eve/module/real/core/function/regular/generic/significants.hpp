//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/exp10.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/ceil.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/log10.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<floating_real_value T, integral_value U>
  EVE_FORCEINLINE T significants_(EVE_SUPPORTS(cpu_)
                               , T const &a
                               , U const &n) noexcept
  {
    if constexpr(has_native_abi_v<T> && has_native_abi_v<U>)
    {
      using elt_t =  element_type_t<T>;
      auto factor = exp10(convert(n, as<elt_t>())- ceil(log10(eve::abs(a))));
      return nearest(a * factor) / factor;
    }
    else  return apply_over(significants, a, n);
  }
}
