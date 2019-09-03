//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_LOGICAL_NOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_LOGICAL_NOT_HPP_INCLUDED

#include <eve/detail/is_native.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_not.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto logical_not_(EVE_SUPPORTS(cpu_), wide<T, N, ABI> const &a) noexcept
  {
    if constexpr(is_aggregated_v<ABI>) { return aggregate(eve::logical_not, a); }
    else if constexpr(is_emulated_v<ABI>)
    {
      return map(eve::logical_not, a);
    }
    else
    {
      return is_equal(a, eve::Zero(as(a)));
    }
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE constexpr auto logical_not_(EVE_SUPPORTS(cpu_),
                                              logical<wide<T, N, ABI>> const &a) noexcept
  {
    return eve::bitwise_cast<logical<wide<T, N, ABI>>>(eve::bitwise_not(a.bits()));
  }
}

#endif
