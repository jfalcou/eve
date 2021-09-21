//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/div_180.hpp>
#include <eve/function/sinpicospi.hpp>

#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T, decorator D>
  EVE_FORCEINLINE constexpr auto sindcosd_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return D()(sinpicospi)(div_180(a0));
    }
    else
      return apply_over2(D()(sindcosd), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto sindcosd_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    return sindcosd(regular_type(), a0);
  }

}
