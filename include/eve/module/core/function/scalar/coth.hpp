//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_COTH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_COTH_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/copysign.hpp>
#include <eve/function/expm1.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/rec.hpp>
#include <type_traits>

namespace eve::detail
{
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto coth_(EVE_SUPPORTS(cpu_)
                                     , T a0) noexcept
  requires std::floating_point<T>
  {
    auto x = eve::abs(a0+a0);
    auto t = rec(expm1(x));
    auto r = fma(T(2), t, T(1)); 
    return copysign(r, a0); 
  }
}

#endif
