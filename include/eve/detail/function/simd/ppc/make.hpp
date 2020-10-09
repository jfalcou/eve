//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch/as_register.hpp>
#include <eve/as.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  //================================================================================================
  // arithmetic cases
  //================================================================================================
  template<real_scalar_value T, typename... Vs>
  EVE_FORCEINLINE auto make(eve::as_<T> const &, eve::ppc_ const &, Vs... vs) noexcept
  {
    using type = as_register_t<T, fixed<sizeof...(vs)>, eve::ppc_>;
    type that  = {static_cast<T>(vs)...};
    return that;
  }

  template<real_scalar_value T, typename V>
  EVE_FORCEINLINE auto make(eve::as_<T> const &, eve::ppc_ const &, V v) noexcept
  {
    auto impl = [&](auto... I) {
      using type = as_register_t<T, expected_cardinal_t<T>, eve::ppc_>;

      auto u   = static_cast<T>(v);
      auto val = [](auto vv, auto const &) { return vv; };

      return type {val(u, I)...};
    };

    return apply<expected_cardinal_v<T>>(impl);
  }

  //================================================================================================
  // logical cases
  //================================================================================================
  template<real_scalar_value T, typename... Vs>
  EVE_FORCEINLINE auto make(eve::as_<logical<T>> const &, eve::ppc_ const &, Vs... vs) noexcept
  {
    using type = as_register_t<logical<T>, fixed<sizeof...(vs)>, eve::ppc_>;
    type that  = {logical<T>(vs).bits()...};
    return that;
  }

  template<real_scalar_value T, typename V>
  EVE_FORCEINLINE auto make(eve::as_<logical<T>> const &, eve::ppc_ const &, V v) noexcept
  {
    using ltype = logical<T>;
    auto impl   = [&](auto... I) {
      using type = as_register_t<ltype, expected_cardinal_t<ltype>, eve::ppc_>;

      auto u   = ltype(v).bits();
      auto val = [](auto vv, auto const &) { return vv; };

      return type {val(u, I)...};
    };

    return apply<expected_cardinal_v<T>>(impl);
  }
}
