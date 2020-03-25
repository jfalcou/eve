//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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
#include <eve/function/bit_notand.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/minus.hpp>
#include <eve/function/max.hpp>
#include <eve/function/saturated.hpp>
#include <eve/concept/stdconcepts.hpp>
//#include <concepts>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto abs_(EVE_SUPPORTS(cpu_)
                           , wide<T, N, ABI> const &v) noexcept
  {
    if constexpr(aggregated<ABI>)                    return aggregate(eve::abs, v);
    else if constexpr(emulated<ABI>)                 return map(eve::abs, v);
    else if constexpr(native_c<ABI>)
    {
      if constexpr(std::unsigned_integral<T>)        return v;
      else if constexpr(std::floating_point<T>)      return bit_notand(Mzero(as(v)), v);
      else if constexpr(std::signed_integral<T>)     return eve::max(v, -v);
    }
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto abs_(EVE_SUPPORTS(cpu_)
                           , saturated_type const &
                           , wide<T, N, ABI> const &a) noexcept
  {
    if constexpr(std::unsigned_integral<T>)    return a;
    else if constexpr(std::floating_point<T>)  return abs(a);
    else // if integral and signed_c
    {
      if constexpr(aggregated<ABI>)                return aggregate(saturated_(eve::abs), a);
      else if constexpr(emulated<ABI>)             return map(saturated_(eve::abs), a);
      else /* if constexpr(is_native_v<ABI>)*/     return if_else(a == Valmin(as(a)), Valmax(as(a)), eve::abs(a));
    }
  }
}

#endif
