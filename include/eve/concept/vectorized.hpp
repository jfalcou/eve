//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/traits/element_type.hpp>
#include <eve/traits/cardinal.hpp>
#include <eve/traits/is_logical.hpp>
#include <eve/forward.hpp>

#include <eve/detail/concepts.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup concepts
  //! @{
  //! @var simd_value
  //! The concept `simd_value<T>` is satisfied if and only if T verifies that :
  //!
  //! <center>`std::is_same_v<cardinal_t<T>,scalar_cardinal> == false`</center>
  //!
  //! #### Examples
  //!
  //! - `eve::logical<eve::wide<char>>`
  //! - `eve::wide<float>`
  //! - `eve::wide<int, eve::fixed<1>>`
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

  template<typename T> struct is_simd_value : std::bool_constant<simd_value<T>> {};
}
