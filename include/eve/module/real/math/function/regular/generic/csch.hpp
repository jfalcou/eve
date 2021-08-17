//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once


#include <eve/detail/implementation.hpp>
#include <eve/function/sinh.hpp>
#include <eve/function/rec.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE auto csch_(EVE_SUPPORTS(cpu_)
                            , T const &a0) noexcept
  {
    if constexpr(has_native_abi_v<T>) return rec(sinh(a0));
    else                    return apply_over(csch, a0);
  }
}

