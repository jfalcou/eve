//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_MUL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_MUL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/saturate.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/saturated.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  mul_(EVE_SUPPORTS(cpu_), T const &a, T const &b) noexcept requires(T, vectorizable<T>)
  {
    return a * b;
  }

  // -----------------------------------------------------------------------------------------------
  // Saturated case
  template<typename T>
  EVE_FORCEINLINE constexpr auto mul_(EVE_SUPPORTS(cpu_)
                                    ,  saturated_type const &
                                     , T const &a
                                     , T const &b) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr( std::is_floating_point_v<T> )
    {
      return a * b;
    }
    else if constexpr( std::is_signed_v<T> )
    {
      if constexpr(sizeof(T) <= 2)
      {
        using up_t =  upgrade_t<T>;
        return static_cast<T>(saturate[as_<T>()](static_cast<up_t>(a)*static_cast<up_t>(b)));
      }
       else if constexpr(sizeof(T) == 4)
      {
        using un_t = std::make_unsigned_t<T>;
        using up_t = int64_t;
        enum Sizee{ value = sizeof(T)*8-1 };

        up_t res = up_t(a)*up_t(b);
        un_t res2 = (un_t(a ^ b) >> Sizee::value) + Valmax<T>();
        T hi = (res >> (Sizee::value+1));
        T lo = res;
        if(hi != (lo >> Sizee::value))  res = res2;
        return res;
      }
      else // if constexpr(sizeof(T) == 8)
      {
        using un_t = std::make_unsigned_t<T>;
        if (b == 0 || a == 0) return Zero<T>();
        T sgn =  bitwise_xor(bitofsign(a), bitofsign(b));
        un_t aa = eve::abs(a);
        un_t bb = eve::abs(b);
        auto aux = [sgn](const T& mini,  const T& maxi,
                         const un_t& amini, const un_t& amaxi)
          {
            un_t z = Valmax<T>()/amaxi;
            return (z < amini)
            ? ( sgn ? Valmin<T>():Valmax<T>())
            : mini*maxi;
          };
        if (bb >= aa)
          return aux(a, b, aa, bb);
        else
          return aux(b, a, bb, aa);
      }
    }
    else // if constexpr(std::is_unsigned_v<T>)
    {
      if constexpr(sizeof(T) <= 4)
      {
        using up_t =  upgrade_t<T>;
        up_t res = up_t(a)*up_t(b);
        return (res > Valmax<T>()) ? Valmax<T>() : static_cast<T>(res);
      }
      else
      {
        auto aux = [](const T& mini,  const T& maxi)
        {
          T z = Valmax<T>()/maxi;
          return (z < mini) ? Valmax<T>() : mini*maxi;
        };
        if (b == 0 || a == 0) return Zero<T>();
        if (b >= a)
          return aux(a, b);
        else
          return aux(b, a);
      }
    }
  }
}

#endif

#include "if_mul.hpp"
