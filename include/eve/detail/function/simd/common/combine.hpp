//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_COMMON_COMBINE_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_COMMON_COMBINE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/forward.hpp>

#if defined(EVE_COMP_IS_GNUC)
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
    if constexpr(is_emulated_v<ABI>)
    {
      return apply<N::value>([&](auto... I) {
        return wide<T, typename N::combined_type>{l[ I ]..., h[ I ]...};
      });
    }
    else if constexpr(is_aggregated_v<ABI>)
    {
      using that_t = wide<T, typename N::combined_type>;
      return that_t(typename that_t::storage_type{l, h});
    }
  }
}

#if defined(EVE_COMP_IS_GNUC)
#  pragma GCC diagnostic pop
#endif

#endif
