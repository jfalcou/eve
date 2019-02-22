//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_IS_NATIVE_HPP_INCLUDED
#define EVE_DETAIL_IS_NATIVE_HPP_INCLUDED

#include <eve/arch/tags.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename X>
  struct is_native
      : std::integral_constant<bool,
                               !std::is_same_v<X, aggregated_> && !std::is_same_v<X, emulated_>>
  {
  };

  template<typename T>
  inline constexpr bool is_native_v = is_native<T>::value;

  template<typename T>
  using is_native_t = typename is_native<T>::type;

  // Associated Concept-like entity
  template<typename T>
  using Native = std::enable_if_t<is_native_v<T>>;
}

#endif
