//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NEZ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NEZ_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/as_logical.hpp>
#include <eve/is_logical.hpp>
#include <eve/forward.hpp>
#include <cmath>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  is_nez_(EVE_SUPPORTS(cpu_), T const &a) noexcept requires(as_logical_t<T>, vectorizable<T>)
  {
    if constexpr(is_logical_v<T>)
      return a;
    else
      return a != T{0};
  }
}

#endif
