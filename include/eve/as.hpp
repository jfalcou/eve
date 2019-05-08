//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_AS_HPP_INCLUDED
#define EVE_AS_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <type_traits>

namespace eve
{
  template<typename T>
  struct as_
  {
    using type = T;
  };

  template<typename T>
  EVE_FORCEINLINE constexpr as_<std::decay_t<T>> as(T &&) noexcept
  {
    return {};
  }
}

#endif
