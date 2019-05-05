//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NORMAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NORMAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/is_finite.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_not_denormal.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/is_logical.hpp>
#include <eve/platform.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto is_normal_(EVE_SUPPORTS(simd_),
                                    wide<T, N, ABI> const &v) noexcept
  {
    if constexpr(std::is_integral_v<T> || !platform::supports_denormals)
    {
      return is_nez(v);
    }
    else
    {
      return logical_and(is_finite(v), logical_and(is_nez(v), is_not_denormal(v)));
    }
  }
  
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE constexpr auto is_normal_ ( EVE_SUPPORTS(simd_),
                                                logical<wide<T, N, ABI>> const& v
                                              ) noexcept
  {
    return is_nez(v);
  }

}

#endif
