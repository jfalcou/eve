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
#include <eve/function/combine.hpp>
#include <eve/function/splat.hpp>
#include <eve/function/swap_adjacent_groups.hpp>
#include <eve/pattern.hpp>
#include <bit>

namespace eve::detail
{
  //================================================================================================
  // reduce toward wide
  template<simd_value Wide, typename Callable>
  EVE_FORCEINLINE auto basic_reduce_( EVE_SUPPORTS(cpu_), splat_type const&
                                    , Wide v, Callable f
                                    ) noexcept
  {
    if constexpr( Wide::size() == 1 )
    {
      return v;
    }
    else if constexpr( !has_aggregated_abi_v<Wide> )
    {
      //============================================================================================
      // We have exactly log2(cardinal) - 1 butterfly steps to perform
      constexpr auto depth = std::bit_width(std::size_t{Wide::size()}) - 1;

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
      auto[l,h] = v.slice();
      auto r = splat(basic_reduce)( f(l,h), f );
      return eve::combine(r,r);
    }
  }

  //================================================================================================
  // reduce toward scalar
  template<simd_value Wide, typename Callable>
  EVE_FORCEINLINE auto basic_reduce_(EVE_SUPPORTS(cpu_), Wide v, Callable f) noexcept
  {
    if constexpr( Wide::size() == 1 )
    {
      return v.get(0);
    }
    else if constexpr( !has_aggregated_abi_v<Wide> )
    {
      auto that = splat(basic_reduce)(v,f);
      return that.get(0);
    }
    else
    {
      //===========================================================================================
      // Slice, do f once, then reduce the result
      auto[l,h] = v.slice();
      return  basic_reduce( f(l,h), f );
    }
  }
}
