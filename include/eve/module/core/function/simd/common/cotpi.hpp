//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_COTPI_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_COTPI_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/module/core/detail/simd/cot_finalize.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_greater_equal.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/quadrant.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/constant/zero.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE constexpr auto cotpi_(EVE_SUPPORTS(cpu_)
                                     , restricted_type const &
                                     , wide<T, N, ABI> const & a0) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr(is_aggregated_v<ABI>)
      {
        return aggregate( restricted_(eve::cotpi), a0);
      }
      else if constexpr(is_emulated_v<ABI>)
      {
        return map( restricted_(eve::cotpi), a0);
      }
      else
      {
        auto x  = eve::abs(a0);
        auto a0pi = Pi<T>()*a0;
        return if_else(is_eqz(a0), rec(a0), if_else(is_not_less_equal(x, T(0.25)), eve::allbits_, rec(tancot_eval(a0pi))));
      }
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::cotpi simd ] - type is not an IEEEValue"); 
    }   
  }
  

  template<typename T, typename N,  typename ABI, typename TAG>
  EVE_FORCEINLINE constexpr auto cotpi_(EVE_SUPPORTS(cpu_)
                                       , TAG const & tag
                                       , wide<T, N, ABI> const &a0) noexcept
  {
    if constexpr(eve::is_trigonometric_tag_v<TAG>)
    {
      if constexpr(is_aggregated_v<ABI>)
      {
        return aggregate(TAG()(eve::cotpi), a0);
      }
      else if constexpr(is_emulated_v<ABI>)
      {
        return map(TAG()(eve::cotpi), a0);
      }
      else
      {
        auto x =  abs(a0);
        x = if_else (is_not_finite(a0) || is_flint(x), eve::allbits_, x);
        auto [fn, xr, dxr] =  rem2(x); 
        return cot_finalize(a0*Pi<T>(), quadrant(fn), xr, dxr);
      }
    }
    else
    {
      static_assert(eve::is_trigonometric_tag_v<TAG>, "[tagged cotpi ]: Used tag is unsupported"); 
    }
  }
  
  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE constexpr auto cotpi_(EVE_SUPPORTS(cpu_)
                                     ,  wide<T, N, ABI> const &a0) noexcept
  {
    return big_(eve::cotpi)(a0); 
  }


}

#endif
