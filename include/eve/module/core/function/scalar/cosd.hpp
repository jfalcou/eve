//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_COSD_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_COSD_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/module/core/detail/generic/cos_kernel.hpp>
#include <eve/module/core/detail/generic/sin_kernel.hpp> 
#include <eve/function/cos.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/deginrad.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/sqr.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T>
  EVE_FORCEINLINE constexpr auto cosd_(EVE_SUPPORTS(cpu_)
                                     , T const &a0) noexcept
  {
    return cos(big_type{}, deginrad(a0)); 
  }
  
  template<typename T>
  EVE_FORCEINLINE constexpr auto cosd_(EVE_SUPPORTS(cpu_)
                                     , restricted_type const &
                                     , T a0) noexcept
  Requires(T, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      auto x  = eve::abs(a0); 
      if (is_not_less_equal(x, T(45))) return Nan<T>();
      auto x2 = sqr(deginrad(x)); 
      return detail::cos_eval(x2);
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::cos scalar ] - type is not an IEEEValue"); 
    }   
  }

  template<typename T>
  EVE_FORCEINLINE auto cosd_(EVE_SUPPORTS(cpu_)
                           , small_type const &       
                           , T const &a0) noexcept
   Requires(T, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      T x = eve::abs(a0);
      auto out = is_not_less_equal(x, T(90)); 
      if (out) return Nan<T>();
      if (x > T(45))
      {
        x -= T(90);
        x =  deginrad(x); 
        return bit_xor(sin_eval(x, sqr(x)), bitofsign(a0));        
      }
      else
      {
        return cos_eval(sqr(deginrad(x)));
      } 
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::cos scalar ] - type is not an IEEEValue"); 
    }   
  }
  
  template<typename T, typename TAG>
  EVE_FORCEINLINE constexpr auto cosd_(EVE_SUPPORTS(cpu_)
                                     , TAG const & tag
                                     , T const &a0) noexcept
  {
    if constexpr(eve::is_trigonometric_tag_v<TAG>)
    {
      const T inv90 = Ieee_constant<T,0x3c360b61,0x3f86c16c16c16c17ll>();
      auto x  = eve::abs(a0); 
      auto xi = nearest(x*inv90);
      auto xr = fnma(xi, T(90), x);
      xr = deginrad(xr); 
      auto fn =  quadrant(xi); 
      return detail::cos_finalize(fn, xr);
    }
    else
    {
      static_assert(eve::is_trigonometric_tag_v<TAG>, "[tagged cosd ]: Used tag is unsupported"); 
    }
  }

}

#endif
