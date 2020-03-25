//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_NEGATE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_NEGATE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/sign.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  negate_(EVE_SUPPORTS(cpu_), T const &a0, T const &a1) noexcept
  Requires(T, Vectorizable<T>)
  {
    if constexpr(std::is_signed_v<T>)
      return a0*sign(a1);
    else
      return if_else(is_nez(a1), a0, eve::zero_);
  }
}

#endif
