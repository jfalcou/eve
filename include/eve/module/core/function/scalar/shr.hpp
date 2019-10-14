//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_SHR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_SHR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto shr_(EVE_SUPPORTS(cpu_), T const &a0, U const &a1) noexcept
                            requires(T, integral<U>, integral<T>)
  {
    return T(a0 >> a1);
  }
}

#endif
