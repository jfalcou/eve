//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018-2021 Joel FALCOU
  Copyright 2018-2021 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/pattern.hpp>

namespace eve::detail
{
  template< typename T, typename N, typename ABI
          , std::ptrdiff_t I0, std::ptrdiff_t... Is
          >
  EVE_FORCEINLINE auto swizzle_pattern( cpu_ const&, wide<T,N,ABI> const& v
                                      , pattern_t<I0, Is...> const&       p
                                      )
  {
    constexpr auto sz = pattern_t<I0, Is...>::size(N::value);
    using that_t      = as_wide_t<wide<T,N,ABI>,fixed<sz>>;

    // Check a pattern is like <0 1 2 ... N-1>
    [[maybe_unused]] constexpr
    auto is_id  = []<std::ptrdiff_t V0, std::ptrdiff_t... Vs>
                  ( std::integer_sequence<std::ptrdiff_t,V0,Vs...>)
                  {
                    return ((I0 == V0) && ... && (Is == Vs));
                  };


    // shuffle to all 0s
    if constexpr( ((I0 == -1) && ... && (Is == -1)) )
    {
      return that_t{0};
    }
    // broadcast a value
    else if constexpr( ((Is == I0) && ...) )
    {
      return that_t{v.get(I0)};
    }
    // shuffle to partial identity
    else if constexpr( is_id(std::make_integer_sequence<std::ptrdiff_t,sz>{}) )
    {
            if constexpr(sz >= N::value)    return that_t(v.storage());
      else  if constexpr(N::value/sz == 2)  return that_t(v.slice(lower_).storage());
      else                                  return v.slice(lower_)[p];
    }

    // If all pattern fails, we return void to signify we need to do a proper swizzle
  }
}
