//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_ADD_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_ADD_HPP_INCLUDED

#include <eve/function/saturate.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/saturated.hpp>
#include <eve/as.hpp>
#include <type_traits>
#include <limits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto add_(EVE_SUPPORTS(cpu_), T const &a, T const &b) noexcept
  requires(T, vectorizable<T>)
  {
    return a + b;
  }

  // -----------------------------------------------------------------------------------------------
  // Saturated case
  template<typename T> EVE_FORCEINLINE
  constexpr auto add_(EVE_SUPPORTS(cpu_)
                     , saturated_type const&
                     , T const& a
                     , T const& b) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr( std::is_floating_point_v<T> )
    {
      return a + b;
    }
    else if constexpr( std::is_signed_v<T> )
    {
      if constexpr( sizeof(T) >= 4 )
      {
        // large signed integral case
        using u_t = std::make_unsigned_t<T>;
        enum sizee { value = sizeof(T)*8-1 };

        u_t ux = a, uy = b;
        u_t res = ux + uy;

        ux = (ux >> sizee::value) + std::numeric_limits<T>::max();

        if( T((ux ^ uy) | ~(uy ^ res)) >= T(0)) return ux;
        return static_cast<T>(res);
      }
      else
      {
        // small signed integral case
        auto r = a+b;
        return static_cast<T>(saturate[as_<T>()](r));
      }
    }
    else // if constexpr( std::is_unsigned_v<T> )
    {
      if constexpr( sizeof(T) >= 4 )
      {
        // large unsigned integral case
        T r  = a + b;
        return r | -(r < a);
      }
      else
      {
        // small unsigned integral case - use C promotion then clamp
        auto        r   = a+b;
        decltype(r) mx  = std::numeric_limits<T>::max();
        return static_cast<T>(std::min(mx,r));
      }
    }
  }
}

#endif

#include "if_add.hpp"
