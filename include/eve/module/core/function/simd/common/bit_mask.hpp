//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BIT_MASK_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BIT_MASK_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto bit_mask_(EVE_SUPPORTS(cpu_), wide<T, N, ABI> const &v) noexcept
  {
    if constexpr(is_native_v<ABI>) { return is_nez(v).mask(); }
    else
    {
      if constexpr(is_aggregated_v<ABI>) return aggregate(eve::bit_mask, v);
      if constexpr(is_emulated_v<ABI>) return map(eve::bit_mask, v);
    }
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto bit_mask_(EVE_SUPPORTS(cpu_), logical<wide<T, N, ABI>> const &v) noexcept
  {
    if constexpr(is_native_v<ABI>) { return v.mask(); }
    else
    {
      if constexpr(is_aggregated_v<ABI>) return aggregate(eve::bit_mask, v);
      if constexpr(is_emulated_v<ABI>) return map(eve::bit_mask, v);
    }
  }
}

#endif
