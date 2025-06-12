//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/concept/options.hpp>
#include <eve/concept/conditional.hpp>
#include <eve/deps/raberu/raberu.hpp>

#include <concepts>

namespace eve::detail
{
  template<typename C, typename T>
  EVE_FORCEINLINE constexpr bool validate_mask_for() noexcept
  {
    if constexpr (scalar_value<T>)
    {
      if constexpr (std::same_as<C, ignore_none_>) return true;
      else if constexpr (C::has_alternative)       return validate_mask_for<typename C::conditional_type, T>();
      else                                         return !(relative_conditional_expr<C> || simd_value<C>);
    }
    else
    {
      return true;
    }
  }

  template<callable_options O, typename T>
  constexpr EVE_FORCEINLINE bool validate_mask_for() noexcept
  {
    if constexpr (O::contains(condition_key)) return validate_mask_for<rbr::result::fetch_t<condition_key, O>, T>();
    else                                      return true;
  }
}
