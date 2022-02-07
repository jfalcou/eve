//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/clamp.hpp>
#include <eve/module/core/regular/inc.hpp>
#include <eve/module/core/regular/is_gtz.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/logical_and.hpp>
#include <concepts>

namespace eve::detail
{
  template<real_scalar_value Target, real_scalar_value U>
  EVE_FORCEINLINE constexpr auto
  saturate_(EVE_SUPPORTS(cpu_), U const &a0, as<Target> const &) noexcept
  {
    if constexpr(std::same_as<U, Target>)
    {
      return a0;
    }
    else if constexpr( std::is_floating_point_v<Target> ) // saturating to floating point
    {
      if constexpr( std::is_floating_point_v<U> ) // from a floating point
      {
        if constexpr( sizeof(Target) >= sizeof(U) )
        {
          return a0;
        }
        else
        {
          auto mn = static_cast<double>(valmin(eve::as<float>()));
          auto mx = static_cast<double>(valmax(eve::as<float>()));
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
          return clamp(a0, static_cast<U>(valmin(eve::as<Target>())), static_cast<U>(valmax(eve::as<Target>())));
        }
        else if constexpr( std::is_signed_v<U> ) // from a signed
        {
          if constexpr( sizeof(Target) >= sizeof(U) )
          {
            return a0;
          }
          else
          {
            return clamp(a0, static_cast<U>(valmin(eve::as<Target>())), static_cast<U>(valmax(eve::as<Target>())));
          }
        }
        else // from an unsigned
        {
          return min(a0, static_cast<U>(valmax(eve::as<Target>())));
        }
      }
      else // saturating to unsigned integer
      {
        if constexpr( std::is_floating_point_v<U> )
        {
          return clamp(a0, static_cast<U>(0), static_cast<U>(valmax(eve::as<Target>())));
        }
        if constexpr( !std::is_signed_v<U> ) // from a unsigned
        {
          if constexpr( sizeof(Target) >= sizeof(U) )
          {
            return a0;
          }
          else
          {
            return min(a0, static_cast<U>(valmax(eve::as<Target>())));
          }
        }
        else // from a signed
        {
          if constexpr( sizeof(Target) >= sizeof(U) )
          {
            return clamp(a0, static_cast<U>(0), valmax(eve::as<U>()));
          }
          else
          {
            return clamp(a0, static_cast<U>(0), static_cast<U>(valmax(eve::as<Target>())));
          }
        }
      }
    }
  }

  template<real_scalar_value Target, real_simd_value U>
  EVE_FORCEINLINE auto saturate_(EVE_SUPPORTS(cpu_), U const &v, as<Target> const &at)
  {
    using elt_u = element_type_t<U>;

    if constexpr(std::same_as<elt_u, Target>)
      return v;
    else if constexpr( has_aggregated_abi_v<U> )
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
            auto mn = U(valmin(eve::as<float>()));
            auto mx = U(valmax(eve::as<float>()));
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
            return clamp(v, static_cast<U>(valmin(eve::as<Target>())), static_cast<U>(valmax(eve::as<Target>())));
          }
          else if constexpr( std::is_signed_v<elt_u> ) // from a signed
          {
            if constexpr( sizeof(Target) >= sizeof(elt_u) )
              return v;
            else
              return clamp(v, U(valmin(eve::as<Target>())), U(valmax(eve::as<Target>())));
          }
          else // from an unsigned
          {
            return min(v, U(valmax(eve::as<Target>())));
          }
        }
        else // saturating to unsigned integer
        {
          if constexpr( std::is_floating_point_v<elt_u> )
          {
            return clamp(v, static_cast<U>(zero(eve::as<Target>())), static_cast<U>(valmax(eve::as<Target>())));
          }
          else if constexpr( !std::is_signed_v<elt_u> ) // from a unsigned
          {
            if constexpr( sizeof(Target) >= sizeof(elt_u) )
              return v;
            else
              return min(v, U(valmax(eve::as<Target>())));
          }
          else // from a signed
          {
            if constexpr( sizeof(Target) >= sizeof(elt_u) )
              return clamp(v, U(zero(eve::as<Target>())), valmax(eve::as<U>()));
            else
              return clamp(v, U(zero(eve::as<Target>())), U(valmax(eve::as<Target>())));
          }
        }
      }
    }
  }
}
