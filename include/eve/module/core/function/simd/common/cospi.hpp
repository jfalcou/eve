//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_COSPI_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_COSPI_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/cos.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/module/core/detail/generic/rem2.hpp>
#include <eve/module/core/detail/generic/cos_kernel.hpp>
#include <eve/module/core/detail/simd/cos_finalize.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/constant/pi.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/function/all.hpp>
#include <type_traits>

namespace eve::detail
{ 
  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto cospi_(EVE_SUPPORTS(cpu_)
                           , restricted_type const &     
                           , eve::wide<T,N,ABI> const &x) noexcept
  {
    return eve::restricted_(cos)(x*Pi<T>()); 
  }

  ///////////////////////////////////////////////////////////////////////////
  // big_,  medium_,  small_
  template<typename D, typename T, typename N,  typename ABI>
  EVE_FORCEINLINE auto cospi_(EVE_SUPPORTS(cpu_)
                           , D const &       
                           , eve::wide<T,N,ABI> const &a0) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr(is_aggregated_v<ABI>)
      {
        return aggregate(D()(eve::cospi), a0);
      }
      else if constexpr(is_emulated_v<ABI>)
      {
        return map( D()(eve::cospi), a0);
      }
      else
      {
        auto x = eve::abs(a0);
        x = if_else (is_not_finite(x), eve::allbits_, x); //Nan or Inf input
        x = if_else (is_greater(x, Maxflint(as(x))), eve::zero_, x);
        auto [n, xr, dxr] = rem2(x);
        return detail::cos_finalize(n, xr, dxr); 
      }
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::cospi simd ] - type is not an IEEEValue"); 
    }   
  }   

  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto cospi_(EVE_SUPPORTS(cpu_)
                            , eve::wide<T,N,ABI> const &a0) noexcept
  {
    auto x =  abs(a0);
    if (all(x <= T(0.25)))  return restricted_(cospi)(x);
    else                    return big_(cospi)(x);
  }
}

#endif
