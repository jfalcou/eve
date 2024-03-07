//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/common_value.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_not_greater_equal.hpp>
#include <eve/module/core/regular/min.hpp>

namespace eve::detail
{


  template<typename T0, typename T1, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...>
  minmag_(EVE_REQUIRES(cpu_), O const & o, T0 a, T1 b, Ts... cs) noexcept
  {
    using r_t = common_value_t<T0, T1, Ts...>;
    auto mino = min[o.drop(saturated2)];
    auto abso =  abs[saturated];
    if constexpr(sizeof...(Ts) == 0) // 2 parameters
    {
      if constexpr(O::contains(numeric2))
      {
        auto aaa = if_else(is_nan(a), b, a);
        auto bbb = if_else(is_nan(b), a, b);
        return eve::minmag[pedantic2](aaa, bbb);
      }
      if constexpr( has_native_abi_v<r_t> )
      {
        auto ra = r_t(a);
        auto rb = r_t(b);
        constexpr bool is_scalar = scalar_value<r_t>;
        auto aa = abso(ra);
        auto bb = abso(rb);
        if constexpr(is_scalar)
        {
          return aa < bb ? ra : bb < aa ? rb : mino(ra, rb);
        }
        else
        {
          auto tmp = if_else(is_not_less_equal(aa, bb), rb, mino(ra, rb));
          return if_else(is_not_less_equal(bb, aa), ra, tmp);
        }
      }
      else
        return arithmetic_call(minmag[o], r_t(a), r_t(b));
    }
    else // N > 2 parameters
    {
      r_t that(minmag[o](r_t(a), r_t(b)));
      ((that = eve::minmag[o](that, r_t(cs))), ...);
      return that;
    }
  }


  template<kumi::non_empty_product_type Ts, callable_options O>
  EVE_FORCEINLINE constexpr auto minmag_(EVE_REQUIRES(cpu_), O const & o, Ts tup) noexcept
  {
    return kumi::apply( [&](auto... a) { return eve::minmag[o](a...); }, tup);
  }
}
