//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NOT_DENORMAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NOT_DENORMAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/as_logical.hpp>
#include <eve/function/scalar/abs.hpp>
#include <eve/function/scalar/is_eqz.hpp>
#include <eve/function/scalar/is_not_less.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/is_logical.hpp>
#include <eve/platform.hpp>
#include <type_traits>

namespace eve::detail
{

  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_not_denormal_(EVE_SUPPORTS(cpu_)
                                                        , T const &a) noexcept
  {
    if constexpr(std::is_integral_v<T> || is_logical_v<T> || !platform::supports_denormals)
    {
      return True(as(a));
    }
    else
    {
      return is_eqz(a) ||  is_not_less(eve::abs(a), Smallestposval(as(a))); 
    }
  }

  EVE_FORCEINLINE constexpr bool is_not_denormal_(EVE_SUPPORTS(cpu_), bool const &a) noexcept
  {
    return true;
  }

}

#endif
