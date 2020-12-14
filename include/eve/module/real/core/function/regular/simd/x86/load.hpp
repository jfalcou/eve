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

namespace eve::detail
{
  //================================================================================================
  // Conditional loads
  //================================================================================================
  template<relative_conditional_expr C, typename Ptr>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(avx_), C const &cond, Ptr p) noexcept
                  -> as_wide_t<std::remove_cvref_t<decltype(*std::declval<Ptr>())>>
  {
    using r_t = as_wide_t<std::remove_cvref_t<decltype(*std::declval<Ptr>())>>;

    if constexpr( !std::is_pointer_v<Ptr> )
    {
      return eve::load[cond](p.get());
    }
    else
    {
      // If the ignore/keep is complete we can jump over if_else
      if constexpr( !C::is_complete )
      {
        r_t that;
        auto mask = cond.mask( as_<r_t>{} ).bits();

        constexpr auto c = categorize<r_t>();

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
          else                                         return load_(EVE_RETARGET(cpu_), cond, p);
        }
        else
        {
          return  load_(EVE_RETARGET(cpu_), cond, p);
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
        return load_(EVE_RETARGET(cpu_), cond, p);
      }
    }
  }
}
