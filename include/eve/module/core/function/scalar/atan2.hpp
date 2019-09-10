//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_ATAN2_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_ATAN2_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/copysign.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_unordered.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/signnz.hpp>
#include <eve/tags.hpp>
#include <eve/assert.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <eve/module/core/detail/scalar/atan_kernel.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto atan2_( EVE_SUPPORTS(cpu_)
                                       , T const &a0
                                       , T const &a1    
                                       ) noexcept
  requires(T,  Floating<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      T q = eve::abs(a0/a1);
      T z = detail::atan_kernel(q, eve::rec(q));
      return (is_positive(a1)? z: Pi<T>()-z)*signnz(a0);
    }
    else 
    {
      EVE_ASSERT(std::is_floating_point_v<T>
                   , "[atan2 scalar] -type is not an IEEEValue"); 
    }    
  }
  
  template<typename T>
  EVE_FORCEINLINE constexpr auto atan2_( EVE_SUPPORTS(cpu_)
                                       , pedantic_type const &  
                                       , T a0
                                       , T a1    
                                       ) noexcept
  requires(T,  Floating<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr(platform::supports_nans)
        if (is_unordered(a0, a1)) return Nan(as(a0));
      
      if constexpr(platform::supports_infinites)
      {
        if (is_infinite(a0) && is_infinite(a1))
        {
          a0 = copysign(One(as(a0)), a0);
          a1 = copysign(One(as(a0)), a1);
        }
      }
      
      T q = eve::abs(a0/a1);
      T z = detail::atan_kernel(q, rec(q));
      T sgn = signnz(a0);
      z = (is_positive(a1)? z: Pi<T>()-z)*sgn;
      return is_eqz(a0) ? if_else(is_negative(a1), Pi(as(a0))*sgn, eve::zero_) : z;
    }
    else 
    {
      static_assert(std::is_floating_point_v<T>
                   , "[atan2 pedantic_ scalar] - type is not an IEEEValue"); 
    }    
  }
}

#endif
