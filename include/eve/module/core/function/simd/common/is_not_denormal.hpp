//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NOT_DENORMAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NOT_DENORMAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/is_not_less.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/platform.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto is_not_denormal_(EVE_SUPPORTS(cpu_), wide<T, N, ABI> const &v) noexcept
  {
    if constexpr(std::is_integral_v<T> || !platform::supports_denormals) { return True(as(v)); }
    else
    {
      return is_eqz(v) || is_not_less(eve::abs(v), Smallestposval(as(v)));
    }
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE constexpr auto is_not_denormal_(EVE_SUPPORTS(cpu_),
                                                  logical<wide<T, N, ABI>> const &a) noexcept
  {
    return True(as(a));
  }
}

#endif
