//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
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
  template<arithmetic_scalar_value T, typename N, typename... Vs>
  EVE_FORCEINLINE auto make(eve::as<wide<T, N>> const &, Vs... vs) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    if constexpr (has_plain_translation<T>)
    {
      return make(eve::as<wide<translate_t<T>, N>>{}, translate(vs)...);
    }
    else
    {
      using type = as_register_t<T, N, ppc_>;
      type that  = {static_cast<T>(vs)...};
      return that;
    }
  }

  template<arithmetic_scalar_value T, typename S, typename V>
  EVE_FORCEINLINE auto make(eve::as<wide<T, S>> const &, V v) noexcept
    requires ppc_abi<abi_t<T, S>>
  {
    if constexpr (has_plain_translation<T>)
    {
      return make(eve::as<wide<translate_t<T>, S>>{}, translate(v));
    }
    else
    {
      using type = as_register_t<T, S, ppc_>;

      return [&]<std::size_t... N>(std::index_sequence<N...> const&)
      {
        auto val = [](auto vv, auto) { return vv; };
        return type { val(static_cast<T>(v), N)... };
      }(std::make_index_sequence<S::value>());
    }
  }

  //================================================================================================
  // logical cases
  //================================================================================================
  template<arithmetic_scalar_value T, typename N, typename... Vs>
  EVE_FORCEINLINE auto make(eve::as<logical<wide<T, N>>> const &, Vs... vs) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    using type = as_logical_register_t<T, N, ppc_>;
    type that  = {logical<T>(vs).bits()...};
    return that;
  }

  template<arithmetic_scalar_value T, typename S, typename V>
  EVE_FORCEINLINE auto make(eve::as<logical<wide<T, S>>> const &, V v) noexcept
  requires ppc_abi<abi_t<T, S>>
  {
    using type = as_logical_register_t<T, S, ppc_>;

    return [&]<std::size_t... N>(std::index_sequence<N...> const&)
    {
      auto u   = logical<T>(v).bits();
      auto val = [](auto vv, auto) { return vv; };
      return type { val(u, N)... };
    }(std::make_index_sequence<S::value>());
  }
}
