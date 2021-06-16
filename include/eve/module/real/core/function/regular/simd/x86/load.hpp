//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/memory.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/function/to_logical.hpp>

namespace eve::detail
{
  //================================================================================================
  // Conditional loads
  //================================================================================================
  template<relative_conditional_expr C, typename Ptr, typename Pack>
  EVE_FORCEINLINE Pack load_( EVE_SUPPORTS(sse2_), C const &cond, safe_type const& s
                            , eve::as_<Pack> const& tgt
                            , Ptr p
                            ) noexcept
  requires simd_compatible_ptr<Ptr, Pack> && x86_abi<typename Pack::abi_type>
  {
    using b_t   = std::remove_cvref_t<decltype(*p)>;
    using r_t   = Pack;

    if constexpr( is_logical_v<b_t> )
    {
      auto const alt = [&]()
      {
        if constexpr( C::has_alternative )  return cond.rebase(cond.alternative.mask());
        else                                return cond;
      };

      using a_t = as_arithmetic_t<b_t>;
      auto const block = [&](auto local_cond)
      {
        if constexpr( !std::is_pointer_v<Ptr> )
        {
          using ptr_t = typename Ptr::template rebind<a_t const>;
          return load(local_cond,s, as_<as_arithmetic_t<Pack>>{}, ptr_t((a_t const*)(p.get())));
        }
        else
        {
          return load(local_cond,s, as_<as_arithmetic_t<Pack>>{}, (a_t const*)(p));
        }
      }(alt());

      if constexpr( current_api >= avx512 ) return to_logical(block);
      else                                  return bit_cast(block, as_<r_t>{});
    }
    // Hack until a proper FIX-#572
    else if constexpr ( has_aggregated_abi_v<r_t> ) return load_(EVE_RETARGET(cpu_), cond, s, tgt, p);
    // Aligned addressed don't need a masked load.
    else if constexpr ( !std::is_pointer_v<Ptr> )   return load_(EVE_RETARGET(cpu_), cond, s, tgt, p);
    else if constexpr ( C::is_complete )            return load_(EVE_RETARGET(cpu_), cond, s, tgt, p);
    else if constexpr( current_api >= avx512 )
    {
      r_t that;

      auto src = [&](auto const& s)
      {
        if constexpr( C::has_alternative )  return r_t{cond.alternative};
        else                                return s;
      };

      auto mask = cond.mask( as_<r_t>{} ).storage().value;
      constexpr auto c = categorize<r_t>();

            if constexpr( c == category::float64x8 ) return _mm512_mask_loadu_pd(src(that),mask,p);
      else  if constexpr( c == category::float64x4 ) return _mm256_mask_loadu_pd(src(that),mask,p);
      else  if constexpr( c == category::float64x2 ) return _mm_mask_loadu_pd(src(that),mask,p);
      else  if constexpr( c == category::float32x16) return _mm512_mask_loadu_ps(src(that),mask,p);
      else  if constexpr( c == category::float32x8 ) return _mm256_mask_loadu_ps(src(that),mask,p);
      else  if constexpr( c == category::float32x4 ) return _mm_mask_loadu_ps(src(that),mask,p);
      else  if constexpr( c == category::int64x8   ) return _mm512_mask_loadu_epi64(src(that),mask,p);
      else  if constexpr( c == category::int64x4   ) return _mm256_mask_loadu_epi64(src(that),mask,p);
      else  if constexpr( c == category::int64x2   ) return _mm_mask_loadu_epi64(src(that),mask,p);
      else  if constexpr( c == category::uint64x8  ) return _mm512_mask_loadu_epi64(src(that),mask,p);
      else  if constexpr( c == category::uint64x4  ) return _mm256_mask_loadu_epi64(src(that),mask,p);
      else  if constexpr( c == category::uint64x2  ) return _mm_mask_loadu_epi64(src(that),mask,p);
      else  if constexpr( c == category::int32x16  ) return _mm512_mask_loadu_epi32(src(that),mask,p);
      else  if constexpr( c == category::int32x8   ) return _mm256_mask_loadu_epi32(src(that),mask,p);
      else  if constexpr( c == category::int32x4   ) return _mm_mask_loadu_epi32(src(that),mask,p);
      else  if constexpr( c == category::uint32x16 ) return _mm512_mask_loadu_epi32(src(that),mask,p);
      else  if constexpr( c == category::uint32x8  ) return _mm256_mask_loadu_epi32(src(that),mask,p);
      else  if constexpr( c == category::uint32x4  ) return _mm_mask_loadu_epi32(src(that),mask,p);
      else  if constexpr( c == category::int16x32  ) return _mm512_mask_loadu_epi16(src(that),mask,p);
      else  if constexpr( c == category::int16x16  ) return _mm256_mask_loadu_epi16(src(that),mask,p);
      else  if constexpr( c == category::int16x8   ) return _mm_mask_loadu_epi16(src(that),mask,p);
      else  if constexpr( c == category::uint16x32 ) return _mm512_mask_loadu_epi16(src(that),mask,p);
      else  if constexpr( c == category::uint16x16 ) return _mm256_mask_loadu_epi16(src(that),mask,p);
      else  if constexpr( c == category::uint16x8  ) return _mm_mask_loadu_epi16(src(that),mask,p);
      else  if constexpr( c == category::int8x64   ) return _mm512_mask_loadu_epi8(src(that),mask,p);
      else  if constexpr( c == category::int8x32   ) return _mm256_mask_loadu_epi8(src(that),mask,p);
      else  if constexpr( c == category::int8x16   ) return _mm_mask_loadu_epi8(src(that),mask,p);
      else  if constexpr( c == category::uint8x64  ) return _mm512_mask_loadu_epi8(src(that),mask,p);
      else  if constexpr( c == category::uint8x32  ) return _mm256_mask_loadu_epi8(src(that),mask,p);
      else  if constexpr( c == category::uint8x16  ) return _mm_mask_loadu_epi8(src(that),mask,p);
    }
    else if constexpr( current_api >= avx )
    {
      r_t that;
      constexpr auto c = categorize<r_t>();
      auto mask = cond.mask( as_<r_t>{} ).bits();

            if constexpr( c == category::float64x4 )  that = _mm256_maskload_pd (p,mask);
      else  if constexpr( c == category::float64x2 )  that = _mm_maskload_pd    (p,mask);
      else  if constexpr( c == category::float32x8 )  that = _mm256_maskload_ps (p,mask);
      else  if constexpr( c == category::float32x4 )  that = _mm_maskload_ps    (p,mask);
      else  if constexpr( current_api >= avx2 )
      {
              if constexpr( c == category::int64x4 ) that = _mm256_maskload_epi64 ((long long const int*)p,mask);
              if constexpr( c == category::uint64x4) that = _mm256_maskload_epi64 ((long long const int*)p,mask);
        else  if constexpr( c == category::int64x2 ) that = _mm_maskload_epi64    ((long long const int*)p,mask);
        else  if constexpr( c == category::uint64x2) that = _mm_maskload_epi64    ((long long const int*)p,mask);
        else  if constexpr( c == category::int32x8 ) that = _mm256_maskload_epi32 ((std::int32_t const*)p,mask);
        else  if constexpr( c == category::uint32x8) that = _mm256_maskload_epi32 ((std::int32_t const*)p,mask);
        else  if constexpr( c == category::int32x4 ) that = _mm_maskload_epi32    ((std::int32_t const*)p,mask);
        else  if constexpr( c == category::uint32x4) that = _mm_maskload_epi32    ((std::int32_t const*)p,mask);
        else                                         return load_(EVE_RETARGET(cpu_), cond, s, tgt, p);
      }
      else return load_(EVE_RETARGET(cpu_), cond, s, tgt, p);

      if constexpr( C::has_alternative )
      {
        constexpr auto blender = [](auto a, auto b, auto m)
        {
          auto mm = typename r_t::storage_type(m.storage());
                if constexpr( c == category::float64x4 )  return _mm256_blendv_pd(a,b,mm);
          else  if constexpr( c == category::float32x8 )  return _mm256_blendv_ps(a,b,mm);
          else  if constexpr( c == category::float64x2 )  return _mm_blendv_pd(a,b,mm);
          else  if constexpr( c == category::float32x4 )  return _mm_blendv_ps(a,b,mm);
          else  if constexpr( sizeof(a) == 32)            return _mm256_blendv_epi8(a,b,mm);
          else  if constexpr( sizeof(a) == 16)            return _mm_blendv_epi8(a,b,mm);
        };

        r_t alt(cond.alternative);
        that = blender(alt,that,mask);
      }

      return that;
  }
  else return load_(EVE_RETARGET(cpu_), cond, s, tgt, p);
}

}
