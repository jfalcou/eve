//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_SATURATE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_SATURATE_HPP_INCLUDED

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/clamp.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/logical_and.hpp>

namespace eve::detail
{
  // Don't do anything if we idem-saturate
  template<value IN>
  EVE_FORCEINLINE auto
  saturate_(EVE_SUPPORTS(cpu_), IN const &v0, as_<element_type_t<IN>> const &) noexcept
  {
    return v0;
  }

  template<real_scalar_value Target, real_scalar_value U>
  EVE_FORCEINLINE constexpr auto
  saturate_(EVE_SUPPORTS(cpu_), U const &a0, as_<Target> const &) noexcept
  {
    if constexpr( std::is_floating_point_v<Target> ) // saturating to floating point
    {
      if constexpr( std::is_floating_point_v<U> ) // from a floating point
      {
        if constexpr( sizeof(Target) >= sizeof(U) )
        {
          return a0;
        }
        else
        {
          auto mn = static_cast<double>(Valmin<float>());
          auto mx = static_cast<double>(Valmax<float>());
          return is_infinite(a0) ? a0 : clamp(a0, mn, mx);
        }
      }
      else // from an integer
      {
        return a0;
      }
    }
    else // saturating to integer
    {
      if constexpr( std::is_signed_v<Target> ) // saturating to signed integer
      {
        if constexpr( std::is_floating_point_v<U> )
        {
          return clamp(a0, static_cast<U>(Valmin<Target>()), static_cast<U>(Valmax<Target>()));
        }
        else if constexpr( std::is_signed_v<U> ) // from a signed
        {
          if constexpr( sizeof(Target) >= sizeof(U) )
          {
            return a0;
          }
          else
          {
            return clamp(a0, static_cast<U>(Valmin<Target>()), static_cast<U>(Valmax<Target>()));
          }
        }
        else // from an unsigned
        {
          return min(a0, static_cast<U>(Valmax<Target>()));
        }
      }
      else // saturating to unsigned integer
      {
        if constexpr( std::is_floating_point_v<U> )
        {
          return clamp(a0, static_cast<U>(0), static_cast<U>(Valmax<Target>()));
        }
        if constexpr( !std::is_signed_v<U> ) // from a unsigned
        {
          if constexpr( sizeof(Target) >= sizeof(U) )
          {
            return a0;
          }
          else
          {
            return min(a0, static_cast<U>(Valmax<Target>()));
          }
        }
        else // from a signed
        {
          if constexpr( sizeof(Target) >= sizeof(U) )
          {
            return clamp(a0, static_cast<U>(0), Valmax<U>());
          }
          else
          {
            return clamp(a0, static_cast<U>(0), static_cast<U>(Valmax<Target>()));
          }
        }
      }
    }
  }

  template<real_scalar_value Target, real_simd_value U>
  EVE_FORCEINLINE auto saturate_(EVE_SUPPORTS(cpu_), U const &v, as_<Target> const &at)
  {
    using elt_u = element_type_t<U>;
    if constexpr( has_aggregated_abi_v<U> )
      return aggregate(eve::saturate, v, at);
    else if constexpr( has_emulated_abi_v<U> )
      return map(eve::saturate, v, at);
    else
    {
      if constexpr( std::is_floating_point_v<Target> ) // saturating to floating point
      {
        if constexpr( std::is_floating_point_v<elt_u> ) // from a floating point
        {
          if constexpr( sizeof(Target) >= sizeof(elt_u) )
            return v;
          else
          {
            auto mn = U(Valmin<float>());
            auto mx = U(Valmax<float>());
            return if_else(is_infinite(v), v, clamp(v, mn, mx));
          }
        }
        else if constexpr( std::is_integral_v<elt_u> )
        {
          return v;
        }
      }

      else // saturating to integer
      {
        if constexpr( std::is_signed_v<Target> ) // saturating to signed integer
        {
          if constexpr( std::is_floating_point_v<elt_u> )
          {
            return clamp(v, static_cast<U>(Valmin<Target>()), static_cast<U>(Valmax<Target>()));
          }
          else if constexpr( std::is_signed_v<elt_u> ) // from a signed
          {
            if constexpr( sizeof(Target) >= sizeof(elt_u) )
              return v;
            else
              return clamp(v, U(Valmin<Target>()), U(Valmax<Target>()));
          }
          else // from an unsigned
          {
            return min(v, U(Valmax<Target>()));
          }
        }
        else // saturating to unsigned integer
        {
          if constexpr( std::is_floating_point_v<elt_u> )
          {
            return clamp(v, static_cast<U>(Zero<Target>()), static_cast<U>(Valmax<Target>()));
          }
          else if constexpr( !std::is_signed_v<elt_u> ) // from a unsigned
          {
            if constexpr( sizeof(Target) >= sizeof(elt_u) )
              return v;
            else
              return min(v, U(Valmax<Target>()));
          }
          else // from a signed
          {
            if constexpr( sizeof(Target) >= sizeof(elt_u) )
              return clamp(v, U(Zero<Target>()), Valmax<U>());
            else
              return clamp(v, U(Zero<Target>()), U(Valmax<Target>()));
          }
        }
      }
    }
  }
}

#endif
