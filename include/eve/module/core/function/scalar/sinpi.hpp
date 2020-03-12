//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_SINPI_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_SINPI_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/module/core/detail/generic/rem2.hpp>
#include <eve/module/core/detail/scalar/sin_finalize.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/sin.hpp>
#include <eve/function/trigo_tags.hpp>
#include <type_traits>

namespace eve::detail
{
    
  template<typename T>
  EVE_FORCEINLINE constexpr auto sinpi_(EVE_SUPPORTS(cpu_)
                                     , restricted_type const &
                                     , T x) noexcept
  requires(T, vectorizable<T>)
  {
    return eve::restricted_(sin)(x*Pi<T>()); 
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////
  // medium,  big,  small
  template<typename D, typename T>
  EVE_FORCEINLINE constexpr auto sinpi_(EVE_SUPPORTS(cpu_)
                                     , D  const &      
                                     , T a0) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if (is_not_finite(a0)) return Nan<T>(); 
      const T x =  eve::abs(a0);
      auto [fn, xr, dxr] = rem2(x);
      return sin_finalize(bitofsign(a0), fn, xr, dxr); 
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::sinpi scalar ] - type is not an IEEEValue");
      return T(); 
    }   
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto sinpi_(EVE_SUPPORTS(cpu_)
                                     , T const &a0) noexcept
  requires(T, vectorizable<T>)
  {
    auto x =  eve::abs(a0);
    if (eve::abs(x) <= T(0.25)) return restricted_(sinpi)(a0);
    else                        return big_(sinpi)(a0);      
  }
  
}

#endif
