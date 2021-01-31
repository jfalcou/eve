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
  template<relative_conditional_expr C, typename Ptr, typename Cardinal>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(sse2_), C const &cond, Ptr p, Cardinal const&) noexcept
                  -> as_wide_t<std::remove_cvref_t<decltype(*p)>, typename Cardinal::type>
  requires( simd_compatible_ptr<Ptr, as_wide_t< std::remove_cvref_t<decltype(*p)>
                                              , typename Cardinal::type>
                                              >
          )
  {
    using b_t   = std::remove_cvref_t<decltype(*p)>;
    using r_t   = as_wide_t<b_t, typename Cardinal::type>;
    using abi_t = typename r_t::abi_type;

    if constexpr( is_logical_v<b_t> )
    {
      using a_t = as_arithmetic_t<b_t>;
      auto block = [&]() -> wide<a_t, typename Cardinal::type>
      {
        if constexpr( !std::is_pointer_v<Ptr> )
        {
          using ptr_t = typename Ptr::template rebind<a_t const>;
          return load_(EVE_RETARGET(sse2_), cond, ptr_t((a_t const*)(p.get())), Cardinal{});
        }
        else
        {
          return load_(EVE_RETARGET(sse2_), cond, (a_t const*)(p), Cardinal{});
        }
      }();

      if constexpr( current_api >= avx512 ) return to_logical(block).storage();
      else                                  return bit_cast(block, as_<r_t>{});
    }
    else if constexpr( !abi_t::is_wide_logical )
    {
      if constexpr( C::is_complete )
      {
        if constexpr(C::is_inverted)  { return eve::load(p, Cardinal{});  }
        else
        {
          if constexpr(C::has_alternative)  return r_t{cond.alternative};
          else                              return r_t{};
        }
      }
      else
      {
        r_t that;

        auto src = [&](auto const& s)
        {
          if constexpr( C::has_alternative )  return r_t{cond.alternative};
          else                                return s;
        };

        auto mask = cond.bitmap( as_<r_t>{} );
        constexpr auto c = categorize<r_t>();

        if constexpr( !std::is_pointer_v<Ptr> )
        {
                if constexpr( c == category::float64x8 ) return _mm512_mask_load_pd(src(that),mask,p.get());
          else  if constexpr( c == category::float64x4 ) return _mm256_mask_load_pd(src(that),mask,p.get());
          else  if constexpr( c == category::float64x2 ) return _mm_mask_load_pd(src(that),mask,p.get());
          else  if constexpr( c == category::float32x16) return _mm512_mask_load_ps(src(that),mask,p.get());
          else  if constexpr( c == category::float32x8 ) return _mm256_mask_load_ps(src(that),mask,p.get());
          else  if constexpr( c == category::float32x4 ) return _mm_mask_load_ps(src(that),mask,p.get());
          else  if constexpr( c == category::int64x8   ) return _mm512_mask_load_epi64(src(that),mask,p.get());
          else  if constexpr( c == category::int64x4   ) return _mm256_mask_load_epi64(src(that),mask,p.get());
          else  if constexpr( c == category::int64x2   ) return _mm_mask_load_epi64(src(that),mask,p.get());
          else  if constexpr( c == category::uint64x8  ) return _mm512_mask_load_epi64(src(that),mask,p.get());
          else  if constexpr( c == category::uint64x4  ) return _mm256_mask_load_epi64(src(that),mask,p.get());
          else  if constexpr( c == category::uint64x2  ) return _mm_mask_load_epi64(src(that),mask,p.get());
          else  if constexpr( c == category::int32x16  ) return _mm512_mask_load_epi32(src(that),mask,p.get());
          else  if constexpr( c == category::int32x8   ) return _mm256_mask_load_epi32(src(that),mask,p.get());
          else  if constexpr( c == category::int32x4   ) return _mm_mask_load_epi32(src(that),mask,p.get());
          else  if constexpr( c == category::uint32x16 ) return _mm512_mask_load_epi32(src(that),mask,p.get());
          else  if constexpr( c == category::uint32x8  ) return _mm256_mask_load_epi32(src(that),mask,p.get());
          else  if constexpr( c == category::uint32x4  ) return _mm_mask_load_epi32(src(that),mask,p.get());
          else  if constexpr( c == category::int16x32  ) return _mm512_mask_loadu_epi16(src(that),mask,p.get());
          else  if constexpr( c == category::int16x16  ) return _mm256_mask_loadu_epi16(src(that),mask,p.get());
          else  if constexpr( c == category::int16x8   ) return _mm_mask_loadu_epi16(src(that),mask,p.get());
          else  if constexpr( c == category::uint16x32 ) return _mm512_mask_loadu_epi16(src(that),mask,p.get());
          else  if constexpr( c == category::uint16x16 ) return _mm256_mask_loadu_epi16(src(that),mask,p.get());
          else  if constexpr( c == category::uint16x8  ) return _mm_mask_loadu_epi16(src(that),mask,p.get());
          else  if constexpr( c == category::int8x64   ) return _mm512_mask_loadu_epi8(src(that),mask,p.get());
          else  if constexpr( c == category::int8x32   ) return _mm256_mask_loadu_epi8(src(that),mask,p.get());
          else  if constexpr( c == category::int8x16   ) return _mm_mask_loadu_epi8(src(that),mask,p.get());
          else  if constexpr( c == category::uint8x64  ) return _mm512_mask_loadu_epi8(src(that),mask,p.get());
          else  if constexpr( c == category::uint8x32  ) return _mm256_mask_loadu_epi8(src(that),mask,p.get());
          else  if constexpr( c == category::uint8x16  ) return _mm_mask_loadu_epi8(src(that),mask,p.get());
        }
        else
        {
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
      }
    }
    else
    {
      if constexpr( !std::is_pointer_v<Ptr> )
      {
        return eve::load[cond](p.get(), Cardinal{});
      }
      else
      {
        // If the ignore/keep is complete we can jump over if_else
        if constexpr( !C::is_complete && current_api > avx )
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
            else                                         return load_(EVE_RETARGET(cpu_), cond, p, Cardinal{});
          }
          else
          {
            return  load_(EVE_RETARGET(cpu_), cond, p, Cardinal{});
          }

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
        else
        {
          return load_(EVE_RETARGET(cpu_), cond, p, Cardinal{});
        }
      }
    }
  }

  template<relative_conditional_expr C, typename Ptr>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(sse2_), C const &cond, Ptr p) noexcept
  {
    using type = std::remove_cvref_t<decltype(*p)>;
    return load_(EVE_RETARGET(sse2_), cond, p, expected_cardinal_t<type>{});
  }
}
