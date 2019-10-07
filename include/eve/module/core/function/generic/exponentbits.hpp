//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_EXPONENTBITS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_EXPONENTBITS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/constant/maxexponent.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <eve/function/shl.hpp>
#include <eve/platform.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/detail/meta.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto exponentbits_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    using v_t = value_type_t<T>;
    using i_t = as_integer_t<T>; 
    i_t i(shl(2*Maxexponent<v_t>()+1, Nbmantissabits<v_t>())); 
    return bitwise_and(i, a);
  }
}

#endif
