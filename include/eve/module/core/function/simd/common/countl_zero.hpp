//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_COUNTL_ZERO_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_COUNTL_ZERO_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/ffs.hpp>
#include <eve/function/bit_reverse.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto countl_zero_(EVE_SUPPORTS(cpu_), wide<T, N, ABI> const &v) noexcept
  {
    if constexpr(is_aggregated_v<ABI>)
    {
      return aggregate(eve::countl_zero, v);
    }
    else if constexpr(is_emulated_v<ABI>)
    {
      return map(eve::countl_zero, v);
    }
    else if constexpr(is_native_v<ABI>)
    {
      using i_t = as_integer_t<T, unsigned>; 
      return if_else(is_eqz(v), eve::zero_, ffs(bit_reverse(bit_cast(v, as<i_t>())); 
    }
  }
}

#endif
