//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_INF_HPP_INCLUDED
#define EVE_CONSTANT_INF_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  template<typename T>
  EVE_FORCEINLINE auto Inf(as_<T> const & = {}) noexcept
  {
    if constexpr(std::is_integer_v<T>)
      return T(std::numeric_limits<base>::max());
    else
      return T(std::numeric_limits<base>::infinity());
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto Inf(as_<wide<T, N, ABI>> const & = {}) noexcept
  {
    return wide<T, N, ABI>(Inf<T>());
  }
}

#endif
