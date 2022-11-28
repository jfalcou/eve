//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T0, typename... Ts>
  requires(   (scalar_value<T0> && ... && scalar_value<Ts>)
          &&  (std::same_as<T0,Ts> && ...)
          )
  T0 find_common_value();

  template<typename... Ts>
  using find_type = decltype(( std::declval<Ts>() + ... ));

  template<typename T0, typename... Ts>
  requires(simd_value<T0> || ... || simd_value<Ts>)
  auto find_common_value() -> find_type<T0, Ts... >;

  template<typename, typename... Ts>
  struct common_value_impl;

  template<typename... Ts>
  struct common_value_impl<std::void_t<decltype(detail::find_common_value<Ts...>())>, Ts...>
  {
    using type = std::remove_cvref_t<decltype(detail::find_common_value<Ts...>())>;
  };
}

namespace eve
{
  template<typename... Ts>
  using common_value_t = typename eve::detail::common_value_impl<void, Ts...>::type;

  template<typename... Ts>
  using common_logical_t = as_logical_t<common_value_t<Ts...>>;

}
