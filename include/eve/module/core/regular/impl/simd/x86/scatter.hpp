//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/convert.hpp>

namespace eve::detail
{
  template<typename T, typename N, typename Idx, typename Ptr, callable_options O>
  EVE_FORCEINLINE void
  scatter_(EVE_REQUIRES(avx512_), O const& opts, wide<T,N> const& v, Ptr ptr, Idx const& idx) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    using           mask_t  = rbr::result::fetch_t<condition_key,O>;
    constexpr auto  c       = categorize<wide<T, N>>();
    constexpr auto  ci      = categorize<Idx>();

    // Unsupported value types go back to emulation
    if      constexpr(sizeof(T) < 4)                    scatter_(EVE_TARGETS(cpu_), opts, v, ptr, idx);
    // Singular scatter goes  back to emulation
    if      constexpr(N::value == 1)                    scatter_(EVE_TARGETS(cpu_), opts, v, ptr, idx);
    // Small indexes are converted to int32
    else if constexpr(sizeof(element_type_t<Idx>) < 4)  scatter[opts](v, ptr, convert(idx, as<std::int32_t>{}));
    // Do we need to aggregate ?
    else if constexpr(has_aggregated_abi_v<wide<T,N>> || has_aggregated_abi_v<Idx>)
    {
      auto [lv,hv] = v.slice();
      auto [li,hi] = idx.slice();

      scatter[opts](lv,ptr,li);
      scatter[opts](hv,ptr,hi);
    }
    // Do we have a non-trivial condition ?
    else if constexpr(!std::same_as<mask_t,ignore_none_>)
    {
      // Use intrinsics
      if constexpr( mask_t::is_complete && !mask_t::is_inverted) return;
      else
      {
        // Use masked intrinsics
        [[maybe_unused]] auto m = expand_mask(opts[condition_key], as(idx)).storage().value;

        if      constexpr(match(ci, category::int64x8 , category::uint64x8 ))
        {
          if      constexpr(match(c, category::int64x8 , category::uint64x8 ))  _mm512_mask_i64scatter_epi64(ptr,m,idx,v,8);
          else if constexpr(c == category::float64x8  )                         _mm512_mask_i64scatter_pd   (ptr,m,idx,v,8);
          else if constexpr(match(c, category::int32x8 , category::uint32x8 ))  _mm512_mask_i64scatter_epi32(ptr,m,idx,v,4);
          else if constexpr(c == category::float32x8  )                         _mm512_mask_i64scatter_ps   (ptr,m,idx,v,4);
        }
        else if constexpr(match(ci, category::int64x4 , category::uint64x4 ))
        {
          if      constexpr(match(c, category::int64x4 , category::uint64x4 ))  _mm256_mask_i64scatter_epi64(ptr,m,idx,v,8);
          else if constexpr(c == category::float64x4  )                         _mm256_mask_i64scatter_pd   (ptr,m,idx,v,8);
          else if constexpr(match(c, category::int32x4 , category::uint32x4 ))  _mm256_mask_i64scatter_epi32(ptr,m,idx,v,4);
          else if constexpr(c == category::float32x4  )                         _mm256_mask_i64scatter_ps   (ptr,m,idx,v,4);
        }
        else if constexpr(match(ci, category::int64x2 , category::uint64x2 ) && N::value == 2)
        {
          if      constexpr(match(c, category::int64x2 , category::uint64x2 ))  _mm_mask_i64scatter_epi64(ptr,m,idx,v,8);
          else if constexpr(match(c, category::int32x4 , category::uint32x4 ))  _mm_mask_i64scatter_epi32(ptr,m,idx,v,4);
          else if constexpr(c == category::float64x2  )                         _mm_mask_i64scatter_pd   (ptr,m,idx,v,8);
          else if constexpr(c == category::float32x4  )                         _mm_mask_i64scatter_ps   (ptr,m,idx,v,4);
        }
        else if constexpr(match(ci, category::int32x16 , category::uint32x16 ))
        {
          // Other types are caught before via aggregation
          if      constexpr(match(c, category::int32x16 , category::uint32x16 ))  _mm512_mask_i32scatter_epi32(ptr,m,idx,v,4);
          else if constexpr(c == category::float32x16  )                          _mm512_mask_i32scatter_ps   (ptr,m,idx,v,4);
        }
        else if constexpr(match(ci, category::int32x8 , category::uint32x8 ))
        {
          if      constexpr(match(c, category::int64x8 , category::uint64x8 ))  _mm512_mask_i32scatter_epi64(ptr,m,idx,v,8);
          else if constexpr(match(c, category::int32x8 , category::uint32x8 ))  _mm256_mask_i32scatter_epi32(ptr,m,idx,v,4);
          else if constexpr(c == category::float64x8  )                         _mm512_mask_i32scatter_pd   (ptr,m,idx,v,8);
          else if constexpr(c == category::float32x8  )                         _mm256_mask_i32scatter_ps   (ptr,m,idx,v,4);
        }
        else if constexpr(match(ci, category::int32x4 , category::uint32x4 ) && N::value == 4)
        {
          if      constexpr(match(c, category::int64x4 , category::uint64x4 ))  _mm256_mask_i32scatter_epi64 (ptr,m,idx,v,8);
          else if constexpr(match(c, category::int32x4 , category::uint32x4 ))  _mm_mask_i32scatter_epi32    (ptr,m,idx,v,4);
          else if constexpr(c == category::float64x4  )                         _mm256_mask_i32scatter_pd    (ptr,m,idx,v,8);
          else if constexpr(c == category::float32x4  )                         _mm_mask_i32scatter_ps       (ptr,m,idx,v,4);
        }
        else if constexpr(match(ci, category::int32x4 , category::uint32x4 ) && N::value == 2)
        {
          if      constexpr(match(c, category::int64x2 , category::uint64x2 ))  _mm_mask_i32scatter_epi64 (ptr,m,idx,v,8);
          else if constexpr(c == category::float64x2  )                         _mm_mask_i32scatter_pd    (ptr,m,idx,v,8);
          else scatter_(EVE_TARGETS(cpu_), opts, v, ptr, idx);
        }
      }
    }
    else
    {
      if      constexpr(match(ci, category::int64x8 , category::uint64x8 ))
      {
        if      constexpr(match(c, category::int64x8 , category::uint64x8 ))  _mm512_i64scatter_epi64(ptr,idx,v,8);
        else if constexpr(c == category::float64x8  )                         _mm512_i64scatter_pd   (ptr,idx,v,8);
        else if constexpr(match(c, category::int32x8 , category::uint32x8 ))  _mm512_i64scatter_epi32(ptr,idx,v,4);
        else if constexpr(c == category::float32x8  )                         _mm512_i64scatter_ps   (ptr,idx,v,4);
      }
      else if constexpr(match(ci, category::int64x4 , category::uint64x4 ))
      {
        if      constexpr(match(c, category::int64x4 , category::uint64x4 ))  _mm256_i64scatter_epi64(ptr,idx,v,8);
        else if constexpr(c == category::float64x4  )                         _mm256_i64scatter_pd   (ptr,idx,v,8);
        else if constexpr(match(c, category::int32x4 , category::uint32x4 ))  _mm256_i64scatter_epi32(ptr,idx,v,4);
        else if constexpr(c == category::float32x4  )                         _mm256_i64scatter_ps   (ptr,idx,v,4);
      }
      else if constexpr(match(ci, category::int64x2 , category::uint64x2 ) && N::value == 2)
      {
        if      constexpr(match(c, category::int64x2 , category::uint64x2 ))  _mm_i64scatter_epi64(ptr,idx,v,8);
        else if constexpr(match(c, category::int32x4 , category::uint32x4 ))  _mm_i64scatter_epi32(ptr,idx,v,4);
        else if constexpr(c == category::float64x2  )                         _mm_i64scatter_pd   (ptr,idx,v,8);
        else if constexpr(c == category::float32x4  )                         _mm_i64scatter_ps   (ptr,idx,v,4);
      }
      else if constexpr(match(ci, category::int32x16 , category::uint32x16 ))
      {
        // Other types are caught before via aggregation
        if      constexpr(match(c, category::int32x16 , category::uint32x16 ))  _mm512_i32scatter_epi32(ptr,idx,v,4);
        else if constexpr(c == category::float32x16  )                          _mm512_i32scatter_ps   (ptr,idx,v,4);
      }
      else if constexpr(match(ci, category::int32x8 , category::uint32x8 ))
      {
        if      constexpr(match(c, category::int64x8 , category::uint64x8 ))  _mm512_i32scatter_epi64(ptr,idx,v,8);
        else if constexpr(match(c, category::int32x8 , category::uint32x8 ))  _mm256_i32scatter_epi32(ptr,idx,v,4);
        else if constexpr(c == category::float64x8  )                         _mm512_i32scatter_pd   (ptr,idx,v,8);
        else if constexpr(c == category::float32x8  )                         _mm256_i32scatter_ps   (ptr,idx,v,4);
      }
      else if constexpr(match(ci, category::int32x4 , category::uint32x4 ) && N::value == 4)
      {
        if      constexpr(match(c, category::int64x4 , category::uint64x4 ))  _mm256_i32scatter_epi64 (ptr,idx,v,8);
        else if constexpr(match(c, category::int32x4 , category::uint32x4 ))  _mm_i32scatter_epi32    (ptr,idx,v,4);
        else if constexpr(c == category::float64x4  )                         _mm256_i32scatter_pd    (ptr,idx,v,8);
        else if constexpr(c == category::float32x4  )                         _mm_i32scatter_ps       (ptr,idx,v,4);
      }
      else if constexpr(match(ci, category::int32x4 , category::uint32x4 ) && N::value == 2)
      {
        if      constexpr(match(c, category::int64x2 , category::uint64x2 ))  _mm_i32scatter_epi64 (ptr,idx,v,8);
        else if constexpr(c == category::float64x2  )                         _mm_i32scatter_pd    (ptr,idx,v,8);
        else scatter_(EVE_TARGETS(cpu_), opts, v, ptr, idx);
      }
    }
  }
}
