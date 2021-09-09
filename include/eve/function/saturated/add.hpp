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
  template<typename Caller>
  struct decorated_callable<saturated_type,tag::add_,Caller>
  {
    template<value T0, value... Tn>
    requires(compatible_values<T0, Tn> && ...)
    EVE_FORCEINLINE constexpr auto operator()(T0 a0, Tn... an) const noexcept
    {
      return Caller::redispatch(func, saturated_type{}, a0, an...);
    }

    Caller func;
  };
}

#include <eve/module/real/core/function/saturated/generic/add.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/saturated/simd/x86/add.hpp>
#endif
