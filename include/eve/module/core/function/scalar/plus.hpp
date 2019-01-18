//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_PLUS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_PLUS_HPP_INCLUDED

//#include <eve/function/saturated.hpp>
// #include <eve/function/scalar/saturate.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
// #include <type_traits>
// #include <limits>
// #include <climits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T> EVE_FORCEINLINE
  constexpr T plus_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
  {
    return a+b;
  }

#if 0
  // -----------------------------------------------------------------------------------------------
  // Saturated case
  template<typename T> EVE_FORCEINLINE
  constexpr T plus_(EVE_SUPPORTS(cpu_), saturated_tag const&, T const& a, T const& b) noexcept
  {
    if constexpr( std::is_floating_point_v<T> )
    {
      return a + b;
    }

    if constexpr( std::is_signed_v<T> )
    {
      if constexpr( sizeof(T) >= 4 )
      {
        // large signed integral case
        using utype = typename std::make_unsigned<T>::type;
        enum sizee { value = sizeof(T)*CHAR_BIT-1 };

        utype ux = a, uy = b;
        utype res = ux + uy;

        ux = (ux >> sizee::value) + std::numeric_limits<T>::max();

        if( T((ux ^ uy) | ~(uy ^ res)) >= T(0)) return ux;
        return static_cast<T>(res);
      }
      else
      {
#if 0
        // small signed integral case
        auto r = a+b;
        return static_cast<T>(saturate<T>(r));
#endif
      }
    }

    if constexpr( std::is_unsigned_v<T> )
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
#endif
}

#endif
