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

#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/pattern.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N, x86_abi ABI, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto gather_low_(EVE_SUPPORTS(sse2_), wide<T,N,ABI> v, Pattern p) noexcept
  {
    constexpr auto cd = cardinal_v<wide<T,N,ABI>>;
    constexpr auto sz = Pattern::size(cd);
    using   that_t    = as_wide_t<wide<T,N,ABI>,fixed<sz>>;

    constexpr Pattern q = {};
    constexpr auto c  = categorize<wide<T,N,ABI>>();

    // We're swizzling so much we aggregate the output
    if constexpr( has_aggregated_abi_v<that_t> )
    {
      return aggregate_swizzle(v,gather_low_n<N::value>);
    }
    // 32bits SSE register only
    else if constexpr(match(c,category::float32x4, category::int32x4, category::uint32x4) )
    {
      if constexpr(cd < 4)
      {
        return that_t(v.get(0));
      }
      else
      {
        using i_t = as_floating_point_t<wide<T,N,ABI>>;
        using o_t = as_floating_point_t<that_t>;
        using tgt_t = as_<that_t>;

        auto const r = bit_cast(v, as_<i_t>() );

              if constexpr(q == pattern<0,1,0,1>  ) return bit_cast( o_t{_mm_movelh_ps(r,r)}, tgt_t{});
        else  if constexpr(q == pattern<0,1,-1,-1>) return bit_cast( o_t{_mm_movelh_ps(r,i_t(0))}, tgt_t{});
        else  if constexpr(q == pattern<-1,-1,0,1>) return bit_cast( o_t{_mm_movelh_ps(i_t(0),r)}, tgt_t{});
      }
    }
    // Strict 64bits SSE register only
    else if constexpr(match(c,category::float64x2, category::int64x2, category::uint64x2) )
    {
      using f_t = as_floating_point_t<wide<T,N,ABI>>;
      auto const r = bit_cast(v, as_<f_t>() );

      return bit_cast( f_t{_mm_unpacklo_pd(r,r)}, as_<that_t>{} );
    }
    else
    {
      return gather_low_(EVE_RETARGET(cpu_),v,p);
    }
  }

  template<typename T, typename N, x86_abi ABI, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto gather_low_(EVE_SUPPORTS(avx_), wide<T,N,ABI> v, Pattern p) noexcept
  {
    constexpr auto cd = cardinal_v<wide<T,N,ABI>>;
    constexpr auto sz = Pattern::size(cd);
    using   that_t    = as_wide_t<wide<T,N,ABI>,fixed<sz>>;

    constexpr Pattern q = {};

    constexpr auto width_in   = cd*sizeof(T);
    constexpr auto width_out  = sz*sizeof(T);

    // We're swizzling so much we aggregate the output
    if constexpr( has_aggregated_abi_v<that_t> )
    {
      return aggregate_swizzle(v,gather_low_n<N::value>);
    }
    // 32bits SSE register only
    else if constexpr( width_in <= 16)
    {
      return gather_low_(EVE_RETARGET(sse2_),v,p);
    }
    else if constexpr( width_in == 32)
    {
      if constexpr(width_out == 32)
      {
        constexpr auto c  = categorize<wide<T,N,ABI>>();
        if constexpr( c == category::float64x4 )
        {
          return that_t{_mm256_permute2f128_pd(v,v,0)};
        }
        // AVX double precision
        else if constexpr( c == category::float32x8 )
        {
          return that_t{_mm256_permute2f128_ps(v,v,0)};
        }
        else if constexpr( (c && category::integer_) && std::same_as<ABI,x86_256_> )
        {
          return that_t{_mm256_permute2f128_si256(v,v,0)};
        }
      }
      else
      {
        return gather_low_(EVE_RETARGET(cpu_),v,p);
      }
    }
    else
    {
      return gather_low_(EVE_RETARGET(cpu_),v,p);
    }
  }
}
