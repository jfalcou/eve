//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_IS_REAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_IS_REAL_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/constant/false.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_real_(EVE_SUPPORTS(cpu_)
                                                    , T const &a) noexcept
  {
    return True(as(a));
  }
}

#endif
