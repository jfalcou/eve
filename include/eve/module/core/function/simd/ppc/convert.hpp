//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_CONVERT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_CONVERT_HPP_INCLUDED

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

#include <type_traits>

namespace eve::detail
{
  template<real_scalar_value T, typename N, real_scalar_value U>
  EVE_FORCEINLINE wide<U, N>
                  convert_(EVE_SUPPORTS(vmx_), wide<T, N, ppc_> const &v0, as_<U> const &tgt) noexcept
  {
    // Idempotent call
    if constexpr( std::is_same_v<T, U> )
      return v0;

    constexpr auto sz = sizeof(U) == sizeof(T);

    if constexpr( std::is_floating_point_v<T> )
    {
      if constexpr( std::is_integral_v<U> && sz )
      {
        if constexpr( std::is_signed_v<U> )
          return vec_cts(v0.storage(), 0);
        else
          return vec_ctu(v0.storage(), 0);
      }
      else
      {
        return convert_(EVE_RETARGET(simd_), v0, tgt);
      }
    }
    else if constexpr( std::is_integral_v<T> )
    {
      if constexpr( std::is_floating_point_v<U> && sz )
        return vec_ctf(v0.storage(), 0);
      else
        return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
    else
    {
      return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
  }
}

#endif
