//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_COMMON_COMBINE_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_COMMON_COMBINE_HPP_INCLUDED

#include <eve/detail/is_native.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/spy.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <cstring>

#if defined(SPY_COMPILER_IS_GNUC)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#  pragma GCC diagnostic ignored "-Wuninitialized"
#endif

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto
  combine(cpu_ const &, wide<T, N, ABI> const &l, wide<T, N, ABI> const &h) noexcept
  {
    using that_t = wide<T, typename N::combined_type>;

    if constexpr(is_emulated_v<ABI>)
    {
      return apply<N::value>( [&](auto... I)
                              {
                                return that_t{l[ I ]..., h[ I ]...};
                              }
                            );
    }
    else if constexpr(is_aggregated_v<ABI>)
    {
      that_t that;

      // Ugly type-punning for performance issues
      auto const *srcl = reinterpret_cast<detail::alias_t<std::byte const> *>(&l);
      auto const *srch = reinterpret_cast<detail::alias_t<std::byte const> *>(&h);
      auto *      dst  = reinterpret_cast<detail::alias_t<std::byte> *>(&that);

      std::memcpy(dst           , srcl, sizeof(l));
      std::memcpy(dst+sizeof(l) , srch, sizeof(h));

      return that;
    }
  }
}

#if defined(SPY_COMPILER_IS_GNUC)
#  pragma GCC diagnostic pop
#endif

#endif
