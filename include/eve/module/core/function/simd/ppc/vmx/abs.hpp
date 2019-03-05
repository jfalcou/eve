//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_VMX_ABS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_VMX_ABS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N> EVE_FORCEINLINE wide<T, N, ppc_> abs_(EVE_SUPPORTS(vmx_)
                                                                        , wide<T, N, ppc_> const &v0) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;
    if constexpr(std::is_floating_point<T>) return vec_abs( v0.storage() );
    if constexpr(is_signed_int<T> && sizeof(T) <=  4) return vec_abs( v0.storage() );
    if constexpr(is_signed_int<T> && sizeof(T) == 8) return map(eve::abs, v0); 
    if constexpr(is_unsigned_int<T>) return v0;
  }
}

#endif
