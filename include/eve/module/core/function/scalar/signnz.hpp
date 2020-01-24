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
#include <eve/function/scalar/bit_and.hpp>
#include <eve/function/scalar/bit_or.hpp>
#include <eve/function/scalar/is_nan.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/signmask.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto signnz_(EVE_SUPPORTS(cpu_),
                                         T const &a) noexcept requires(T, vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
#ifndef EVE_NO_NANS
      return is_nan(a) ? Nan(as(a)) : bit_or(One(as(a)), bit_and(Signmask(as(a)), a));
#else
      return bit_or(One(as(a)), bit_and(Signmask(as(a)), a));
#endif
    }
    else
    {
      if constexpr(std::is_signed_v<T>)
        return (a >> (sizeof(T) * 8 - 2)) | 1;
      else
        return One(as(a));
    }
  }
}

#endif
