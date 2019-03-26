//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_POSITIVE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_POSITIVE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/as_logical.hpp>
#include <eve/function/scalar/bitwise_cast.hpp>
#include <eve/constant/true.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_positive_(EVE_SUPPORTS(cpu_)
                                                        , T const &a) noexcept
  {
    if constexpr(std::is_integral_v<T>)
      return a >= T(0);
    else
    {
      using si_t = eve::detail::as_integer_t<T, signed>; 
      return as_logical_t<T>(bitwise_cast<si_t>(a) >=  si_t(0));
    }
    
  }
  
  template<typename T>
  EVE_FORCEINLINE constexpr logical<T> is_positive_(EVE_SUPPORTS(cpu_)
                                                   , logical<T> const &a) noexcept
  {
    return True(as(a)); 
  }
  
  EVE_FORCEINLINE constexpr bool is_positive_(EVE_SUPPORTS(cpu_)
                                             , bool const &a) noexcept
  {
    return  true; 
  }

}

#endif
