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
#include <eve/concept/same_lanes.hpp>
#include <eve/concept/same_types.hpp>
#include <eve/traits/bit_value.hpp>

#include <concepts>
#include <type_traits>

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

  template<conditional_expr C, typename T0, typename... Ts>
  constexpr EVE_FORCEINLINE bool bit_validate_mask_for() noexcept
  {
    if constexpr (std::same_as<C, ignore_none_>) return true;
    else if constexpr (C::has_alternative)
    {
      using alt_t = typename C::alternative_type;

      if constexpr (simd_value<alt_t>)
      {
        if constexpr (kumi::product_type<T0>) return same_types_tuple<T0> && std::same_as<alt_t, kumi::apply_traits_t<bit_value, T0>>;
        else                                  return same_types<T0, Ts...> && std::same_as<alt_t, bit_value_t<T0, Ts...>>;
      }
      else
      {
        if constexpr (kumi::product_type<T0>) return same_types_tuple<T0> ;
        else                                  return same_types<T0, Ts...>;
      }
    }
    else
    {
      if constexpr (kumi::product_type<T0>)   return same_lanes_or_scalar_tuple<T0>;
      else                                    return same_lanes_or_scalar<T0, Ts...>;
    }
  }

  template<callable_options O, typename T0, typename... Ts>
  constexpr EVE_FORCEINLINE bool bit_validate_mask_for() noexcept
  {
    if constexpr (O::contains(condition_key)) return bit_validate_mask_for<rbr::result::fetch_t<condition_key, O>, T0, Ts...>();
    else                                      return true;
  }
}
