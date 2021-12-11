//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/as_register.hpp>
#include <eve/arch/fundamental_cardinal.hpp>
#include <eve/as.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  //================================================================================================
  // arithmetic cases
  //================================================================================================
  template<real_scalar_value T, typename N, typename... Vs>
  EVE_FORCEINLINE auto make(eve::as<wide<T, N>> const &, Vs... vs) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    using type = as_register_t<T, N, ppc_>;
    type that  = {static_cast<T>(vs)...};
    return that;
  }

  template<real_scalar_value T, typename S, typename V>
  EVE_FORCEINLINE auto make(eve::as<wide<T, S>> const &, V v) noexcept
    requires ppc_abi<abi_t<T, S>>
  {
    using type = as_register_t<T, S, ppc_>;

    return [&]<std::size_t... N>(std::index_sequence<N...> const&)
    {
      return type { (static_cast<T>(N<S::value ? v : 0))... };
    }(std::make_index_sequence<fundamental_cardinal_v<T>>());
  }

  //================================================================================================
  // logical cases
  //================================================================================================
  template<real_scalar_value T, typename N, typename... Vs>
  EVE_FORCEINLINE auto make(eve::as<logical<wide<T, N>>> const &, Vs... vs) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    using type = as_logical_register_t<T, N, ppc_>;
    type that  = {logical<T>(vs).bits()...};
    return that;
  }

  template<real_scalar_value T, typename S, typename V>
  EVE_FORCEINLINE auto make(eve::as<logical<wide<T, S>>> const &, V v) noexcept
    requires ppc_abi<abi_t<T, S>>
  {
    return [&]<std::size_t... N>(std::index_sequence<N...> const&)
    {
      using type = as_logical_register_t<T, S, ppc_>;

      auto u   = logical<T>(v).bits();
      auto z   = logical<T>(false).bits();
      using t_t = decltype(u);

      auto val = [&](auto vv, auto i) -> t_t { return (i<S::value) ? vv : z; };

      return type {val(u, N)...};
    }(std::make_index_sequence<fundamental_cardinal_v<T>>());
  }
}
