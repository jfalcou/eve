//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_COSPI_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_COSPI_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/cos.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/module/core/detail/generic/rem2.hpp>
#include <eve/module/core/detail/generic/cos_kernel.hpp>
#include <eve/module/core/detail/simd/cos_finalize.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pi.hpp>
#include <eve/function/trigo_tags.hpp>
#include <type_traits>

namespace eve::detail
{
    
  template<typename T>
  EVE_FORCEINLINE constexpr auto cospi_(EVE_SUPPORTS(cpu_)
                                     , restricted_type const &
                                     , T x) noexcept
  Requires(T, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      return eve::restricted_(cos)(x*Pi<T>()); 
    }
    else if constexpr(std::is_signed_v<T>)
    {
      return if_else(is_odd(x), eve::mone_, One(as(x))); 
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::cospi simd ] - type is not an IEEEValue"); 
    }   
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////
  // medium,  big,  small
  template<typename D, typename T>
  EVE_FORCEINLINE constexpr auto cospi_(EVE_SUPPORTS(cpu_)
                                     , D  const &      
                                     , T a0) noexcept
  Requires(T, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if (is_not_finite(a0)) return Nan<T>(); 
      const T x =  eve::abs(a0);
      if (x > Maxflint<T>()) return T(1); 
      auto [fn, xr, dxr] = rem2(x); 
      return cos_finalize(fn, xr, dxr); 
    }
    else if constexpr(std::is_signed_v<T>)
    {
      return if_else(is_odd(a0), eve::mone_, One(as(a0))); 
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::cospi scalar ] - type is not an IEEEValue");
      return T(); 
    }   
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto cospi_(EVE_SUPPORTS(cpu_)
                                     , T const &a0) noexcept
  Requires(T, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      auto x =  abs(a0);
      if (eve::abs(x) <= T(0.25)) return restricted_(cospi)(x);
      else                         return big_(cospi)(x);      
    }
    else if constexpr(std::is_signed_v<T>)
    {
      return if_else(is_odd(a0), eve::mone_, One(as(a0))); 
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::cospi scalar ] - type is not an IEEEValue");
      return T(); 
    }   
  }
}

#endif
