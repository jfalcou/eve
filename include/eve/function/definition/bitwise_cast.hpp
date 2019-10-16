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
  using bitwise_compatible = std::void_t<decltype( bitwise_cast(std::declval<T>(), as<U>()) )>;
}

#endif
