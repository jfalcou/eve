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
#include <eve/detail/function/simd/x86/patterns.hpp>
#include <eve/pattern.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template< typename T, typename N, x86_abi ABI
          , std::ptrdiff_t... I
          >
  EVE_FORCEINLINE auto gather_high_(EVE_SUPPORTS(sse2_), wide<T,N,ABI> v, pattern_t<I...> p) noexcept
  {
    constexpr auto cd = cardinal_v<wide<T,N,ABI>>;
    constexpr auto sz = pattern_t<I...>::size(cd);
    using   that_t    = as_wide_t<wide<T,N,ABI>,fixed<sz>>;

    constexpr pattern_t<I...> q = {};
    constexpr auto c  = categorize<wide<T,N,ABI>>();

    // We're swizzling so much we aggregate the output
    if constexpr( has_aggregated_abi_v<that_t> )
    {
      return aggregate_swizzle(v,gather_high_n<N::value>);
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
        constexpr auto m = is_mov<sizeof...(I)/2,I...>;

        if constexpr(sz == 4)
        {
              if constexpr(m == regular_mov ) return bit_cast( o_t{_mm_movehl_ps(r,r)}, tgt_t{});
        else  if constexpr(m == half_mov0   ) return bit_cast( o_t{_mm_movehl_ps(r,i_t(0))}, tgt_t{});
        else  if constexpr(m == half_0mov   ) return bit_cast( o_t{_mm_movehl_ps(i_t(0),r)}, tgt_t{});
        }
        else
        {
          return basic_swizzle(v,q);
        }
      }
    }
    // Strict 64bits SSE register only
    else if constexpr(match(c,category::float64x2, category::int64x2, category::uint64x2) )
    {
      using i_t = as_floating_point_t<wide<T,N,ABI>>;
      using o_t = as_floating_point_t<that_t>;
      using tgt_t = as_<that_t>;
      auto const r = bit_cast(v, as_<i_t>() );

      constexpr auto m = is_mov<sizeof...(I)/2,I...>;

            if constexpr(m == regular_mov ) return bit_cast( o_t{_mm_unpackhi_pd(r,r)}, tgt_t{});
      else  if constexpr(m == half_mov0   ) return bit_cast( o_t{_mm_unpackhi_pd(r,i_t(0))}, tgt_t{});
      else  if constexpr(m == half_0mov   ) return bit_cast( o_t{_mm_unpackhi_pd(i_t(0),r)}, tgt_t{});
    }
    else
    {
      return gather_high_(EVE_RETARGET(cpu_),v,p);
    }
  }

  template< typename T, typename N, x86_abi ABI
          , std::ptrdiff_t... I
          >
  EVE_FORCEINLINE auto gather_high_(EVE_SUPPORTS(avx_), wide<T,N,ABI> v, pattern_t<I...> p) noexcept
  {
    constexpr auto cd = cardinal_v<wide<T,N,ABI>>;
    constexpr auto sz = pattern_t<I...>::size(cd);
    using   that_t    = as_wide_t<wide<T,N,ABI>,fixed<sz>>;

    constexpr pattern_t<I...> q = {};

    constexpr auto width_in   = cd*sizeof(T);
    constexpr auto width_out  = sz*sizeof(T);

    // We're swizzling so much we aggregate the output
    if constexpr( has_aggregated_abi_v<that_t> )
    {
      return aggregate_swizzle(v,gather_high_n<N::value>);
    }
    // 32bits SSE register only
    else if constexpr( width_in <= 16)
    {
      return gather_high_(EVE_RETARGET(sse2_),v,p);
    }
    else if constexpr( width_in == 32)
    {
      if constexpr(width_out == 32)
      {
        constexpr auto c  = categorize<wide<T,N,ABI>>();
        [[maybe_unused]] wide<T,N,ABI> z(0);

        constexpr auto m = is_mov<sizeof...(I)/2,I...>;

        if constexpr( c == category::float64x4 )
        {
                if constexpr(m == regular_mov) return that_t{_mm256_permute2f128_pd(v,v,0x11)};
          else  if constexpr(m == half_mov0  ) return that_t{_mm256_permute2f128_pd(v,z,0x31)};
          else  if constexpr(m == half_0mov  ) return that_t{_mm256_permute2f128_pd(z,v,0x31)};
        }
        // AVX double precision
        else if constexpr( c == category::float32x8 )
        {
                if constexpr(m == regular_mov) return that_t{_mm256_permute2f128_ps(v,v,0x11)};
          else  if constexpr(m == half_mov0  ) return that_t{_mm256_permute2f128_ps(v,z,0x31)};
          else  if constexpr(m == half_0mov  ) return that_t{_mm256_permute2f128_ps(z,v,0x31)};
        }
        else if constexpr( std::same_as<ABI,x86_256_> )
        {
                if constexpr(m == regular_mov) return that_t{_mm256_permute2f128_si256(v,v,0x11)};
          else  if constexpr(m == half_mov0  ) return that_t{_mm256_permute2f128_si256(v,z,0x31)};
          else  if constexpr(m == half_0mov  ) return that_t{_mm256_permute2f128_si256(z,v,0x31)};
        }
      }
      else
      {
        return gather_high_(EVE_RETARGET(cpu_),v,p);
      }
    }
    else
    {
      return gather_high_(EVE_RETARGET(cpu_),v,p);
    }
  }
}
