//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_CLAMP_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_CLAMP_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto clamp_(EVE_SUPPORTS(cpu_),T const &v,T const &lo,T const &hi)
  noexcept requires(T, vectorizable<T>)
  {
    return (v < lo) ? lo : (hi < v) ? hi : v;
  }
}

#endif
