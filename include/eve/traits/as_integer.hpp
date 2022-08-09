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
#include <eve/traits/element_type.hpp>

namespace eve
{
  namespace detail
  {
    template<typename T>
    struct default_as_integer_sign :
     std::conditional<std::is_signed_v<element_type_t<T>>, signed, unsigned>
    {
    };

    template<typename T>
    struct default_as_integer_sign<logical<T>> : default_as_integer_sign<T> {};

    template <typename T>
    using default_as_integer_sign_t = typename default_as_integer_sign<T>::type;
  }

  template<typename T, typename Sign = detail::default_as_integer_sign_t<T>>
  struct as_integer
  {
    using type = detail::make_integer_t<sizeof(T), Sign>;
  };

  template<typename T, typename N, typename Sign>
  struct as_integer<wide<T,N>, Sign>
  {
    using type = wide<typename as_integer<T,Sign>::type, N>;
  };

  template<typename T, typename Sign>
  struct as_integer<logical<T>, Sign>
  {
    using type = logical< typename as_integer<T,Sign>::type >;
  };

  template<typename T, typename Sign = detail::default_as_integer_sign_t<T>>
  using as_integer_t = typename as_integer<T, Sign>::type;

  template<typename T>
  struct as_uinteger : as_integer<T,unsigned>
  {};

  template<typename T>
  using as_uinteger_t = typename as_uinteger<T>::type;
}
