//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_SIND_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_SIND_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/sinpi.hpp>

#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T, typename D>
  EVE_FORCEINLINE constexpr auto sind_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  {
    using elt_t         = element_type_t<T>;
    const double inv180 = 5.5555555555555555555555555555555555555555555555555e-3;
    if constexpr( std::is_same_v<elt_t, double> )
    {
      return D()(sinpi)(a0 * inv180);
    }
    else if constexpr( std::is_same_v<elt_t, float> )
    {
      auto tmp = convert(convert(a0, double_) * inv180, single_);
      return D()(sinpi)(tmp);
    }
    else
      return apply_over(D()(sind), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto sind_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    return sind(regular_type(), a0);
  }

}

#endif
