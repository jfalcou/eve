//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/memory.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/function/to_logical.hpp>
#include <eve/detail/function/simd/common/load.hpp>

namespace eve::detail
{
  //================================================================================================
  // Regular loads
  //================================================================================================
  template<typename T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE wide<T, N> load_impl(Ptr p, as<wide<T, N>> tgt) noexcept
    requires (dereference_as<T, Ptr>::value && x86_abi<abi_t<T, N>>)
  {
    constexpr auto cat = categorize<wide<T, N>>();
    constexpr bool isfull512 = N::value*sizeof(T) == x86_512_::bytes;
    constexpr bool isfull256 = N::value*sizeof(T) == x86_256_::bytes;
    constexpr bool isfull128 = N::value*sizeof(T) == x86_128_::bytes;

    if constexpr( !std::is_pointer_v<Ptr> )
    {
      if constexpr( isfull512 )
      {
              if constexpr( cat == category::float64x8 )   return _mm512_load_pd(p.get());
        else  if constexpr( cat == category::float32x16 )  return _mm512_load_ps(p.get());
        else return _mm512_load_si512((__m512i *)p.get());
      }
      else if constexpr( isfull256 )
      {
              if constexpr( cat == category::float64x4 )  return _mm256_load_pd(p.get());
        else  if constexpr( cat == category::float32x8 )  return _mm256_load_ps(p.get());
        else return _mm256_load_si256((__m256i *)p.get());
      }
      else if constexpr( isfull128 )
      {
              if constexpr( cat == category::float64x2 )  return _mm_load_pd(p.get());
        else  if constexpr( cat == category::float32x4 )  return _mm_load_ps(p.get());
        else  return _mm_load_si128((__m128i *)p.get());
      }
      else
      {
        typename wide<T, N>::storage_type that{};
        std::memcpy(&that, p.get(), N::value * sizeof(T));
        return that;
      }
    }
    else
    {
      if constexpr( isfull512 )
      {
              if constexpr( cat == category::float64x8 )   return _mm512_loadu_pd(p);
        else  if constexpr( cat == category::float32x16 )  return _mm512_loadu_ps(p);
        else return _mm512_loadu_si512((__m512i *)p);
      }
      else if constexpr( isfull256 )
      {
              if constexpr( cat == category::float64x4 )  return _mm256_loadu_pd(p);
        else  if constexpr( cat == category::float32x8 )  return _mm256_loadu_ps(p);
        else return _mm256_loadu_si256((__m256i *)p);
      }
      else if constexpr( isfull128 )
      {
              if constexpr( cat == category::float64x2 )  return _mm_loadu_pd(p);
        else  if constexpr( cat == category::float32x4 )  return _mm_loadu_ps(p);
        else  return _mm_loadu_si128((__m128i *)p);
      }
      else
      {
        typename wide<T, N>::storage_type that{};
        std::memcpy(&that, p, N::value * sizeof(T));
        return that;
      }
    }
  }

  //================================================================================================
  // logical loads require some specific setup
  //================================================================================================
  // template<callable_options O, typename T, typename N, typename Ptr>
  // EVE_FORCEINLINE logical<wide<T, N>>
  // load_( EVE_REQUIRES(cpu_), O const& opts, Ptr p, as<logical<wide<T, N>>> tgt) noexcept
  //   requires (dereference_as<logical<T>, Ptr>::value && x86_abi<abi_t<T, N>> && load_safe_no_cx<O>)
  // {
  //   auto block = [&]() -> wide<T, N>
  //   {
  //     return load(ptr_cast<T const>(p), as<wide<T, N>>{});
  //   }();

  //   if constexpr( current_api >= avx512 ) return to_logical(block);
  //   else                                  return bit_cast(block, tgt);
  // }

  // template<callable_options O, typename Iterator, typename T, typename N>
  // EVE_FORCEINLINE logical<wide<T, N>>
  // load_(EVE_REQUIRES(cpu_), O const& opts, Iterator b, Iterator e, as<logical<wide<T, N>>> tgt) noexcept
  //   requires (x86_abi<abi_t<T, N>> && load_safe_no_cx<O>)
  // {
  //   auto block = [&]() -> wide<T, N>
  //   {
  //     return load(b, e, as<wide<T, N>>{});
  //   }();

