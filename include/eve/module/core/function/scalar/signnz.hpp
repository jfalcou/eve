//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_SIGNNZ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_SIGNNZ_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/scalar/bitofsign.hpp>
#include <eve/function/scalar/bit_or.hpp>
#include <eve/function/scalar/is_nan.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/signmask.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/platform.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto signnz_(EVE_SUPPORTS(cpu_),
                                         T const &a) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      return bit_or(One(as(a)), bitofsign(a));
    }
    else
    {
      if constexpr(std::is_signed_v<T>)
        return (a >> (sizeof(T) * 8 - 2)) | 1;
      else
        return One(as(a));
    }
  }

  template<typename T>
 EVE_FORCEINLINE constexpr auto signnz_(EVE_SUPPORTS(cpu_)
                                       , pedantic_type const &
                                       , T const &a) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr(eve::platform::supports_invalids)
        return is_nan(a) ? a : signnz(a);
    }
    else return signnz(a); 

  }  
}

#endif
