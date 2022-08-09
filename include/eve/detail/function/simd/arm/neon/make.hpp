//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/detail/abi.hpp>
#include <eve/arch/fundamental_cardinal.hpp>

namespace eve::detail
{
  //================================================================================================
  // Arithmetic cases
  //================================================================================================
  template<typename T, typename Size> struct neon_maker
  {
    using abi_type = abi_t<T,Size>;
    template<typename... Vs> auto operator()(Vs... vs) const
    {
      using type = as_register_t<T, fixed<sizeof...(vs)>, abi_type>;
      type that {static_cast<T>(vs)...};
      return that;
    }

    template<typename U> static U val(U u, int i)
    {
      if constexpr( std::same_as<abi_type,arm_64_> ) return (i < Size::value) ? u : U{0};
      else return u;
    }

    template<typename V> auto operator()(V v) const
    {
      auto impl = [&](auto... I)
      {
        using type = as_register_t<T, expected_cardinal_t<T, abi_type>, abi_type>;
        auto u     = static_cast<T>(v);
        return type {val(u, I)...};
      };

      return apply<expected_cardinal_v<T, abi_type>>(impl);
    }
  };

  template<real_scalar_value T, typename N, typename... Vs>
  EVE_FORCEINLINE auto make(eve::as<wide<T,N>> const &, Vs... vs) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    return neon_maker<T, N> {}(vs...);
  }

  //================================================================================================
  // Logical cases
  //================================================================================================
  template<real_scalar_value T, typename Size> struct neon_maker<logical<T>, Size>
  {
    using abi_type = abi_t<T,Size>;

    template<typename... Vs> auto operator()(Vs... vs) const
    {
      using type  = as_logical_register_t<T, fixed<sizeof...(vs)>, abi_type>;
      type that {logical<T>(vs).bits()...};
      return that;
    }

    template<typename U> static U val(U u, U z, int i)
    {
      if constexpr( std::same_as<abi_type,arm_64_> ) return (i < Size::value) ? u : z;
      else return u;
    }

    template<typename V> auto operator()(V v) const
    {
      auto impl   = [&](auto... I) {
        using type = as_logical_register_t<T, expected_cardinal_t<T, abi_type>, abi_type>;

        auto u  = logical<T>(v).bits();
        auto z  = logical<T>(false).bits();
        return type {val(u,z,I)...};
      };

      return apply<expected_cardinal_v<T, abi_type>>(impl);
    }
  };

  template<real_scalar_value T, typename N, typename... Vs>
  EVE_FORCEINLINE auto make(eve::as<logical<wide<T,N>>> const &, Vs... vs) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    return neon_maker<logical<T>, N> {}(vs...);
  }
}
