//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_LTZ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_LTZ_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_less.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/zero.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto is_ltz_(EVE_SUPPORTS(cpu_), wide<T, N, ABI> const &v) noexcept
  {
    if constexpr(std::is_unsigned_v<T>)
    {
      return False(as(v));
    }
    else
    {
      return is_less(v, Zero(as(v)));
    }
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto is_ltz_(EVE_SUPPORTS(cpu_), logical<wide<T, N, ABI>> const &v) noexcept
  {
    return False(as(v));
  }
}

#endif
