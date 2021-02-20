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

#include <eve/detail/function/swizzle.hpp>
#include <eve/detail/function/gather_low.hpp>
#include <eve/detail/function/gather_high.hpp>
#include <eve/detail/function/broadcast.hpp>
#include <eve/detail/function/simd/common/patterns.hpp>
#include <eve/detail/function/simd/x86/patterns.hpp>
#include <eve/constant/zero.hpp>

namespace eve::detail
{
  //================================================================================================
  // Look to see if a given pattern is optimizable and returns the optimized function object
  //================================================================================================
  template<int... I> consteval auto find_optimized_pattern()
  {
          if constexpr( is_zero<I...>       ) return zero;
    else  if constexpr( is_broadcast<I...>  ) return broadcast;
    else  if constexpr( is_identity<I...>   ) return perform_identity{};
    else  if constexpr( is_movhl<I...>      ) return gather_high;
    else  if constexpr( is_movlh<I...>      ) return gather_low;
    else                                      return basic_swizzle;
  }
}
