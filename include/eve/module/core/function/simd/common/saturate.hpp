//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SATURATE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SATURATE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/min.hpp>
#include <eve/function/clamp.hpp>
#include <eve/as.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename Target, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto saturate_(EVE_SUPPORTS(cpu_),
                                 as_<Target> const &    at,
                                 wide<U, N, ABI> const &v) noexcept requires(wide<U, N, ABI>,
                                                                             vectorizable<Target>)
  {
    using u_t = wide<U, N, ABI>;
    if constexpr(is_aggregated_v<ABI>)
      return aggregate(eve::saturate, at, v);
    else if constexpr(is_emulated_v<ABI>)
      return map(eve::saturate, at, v);
    else
    {
      if constexpr(std::is_floating_point_v<Target>) // saturating to floating point
      {
        if constexpr(std::is_floating_point_v<U>) // from a floating point
        {
          if constexpr(sizeof(Target) >= sizeof(U))
            return v;
          else
          {
            auto mn = u_t(Valmin<float>());
            auto mx = u_t(Valmax<float>());
            return if_else(is_infinite(v), v, clamp(v, mn, mx));
          }
        }
        else // if constexpr(std::is_integral_v<U>)
        {
          if constexpr(sizeof(Target) > sizeof(U))
          {
            return v;
          }
          else
          {
            return  clamp(v, u_t(Valmin<Target>()), u_t(Valmax<Target>()));
          }         
        }
      }
      
      else // saturating to integer
      {
        if constexpr(std::is_signed_v<Target>) // saturating to signed integer
        {
          if constexpr(std::is_signed_v<U>) // from a signed
          {
            if constexpr(sizeof(Target) >= sizeof(U))
              return v;
            else
              return clamp(v, u_t(Valmin<Target>()), u_t(Valmax<Target>()));
          }
          else // from an unsigned
          {
            return min(v, u_t(Valmax<Target>()));
          }
        }
        else // saturating to unsigned integer
        {
          if constexpr(!std::is_signed_v<U>) // from a unsigned
          {
            if constexpr(sizeof(Target) >= sizeof(U))
              return v;
            else
              return min(v, u_t(Valmax<Target>()));
          }
          else // from a signed
          {
            if constexpr(sizeof(Target) >= sizeof(U))
              return clamp(v, u_t(Zero<Target>()), Valmax<u_t>());
            else
              return clamp(v, u_t(Zero<Target>()), u_t(Valmax<Target>()));
          }
        }
      }
    }
  }
}

#endif
