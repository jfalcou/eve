//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ASECD_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ASECD_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/asec.hpp>
#include <eve/function/indeg.hpp>
#include <eve/function/raw.hpp>

namespace eve::detail
{
  template<floating_real_value T, typename D>
  EVE_FORCEINLINE constexpr auto asecd_(EVE_SUPPORTS(cpu_), D const &decorator, T const &a) noexcept
      requires(contains<D>(types<regular_type(), raw_type> {}))
  {
    if constexpr( has_native_abi_v<T> )
    {
      return indeg(decorator(asec)(a));
    }
    else
    {
      return apply_over(decorator(asecd), a);
    }
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto asecd_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    return asecd(regular_type(), a);
  }
}

#endif
