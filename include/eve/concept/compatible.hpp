//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/traits/element_type.hpp>
#include <eve/detail/wide_forward.hpp>

namespace eve
{
  template<typename T, typename U>
  concept element_compatible_to = scalar_value<T>
                               && simd_value<U>
                               && std::convertible_to<T, element_type_t<U>>;

  template<typename T, typename U>
  concept compatible_values = element_compatible_to<std::remove_cvref_t<T>, std::remove_cvref_t<U>>
                           || element_compatible_to<std::remove_cvref_t<U>, std::remove_cvref_t<T>>
                           || std::same_as<std::remove_cvref_t<T>,std::remove_cvref_t<U>>;

  template<typename T, typename U>
  concept size_compatible_to = scalar_value<T>
                            || std::same_as<cardinal_t<T>, cardinal_t<U>>;

  template<typename T, typename U>
  concept size_compatible_values = size_compatible_to<T, U>
                                || size_compatible_to<U, T>;

  template<typename T, typename... Ts>
  concept same_element_type = (std::same_as<element_type_t<std::remove_cvref_t<T>>, element_type_t<std::remove_cvref_t<Ts>>> && ...);

  template<typename T, typename U>
  concept different_value_type = !std::same_as<element_type_t<U>, element_type_t<T>>;

  template<typename I, typename T>
  concept index_compatible_values = integral_value<I> && floating_value<T> && size_compatible_values<I, T>;

  template<typename T, typename U>
  concept compatible_arithmetic_values = scalar_value<T> || scalar_value<U> || std::same_as<T, U>;
}
