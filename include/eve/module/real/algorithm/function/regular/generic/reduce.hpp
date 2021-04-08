//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/vectorized.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/function/swap_adjacent_groups.hpp>
#include <eve/function/splat.hpp>
#include <eve/pattern.hpp>
#include <bit>

namespace eve::detail
{
  //================================================================================================
  // reduce toward wide
  template<real_scalar_value T, typename N, typename ABI, typename Callable>
  EVE_FORCEINLINE auto reduce_( EVE_SUPPORTS(cpu_), splat_type const&
                              , wide<T,N,ABI> v, Callable f
                              ) noexcept
  {
    if constexpr( N::value == 1 )
    {
      return v;
    }
    else if constexpr( !is_aggregated_v<wide<T,N,ABI>> )
    {
      //============================================================================================
      // We have exactly log2(cardinal) - 1 butterfly steps to perform
      constexpr auto depth = std::bit_width(std::size_t{N::value}) - 1;

      //============================================================================================
      // Iterate over all levels
      return [&]<std::size_t... I>(std::index_sequence<I...>) mutable
      {
        ((v = f(v,swap_adjacent_groups(v, fixed<(1<<I)>{} ))),...);
        return v;
      }(std::make_index_sequence<depth>{});
    }
    else
    {
      //===========================================================================================
      // Slice, do f once, then reduce the result
      auto[l,h] = f.slice();
      return reduce( f(l,h) );
    }
  }

  //================================================================================================
  // reduce toward scalar
  template<real_scalar_value T, typename N, typename ABI, typename Callable>
  EVE_FORCEINLINE
  auto reduce_(EVE_SUPPORTS(cpu_), wide<T,N,ABI> v, Callable f) noexcept
  {
    auto that = splat(reduce)(v,f);
    return that.get(0);
  }
}
