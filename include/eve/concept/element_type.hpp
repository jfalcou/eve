//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/simd.hpp>
#include <eve/traits/element_type.hpp>

namespace eve
{
  template<typename T, typename... Ts>
  concept same_element_type = (std::same_as<element_type_t<T>, element_type_t<Ts>> || ...);

  template<typename T, typename... Ts>
  concept same_element_type_or_scalar = (scalar_value<T> || ... || scalar_value<Ts>) || same_element_type<T, Ts...>;
}
