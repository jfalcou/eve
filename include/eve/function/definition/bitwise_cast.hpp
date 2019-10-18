//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_BITWISE_CAST_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_BITWISE_CAST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(bitwise_cast_, bitwise_cast);
}

// Concept based on bitwise_cast
namespace eve::detail
{
  template<typename T, typename U>
  using bits_convertible_with = std::void_t<decltype( bitwise_cast(std::declval<T>(), as<U>()) )>;

    // Concept based on bitwise_cast support
  template<typename T, typename U>
  using mixed_bitwise_compatible = std::void_t< vectorizable<T>,
                                                bits_convertible_with<T, value_type_t<U>>
                                              >;

  template<typename T, typename U>
  using bitwise_compatible = either < as_trait< bits_convertible_with, T, U>::value
                                    , as_trait< mixed_bitwise_compatible, T, U>::value
                                    , as_trait< mixed_bitwise_compatible, U, T>::value
                                    >;
}

#endif
