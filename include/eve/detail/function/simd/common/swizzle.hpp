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
#include <eve/detail/function/simd/common/swizzle_patterns.hpp>
#include <eve/forward.hpp>
#include <eve/pattern.hpp>

namespace eve::detail
{
  //================================================================================================
  // Helper for aggregate swizzle
  //================================================================================================
  template<typename Wide, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto aggregate_swizzle(Wide const& v, Pattern p) noexcept
  {
    constexpr auto sz = Pattern::size(cardinal_v<Wide>);
    using   that_t    = as_wide_t<Wide,fixed<sz>>;

    return that_t(v[pattern_view<0,sz/2,sz>(p)], v[pattern_view<sz/2,sz,sz>(p)]);
  }

  //================================================================================================
  // Unary swizzle - logical
  //================================================================================================
  template<typename T, typename N, typename ABI, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto swizzle( cpu_ const&, logical<wide<T,N,ABI>> const& v, Pattern p) noexcept
  {
    constexpr auto sz = Pattern::size(N::value);
    return bit_cast( v.mask()[p], as<logical<wide<T,fixed<sz>>>>() );
  }

  //================================================================================================
  // Emulation
  //================================================================================================
  template<typename T, typename N, typename ABI, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto swizzle(cpu_ const&, wide<T,N,ABI> const& v, Pattern const& p)
  {
    constexpr auto cd = N::value;
    constexpr auto sz = Pattern::size(cd);
    using that_t      = as_wide_t<wide<T,N,ABI>,fixed<sz>>;

    constexpr auto q = as_pattern<cd>(Pattern{});

    // We're swizzling so much we aggregate the output
    if constexpr( has_aggregated_abi_v<that_t> && !has_aggregated_abi_v<wide<T,N,ABI>> )
    {
      return aggregate_swizzle(v,q);
    }
    // We're swizzling the first half of an aggregate
    else if constexpr( has_aggregated_abi_v<wide<T,N,ABI>> && (as_pattern<sz>(Pattern{}) < cd/2) )
    {
      return v.slice(lower_)[q];
    }
    // We're swizzling the second half of an aggregate
    else if constexpr( has_aggregated_abi_v<wide<T,N,ABI>> && (as_pattern<sz>(Pattern{}) >= cd/2) )
    {
      return v.slice(upper_)[ slide_pattern<cd/2,sz>(q) ];
    }
    // We're swizzling an aggregate in steplock [lo | hi]
    else if constexpr (   has_aggregated_abi_v<wide<T,N,ABI>>
                      && (as_pattern<sz>(pattern_view<0   ,sz/2,sz>(Pattern{})) <  cd/2)
                      && (as_pattern<sz>(pattern_view<sz/2,sz  ,sz>(Pattern{})) >= cd/2)
                      )
    {
      return that_t{ v[pattern_view<0,sz/2,sz>(q)], v[pattern_view<sz/2,sz,sz>(q)] };
    }
    // We're swizzling an aggregate in steplock [hi | lo]
    else if constexpr (   has_aggregated_abi_v<wide<T,N,ABI>>
                      && (as_pattern<sz>(pattern_view<0   ,sz/2,sz>(Pattern{})) >= cd/2)
                      && (as_pattern<sz>(pattern_view<sz/2,sz  ,sz>(Pattern{})) <  cd/2)
                      )
    {
      return that_t{ v[pattern_view<0,sz/2,sz>(q)], v[pattern_view<sz/2,sz,sz>(q)] };
    }
    // Check for patterns
    else if constexpr( !std::same_as<void, decltype(swizzle_pattern(cpu_{},v,q))> )
    {
      return swizzle_pattern(cpu_{},v,q);
    }
    else
    {
      return [=]<std::ptrdiff_t... I>(pattern_t<I...> const&)
      {
        return that_t{ (I == -1 ? T{0} : v.get(I))... };
      }(as_pattern<sz>(p));
    }
  }
}
