//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/minf.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/binarize.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_ngtz.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/oneminus.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T signgam_(EVE_SUPPORTS(cpu_), T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto isleza0 = is_ngtz(a0);
      auto a       = if_else(is_flint(a0) || is_infinite(a0),
                       eve::allbits,
                       oneminus(binarize(is_odd(floor(a0))) * T(2)));
      a = if_else(is_eqz(a0), bit_or(one(as(a0)), bitofsign(a0)), a);
      return if_else(is_nan(a0), a0, if_else(isleza0, a, eve::one));
    }
    else
      return apply_over(signgam, a0);
  }
}
