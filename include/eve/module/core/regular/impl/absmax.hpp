//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<typename T0, typename T1, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...>
  absmax_(EVE_REQUIRES(cpu_), O const & o, T0 r0, T1 r1, Ts... rs) noexcept
  {
    auto tmp1 =  rbr::drop(saturated2, o);
    auto omax = options<decltype(tmp1)>{tmp1};

    auto tmp2 =  rbr::drop(pedantic2, o);
    auto oabs1 = options<decltype(tmp2)>{tmp2};
    auto tmp3 =  rbr::drop(numeric2, oabs1);
    auto oabs = options<decltype(tmp3)>{tmp3};


     return eve::abs[oabs](eve::max[omax](r0, r1, rs...));
  }

  //================================================================================================
  // tuples
  //================================================================================================
  template<kumi::non_empty_product_type Ts, callable_options O>
  EVE_FORCEINLINE constexpr auto
  absmax_(EVE_REQUIRES(cpu_), O const & o, Ts tup) noexcept
  //  requires (kumi::size_v<Ts> >=  2)
  {
    auto tmp1 =  rbr::drop(saturated2, o);
    auto omax = options<decltype(tmp1)>{tmp1};

    auto tmp2 =  rbr::drop(pedantic2, o);
    auto oabs1 = options<decltype(tmp2)>{tmp2};
    auto tmp3 =  rbr::drop(numeric2, oabs1);
    auto oabs = options<decltype(tmp3)>{tmp3};

    return eve::abs[oabs](eve::max[omax](tup));

  }

}
