//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_DIST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_DIST_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/min.hpp>
#include <eve/function/max.hpp>
#include <eve/function/saturated.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/skeleton_calls.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto dist_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(dist, a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE T dist_(EVE_SUPPORTS(cpu_)
                         , T const &a
                         , T const &b) noexcept
  requires has_native_abi_v<T>
  {
    return eve::max(a, b) - eve::min(a, b);
  }

  // -----------------------------------------------------------------------------------------------
  // saturated case
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto dist_(EVE_SUPPORTS(cpu_)
                            , saturated_type const &
                            , T const &a
                            , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(saturated_(dist), a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE T dist_(EVE_SUPPORTS(cpu_)
                         , saturated_type const &
                         , T const &a
                         , T const &b) noexcept
  requires has_native_abi_v<T>
  {
      auto d = dist(a, b);
      if constexpr(signed_integral_value<T>) return if_else(is_ltz(d), Valmax(as(a)), d);
      else                                   return d;
  }
}

#endif
