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

#include <eve/function/converter.hpp>
#include <eve/function/derivative/rec.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/mone.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T rec_(EVE_SUPPORTS(cpu_)
                                    , diff_type<1> const &
                                    , T x) noexcept
  {
    if constexpr( has_native_abi_v<T> )
      return -rec(sqr(x));
    else
      return apply_over(diff(rec), x);
  }
}
