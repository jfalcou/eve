//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/detail/abi.hpp>

namespace eve::detail
{
  //================================================================================================
  // Arithmetic cases
  //================================================================================================
  template<typename T, typename ABI> struct neon_maker
  {
    template<typename... Vs> auto operator()(Vs... vs) const
    {
      using type = as_register_t<T, fixed<sizeof...(vs)>, ABI>;
      type that {static_cast<T>(vs)...};
      return that;
    }

    template<typename U> static auto val(U u, int) { return u; }

    template<typename V> auto operator()(V v) const
    {
      auto impl = [&](auto... I) {
        using type = as_register_t<T, expected_cardinal_t<T, ABI>, ABI>;
        auto u     = static_cast<T>(v);
        return type {val(u, I)...};
      };

      return apply<expected_cardinal_v<T, ABI>>(impl);
    }
  };

  template<real_scalar_value T, typename N, arm_abi ABI, typename... Vs>
  EVE_FORCEINLINE auto make(eve::as_<wide<T,N,ABI>> const &, Vs... vs) noexcept
  {
    return neon_maker<T, ABI> {}(vs...);
  }

  //================================================================================================
  // Logical cases
  //================================================================================================
  template<real_scalar_value T, typename ABI> struct neon_maker<logical<T>, ABI>
  {
    template<typename... Vs> auto operator()(Vs... vs) const
    {
      using type  = as_logical_register_t<T, fixed<sizeof...(vs)>, ABI>;
      type that {logical<T>(vs).bits()...};
      return that;
    }

    template<typename V> auto operator()(V v) const
    {
      auto impl   = [&](auto... I) {
        using type = as_logical_register_t<T, expected_cardinal_t<T, ABI>, ABI>;

        auto u   = logical<T>(v).bits();
        auto val = [](auto vv, auto const &) { return vv; };

        return type {val(u, I)...};
      };

      return apply<expected_cardinal_v<T, ABI>>(impl);
    }
  };

  template<real_scalar_value T, typename N, arm_abi ABI, typename... Vs>
  EVE_FORCEINLINE auto make(eve::as_<logical<wide<T,N,ABI>>> const &, Vs... vs) noexcept
  {
    return neon_maker<logical<T>, ABI> {}(vs...);
  }
}
