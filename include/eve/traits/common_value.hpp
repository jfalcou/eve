//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/concept/simd.hpp>
#include <eve/traits/as_wide.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  struct find_common_value_reducer;

  template<>
  struct find_common_value_reducer<void> {};

  template<typename T>
  struct find_common_value_reducer
  {
    using type = T;

    template <typename U>
    friend auto operator%(
      find_common_value_reducer x,
      find_common_value_reducer<U> y
    ) {
      if constexpr (plain_scalar_value<T> && plain_scalar_value<U>)
      {
        return find_common_value_reducer<decltype(std::declval<T>() + std::declval<U>())>{};
      } else if constexpr (scalar_value<T> && arithmetic_simd_value<U>) {
        return y;
      } else if constexpr (arithmetic_simd_value<T> && (scalar_value<U> || std::same_as<T, U>)) {
        return x;
      }
      else
      {
        return find_common_value_reducer<void>{};
      }
    }
  };

  template<typename... Ts>
  using find_common_value_wide = typename decltype((find_common_value_reducer<Ts>{} % ...))::type;

  template<typename... Ts>
  requires (!scalar_value<Ts> || ...)
  auto find_common_value() -> find_common_value_wide<Ts... >;

  template<typename T0, typename... Ts>
  requires((scalar_value<T0> && ... && scalar_value<Ts>) && (std::same_as<T0,Ts> && ...))
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
  template<typename T>
  struct find_common_logical_reducer;

  template<>
  struct find_common_logical_reducer<void> {};

  template<typename T>
  struct find_common_logical_reducer
  {
    using type = T;

    template <typename U>
    friend auto operator%(
      find_common_logical_reducer x,
      find_common_logical_reducer<U> y
    ) {
      if      constexpr (simd_value<T>)                                  return find_common_logical_reducer<as_logical_t<T>>{};
      else if constexpr (std::same_as<T, bool> && std::same_as<U, bool>) return find_common_logical_reducer<bool>{};
      else if constexpr (std::same_as<T, bool>)                          return find_common_logical_reducer<as_logical_t<U>>{};
      else if constexpr (std::same_as<U, bool>)                          return find_common_logical_reducer<as_logical_t<T>>{};
      else if constexpr (scalar_value<U>)                                return find_common_logical_reducer<as_logical_t<T>>{};
      else if constexpr (simd_value<U>)                                  return find_common_logical_reducer<as_logical_t<as_wide_as_t<T, U>>>{};
      else                                                               return find_common_logical_reducer<void>{};
    }
  };

  template<typename... Ts>
  auto find_common_logical() -> typename decltype((find_common_logical_reducer<Ts>{} % ...))::type;

  template<typename, typename... Ts>
  struct common_logical_impl {};

  template<typename... Ts>
  struct common_logical_impl<std::void_t<decltype(detail::find_common_logical<Ts...>())>, Ts...>
  {
    using type = std::remove_cvref_t<decltype(detail::find_common_logical<Ts...>())>;
  };
}

namespace eve
{
  template<typename... Ts>
  using common_logical_t = typename eve::detail::common_logical_impl<void, Ts...>::type;

  template<typename... Ts>
  struct common_logical : eve::detail::common_logical_impl<void, Ts...>
  {};
}
