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
#include <eve/detail/kumi.hpp>
#include <eve/detail/logical_tie_breaker.hpp>

namespace eve
{
  template<typename T>
  struct as_logical
  {
    using type = logical<T>;
  };

  template<>
  struct as_logical<bool>
  {
    using type = bool;
  };

  template<typename T>
  struct as_logical<logical<T>>
  {
    using type = logical<T>;
  };

  template<has_plain_translation T>
  struct as_logical<T> : as_logical< translate_t<T> >
  {};

  template<kumi::product_type T>
  struct as_logical<T> : as_logical<kumi::apply_traits_t<detail::logical_tie_breaker, T>>
  {};

  template<typename T>
  using as_logical_t = typename as_logical<T>::type;
}
