//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/operators.hpp>
#include <eve/traits/common_compatible.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/combine.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/promoted.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/pattern.hpp>
#include <concepts>
#include <bit>

namespace eve::detail
{
  template<unsigned_scalar_value T, typename N>
  EVE_FORCEINLINE
  auto mul_(EVE_SUPPORTS(sse2_), promoted_type const &, wide<T, N> a, wide<T, N> b) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    using in_t = wide<T, N>;
    using ou_t = wide<upgrade_t<T>, N>;
    constexpr auto c = categorize<in_t>();
    if constexpr(c == category::uint32x16 && current_api >= avx512)
    {
      using tmp_t = wide < upgrade_t<T>, fixed<8>>;
      constexpr auto slo = eve::fix_pattern<16>([](auto i, auto) { return i&1 ?  -1: i/2; });
      constexpr auto shi = eve::fix_pattern<16>([](auto i, auto) { return i&1 ?  -1: 8+i/2; });

      tmp_t alo = std::bit_cast<tmp_t>(a[slo]);
      tmp_t blo = std::bit_cast<tmp_t>(b[slo]);
      tmp_t lo(_mm512_mul_epu32(alo, blo));
      tmp_t ahi = std::bit_cast<tmp_t>(a[shi]);
      tmp_t bhi = std::bit_cast<tmp_t>(b[shi]);
      tmp_t hi(_mm512_mul_epu32(ahi, bhi));
      return eve::combine(lo, hi);
    }
    else if constexpr(c == category::uint32x8 && current_api >= avx2)
    {
      using tmp_t = wide < upgrade_t<T>, fixed<4>>;
      constexpr auto slo = eve::fix_pattern<8>([](auto i, auto) { return i&1 ?  -1 : i/2; });
      constexpr auto shi = eve::fix_pattern<8>([](auto i, auto) { return i&1 ?  -1 : 4+i/2; });
      tmp_t alo = std::bit_cast<tmp_t>(a[slo]);
      tmp_t blo = std::bit_cast<tmp_t>(b[slo]);
      tmp_t lo(_mm256_mul_epu32(alo, blo));
      tmp_t ahi = std::bit_cast<tmp_t>(a[shi]);
      tmp_t bhi = std::bit_cast<tmp_t>(b[shi]);
      tmp_t hi(_mm256_mul_epu32(ahi, bhi));
      return eve::combine(lo, hi);
    }
    else if constexpr(c == category::uint32x4 )
    {
      if constexpr(N::value == 4)
      {
        if constexpr(current_api >= avx2 )
        {
          auto a64 = convert(a, as<uint64_t>());
          auto b64 = convert(b, as<uint64_t>());
          const __m256i ret = _mm256_mul_epu32(a64, b64);
          return ou_t(ret);
        }
        else
        {
          auto mul0 = in_t(_mm_mul_epu32(a, b));
          auto mul1 = in_t(_mm_mul_epu32(a[pattern<1,1,3,3>],b[pattern<1,1,3,3>]));
          in_t lo   = in_t(_mm_unpacklo_epi64(mul0, mul1));
          in_t hi   = in_t(_mm_unpackhi_epi64(mul0, mul1));
          auto res = eve::combine(lo, hi);
          return std::bit_cast<ou_t>(res);
        }
      }
      else if constexpr(N::value == 2)
      {
        using tin_t = wide<T, fixed<4>>;
        tin_t ta(a.storage());
        ta = ta[pattern < 0, -1, 1, -1>];
        tin_t tb(b.storage());
        tb = tb[pattern < 0, -1, 1, -1>];
        return ou_t(_mm_mul_epu32(ta, tb));
      }
      else
      {
        return mul_(EVE_RETARGET(cpu_),promoted_type(), a, b);
      }
    }
    else if constexpr(c == category::uint16x32 )
    {
      in_t abh(_mm512_mulhi_epu16(a, b));
      in_t abl(_mm512_mullo_epi16(a, b));
      constexpr auto s = eve::fix_pattern<N::value*2>([](auto i, auto) { return i&1 ?  N::value+i/2 :i/2; });
      auto res = eve::combine(abl, abh)[s];
      return std::bit_cast<ou_t>(res);
    }
    else  if constexpr(c == category::uint16x16 && current_api >= avx2 )
    {
      in_t abh(_mm256_mulhi_epu16(a, b));
      in_t abl(_mm256_mullo_epi16(a, b));
      auto res = eve::combine(abl, abh);
      constexpr auto s = eve::fix_pattern<N::value*2>([](auto i, auto) { return i&1 ?  N::value+i/2 :i/2; });
      auto r = res[s];
      return std::bit_cast<ou_t>(r);
    }
    else  if constexpr(c == category::uint16x8)
    {
      if constexpr(N::value !=  1)
      {
        in_t abh(_mm_mulhi_epu16(a, b));
        in_t abl(mul(a, b));
        auto res = eve::combine(abl, abh);
        constexpr auto s = eve::fix_pattern<N::value*2>([](auto i, auto) { return i&1 ?  N::value+i/2 :i/2; });
        auto r = res[s];
        return std::bit_cast<ou_t>(r);
      }
      else
      {
        return  mul_(EVE_RETARGET(cpu_),promoted_type(), a, b);
      }
    }
    else
    {
      return  mul_(EVE_RETARGET(cpu_),promoted_type(), a, b);
    }
  }

  template<signed_integral_scalar_value T, typename N>
  EVE_FORCEINLINE
  auto mul_(EVE_SUPPORTS(sse2_), promoted_type const &, wide<T, N> a, wide<T, N> b) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    using in_t = wide<T, N>;
    using ou_t = wide<upgrade_t<T>, N>;
    constexpr auto c = categorize<in_t>();
    if constexpr(c == category::int32x16 && current_api >= avx512)
    {
      using tmp_t = wide < upgrade_t<T>, fixed<8>>;
      constexpr auto slo = eve::fix_pattern<16>([](auto i, auto) { return i&1 ?  -1: i/2; });
      constexpr auto shi = eve::fix_pattern<16>([](auto i, auto) { return i&1 ?  -1: 8+i/2; });

      tmp_t alo = std::bit_cast<tmp_t>(a[slo]);
      tmp_t blo = std::bit_cast<tmp_t>(b[slo]);
      tmp_t lo(_mm512_mul_epi32(alo, blo));
      tmp_t ahi = std::bit_cast<tmp_t>(a[shi]);
      tmp_t bhi = std::bit_cast<tmp_t>(b[shi]);
      tmp_t hi(_mm512_mul_epi32(ahi, bhi));
      return eve::combine(lo, hi);
    }
    else if constexpr(c == category::int32x8 && current_api >= avx2)
    {
      using tmp_t = wide < upgrade_t<T>, fixed<4>>;
      constexpr auto slo = eve::fix_pattern<8>([](auto i, auto) { return i&1 ?  -1 : i/2; });
      constexpr auto shi = eve::fix_pattern<8>([](auto i, auto) { return i&1 ?  -1 : 4+i/2; });
      tmp_t alo = std::bit_cast<tmp_t>(a[slo]);
      tmp_t blo = std::bit_cast<tmp_t>(b[slo]);
      tmp_t lo(_mm256_mul_epi32(alo, blo));
      tmp_t ahi = std::bit_cast<tmp_t>(a[shi]);
      tmp_t bhi = std::bit_cast<tmp_t>(b[shi]);
      tmp_t hi(_mm256_mul_epi32(ahi, bhi));
      return eve::combine(lo, hi);
    }
    else if constexpr(c == category::int32x4 )
    {
      if constexpr(N::value == 4)
      {
        if constexpr(current_api >= avx2 )
        {
          auto a64 = convert(a, as<int64_t>());
          auto b64 = convert(b, as<int64_t>());
          const __m256i ret = _mm256_mul_epi32(a64, b64);
          return ou_t(ret);
        }
        else if constexpr(current_api >= sse4_1 )
        {
          auto mul0 = in_t(_mm_mul_epi32(a, b));
          auto mul1 = in_t(_mm_mul_epi32(a[pattern<1,1,3,3>],b[pattern<1,1,3,3>]));
          in_t lo   = in_t(_mm_unpacklo_epi64(mul0, mul1));
          in_t hi   = in_t(_mm_unpackhi_epi64(mul0, mul1));
          auto res = eve::combine(lo, hi);
          return std::bit_cast<ou_t>(res);
        }
        else
        {
          return mul_(EVE_RETARGET(cpu_),promoted_type(), a, b);
        }
      }
      else if constexpr(N::value == 2 && current_api >= sse4_1 )
      {
        using tin_t = wide<T, fixed<4>>;
        tin_t ta(a.storage());
        ta = ta[pattern < 0, -1, 1, -1>];
        tin_t tb(b.storage());
        tb = tb[pattern < 0, -1, 1, -1>];
        return ou_t(_mm_mul_epi32(ta, tb));
      }
      else
      {
        return mul_(EVE_RETARGET(cpu_),promoted_type(), a, b);
      }
    }
    else if constexpr(c == category::int16x32 )
    {
      in_t abh(_mm512_mulhi_epi16(a, b));
      in_t abl(_mm512_mullo_epi16(a, b));
      constexpr auto s = eve::fix_pattern<N::value*2>([](auto i, auto) { return i&1 ?  N::value+i/2 :i/2; });
      auto res = eve::combine(abl, abh)[s];
      return std::bit_cast<ou_t>(res);
    }
    else  if constexpr(c == category::int16x16 && current_api >= avx2 )
    {
      in_t abh(_mm256_mulhi_epi16(a, b));
      in_t abl(_mm256_mullo_epi16(a, b));
      auto res = eve::combine(abl, abh);
      constexpr auto s = eve::fix_pattern<N::value*2>([](auto i, auto) { return i&1 ?  N::value+i/2 :i/2; });
      auto r = res[s];
      return std::bit_cast<ou_t>(r);
    }
    else if constexpr(c == category::int16x8  && N::value != 1)
    {

      in_t abh(_mm_mulhi_epi16(a, b));
      in_t abl(mul(a, b));
      auto res = eve::combine(abl, abh);
      constexpr auto s = eve::fix_pattern<N::value*2>([](auto i, auto) { return i&1 ?  N::value+i/2 :i/2; });
      auto r = res[s];
      return std::bit_cast<ou_t>(r);
    }
    else
    {
      return  mul_(EVE_RETARGET(cpu_),promoted_type(), a, b);
    }
  }

}
