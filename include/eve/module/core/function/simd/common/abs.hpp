//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ABS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ABS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/function/bitwise_notand.hpp>
#include <eve/function/unary_minus.hpp>
#include <eve/function/max.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto abs_(EVE_SUPPORTS(cpu_), wide<T, N, ABI> const &v) noexcept
  {
    if constexpr(is_aggregated_v<ABI>) { return aggregate(eve::abs, v); }
    else if constexpr(is_emulated_v<ABI>)
    {
      return map(eve::abs, v);
    }
    else if constexpr(is_native_v<ABI>)
    {
      if constexpr(std::is_unsigned_v<T>) return v;
      if constexpr(std::is_floating_point_v<T>)
        return bitwise_notand(Mzero(as(v)), v);
      else if constexpr(std::is_integral_v<T> && std::is_signed_v<T>)
        return eve::max(v, -v);
    }
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto
  abs_(EVE_SUPPORTS(cpu_), saturated_type const &, wide<T, N, ABI> const &a) noexcept
  {
    if constexpr(std::is_integral_v<T> && std::is_signed_v<T>)
    {
      if constexpr(is_aggregated_v<ABI>)
        return aggregate(saturated_(eve::abs), a);
      else if constexpr(is_emulated_v<ABI>)
        return map(saturated_(eve::abs), a);
      else if constexpr(is_native_v<ABI>)
        return if_else(a == Valmin(as(a)), Valmax(as(a)), eve::abs(a));
    }
    else
    {
      return eve::abs(a);
    }
  }
}

#endif
