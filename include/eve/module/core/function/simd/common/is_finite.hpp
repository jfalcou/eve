//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_FINITE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_FINITE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/true.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/sub.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto is_finite_(EVE_SUPPORTS(simd_),wide<T, N, ABI> const &v) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      return is_eqz(v-v);
    }
    else
    {
      return True(as(v));
    }
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto is_finite_(EVE_SUPPORTS(simd_), logical<wide<T, N, ABI>> const &v) noexcept
  {
    return True(as(v));
  }
}

#endif
