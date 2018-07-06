//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_SIMD_PPC_VMX_MAKE_HPP_INCLUDED
#define EVE_FUNCTION_SIMD_PPC_VMX_MAKE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/alias.hpp>
#include <eve/detail/compiler.hpp>
#include <eve/as.hpp>

#if defined(EVE_COMP_IS_GNUC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

namespace eve { namespace detail
{
  template< typename T,typename... Vs>
  EVE_FORCEINLINE auto make(as_<T> const&, eve::ppc_ const&, Vs... vs) noexcept
  {
    using type = ext::as_register_t<T,sizeof...(vs),eve::ppc_>;
    type that = { static_cast<T>(vs)... };
    return that;
  }

  template< typename T,typename V>
  EVE_FORCEINLINE auto make(as_<T> const&, eve::ppc_ const&, V v) noexcept
  {
    auto impl = [&](auto... I)
                {
                  using type = ext::as_register_t<T,expected_cardinal_v<T>,eve::ppc_>;

                  auto u = static_cast<T>(v);
                  auto val = [](auto vv, auto const&) { return vv; };

                  return type{val(u,I)...};
                };

    return apply<expected_cardinal_v<T>>(impl);
  }
} }

#if defined(EVE_COMP_IS_GNUC)
#pragma GCC diagnostic pop
#endif

#endif
