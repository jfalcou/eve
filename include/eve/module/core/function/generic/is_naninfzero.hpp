//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/is_greater_equal.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr logical<T> is_naninfzero_(EVE_SUPPORTS(cpu_)
                                                          , T const &a) noexcept
  {
    using ui_t =  as_integer_t<T, unsigned>;
    using sui_t = element_type_t<ui_t>;
    constexpr sui_t lim = (sizeof(sui_t) == 4) ? 4278190079ULL : 18437736874454810623ULL; //bit_cast(Inf<T>(), as<sui_t>())
    if constexpr(scalar_value<T>)
    {
      return 2*bit_cast(a, as<ui_t>())-1 >=  lim;
    }
    else if constexpr(has_native_abi_v<T>)
    {
      using l_t = logical<T>;
      return bit_cast(2*bit_cast(a, as<ui_t>())-1 >= lim, as<l_t>());
    }
    else  return apply_over(is_naninfzero, a);
   }
}
