//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_IS_POW2_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_IS_POW2_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_pow2_(EVE_SUPPORTS(cpu_)
                                                   , T const &a) noexcept
  requires integral_value<T>
  {
    if constexpr(native<T>)
    {
       return  is_gtz(a) && is_eqz(a & dec(a));
    }
    else  return apply_over(is_pow2, a);
  }
}

#endif
