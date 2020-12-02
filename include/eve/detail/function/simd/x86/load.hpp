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
  // Regular loads
  //================================================================================================
  template<scalar_pointer Ptr, typename T, typename N, x86_abi ABI>
  EVE_FORCEINLINE auto load(eve::as_<wide<T, N>> const &, ABI const &, Ptr p)
  requires( std::same_as<T, std::remove_cvref_t<decltype(*p)>> )
  {
    constexpr auto cat = categorize<wide<T, N>>();
    constexpr bool isfull256 = N::value*sizeof(T) == x86_256_::bytes;
    constexpr bool isfull128 = N::value*sizeof(T) == x86_128_::bytes;

    if constexpr( !std::is_pointer_v<Ptr> )
    {
      if constexpr( isfull256 )
      {
              if constexpr( cat == category::float64x4 )  return _mm256_load_pd(p.get());
        else  if constexpr( cat == category::float32x8 )  return _mm256_load_ps(p.get());
        else return _mm256_load_si256((__m256i *)p.get());
      }
      else  if constexpr( isfull128 )
      {
              if constexpr( cat == category::float64x2 )  return _mm_load_pd(p.get());
        else  if constexpr( cat == category::float32x4 )  return _mm_load_ps(p.get());
        else  return _mm_load_si128((__m128i *)p.get());
      }
      else
      {
        typename wide<T, N>::storage_type that;
        std::memcpy(&that, p.get(), N::value * sizeof(T));
        return that;
      }
    }
    else
    {
      if constexpr( isfull256 )
      {
              if constexpr( cat == category::float64x4 )  return _mm256_loadu_pd(p);
        else  if constexpr( cat == category::float32x8 )  return _mm256_loadu_ps(p);
        else return _mm256_loadu_si256((__m256i *)p);
      }
      else  if constexpr( isfull128 )
      {
              if constexpr( cat == category::float64x2 )  return _mm_loadu_pd(p);
        else  if constexpr( cat == category::float32x4 )  return _mm_loadu_ps(p);
        else  return _mm_loadu_si128((__m128i *)p);
      }
      else
      {
        typename wide<T, N>::storage_type that;
        std::memcpy(&that, p, N::value * sizeof(T));
        return that;
      }
    }
  }

  //================================================================================================
  // Conditional loads
  //================================================================================================
  template<relative_conditional_expr C, typename T>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(avx_), C const &cond, T* ptr) noexcept
                  -> as_wide_t<std::remove_cvref_t<T>>
  {
    using r_t = as_wide_t<std::remove_cvref_t<T>>;

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
