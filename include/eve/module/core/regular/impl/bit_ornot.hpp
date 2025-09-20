//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/bit_not.hpp>
#include <eve/module/core/regular/bit_or.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/traits/as_wides.hpp>
#include <eve/module/core/constant/allbits.hpp>

namespace eve::detail
{
  template<typename T0, callable_options O>
  EVE_FORCEINLINE auto
  bit_ornot_(EVE_REQUIRES(cpu_), O const &, T0 a) noexcept
  {
    return a;
  }

  template<typename T0, typename T1, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr bit_value_t<T0, T1, Ts...>
  bit_ornot_(EVE_REQUIRES(cpu_), O const &, T0 a, T1 b, Ts... args) noexcept
  {
    using r_t = bit_value_t<T0, T1, Ts...>;
    using b_t = as_integer_t<r_t>;
    if constexpr(sizeof...(Ts) == 0) //two parameters
    {
      using ra_t = detail::conditional_t<scalar_value<T0>,element_type_t<b_t>,b_t>;
      using rb_t = detail::conditional_t<scalar_value<T1>,element_type_t<b_t>,b_t>;
      auto ba = bit_cast(a, as<ra_t>{});
      auto bb = bit_cast(b, as<rb_t>{});
      return bit_cast( bit_or(b_t(ba),bit_not(b_t(bb))), as<r_t>());
    }
    else
    {
      return eve::bit_ornot(a, bit_and(b, args...));
    }
  }
}
