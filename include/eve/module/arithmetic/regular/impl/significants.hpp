//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/exp10.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/ceil.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/log10.hpp>
#include <eve/function/rec.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/module/arithmetic/regular/is_eqz.hpp>

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
      auto nn = convert(n, as<elt_t>());
      auto e = floor(inc(log10(eve::abs(a)) - nn));
      auto factor = exp10(abs(e));
      auto tmp = if_else(is_gez(e),nearest(a/factor)*factor,nearest(a*factor)/factor);
      tmp = if_else(is_eqz(a), a, tmp);
      return if_else(is_nez(nn), tmp, allbits);
    }
    else  return apply_over(significants, a, n);
  }
}
