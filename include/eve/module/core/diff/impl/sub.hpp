//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/derivative.hpp>
#include <eve/traits/common_compatible.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/constant/mone.hpp>

namespace eve::detail
{
  template<auto N, floating_real_value T, floating_real_value... Ts>
  EVE_FORCEINLINE constexpr auto sub_(EVE_SUPPORTS(cpu_)
                                    , diff_type<N> const &
                                    , T, Ts ... ) noexcept
  {
    using r_t = common_compatible_t<T,Ts...>;
    if constexpr(N > sizeof...(Ts)+1) return zero(as < r_t>());
    else if constexpr(N == 1) return one(as<r_t>());
    else return mone(as<r_t>());
  }
}
