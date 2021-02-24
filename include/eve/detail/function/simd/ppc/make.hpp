//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
  template<real_scalar_value T, typename N, typename... Vs>
  EVE_FORCEINLINE auto make(eve::as_<wide<T,N,ppc_>> const &, Vs... vs) noexcept
  {
    using type = as_register_t<T, N, ppc_>;
    type that  = {static_cast<T>(vs)...};
    return that;
  }

  template<real_scalar_value T, typename N, typename V>
  EVE_FORCEINLINE auto make(eve::as_<wide<T,N,ppc_>> const &, V v) noexcept
  {
    auto impl = [&](auto... I)
    {
      using type = as_register_t<T, N, ppc_>;

      auto u   = static_cast<T>(v);
      auto val = [](auto vv, auto const &) { return vv; };

      return type {val(u, I)...};
    };

    return apply<expected_cardinal_v<T>>(impl);
  }

  //================================================================================================
  // logical cases
  //================================================================================================
  template<real_scalar_value T, typename N, typename... Vs>
  EVE_FORCEINLINE auto make(eve::as_<logical<wide<T,N,ppc_>>> const &, Vs... vs) noexcept
  {
    using type = as_logical_register_t<T, N, ppc_>;
    type that  = {logical<T>(vs).bits()...};
    return that;
  }

  template<real_scalar_value T, typename N, typename V>
  EVE_FORCEINLINE auto make(eve::as_<logical<wide<T,N,ppc_>>> const &, V v) noexcept
  {
    auto impl   = [&](auto... I)
    {
      using type = as_logical_register_t<T, N, ppc_>;

      auto u   = logical<T>(v).bits();
      auto val = [](auto vv, auto const &) { return vv; };

      return type {val(u, I)...};
    };

    return apply<expected_cardinal_v<T>>(impl);
  }
}
