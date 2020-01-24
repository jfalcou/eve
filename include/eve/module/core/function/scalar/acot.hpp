//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_ACOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_ACOT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/rec.hpp>
#include <eve/module/core/detail/scalar/atan_kernel.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T>
  EVE_FORCEINLINE constexpr auto acot_(EVE_SUPPORTS(cpu_)
                                  , T const &a) noexcept
  requires(T, floating_point<T>)
  {
    T x  = eve::abs(a);
    return bit_xor(atan_kernel(rec(x), x), bitofsign(a));
  }
}

#endif
