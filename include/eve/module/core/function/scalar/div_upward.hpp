//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_DIV_UPWARD_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_DIV_UPWARD_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/function/iceil.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/saturated.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4723) // potential divide by 0
#endif
  
  //-----------------------------------------------------------------------------------------------
  // div upward_
  template<typename T>
  EVE_FORCEINLINE constexpr auto div_(EVE_SUPPORTS(cpu_)
                                     , T const &a0
                                     , T const &a1
                                     , upward_type const &
                                     ) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>) return ceil(a0/a1);
    else if constexpr(std::is_signed_v<T>)
    {
      if constexpr(std::is_same_v<T, std::int64_t>)
      {
        if (!a0) return  Zero<T>();
        if(a1)
        {
          auto q = saturated_(div)(a0, a1);
          auto r =a0-q*a1;
          if (is_nez(r)&&((a0^a1) >= 0)) return saturated_(inc)(q);
          return q;
        }
        else
          return ((a0>0) ? Valmax<T>() : Valmin<T>());
      }
      else
      {
        if(a1)
        {
          std::cout << a0 <<  "  " << a1 << std::endl;
          std::cout << static_cast<double>(a0)/static_cast<double>(a1) << std::endl;
          std::cout << iceil(static_cast<double>(a0)/static_cast<double>(a1)) << std::endl;
          return saturated_(convert)(iceil(static_cast<double>(a0)/static_cast<double>(a1)), as<T>());
        }
        else
          return (a0) ? ((a0>0) ? Valmax<T>() : Valmin<T>()) : Zero<T>();        
      }
    }
    else //if constexpr(std::is_unsigned_v<T>)
    {
      if(a1)
      {
        T q = a0/a1;
        if (is_nez(a0-q*a1)) return inc(q);
        return q;
      }
      else
        return bitwise_mask(a0);
    }
  }
}

#ifdef BOOST_MSVC
# pragma warning(pop)
#endif

#endif


