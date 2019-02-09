//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_MZERO_HPP_INCLUDED
#define EVE_CONSTANT_MZERO_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  template<typename T>
  EVE_FORCEINLINE auto Mzero(as_<T> const & = {}) noexcept
  {
    if constexpr(std::is_same_v<T, float>) return T(-0.0f);
    if constexpr(std::is_same_v<T, double>) return T(-0.0);
    return T(0);
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto Mzero(as_<wide<T, N, ABI>> const & = {}) noexcept
  {
    return wide<T, N, ABI>(Mzero<T>());
  }
}

#endif
