//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_LTZ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_LTZ_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/as_logical.hpp>
#include <eve/function/scalar/logical_not.hpp>
#include <eve/constant/false.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_ltz_(EVE_SUPPORTS(cpu_)
                                                   , T const &a) noexcept
  {
    return a < T(0);
  }

  template<typename T>
  EVE_FORCEINLINE constexpr logical<T> is_ltz_(EVE_SUPPORTS(cpu_)
                                              , logical<T> const &a) noexcept
  {
    return False<T>(); 
  }

  EVE_FORCEINLINE constexpr bool is_ltz_(EVE_SUPPORTS(cpu_)
                                        , bool const &a) noexcept
  {
    return  false; 
  }

}

#endif
