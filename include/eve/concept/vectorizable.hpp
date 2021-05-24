//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/forward.hpp>
#include <eve/detail/is_wide.hpp>
#include <eve/traits/element_type.hpp>
#include <eve/traits/is_logical.hpp>

#include <eve/detail/concepts.hpp>
#include <type_traits>

namespace eve::detail
{
  //==============================================================================================
  // Check if something is a scalar_value
  //==============================================================================================
  template<typename T> struct is_scalar_value : std::is_arithmetic<T>
  {};

  template<typename T>
  struct is_scalar_value<eve::logical<T>> : std::is_arithmetic<T>
  {};
}

namespace eve
{
  template<typename T> concept scalar_value                   = detail::is_scalar_value<T>::value;

  template<typename T> concept integral_scalar_value          = scalar_value<T> && std::integral<T>;
  template<typename T> concept signed_scalar_value            = scalar_value<T> && std::is_signed_v<T>;
  template<typename T> concept unsigned_scalar_value          = scalar_value<T> && std::unsigned_integral<T>;
  template<typename T> concept signed_integral_scalar_value   = scalar_value<T> && std::signed_integral<T>;
  template<typename T> concept floating_scalar_value          = scalar_value<T> && std::floating_point<T>;
  template<typename T> concept logical_scalar_value           = scalar_value<T> && is_logical_v<T>;
  template<typename T> concept real_scalar_value              = scalar_value<T> && std::same_as< detail::value_type_t<T>, element_type_t<T>>;
  template<typename T> concept floating_real_scalar_value     = real_scalar_value<T> && std::floating_point<detail::value_type_t<T>>;
  template<typename T> concept integral_real_scalar_value     = real_scalar_value<T> && std::integral<detail::value_type_t<T>>;
}

