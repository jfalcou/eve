//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_ARM_NEON_MAKE_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_ARM_NEON_MAKE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/as.hpp>
#include <iostream>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Arithmetic cases
  template<typename T, typename ABI>
  struct neon_maker
  {
    template<typename... Vs>
    auto operator()(Vs... vs) const
    {
      using type = as_register_t<T, fixed<sizeof...(vs)>, ABI>;
      type that{static_cast<T>(vs)...};
      return that;
    }

    template<typename U>
    static auto val(U u, int)
    {
      return u;
    }

    template<typename V>
    auto operator()(V v) const
    {
      auto impl = [&](auto... I) {
        using type = as_register_t<T, expected_cardinal_t<T, ABI>, ABI>;
        auto u     = static_cast<T>(v);
        return type{val(u, I)...};
      };

      return apply<expected_cardinal_v<T, ABI>>(impl);
    }
  };

  template<typename T, typename... Vs>
  EVE_FORCEINLINE auto make(as_<T> const &, eve::neon64_ const &, Vs... vs) noexcept
  {
    return neon_maker<T, eve::neon64_>{}(vs...);
  }

  template<typename T, typename... Vs>
  EVE_FORCEINLINE auto make(as_<T> const &, eve::neon128_ const &, Vs... vs) noexcept
  {
    return neon_maker<T, eve::neon128_>{}(vs...);
  }

  // -----------------------------------------------------------------------------------------------
  // Logical cases
  template<typename T, typename ABI>
  struct neon_maker<logical<T>, ABI>
  {
    template<typename... Vs>
    auto operator()(Vs... vs) const
    {
      using ltype = logical<T>;
      using type  = as_register_t<logical<T>, fixed<sizeof...(vs)>, ABI>;
      type that{ltype(vs).bits()...};
      return that;
    }

    template<typename V>
    auto operator()(V v) const
    {
      using ltype = logical<T>;
      auto impl   = [&](auto... I) {
        using type = as_register_t<ltype, expected_cardinal_t<ltype, ABI>, ABI>;

        auto u   = ltype(v).bits();
        auto val = [](auto vv, auto const &) { return vv; };

        return type{val(u, I)...};
      };

      return apply<expected_cardinal_v<ltype, ABI>>(impl);
    }
  };

  template<typename T, typename... Vs>
  EVE_FORCEINLINE auto make(as_<logical<T>> const &, eve::neon64_ const &, Vs... vs) noexcept
  {
    return neon_maker<logical<T>, eve::neon64_>{}(vs...);
  }

  template<typename T, typename... Vs>
  EVE_FORCEINLINE auto make(as_<logical<T>> const &, eve::neon128_ const &, Vs... vs) noexcept
  {
    return neon_maker<logical<T>, eve::neon128_>{}(vs...);
  }
}

#endif
