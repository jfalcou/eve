//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_NAN_HPP_INCLUDED
#define EVE_CONSTANT_NAN_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  template<typename T>
  EVE_FORCEINLINE auto Nan(as_<T> const & = {}) noexcept
  {
    if constexpr(std::is_same_v < float>) return  T{bitwise_cast<base>(0xFFFFFFFFU)};
    if constexpr(std::is_same_v <double>) return  T{bitwise_cast<base>(0xFFFFFFFFFFFFFFFFULL)};
    return T(0);
  }

  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto Nan(as_<wide< T, N, ABI>> const & = {}) noexcept
  {
    return wide<T, N, ABI>(Nan<T>()); 
  }
}

#endif
