//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONCEPT_COMPATIBLE_HPP_INCLUDED
#define EVE_CONCEPT_COMPATIBLE_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/traits/element_type.hpp>
#include <eve/forward.hpp>

namespace eve
{
  template<typename T, typename U>
  concept element_compatible_to = scalar_value<T>
                               && simd_value<U>
                               && std::convertible_to<T, element_type_t<U>>;

  template<typename T, typename U>
  concept compatible_values = element_compatible_to<T, U>
                           || element_compatible_to<U, T>
                           || std::same_as<T,U>;

  template<typename T, typename U>
  concept element_bit_compatible_to = scalar_value<T>
                                   && simd_value<U>
                                   && (sizeof(T) == sizeof(element_type_t<U>));

  template<typename T, typename U>
  concept bit_compatible_values = (sizeof(T) == sizeof(U))
                               || element_bit_compatible_to<T, U>
                               || element_bit_compatible_to<U, T>;


}

#endif
