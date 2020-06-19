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

#include <eve/detail/abi.hpp>
#include <type_traits>
#include <cstdint>

namespace eve
{
  template<typename T>
  struct as_
  {
    using type = T;
  };

  template<typename T>
  EVE_FORCEINLINE constexpr as_<std::decay_t<T>> as(T && = {}) noexcept
  {
    return {};
  }
}
