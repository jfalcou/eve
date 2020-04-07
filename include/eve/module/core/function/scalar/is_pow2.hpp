//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_POW2_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_POW2_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/traits/as_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  template <typename T>
  EVE_FORCEINLINE constexpr auto is_pow2_(EVE_SUPPORTS(cpu_)
                                        , const T &x) noexcept
  Requires(logical<T>, integral<T>)
  {
    return x != 0 && (x & (x - 1)) == 0;
  }

}

#endif
