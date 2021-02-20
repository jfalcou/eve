//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/forward.hpp>
#include <eve/detail/meta.hpp>

namespace eve
{
  namespace detail
  {
    template<typename T> struct sign_of<logical<T>> : sign_of<T> {};
  }

  template<typename T, typename Sign = detail::sign_of_t<T>>
  struct as_integer
  {
    using type = detail::make_integer_t<sizeof(T), Sign>;
  };

  template<typename T, typename N, typename ABI, typename Sign>
  struct as_integer<wide<T,N,ABI>, Sign>
  {
    using type = wide<typename as_integer<T,Sign>::type, N>;
  };

  template<typename T, typename Sign>
  struct as_integer<logical<T>, Sign>
  {
    using type = logical< typename as_integer<T,Sign>::type >;
  };

  template<typename T, typename Sign = detail::sign_of_t<T>>
  using as_integer_t = typename as_integer<T, Sign>::type;

  template<typename T>
  struct as_uinteger : as_integer<T,unsigned>
  {};

  template<typename T>
  using as_uinteger_t = typename as_uinteger<T>::type;
}
