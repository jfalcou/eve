//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/traits/overload/impl/tuple.hpp>
#include <eve/detail/function/inner_bit_cast.hpp>
#include <eve/traits/bit_value.hpp>

namespace eve
{
  template< template<typename> class Func
          , typename OptionsValues
          , typename... Options
          >
  struct bit_callable : strict_tuple_callable<Func, OptionsValues, Options...>
  {
    using base_t = strict_tuple_callable<Func, OptionsValues, Options...>;

    template<typename T>
    constexpr static EVE_FORCEINLINE auto process_input(T v) noexcept
    {
      if constexpr (has_emulated_abi_v<as_wide<T>>) return detail::inner_bit_cast(v, as<as_uinteger_t<T>>{});
      else                                          return v;
    }

    template<callable_options O, kumi::product_type T>
    constexpr EVE_FORCEINLINE auto behavior(auto arch, O const& opts, T x) const
    {
      return kumi::apply([&](auto... xs) {
        const auto res = static_cast<base_t const&>(*this).behavior(arch, opts, process_input(xs)...);
        return detail::inner_bit_cast(res, as<bit_value_t<decltype(xs)...>>{});
      }, x);
    }

    template<callable_options O, typename... Ts>
    constexpr EVE_FORCEINLINE auto behavior(auto arch, O const& opts, Ts... xs) const
    {
      constexpr auto tgt = as<bit_value_t<Ts...>>{};
      return detail::inner_bit_cast(base_t::behavior(arch, opts, process_input(xs)...), tgt);
    }
  };
}
