//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/add.hpp>

namespace eve::detail
{
  template<auto N, typename Caller>
  struct decorated_callable<diff_type<N>,tag::add_,Caller>
  {
    template<floating_value T0, floating_value... Tn>
    requires(compatible_values<T0, Tn> && ...)
    EVE_FORCEINLINE constexpr auto operator()(T0 a0, Tn... an) const noexcept
    {
      return Caller::redispatch(func, diff_type<N>{}, a0, an...);
    }

    Caller func;
  };
}

#include <eve/module/real/core/function/diff/generic/add.hpp>
