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

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/div_180.hpp>
#include <eve/function/cospi.hpp>
#include <eve/function/regular.hpp>

#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T, decorator D>
  EVE_FORCEINLINE constexpr auto cosd_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      using elt_t = element_type_t<T>;
      if constexpr(std::is_same_v<elt_t, double>)
      {
        return D()(cospi)(div_180(a0));
      }
      else
      {
        auto a0_180 =  single_(div_180(double_(a0))); // better precision in float
        return D()(cospi)(a0_180);
      }
    }
    else
      return apply_over(D()(cosd), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cosd_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    return cosd(regular_type(), a0);
  }

}
