//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/pattern.hpp>
#include <eve/forward.hpp>
#include <eve/detail/function/slice.hpp>

namespace eve::detail
{
  //================================================================================================
  // Helper for aggregate basic_shuffle
  //================================================================================================
  template<typename Wide, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto aggregate_shuffler(Wide const& v, Pattern p) noexcept
  {
    constexpr auto sz = Pattern::size();
    using   that_t    = as_wide_t<Wide,fixed<sz>>;

    return that_t ( shuffle(v,pattern_view<0,sz/2,sz>(p))
                  , shuffle(v,pattern_view<sz/2,sz,sz>(p))
                  );
  }

  //================================================================================================
  // Unary basic shuffle - logical
  //================================================================================================
  template<typename T, typename N, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto basic_shuffle_ ( EVE_SUPPORTS(cpu_)
                                      , logical<wide<T,N>> const& v, Pattern p
                                      ) noexcept
  {
    constexpr auto sz = Pattern::size();
    return bit_cast( shuffle(v.mask(),p), as<logical<wide<T,fixed<sz>>>>() );
  }

  template<typename T, typename N, std::ptrdiff_t... I>
  EVE_FORCEINLINE auto basic_shuffle_emulated(wide<T,N> const& v, pattern_t<I...>)
  {
    constexpr auto sz = pattern_t<I...>::size();
    using that_t      = as_wide_t<wide<T,N>,fixed<sz>>;

    return that_t{ (I == na_ ? T{0} : v.get(I))... };
  }

  //================================================================================================
  // Emulation
  //================================================================================================
  template<typename T, typename N, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto basic_shuffle_(EVE_SUPPORTS(cpu_), wide<T,N> const& v, Pattern const&)
  {
    constexpr auto cd = N::value;
    constexpr auto sz = Pattern::size();
    using that_t      = as_wide_t<wide<T,N>,fixed<sz>>;

    constexpr Pattern q = {};

    // We're swizzling so much we aggregate the output
    if constexpr( has_bundle_abi_v<that_t> )
    {
      return that_t{ kumi::map( [](auto m) { return shuffle(m,Pattern{}); }, v ) };
    }
    else if constexpr( has_aggregated_abi_v<that_t> && !has_aggregated_abi_v<wide<T,N>> )
    {
      return aggregate_shuffler(v,q);
    }
    // Be sure we can shuffle everything ionside a single vector of ouput
    else if constexpr( !has_aggregated_abi_v<that_t> )
    {
      // We're swizzling the first half of an aggregate
      if constexpr( has_aggregated_abi_v<wide<T,N>> && q.strictly_under(cd/2) )
      {
        return shuffle(v.slice(lower_),q);
      }
      // We're swizzling the second half of an aggregate
      else if constexpr( has_aggregated_abi_v<wide<T,N>> && q.over(cd/2) )
      {
        return shuffle(v.slice(upper_), slide_pattern<cd/2,sz>(q) );
      }
      // We're swizzling an aggregate in steplock [lo | hi]
      else if constexpr (   has_aggregated_abi_v<wide<T,N>>
                        && pattern_view<0   ,sz/2,sz>(q).strictly_under(cd/2)
                        && pattern_view<sz/2,sz  ,sz>(q).over(cd/2)
                        )
      {
        return that_t { shuffle(v,pattern_view<0,sz/2,sz>(q))
                      , shuffle(v,pattern_view<sz/2,sz,sz>(q))
                      };
      }
      // We're swizzling an aggregate in steplock [hi | lo]
      else if constexpr (   has_aggregated_abi_v<wide<T,N>>
                        && pattern_view<0   ,sz/2,sz>(q).over(cd/2)
                        && pattern_view<sz/2,sz  ,sz>(q).strictly_under(cd/2)
                        )
      {
        return that_t { shuffle(v,pattern_view<0,sz/2,sz>(q))
                      , shuffle(v,pattern_view<sz/2,sz,sz>(q))
                      };
      }
      else
      {
        return basic_shuffle_emulated(v, q);
      }
    }
    else
    {
      return basic_shuffle_emulated(v, q);
    }
  }
}
