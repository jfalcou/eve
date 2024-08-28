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
#include <eve/traits/translation.hpp>

namespace eve
{
  template<typename T>
  inline constexpr auto under_size = sizeof(translate_element_type_t<T>);

  template<typename T>
  struct  as_floating_point
        : detail::make_floating_point<(under_size<T> <= 4) ? 4: under_size<T>>
  {};

  template<typename T, typename N>
  struct as_floating_point<wide<T,N>>
  {
    using type = wide<typename as_floating_point<T>::type, N>;
  };

  template<typename T>
  struct as_floating_point<logical<T>>
  {
    using type = logical< typename as_floating_point<T>::type >;
  };

  template<typename T>
  using as_floating_point_t = typename as_floating_point<T>::type;
}
