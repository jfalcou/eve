//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_ATAN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_ATAN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/function/rec.hpp>
#include <eve/module/core/detail/scalar/atan_kernel.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T>
  EVE_FORCEINLINE constexpr auto atan_(EVE_SUPPORTS(cpu_)
                                  , T const &a) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      T x  = eve::abs(a);
      return bitwise_xor(atan_kernel(x, rec(x)), bitofsign(a));
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::atan scalar ] - type is not an IEEEValue"); 
    }
  }
}

#endif
