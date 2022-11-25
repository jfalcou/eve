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

  //================================================================================================
  //! @addtogroup traits
  //! @{
  //!
  //! @struct common_value_t
  //!
  //! @brief Computes a type that can represent all values in a list of types.
  //!
  //! **Required header:** `#include <eve/traits/common_value.hpp>`
  //!
  //! Similar to `std::common_type`.
  //!
  //! We cannot use `std::common_type` because it tends to return a bigger type:
  //!   For example: `std::int16_t`, `std::int8_t` will return `std::int32_t`: https://godbolt.org/z/vjf9c45E5
  //!
  //! We also do not follow standard promotion rules:
  //!      `std::common_value_t<std::int16_t, std::uint16_t>` is `std::int32_t`
  //! BUT: `std::common_value_t<std::int32_t, std::uint32_t>` is `std::uint32_t`
  //! We always do like 32 bit one: - `eve::common_value_t<std::int16_t, std::uint16_t>` is `std::uint16_t`
  //!
  //! For functors from eve/constant support is incomplete: FIX-#941.
  //! For now, we just skip them.
  //!
  //! *NOTE:* for signed unsigned of the same size we return unsigned of this size (same as std).
  //!
  //! For product types TODO: FIX-#905
  //! Right now we have some simplified logic.
  //!
  //! @}
  //================================================================================================

namespace eve::detail
{
  template<typename T0, typename... Ts>
  requires(   (scalar_value<T0> && ... && scalar_value<Ts>)
          &&  (std::same_as<T0,Ts> && ...)
          )
  T0 find_common_value();

  template<typename T0, typename... Ts>
  requires(simd_value<T0> || ... || simd_value<Ts>)
  auto find_common_value() -> decltype(( std::declval<T0>() + ... + std::declval<Ts>() ));

  template<typename, typename... Ts>
  struct common_value_impl;

  template<typename... Ts>
  struct common_value_impl<std::void_t<decltype(detail::find_common_value<Ts...>())>, Ts...>
  {
    using type = decltype(detail::find_common_value<Ts...>());
  };
}

namespace eve
{
  template<typename... Ts>
  using common_value_t = typename eve::detail::common_value_impl<void, Ts...>::type;
}
