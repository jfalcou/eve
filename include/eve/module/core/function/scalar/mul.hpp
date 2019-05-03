//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_MUL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_MUL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto mul_(EVE_SUPPORTS(cpu_), T const &a, T const &b)
                  noexcept requires(T, Arithmetic<T>)
  {
    return a*b;
  }
}

namespace eve
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto operator*(T const& a, U const &b) noexcept -> decltype(eve::mul(a, b))
  {
    return eve::mul(a, b);
  }
}

#endif
