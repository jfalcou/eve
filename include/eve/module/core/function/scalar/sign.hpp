//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_SIGN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_SIGN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/scalar/is_nan.hpp>
#include <eve/function/scalar/is_ltz.hpp>
#include <eve/function/scalar/is_gtz.hpp>
#include <eve/function/scalar/shr.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto sign_(EVE_SUPPORTS(cpu_),
                                       T const &a) noexcept requires(T, vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      T r = bool(is_gtz(a)) - bool(is_ltz(a));
#ifdef EVE_NO_NANS
      return r;
#else
      return is_nan(a) ? a : r;
#endif
    }
    else
    {
      if constexpr(std::is_signed_v<T>)
        return shr(a, (sizeof(T) * 8 - 1)) - shr(-a, (sizeof(T) * 8 - 1));
      else
        return T(!!a);
    }
  }
}

#endif