  //   return to_logical(block);
  // }

  //================================================================================================
  // Conditional loads
  //================================================================================================
  template<relative_conditional_expr C, typename Ptr, typename Wide>
  EVE_FORCEINLINE Wide load_impl(C const& cond, Ptr p, as<Wide> tgt) noexcept
    requires (x86_abi<typename Wide::abi_type> && simd_compatible_ptr<Ptr, Wide> && std::is_pointer_v<Ptr>)
  {
    using b_t = std::remove_cvref_t<decltype(*p)>;
    using r_t = Wide;

    if constexpr( is_logical_v<b_t> )
    {
      auto const alt = [&]()
      {
        if constexpr( C::has_alternative ) return cond.rebase(cond.alternative.mask());
        else return cond;
      };

      using a_t        = as_arithmetic_t<b_t>;
      auto const block = [&](auto local_cond)
      {
        if constexpr( !std::is_pointer_v<Ptr> )
        {
          using ptr_t = typename Ptr::template rebind<a_t const>;
          return load[local_cond](ptr_t((a_t const *)(p.get())), as<as_arithmetic_t<Wide>> {});
        }
        else { return load[local_cond]((a_t const *)(p), as<as_arithmetic_t<Wide>> {}); }
      }(alt());

      if constexpr( current_api >= avx512 ) return to_logical(block);
      else return bit_cast(block, as<r_t> {});
    }
    // Aligned addressed don't need a masked load.
    else if constexpr( !std::is_pointer_v<Ptr> ) return load.behavior(cpu_{}, opts, p, tgt);
    else if constexpr( C::is_complete ) return load.behavior(cpu_{}, opts, p, tgt);
    else if constexpr( current_api >= avx512 )
      {
      r_t  that;
      auto src = [&](auto const& vs)
      {
        if constexpr( C::has_alternative ) return r_t {cond.alternative};
        else return vs;
      };
      auto           mask = cond.mask(as<r_t> {}).storage().value;
      constexpr auto c    = categorize<r_t>();

      if constexpr( c == category::float64x8 ) return _mm512_mask_loadu_pd(src(that), mask, p);
      else if constexpr( c == category::float64x4 ) return _mm256_mask_loadu_pd(src(that), mask, p);
      else if constexpr( c == category::float64x2 ) return _mm_mask_loadu_pd(src(that), mask, p);
      else if constexpr( c == category::float32x16 ) return _mm512_mask_loadu_ps(src(that), mask, p);
      else if constexpr( c == category::float32x8 ) return _mm256_mask_loadu_ps(src(that), mask, p);
      else if constexpr( c == category::float32x4 ) return _mm_mask_loadu_ps(src(that), mask, p);
      else if constexpr( c == category::int64x8 ) return _mm512_mask_loadu_epi64(src(that), mask, p);
      else if constexpr( c == category::int64x4 ) return _mm256_mask_loadu_epi64(src(that), mask, p);
      else if constexpr( c == category::int64x2 ) return _mm_mask_loadu_epi64(src(that), mask, p);
      else if constexpr( c == category::uint64x8 ) return _mm512_mask_loadu_epi64(src(that), mask, p);
      else if constexpr( c == category::uint64x4 ) return _mm256_mask_loadu_epi64(src(that), mask, p);
      else if constexpr( c == category::uint64x2 ) return _mm_mask_loadu_epi64(src(that), mask, p);
      else if constexpr( c == category::int32x16 ) return _mm512_mask_loadu_epi32(src(that), mask, p);
      else if constexpr( c == category::int32x8 ) return _mm256_mask_loadu_epi32(src(that), mask, p);
      else if constexpr( c == category::int32x4 ) return _mm_mask_loadu_epi32(src(that), mask, p);
      else if constexpr( c == category::uint32x16 )
        return _mm512_mask_loadu_epi32(src(that), mask, p);
      else if constexpr( c == category::uint32x8 ) return _mm256_mask_loadu_epi32(src(that), mask, p);
      else if constexpr( c == category::uint32x4 ) return _mm_mask_loadu_epi32(src(that), mask, p);
      else if constexpr( c == category::int16x32 ) return _mm512_mask_loadu_epi16(src(that), mask, p);
      else if constexpr( c == category::int16x16 ) return _mm256_mask_loadu_epi16(src(that), mask, p);
      else if constexpr( c == category::int16x8 ) return _mm_mask_loadu_epi16(src(that), mask, p);
      else if constexpr( c == category::uint16x32 )
        return _mm512_mask_loadu_epi16(src(that), mask, p);
      else if constexpr( c == category::uint16x16 )
        return _mm256_mask_loadu_epi16(src(that), mask, p);
      else if constexpr( c == category::uint16x8 ) return _mm_mask_loadu_epi16(src(that), mask, p);
      else if constexpr( c == category::int8x64 ) return _mm512_mask_loadu_epi8(src(that), mask, p);
      else if constexpr( c == category::int8x32 ) return _mm256_mask_loadu_epi8(src(that), mask, p);
      else if constexpr( c == category::int8x16 ) return _mm_mask_loadu_epi8(src(that), mask, p);
      else if constexpr( c == category::uint8x64 ) return _mm512_mask_loadu_epi8(src(that), mask, p);
      else if constexpr( c == category::uint8x32 ) return _mm256_mask_loadu_epi8(src(that), mask, p);
      else if constexpr( c == category::uint8x16 ) return _mm_mask_loadu_epi8(src(that), mask, p);
    }
    else if constexpr( current_api >= avx )
    {
      r_t            that;
      constexpr auto c    = categorize<r_t>();
      auto           mask = cond.mask(as<r_t> {}).bits();

      if constexpr( c == category::float64x4 ) that = _mm256_maskload_pd(p, mask);
      else if constexpr( c == category::float64x2 ) that = _mm_maskload_pd(p, mask);
      else if constexpr( c == category::float32x8 ) that = _mm256_maskload_ps(p, mask);
      else if constexpr( c == category::float32x4 ) that = _mm_maskload_ps(p, mask);
      else if constexpr( current_api >= avx2 )
      {
        if constexpr( c == category::int64x4 )
          that = _mm256_maskload_epi64((long long const int *)p, mask);
        if constexpr( c == category::uint64x4 )
          that = _mm256_maskload_epi64((long long const int *)p, mask);
        else if constexpr( c == category::int64x2 )
          that = _mm_maskload_epi64((long long const int *)p, mask);
        else if constexpr( c == category::uint64x2 )
          that = _mm_maskload_epi64((long long const int *)p, mask);
        else if constexpr( c == category::int32x8 )
          that = _mm256_maskload_epi32((std::int32_t const *)p, mask);
        else if constexpr( c == category::uint32x8 )
          that = _mm256_maskload_epi32((std::int32_t const *)p, mask);
        else if constexpr( c == category::int32x4 )
          that = _mm_maskload_epi32((std::int32_t const *)p, mask);
        else if constexpr( c == category::uint32x4 )
          that = _mm_maskload_epi32((std::int32_t const *)p, mask);
        else return load.behavior(cpu_{}, opts, p, tgt);
      }
      else return load.behavior(cpu_{}, opts, p, tgt);

      if constexpr( C::has_alternative )
      {
        constexpr auto blender = [](auto a, auto b, auto m)
        {
          auto mm = typename r_t::storage_type(m.storage());
          if constexpr( c == category::float64x4 ) return _mm256_blendv_pd(a, b, mm);
          else if constexpr( c == category::float32x8 ) return _mm256_blendv_ps(a, b, mm);
          else if constexpr( c == category::float64x2 ) return _mm_blendv_pd(a, b, mm);
          else if constexpr( c == category::float32x4 ) return _mm_blendv_ps(a, b, mm);
          else if constexpr( sizeof(a) == 32 ) return _mm256_blendv_epi8(a, b, mm);
          else if constexpr( sizeof(a) == 16 ) return _mm_blendv_epi8(a, b, mm);
        };

        r_t alt(cond.alternative);
        that = blender(alt, that, mask);
      }

      return that;
    }
    else return load.behavior(cpu_{}, opts, p, tgt);
  }
}
