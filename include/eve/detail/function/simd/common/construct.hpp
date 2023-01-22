//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/kumi.hpp>

namespace eve::detail
{
  template<simd_value Pack, typename... Args>
  EVE_FORCEINLINE auto construct_(EVE_SUPPORTS(cpu_), as<Pack> const&, Args const&... args) noexcept
  {
    using v_t = typename Pack::value_type;
    Pack that ( [&]<std::size_t... I>(std::index_sequence<I...>)
                {
                  constexpr auto K = sizeof...(Args);
                  return kumi::map( [&]<typename W>(auto const& n, W const&) { return W(n); }
                                  , kumi::make_tuple(args..., kumi::element_t<K+I,v_t>{}...)
                                  , Pack{} // used for types only
                                  );
                }(std::make_index_sequence<kumi::size_v<v_t> - sizeof...(Args)>{})
              );
    return that;
  }
}
