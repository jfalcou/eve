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

#include <cstddef>

namespace eve::detail
{
  template<typename... Matcher>
  struct swizzle_matcher
  {
    // For a given list of pattern matcher and a pattern, find the first matcher matching it.
    template<typename Pattern, typename Wide> static constexpr auto find() noexcept
    {
      Pattern p;
      std::size_t i = 0;

      bool found[] = { Matcher::check(p, as_<Wide>())... };
      for(;i<sizeof...(Matcher);++i)
      {
        if( found[i] )
          return i;
      }

      return i;
    }

    // Ensure that a pattern don't try to reference non-existent lanes
    template<int N, typename Pattern> static constexpr bool validate(Pattern const& p) noexcept
    {
      constexpr auto sz = Pattern::size(N);

      for(int i=0;i<sz;++i)
        if( (p(i,sz) >= N) || (p(i,sz) < -1) )
          return false;

      return true;
    }

    // Perform a swizzle with the best strategy for current pattern
    template<typename Pattern, typename Wide>
    EVE_FORCEINLINE auto operator()(Pattern const& p, Wide const& r) const
    {
      static_assert ( validate<cardinal_v<Wide>>(Pattern())
                    , "[eve::swizzle] - Out of range pattern index"
                    );

      constexpr auto  sz    = Pattern::size(cardinal_v<Wide>);
      using that_t  = as_wide_t<Wide,fixed<sz>>;
      using found   = typename type_at<find<Pattern, that_t>(), types<Matcher...>>::type;

      if constexpr( has_aggregated_abi_v<that_t> )
      {
        // We're swizzling so much we aggregate the output
        return that_t( r[ pattern_view<0,sz/2>(p) ], r[ pattern_view<sz/2,sz/2>(p) ] );
      }
      else
      {
        // We select the proper shuffler/swizzler
        std::cout << typeid(found).name() << "\n";
        return do_swizzle(delay_t{},EVE_CURRENT_API{}, found{}, p, r);
      }
    }
  };
}
