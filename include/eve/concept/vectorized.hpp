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

#include <eve/traits/element_type.hpp>
#include <eve/traits/cardinal.hpp>
#include <eve/traits/is_logical.hpp>
#include <eve/forward.hpp>

#include <concepts>

namespace eve
{
  //================================================================================================
  // A type satisfies simd_value iff its cardinal is not scalar_cardinal
  //================================================================================================
  template<typename T> concept simd_value = !std::same_as<eve::cardinal_t<T>, scalar_cardinal>;

  template<typename T> concept integral_simd_value        = simd_value<T> && std::integral<detail::value_type_t<T>>;
  template<typename T> concept signed_simd_value          = simd_value<T> && std::is_signed_v<detail::value_type_t<T>>;
  template<typename T> concept unsigned_simd_value        = simd_value<T> && std::unsigned_integral<detail::value_type_t<T>>;
  template<typename T> concept signed_integral_simd_value = simd_value<T> && std::signed_integral<detail::value_type_t<T>>;
  template<typename T> concept floating_simd_value        = simd_value<T> && std::floating_point<detail::value_type_t<T>>;
  template<typename T> concept logical_simd_value         = simd_value<T> && is_logical_v<T>;
  template<typename T> concept real_simd_value            = simd_value<T> && std::same_as< detail::value_type_t<T>, element_type_t<T>>;
  template<typename T> concept floating_real_simd_value   = real_simd_value<T> && std::floating_point<detail::value_type_t<T>>;
  template<typename T> concept integral_real_simd_value   = real_simd_value<T> && std::integral<detail::value_type_t<T>>;
}

