//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/traits/cardinal.hpp>
#include <eve/as.hpp>

#include <cstddef>

namespace eve::detail
{
  template<typename... Matcher>
  struct swizzle_matcher
  {
    // For a given list of pattern matcher and a pattern, find the first matcher matching it.
    template<typename Wide, typename Pattern>
    static constexpr auto find(Pattern p, as_<Wide> t ) noexcept
    {
      bool found[] = { Matcher::check(p, t)... };

      std::size_t i = 0;
      for(;i<sizeof...(Matcher);++i) { if( found[i] ) return i; }

      return i;
    }

    // Perform a swizzle with the best strategy for current pattern
    template<typename Pattern, typename Wide>
    EVE_FORCEINLINE auto operator()(Pattern const& p, Wide const& r) const
    {
      constexpr auto  cd  = cardinal_v<Wide>;
      constexpr auto  sz  = Pattern::size(cd);
      using that_t        = as_wide_t<Wide,fixed<sz>>;

      // We're swizzling so much we aggregate the output
      if constexpr( has_aggregated_abi_v<that_t> )
      {
        return that_t( r[ pattern_view<0,sz/2>(p) ], r[ pattern_view<sz/2,sz/2>(p) ] );
      }
      // We're swizzling the first half of an aggregate
      else if constexpr( has_aggregated_abi_v<Wide> && (as_pattern<sz>(Pattern{}) < cd/2) )
      {
        return r.slice(lower_)[p];
      }
      // We're swizzling the second half of an aggregate
      else if constexpr( has_aggregated_abi_v<Wide> && (as_pattern<sz>(Pattern{}) >= cd/2) )
      {
        return r.slice(upper_)[ slide_pattern<cd/2,sz>(p) ];
      }
      // We're swizzling the a full aggregate
      else if constexpr( has_aggregated_abi_v<Wide> )
      {
        puts("FUCKED UP");
        return that_t{};
      }
      else
      {
        // We select the proper shuffler/swizzler
        using found = typename type_at< find( as_pattern<sz>(Pattern{}), as_<that_t>())
                                      , types<Matcher...>
                                      >::type;

//        std::cout << typeid(found).name() << "\n";

        // We call the associated processing function
        return do_swizzle ( delay_t{}, EVE_CURRENT_API{}
                          , found{}
                          , as_<that_t>(), as_pattern<sz>(p), r
                          );
      }
    }
  };
}
