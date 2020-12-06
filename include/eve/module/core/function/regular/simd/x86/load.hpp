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
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(avx_), C const &cond, Ptr ptr) noexcept
                  -> as_wide_t<std::remove_cvref_t<decltype(*std::declval<Ptr>())>>
  {
    using r_t = as_wide_t<std::remove_cvref_t<decltype(*std::declval<Ptr>())>>;

    if constexpr( !std::is_pointer_v<Ptr> )
    {
      return eve::load[cond](ptr.get());
    }
    else
    {
      // If the ignore/keep is complete we can jump over if_else
      if constexpr( !C::is_complete )
      {
        r_t that;
        auto mask = cond.mask( as_<r_t>{} ).bits();

        constexpr auto cat = categorize<r_t>();

              if constexpr( cat == category::float64x4 )  that = _mm256_maskload_pd (ptr,mask);
        else  if constexpr( cat == category::float64x2 )  that = _mm_maskload_pd    (ptr,mask);
        else  if constexpr( cat == category::float32x8 )  that = _mm256_maskload_ps (ptr,mask);
        else  if constexpr( cat == category::float32x4 )  that = _mm_maskload_ps    (ptr,mask);
        else  if constexpr( current_api >= avx2 )
        {
          constexpr auto m64x4 = match(cat, category::int64x4, category::uint64x4);
          constexpr auto m64x2 = match(cat, category::int64x2, category::uint64x2);
          constexpr auto m32x8 = match(cat, category::int32x8, category::uint32x8);
          constexpr auto m32x4 = match(cat, category::int32x4, category::uint32x4);

                if constexpr( m64x4 ) that = _mm256_maskload_epi64 ((long long const int*)ptr,mask);
          else  if constexpr( m64x2 ) that = _mm_maskload_epi64    ((long long const int*)ptr,mask);
          else  if constexpr( m32x8 ) that = _mm256_maskload_epi32 ((std::int32_t const*)ptr,mask);
          else  if constexpr( m32x4 ) that = _mm_maskload_epi32    ((std::int32_t const*)ptr,mask);
          else                        return load_(EVE_RETARGET(cpu_), cond, ptr);
        }
        else
        {
          return  load_(EVE_RETARGET(cpu_), cond, ptr);
        }

        if constexpr( C::has_alternative )
        {
          constexpr auto blender = [](auto a, auto b, auto m)
          {
            auto mm = typename r_t::storage_type(m.storage());
                  if constexpr( cat == category::float64x4 )  return _mm256_blendv_pd(a,b,mm);
            else  if constexpr( cat == category::float32x8 )  return _mm256_blendv_ps(a,b,mm);
            else  if constexpr( cat == category::float64x2 )  return _mm_blendv_pd(a,b,mm);
            else  if constexpr( cat == category::float32x4 )  return _mm_blendv_ps(a,b,mm);
            else  if constexpr( sizeof(a) == 32)              return _mm256_blendv_epi8(a,b,mm);
            else  if constexpr( sizeof(a) == 16)              return _mm_blendv_epi8(a,b,mm);
          };

          r_t alt(cond.alternative);
          that = blender(alt,that,mask);
        }

        return that;
      }
      else
      {
        return load_(EVE_RETARGET(cpu_), cond, ptr);
      }
    }
  }
}
