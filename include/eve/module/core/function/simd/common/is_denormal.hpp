//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_DENORMAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_DENORMAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/false.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/abs.hpp>
#include <eve/platform.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto is_denormal_(EVE_SUPPORTS(cpu_),wide<T, N, ABI> const &a) noexcept
  {
    if constexpr(std::is_integral_v<T> || !platform::supports_denormals)
    {
      return False(as(a));
    }
    else
    {
      return is_nez(a) && is_less(abs(a), Smallestposval<T>());
    }
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE constexpr auto is_denormal_ ( EVE_SUPPORTS(cpu_),
                                                logical<wide<T, N, ABI>> const& a
                                              ) noexcept
  {
    return False(as(a));
  }
}

#endif
