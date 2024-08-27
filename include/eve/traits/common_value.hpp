//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/traits/as_wide.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  struct fth {
    using type = T;
  };

  template<plain_scalar_value S0, plain_scalar_value S1>
  consteval auto operator%(fth<S0>, fth<S1>) noexcept {
    return fth<decltype((std::declval<S0>() + std::declval<S1>()))>{};
  }

  template<typename T, typename N, plain_scalar_value S>
  consteval auto operator%(fth<wide<T, N>>, fth<S>) noexcept {
    return fth<wide<T, N>>{};
  }

  template<typename T, typename N, plain_scalar_value S>
  consteval auto operator%(fth<S>, fth<wide<T, N>>) noexcept {
    return fth<wide<T, N>>{};
  }

  template<typename T, typename N>
  consteval auto operator%(fth<wide<T, N>>, fth<wide<T, N>>) noexcept {
    return fth<wide<T, N>>{};
  }

  template<typename... Ts>
  using find_type = typename decltype((fth<Ts>{} % ...))::type;

  template<typename... Ts>
  requires(!plain_scalar_value<Ts> || ... )
  auto find_common_value() -> find_type<Ts... >;

  template<typename T0, typename... Ts>
  requires(   (plain_scalar_value<T0> && ... && plain_scalar_value<Ts>)
          &&  (std::same_as<T0,Ts> && ...)
          )
  T0 find_common_value();

  template<typename, typename... Ts>
  struct common_value_impl {};

  template<typename... Ts>
  struct common_value_impl<std::void_t<decltype(detail::find_common_value<Ts...>())>, Ts...>
  {
    using type = std::remove_cvref_t<decltype(detail::find_common_value<Ts...>())>;
  };
}

namespace eve
{
  /// Computes the SIMD-compatible common type between all `Ts`.
  template<typename... Ts>
  using common_value_t = typename eve::detail::common_value_impl<void, Ts...>::type;

  template<typename... Ts>
  struct common_value : eve::detail::common_value_impl<void, Ts...>
  {};
}

namespace eve::detail
{
  template<typename T, typename U>
  struct common_logical_impl;

  template<scalar_value T, scalar_value U>
  struct common_logical_impl<T,U> : as_logical<T>
  {};

  template<kumi::product_type T>
  struct common_logical_impl<T,T> : as_logical<T>
  {};

  template<value T, value U>
  struct common_logical_impl<logical<T>,logical<U>>
  {
    using type = logical<std::conditional_t<simd_value<T>, T, U>>;
  };

  template<scalar_value T, scalar_value U>
  struct common_logical_impl<logical<T>,logical<U>>
  {
    using type = logical<T>;
  };

  template<typename T, typename U>
    requires(!(scalar_value<T> && scalar_value<U>) && requires{ typename common_value<T, U>::type; } )
  struct common_logical_impl<T, U> : as_logical<typename common_value<T, U>::type>
  {};
}

namespace eve
{
  template<typename T, typename U>
  using common_logical_t = typename eve::detail::common_logical_impl<T, U>::type;

  template<typename T, typename U>
  struct common_logical : eve::detail::common_logical_impl<T, U>
  {};
}
