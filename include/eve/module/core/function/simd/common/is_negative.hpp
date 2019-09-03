//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NEGATIVE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NEGATIVE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/constant/zero.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto is_negative_(EVE_SUPPORTS(cpu_), wide<T, N, ABI> const &v) noexcept
  {
    if constexpr(std::is_integral_v<T>) { return is_ltz(v); }
    else
    {
      using swi_t = wide<eve::detail::as_integer_t<T, signed>, N>;
      using lwi_t = as_logical_t<wide<T, N, ABI>>;
      return bitwise_cast<lwi_t>(is_ltz(bitwise_cast<swi_t>(v)));
    }
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto is_negative_(EVE_SUPPORTS(cpu_), logical<wide<T, N, ABI>> const &v) noexcept
  {
    return False(as(v));
  }
}

#endif
