//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/wide_forward.hpp>
#include <eve/traits/translation.hpp>
#include <eve/deps/kumi.hpp>

namespace eve
{
  namespace _
  {
    template<typename T>
    extern logical<T> as_logical;

    template<typename T>
    requires(std::same_as<T,bool>)
    extern bool as_logical<T>;

    template<typename T>
    extern logical<T> as_logical<logical<T>>;

    template<has_plain_translation T>
    extern decltype(as_logical<translate_t<T>>) as_logical<T>;

    template<eve::product_type T>
    extern kumi::apply_traits<common_logical, T> as_logical<T>;
  }

  // forward declare common_logical
  template<typename... Ts>
  struct common_logical;

  template<typename T>
  using as_logical_t = decltype(as_logical<T>);
}
