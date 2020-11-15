//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/swizzle.hpp>

namespace eve::detail
{
  //================================================================================================
  // Arbitrary SSE2 unary pattern
  //================================================================================================
  struct sse2_match
  {
    template<typename In, typename Out, std::ptrdiff_t... I>
    static constexpr auto check(pattern_<I...>, as_<In>, as_<Out>)  noexcept
    {
      using t_t = element_type_t<Out>;
      return (cardinal_v<Out> <= expected_cardinal_t<t_t>::value) && (sizeof(t_t) >= 4 );
    }
  };

  //================================================================================================
  // Arbitrary SSE2 binary pattern
  //================================================================================================
  struct sse2_binary_match
  {
    static constexpr auto mixed     = 0;
    static constexpr auto direct    = 1;
    static constexpr auto indirect  = 2;

    template<std::ptrdiff_t... I>
    static constexpr auto categorize(pattern_<I...> p, std::size_t card)  noexcept
    {
      if(card == 2)
      {
        auto p0 = p(0,2); auto p1 = p(1,2);

        if( (p0 < 2) && (p1 ==-1 || p1 >=2 ) )  return direct;
        else                                    return indirect;
      }

      if(card == 4)
      {
        auto p0 = p(0,4); auto p1 = p(1,4); auto p2 = p(2,4); auto p3 = p(3,4);

        if((p0 < 4) && (p1 < 4) && (p2 >= 4 || p2 == -1) && (p3 >= 4 || p3 == -1))  return direct;
        if((p2 < 4) && (p3 < 4) && (p0 >= 4 || p0 == -1) && (p1 >= 4 || p1 == -1))  return indirect;

        return mixed;
      }
    }

    template<typename In, typename Out, std::ptrdiff_t... I>
    static constexpr auto check(pattern_<I...> p, as_<In>, as_<Out>)  noexcept
    {
      if( sizeof(element_type_t<Out>) < 4) return false;
      return categorize(p, cardinal_v<In> ) != mixed;
    }
  };

  template<typename Wide, typename Target, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(sse2_), sse2_match const&
                                  , as_<Target> , Pattern const& p, Wide const& v
                                  )
  {
    constexpr auto m  = swizzle_mask<Pattern,sizeof(element_type_t<Wide>)>();

    if constexpr( sizeof(element_type_t<Wide>) == 8 )
    {
      auto perm = [&]<typename W>(W r)
      {
        if constexpr( current_api >= avx) return process_zeros(W(_mm_permute_pd(r  ,m)),p);
        else                              return process_zeros(W(_mm_shuffle_pd(r,r,m)),p);
      };

      return bit_cast( perm( bit_cast(v, as_<wide<double,cardinal_t<Target>>>() )), as_<Target>() );
    }
    else if constexpr( std::same_as<float, element_type_t<Wide>> )
    {
      auto perm = [&](auto r)
      {
        if constexpr( current_api >= avx) return process_zeros(Target(_mm_permute_ps(r  ,m)),p);
        else                              return process_zeros(Target(_mm_shuffle_ps(r,r,m)),p);
      };

      return perm(v);
    }
    else
    {
      return process_zeros(Target(_mm_shuffle_epi32(v,m)),p);
    }
  }

  template<typename Wide, typename Target, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto do_shuffle ( EVE_SUPPORTS(sse2_), sse2_binary_match const&
                                  , as_<Target> , Pattern const& p
                                  , Wide const& v0, Wide const& v1
                                  )
  {
    auto perm = [&p]<typename W>(W const& r, W const& s)
    {
      using           e_t = element_type_t<W>;
      constexpr auto  m   = swizzle_mask<Pattern,sizeof(e_t)>();

      if constexpr( sizeof(e_t) == 8 ) return process_zeros(W(_mm_shuffle_pd(r,s,m)),p);
      if constexpr( sizeof(e_t) == 4 ) return process_zeros(W(_mm_shuffle_ps(r,s,m)),p);
    };

    using           f_t = as_floating_point_t<Wide>;
    constexpr auto  cat = sse2_binary_match::categorize(Pattern{},cardinal_v<Target>);

    // shuffle pattern is [v0... v1...]
    if constexpr( cat == sse2_binary_match::direct   )
    {
      return bit_cast ( perm( bit_cast(v0, as_<f_t>() ), bit_cast(v1, as_<f_t>()) )
                      , as_<Target>()
                      );
    }
    // shuffle pattern is [v1... v0...]
    else if constexpr( cat == sse2_binary_match::indirect )
    {
      return bit_cast ( perm( bit_cast(v1, as_<f_t>() ), bit_cast(v0, as_<f_t>()) )
                      , as_<Target>()
                      );
    }
  }
}
