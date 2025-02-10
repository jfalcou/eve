//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/traits/overload/impl/relative_conditional.hpp>

namespace eve
{
  template< template<typename> class Func
  , typename OptionsValues
  , typename... Options
  >
  struct conditional_callable : relative_conditional_callable<Func, OptionsValues, conditional_option, Options...>
  {
    using base_t = relative_conditional_callable<Func, OptionsValues, conditional_option, Options...>;
    using func_t =  Func<OptionsValues>;

    struct ignore { template<typename T> operator T() { return T{}; } };

    template<callable_options O, typename T, typename... Ts>
    constexpr EVE_FORCEINLINE auto behavior(auto arch, O const& opts, T x0, Ts... xs) const
    {
      return base_t::behavior(arch, opts, x0, xs...);
    }
  };
}
