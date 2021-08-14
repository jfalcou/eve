//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/forward.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/traits/is_logical.hpp>

#include <concepts>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup concepts
  //! @{
  //! @var value
  //! The concept `value<T>` is satisfied if and only if T satisfies
  //! either `eve::scalar_value` or `eve::simd_value`.
  //!
  //! #### Examples
  //! - `eve::logical<eve::wide<char>>`
  //! - `float`
  //! - `eve::wide<int, eve::fixed<1>>`
  //!
  //! the concept can be refined in :
  //!  -  integral_value
  //!  -  signed_value
  //!  -  unsigned_value
  //!  -  signed_integral_value
  //!  -  floating_value
  //!  -  real_value
  //!  -  floating_real_value
  //!  -  integral_real_value
  //!  -  logical_value
  //!
  //! with obvious meanings
  //! @}
  //================================================================================================
  template<typename T> concept value                 = simd_value<T> || scalar_value<T>;

  template<typename T> concept integral_value        = value<T> && std::integral<detail::value_type_t<T>>;
  template<typename T> concept signed_value          = value<T> && std::is_signed_v<detail::value_type_t<T>>;
  template<typename T> concept unsigned_value        = value<T> && std::unsigned_integral<detail::value_type_t<T>>;
  template<typename T> concept signed_integral_value = value<T> && std::signed_integral<detail::value_type_t<T>>;
  template<typename T> concept floating_value        = value<T> && std::floating_point<detail::value_type_t<T>>;
  template<typename T> concept real_value            = real_simd_value<T> || real_scalar_value<T>;
  template<typename T> concept floating_real_value   = real_value<T> && std::floating_point<detail::value_type_t<T>>;
  template<typename T> concept integral_real_value   = real_value<T> && std::integral<detail::value_type_t<T>>;
  template<typename T> concept logical_value         = value<T> && is_logical_v<T>;
}
