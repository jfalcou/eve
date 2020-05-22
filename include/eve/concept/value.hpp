//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONCEPT_VALUE_HPP_INCLUDED
#define EVE_CONCEPT_VALUE_HPP_INCLUDED

#include <eve/forward.hpp>
#include <concepts> // to replace by <concepts> when libc++ is uptodate
#include <eve/concept/vectorizable.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/traits/is_logical.hpp>
#include <type_traits>

namespace eve
{
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

#endif
