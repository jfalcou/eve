//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_IS_LEZ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_IS_LEZ_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/zero.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_lez_(EVE_SUPPORTS(cpu_)
                                                   , T const &a) noexcept
  {
    if constexpr(native<T>)
    {
      if constexpr(unsigned_value<T>) return is_eqz(a);
      else                            return a <= Zero(as(a));
    }
    else                              return apply_over(is_lez, a);
  }
}

#endif
