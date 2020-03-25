//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_EXPONENT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_EXPONENT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_nez.hpp> 
#include <eve/function/binarize.hpp>
#include <eve/function/shr.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/exponentbits.hpp>
#include <eve/constant/maxexponent.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto exponent_(EVE_SUPPORTS(cpu_),
                                      T const &a) noexcept
  Requires(as_integer_t<T>, floating_point<T>)
  {
    if (is_eqz(a)) return as_integer_t<T>(0); 
    if (is_not_finite(a)) return as_integer_t<T>(0); 
    auto x = shr(exponentbits(a), Nbmantissabits<T>()); 
    return sub[is_nez(a)](x, Maxexponent<T>());
  }
}

#endif
