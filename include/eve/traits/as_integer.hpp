//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/meta.hpp>
#include <eve/detail/wide_forward.hpp>
#include <eve/concept/value.hpp>
#include <eve/traits/element_type.hpp>
#include <eve/traits/translation.hpp>

namespace eve
{
  namespace _
  {
    template<typename T>
    extern unsigned integer_sign;

    template<signed_value T>
    extern signed integer_sign<T>;

    template<signed_value T>
    extern decltype(integer_sign<T>) integer_sign<logical<T>>;

    template <typename T>
    using integer_sign_t = decltype(integer_sign<T>);

    template<typename T, typename Sign = _::integer_sign_t<T>>
    extern _::make_integer_t<sizeof(T), Sign> as_integer;

    template<typename T, typename N, typename Sign>
    extern wide<decltype(as_integer<T,Sign>), N> as_integer<wide<T,N>, Sign>;

    template<typename T, typename Sign>
    extern logical<decltype(as_integer<T,Sign>)> as_integer<logical<T>, Sign>;
  }

  template<typename T, typename Sign = _::integer_sign_t<T>>
  using as_integer_t = decltype(_::as_integer<T, Sign>);

  template<typename T>
  using as_uinteger_t = decltype(_::as_integer<T,unsigned>);
}
