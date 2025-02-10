//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/traits/overload/impl/strict_elementwise.hpp>

namespace eve
{
  ///TODO: DOC
  template< template<typename> class Func
  , typename OptionsValues
  , typename... Options
  >
  struct strict_tuple_callable : strict_elementwise_callable<Func, OptionsValues, Options...>
  {
    using base_t = strict_elementwise_callable<Func, OptionsValues, Options...>;

    template<callable_options O, kumi::product_type T>
    constexpr EVE_FORCEINLINE auto behavior(auto arch, O const& opts, T x) const
    {
      return kumi::apply( [&](auto... a) { return static_cast<base_t const&>(*this).behavior(arch, opts, a...); }, x);
    }

    template<callable_options O, typename T, typename... Ts>
    constexpr EVE_FORCEINLINE auto behavior(auto arch, O const& opts, T x0, Ts... xs) const
    {
      return base_t::behavior(arch, opts, x0, xs...);
    }
  };
}
