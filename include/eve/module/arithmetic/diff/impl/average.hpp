//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/constant/half.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/rec.hpp>
#include <eve/traits/common_compatible.hpp>

namespace eve::detail
{
  template<auto N, floating_real_value T, floating_real_value... Ts>
  EVE_FORCEINLINE constexpr T average_(EVE_SUPPORTS(cpu_)
                                    , diff_type<N> const &
                                    , T , Ts ... ys ) noexcept
  {
    using r_t = common_compatible_t<T,Ts...>;
    using elt_t = element_type_t<r_t>;
    return (N > sizeof...(Ts)+1) ? zero(as < r_t>()) : r_t(rec(elt_t(sizeof...(ys)+1)));
  }

}
