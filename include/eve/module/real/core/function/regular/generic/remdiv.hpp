//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/div.hpp>
#include <eve/function/rem.hpp>
#include <eve/function/decorator.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/detail/apply_over.hpp>
#include <array>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto remdiv_(EVE_SUPPORTS(cpu_), T a, U b) noexcept
  requires compatible_values<T, U>
  {
    using r_t = common_compatible_t<T, U>;
    if constexpr(has_native_abi_v<T>)
    {
      return std::tuple<r_t, r_t>{rem(r_t(a), r_t(b)), toward_zero(div)(r_t(a), r_t(b))};
    }
    else  return apply_over2t(remdiv, r_t(a),r_t(b));
  }
}
