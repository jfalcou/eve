//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_ARM_NEON_MAKE_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_ARM_NEON_MAKE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/as.hpp>
#include <iostream>

namespace eve { namespace detail
{
  template< typename T,typename... Vs>
  EVE_FORCEINLINE auto make(as_<T> const&, eve::neon64_ const&, Vs... vs) noexcept
  {
    using type = ext::as_register_t<T,fixed<sizeof...(vs)>,eve::neon64_>;
    type that{ static_cast<T>(vs)... };
    return that;
  }

  template< typename T,typename... Vs>
  EVE_FORCEINLINE auto make(as_<T> const&, eve::neon128_ const&, Vs... vs) noexcept
  {
    using type = ext::as_register_t<T,fixed<sizeof...(vs)>,eve::neon128_>;
    type that{ static_cast<T>(vs)... };
    return that;
  }

  template< typename T,typename V>
  EVE_FORCEINLINE auto make(as_<T> const&, eve::neon64_ const&, V v) noexcept
  {
    auto impl = [&](auto... I)
    {
      using type = ext::as_register_t<T,expected_cardinal_t<T,eve::neon64_>,neon64_>;

      auto u = static_cast<T>(v);
      auto val = [](auto vv, auto const&) { return vv; };

      return type{val(u,I)...};
    };

    return apply<expected_cardinal_v<T,eve::neon64_>>(impl);
  }

  template< typename T,typename V>
  EVE_FORCEINLINE auto make(as_<T> const&, eve::neon128_ const&, V v) noexcept
  {
    auto impl = [&](auto... I)
    {
      using type = ext::as_register_t<T,expected_cardinal_t<T,eve::neon128_>,neon128_>;

      auto u = static_cast<T>(v);
      auto val = [](auto vv, auto const&) { return vv; };

      return type{val(u,I)...};
    };

    return apply<expected_cardinal_v<T,eve::neon128_>>(impl);
  }
} }

#endif
