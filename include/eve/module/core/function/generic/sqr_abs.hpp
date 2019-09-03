//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_SQR_ABS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_SQR_ABS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/sqr.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr T sqr_abs_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    if constexpr(std::is_floating_point_v<value_type_t<T>>) { return sqr(a); }
    else
    {
      static_assert(std::is_floating_point_v<value_type_t<T>>,
                    "[eve::sqr_abs] - Unsupported type: use eve::sqr.");
      return {};
    }
  }
}

#endif
