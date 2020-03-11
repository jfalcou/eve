//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_BIT_CAST_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_BIT_CAST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(bit_cast_, bit_cast);
}

// Concept based on bit_cast
namespace eve::detail
{
  template<typename T, typename U>
  using bits_convertible_with = std::void_t<decltype( bit_cast(std::declval<T>(), as<U>()) )>;

    // Concept based on bit_cast support
  template<typename T, typename U>
  using mixed_bit_compatible = std::void_t< vectorizable<T>,
                                                bits_convertible_with<T, value_type_t<U>>
                                              >;

  template<typename T, typename U>
  using bit_compatible = either < as_trait< bits_convertible_with, T, U>::value
                                    , as_trait< mixed_bit_compatible, T, U>::value
                                    , as_trait< mixed_bit_compatible, U, T>::value
                                    >;
}

#endif
