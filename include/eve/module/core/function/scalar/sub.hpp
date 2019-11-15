//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_SUB_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_SUB_HPP_INCLUDED

#include <eve/concept/vectorizable.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/saturate.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/function/saturated.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  sub_(EVE_SUPPORTS(cpu_), T const &a, T const &b) noexcept requires(T, vectorizable<T>)
  {
    return a - b;
  }

  // -----------------------------------------------------------------------------------------------
  // Saturated case
  template<typename T> EVE_FORCEINLINE
  constexpr auto sub_(EVE_SUPPORTS(cpu_)
                     , saturated_type const&
                     , T const& a
                     , T const& b) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr( std::is_floating_point_v<T> )
    {
      return a - b;
    }
    else if constexpr( std::is_signed_v<T> )
    {
      if constexpr( sizeof(T) >= 4 )
      {
        using u_t = std::make_unsigned_t<T>;
        enum sizee { value = sizeof(T)*8-1 };

        u_t ux = a;
        u_t uy = b;
        u_t res = ux - uy;

        ux = (ux >> sizee::value) + std::numeric_limits<T>::max();

        if(T((ux ^ uy) & (ux ^ res)) < T(0)) res = ux;
        return static_cast<T>(res);
      }
      else
      {
        // small signed integral case
        auto r = a-b;
        return static_cast<T>(saturate(r, as<T>()));
      }
    }
    else // if constexpr( std::is_unsigned_v<T> )
    {
      // large unsigned integral case
      T r  = a - b;
      return r & -(r <= a);
    }
  }
}

#endif

#include "if_sub.hpp"
