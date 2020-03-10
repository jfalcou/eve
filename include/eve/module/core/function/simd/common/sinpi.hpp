//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SINPI_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SINPI_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/sin.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/module/core/detail/generic/rem2.hpp>
#include <eve/module/core/detail/simd/sin_finalize.hpp>
#include <eve/constant/pi.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/function/all.hpp>
#include <type_traits>

namespace eve::detail
{ 
  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto sinpi_(EVE_SUPPORTS(cpu_)
                           , restricted_type const &     
                           , eve::wide<T,N,ABI> const &x) noexcept
  {
    return eve::restricted_(sin)(x*Pi<T>()); 
  }

  ///////////////////////////////////////////////////////////////////////////
  // big_,  medium_,  small_
  template<typename D, typename T, typename N,  typename ABI>
  EVE_FORCEINLINE auto sinpi_(EVE_SUPPORTS(cpu_)
                           , D const &       
                           , eve::wide<T,N,ABI> const &a0) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      auto x = eve::abs(a0);
      auto [n, xr, dxr] = rem2(x); 
      return detail::sin_finalize(bitofsign(a0), n, xr, dxr); 
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::sinpi simd ] - type is not an IEEEValue"); 
    }   
  }   

  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto sinpi_(EVE_SUPPORTS(cpu_)
                            , eve::wide<T,N,ABI> const &a0) noexcept
  {
    auto x =  abs(a0);
    if (all(x <= T(0.25)))  return restricted_(sinpi)(x);
    else                    return big_(sinpi)(x);
  }
}

#endif
