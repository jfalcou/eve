//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_IS_FLINT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_IS_FLINT_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/frac.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr auto is_flint_(EVE_SUPPORTS(cpu_)
                                          , T const &a) noexcept
  {
    if constexpr(native<T>) return is_eqz(frac(a));
     else                   return apply_over(is_flint, a);
  }
}

#endif
