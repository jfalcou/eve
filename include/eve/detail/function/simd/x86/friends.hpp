//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch/as_register.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/function/simd/x86/flags.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/category.hpp>
#include <eve/traits/as_floating_point.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  //================================================================================================
  template<typename T, typename U, typename N, x86_abi ABI>
  EVE_FORCEINLINE auto self_logand( sse2_ const&
                                  , logical<wide<T,N,ABI>> v, logical<wide<U,N,ABI>> w
                                  ) noexcept
  {
    if constexpr( !use_is_wide_logical<ABI>::value )
    {
      using storage_t = typename logical<wide<T, N, ABI>>::storage_type;
      using m_t       = typename storage_t::type;
      m_t that = v.storage().value & w.storage().value;
      return logical<wide<T, N, ABI>>(storage_t{that});
    }
    else
    {
      return self_logand(cpu_{},v,w);
    }
  }

  //================================================================================================
  template<typename T, typename U, typename N, x86_abi ABI>
  EVE_FORCEINLINE auto self_logor ( sse2_ const&
                                  , logical<wide<T,N,ABI>> v, logical<wide<U,N,ABI>> w
                                  ) noexcept
  {
    if constexpr( !use_is_wide_logical<ABI>::value )
    {
      using storage_t = typename logical<wide<T, N, ABI>>::storage_type;
      using m_t       = typename storage_t::type;
      m_t that = v.storage().value | w.storage().value;
      return logical<wide<T, N, ABI>>(storage_t{that});
    }
    else
    {
      return self_logor(cpu_{},v,w);
    }
  }

  //================================================================================================
  template<real_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE auto self_lognot(logical<wide<T, N, ABI>> v) noexcept
  {
    if constexpr( !ABI::is_wide_logical )
    {
      using l_t = logical<wide<T, N, ABI>>;
      return l_t{~v.storage()};
    }
    else
    {
      return bit_cast(~v.bits(), as(v));
    }
  }

  //================================================================================================
  template<real_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE as_logical_t<wide<T, N, ABI>> self_eq(wide<T,N,ABI> v, wide<T,N,ABI> w) noexcept
  {
    constexpr auto c = categorize<wide<T, N, ABI>>();
    constexpr auto f = to_integer(cmp_flt::eq_oq);

    if constexpr( current_api >= avx512 )
    {
            if constexpr( c == category::float32x16 ) return mask16{_mm512_cmp_ps_mask(v, w, f )};
      else  if constexpr( c == category::float32x8  ) return mask8 {_mm256_cmp_ps_mask(v, w, f )};
      else  if constexpr( c == category::float32x4  ) return mask8 {_mm_cmp_ps_mask   (v, w, f )};
      else  if constexpr( c == category::float64x8  ) return mask8 {_mm512_cmp_pd_mask(v, w, f )};
      else  if constexpr( c == category::float64x4  ) return mask8 {_mm256_cmp_pd_mask(v, w, f )};
      else  if constexpr( c == category::float64x2  ) return mask8 {_mm_cmp_pd_mask   (v, w, f )};
      else  if constexpr( c == category::uint64x8   ) return mask8 {_mm512_cmpeq_epu64_mask(v,w)};
      else  if constexpr( c == category::uint64x4   ) return mask8 {_mm256_cmpeq_epu64_mask(v,w)};
      else  if constexpr( c == category::uint64x2   ) return mask8 {_mm_cmpeq_epu64_mask   (v,w)};
      else  if constexpr( c == category::uint32x16  ) return mask16{_mm512_cmpeq_epu32_mask(v,w)};
      else  if constexpr( c == category::uint32x8   ) return mask8 {_mm256_cmpeq_epu32_mask(v,w)};
      else  if constexpr( c == category::uint32x4   ) return mask8 {_mm_cmpeq_epu32_mask   (v,w)};
      else  if constexpr( c == category::uint16x32  ) return mask32{_mm512_cmpeq_epu16_mask(v,w)};
      else  if constexpr( c == category::uint16x16  ) return mask16{_mm256_cmpeq_epu16_mask(v,w)};
      else  if constexpr( c == category::uint16x8   ) return mask8 {_mm_cmpeq_epu16_mask    (v,w)};
      else  if constexpr( c == category::uint8x64   ) return mask64{_mm512_cmpeq_epu8_mask (v,w)};
      else  if constexpr( c == category::uint8x32   ) return mask32{_mm256_cmpeq_epu8_mask (v,w)};
      else  if constexpr( c == category::uint8x16   ) return mask16{_mm_cmpeq_epu8_mask    (v,w)};
      else  if constexpr( c == category::int64x8    ) return mask8 {_mm512_cmpeq_epi64_mask(v,w)};
      else  if constexpr( c == category::int64x4    ) return mask8 {_mm256_cmpeq_epi64_mask(v,w)};
      else  if constexpr( c == category::int64x2    ) return mask8 {_mm_cmpeq_epi64_mask   (v,w)};
      else  if constexpr( c == category::int32x16   ) return mask16{_mm512_cmpeq_epi32_mask(v,w)};
      else  if constexpr( c == category::int32x8    ) return mask8 {_mm256_cmpeq_epi32_mask(v,w)};
      else  if constexpr( c == category::int32x4    ) return mask8 {_mm_cmpeq_epi32_mask   (v,w)};
      else  if constexpr( c == category::int16x32   ) return mask32{_mm512_cmpeq_epi16_mask(v,w)};
      else  if constexpr( c == category::int16x16   ) return mask16{_mm256_cmpeq_epi16_mask(v,w)};
      else  if constexpr( c == category::int16x8    ) return mask8 {_mm_cmpeq_epi16_mask   (v,w)};
      else  if constexpr( c == category::int8x64    ) return mask64{_mm512_cmpeq_epi8_mask (v,w)};
      else  if constexpr( c == category::int8x32    ) return mask32{_mm256_cmpeq_epi8_mask (v,w)};
      else  if constexpr( c == category::int8x16    ) return mask16{_mm_cmpeq_epi8_mask    (v,w)};
    }
    else
    {
      constexpr auto f = to_integer(cmp_flt::eq_oq);

            if constexpr( c == category::float32x8  ) return _mm256_cmp_ps(v,w,f);
      else  if constexpr( c == category::float64x4  ) return _mm256_cmp_pd(v,w,f);
      else  if constexpr( c == category::float32x4  ) return _mm_cmpeq_ps(v,w);
      else  if constexpr( c == category::float64x2  ) return _mm_cmpeq_pd(v,w);
      else  if constexpr(supports_xop)
      {
              if constexpr( c == category::uint64x2 ) return _mm_comeq_epu64(v,w);
        else  if constexpr( c == category::uint32x4 ) return _mm_comeq_epu32(v,w);
        else  if constexpr( c == category::uint16x8 ) return _mm_comeq_epu16(v,w);
        else  if constexpr( c == category::uint8x16 ) return _mm_comeq_epu8 (v,w);
        else  if constexpr( c == category::int64x2  ) return _mm_comeq_epi64(v,w);
        else  if constexpr( c == category::int32x4  ) return _mm_comeq_epi32(v,w);
        else  if constexpr( c == category::int16x8  ) return _mm_comeq_epi16(v,w);
        else  if constexpr( c == category::int8x16  ) return _mm_comeq_epi8 (v,w);
      }
      else
      {
        constexpr auto use_avx2 = current_api >= avx2;
        constexpr auto eq = []<typename E>(E e, E f) { return as_logical_t<E>(e == f); };

              if constexpr(use_avx2 && c == category::int64x4  )  return _mm256_cmpeq_epi64(v,w);
        else  if constexpr(use_avx2 && c == category::uint64x4 )  return _mm256_cmpeq_epi64(v,w);
        else  if constexpr(use_avx2 && c == category::int32x8  )  return _mm256_cmpeq_epi32(v,w);
        else  if constexpr(use_avx2 && c == category::uint32x8 )  return _mm256_cmpeq_epi32(v,w);
        else  if constexpr(use_avx2 && c == category::int16x16 )  return _mm256_cmpeq_epi16(v,w);
        else  if constexpr(use_avx2 && c == category::uint16x16)  return _mm256_cmpeq_epi16(v,w);
        else  if constexpr(use_avx2 && c == category::int8x32  )  return _mm256_cmpeq_epi8 (v,w);
        else  if constexpr(use_avx2 && c == category::uint8x32 )  return _mm256_cmpeq_epi8 (v,w);
        else  if constexpr( c == category::int64x2  )             return map(eq,v,w);
        else  if constexpr( c == category::int32x4  )             return _mm_cmpeq_epi32(v,w);
        else  if constexpr( c == category::int16x8  )             return _mm_cmpeq_epi16(v,w);
        else  if constexpr( c == category::int8x16  )             return _mm_cmpeq_epi8 (v,w);
        else  if constexpr( c == category::uint64x2 )             return map(eq,v,w);
        else  if constexpr( c == category::uint32x4 )             return _mm_cmpeq_epi32(v,w);
        else  if constexpr( c == category::uint16x8 )             return _mm_cmpeq_epi16(v,w);
        else  if constexpr( c == category::uint8x16 )             return _mm_cmpeq_epi8 (v,w);
        else  if constexpr( c == category::int64x4 || c == category::uint64x4 ||
                            c == category::int32x8 || c == category::uint32x8
                          )
        {
          using f_t = as_floating_point_t<wide<T, N, ABI>>;
          auto fv   = bit_cast( v , as_<f_t>{});
               fv  ^= bit_cast( w, as_<f_t>{});
          return bit_cast ( !to_logical( fv ), as_<logical<wide<T, N, ABI>>>{} );
        }
        else                                                      return aggregate(eq,v,w);
      }
    }
  }

  template<real_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE auto self_eq(logical<wide<T,N,ABI>> v, logical<wide<T,N,ABI>> w) noexcept
  {
    if constexpr( !ABI::is_wide_logical )
    {
      return logical<wide<T,N,ABI>>{ ~(v.storage() ^ w.storage()) };
    }
    else
    {
      return bit_cast(~v.bits() ^ w.bits(), as(v));
    }
  }

  //================================================================================================
  template<real_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE as_logical_t<wide<T, N, ABI>> self_neq(wide<T,N,ABI> v, wide<T,N,ABI> w) noexcept
  {
    constexpr auto c = categorize<wide<T, N, ABI>>();
    constexpr auto f = to_integer(cmp_flt::neq_uq);

    if constexpr( current_api >= avx512 )
    {
            if constexpr( c == category::float32x16 ) return mask16{_mm512_cmp_ps_mask   (v,w,f)};
      else  if constexpr( c == category::float32x8  ) return mask8 {_mm256_cmp_ps_mask   (v,w,f)};
      else  if constexpr( c == category::float32x4  ) return mask8 {_mm_cmp_ps_mask      (v,w,f)};
      else  if constexpr( c == category::float64x8  ) return mask8 {_mm512_cmp_pd_mask   (v,w,f)};
      else  if constexpr( c == category::float64x4  ) return mask8 {_mm256_cmp_pd_mask   (v,w,f)};
      else  if constexpr( c == category::float64x2  ) return mask8 {_mm_cmp_pd_mask      (v,w,f)};
      else  if constexpr( c == category::uint64x8   ) return mask8 {_mm512_cmpneq_epu64_mask(v,w)};
      else  if constexpr( c == category::uint64x4   ) return mask8 {_mm256_cmpneq_epu64_mask(v,w)};
      else  if constexpr( c == category::uint64x2   ) return mask8 {_mm_cmpneq_epu64_mask   (v,w)};
      else  if constexpr( c == category::uint32x16  ) return mask16{_mm512_cmpneq_epu32_mask(v,w)};
      else  if constexpr( c == category::uint32x8   ) return mask8 {_mm256_cmpneq_epu32_mask(v,w)};
      else  if constexpr( c == category::uint32x4   ) return mask8 {_mm_cmpneq_epu32_mask   (v,w)};
      else  if constexpr( c == category::uint16x32  ) return mask32{_mm512_cmpneq_epu16_mask(v,w)};
      else  if constexpr( c == category::uint16x16  ) return mask16{_mm256_cmpneq_epu16_mask(v,w)};
      else  if constexpr( c == category::uint16x8   ) return mask8 {_mm_cmpneq_epu16_mask    (v,w)};
      else  if constexpr( c == category::uint8x64   ) return mask64{_mm512_cmpneq_epu8_mask (v,w)};
      else  if constexpr( c == category::uint8x32   ) return mask32{_mm256_cmpneq_epu8_mask (v,w)};
      else  if constexpr( c == category::uint8x16   ) return mask16{_mm_cmpneq_epu8_mask    (v,w)};
      else  if constexpr( c == category::int64x8    ) return mask8 {_mm512_cmpneq_epi64_mask(v,w)};
      else  if constexpr( c == category::int64x4    ) return mask8 {_mm256_cmpneq_epi64_mask(v,w)};
      else  if constexpr( c == category::int64x2    ) return mask8 {_mm_cmpneq_epi64_mask   (v,w)};
      else  if constexpr( c == category::int32x16   ) return mask16{_mm512_cmpneq_epi32_mask(v,w)};
      else  if constexpr( c == category::int32x8    ) return mask8 {_mm256_cmpneq_epi32_mask(v,w)};
      else  if constexpr( c == category::int32x4    ) return mask8 {_mm_cmpneq_epi32_mask   (v,w)};
      else  if constexpr( c == category::int16x32   ) return mask32{_mm512_cmpneq_epi16_mask(v,w)};
      else  if constexpr( c == category::int16x16   ) return mask16{_mm256_cmpneq_epi16_mask(v,w)};
      else  if constexpr( c == category::int16x8    ) return mask8 {_mm_cmpneq_epi16_mask   (v,w)};
      else  if constexpr( c == category::int8x64    ) return mask64{_mm512_cmpneq_epi8_mask (v,w)};
      else  if constexpr( c == category::int8x32    ) return mask32{_mm256_cmpneq_epi8_mask (v,w)};
      else  if constexpr( c == category::int8x16    ) return mask16{_mm_cmpneq_epi8_mask    (v,w)};
    }
    else
    {
            if constexpr( c == category::float32x8  ) return _mm256_cmp_ps(v,w,f);
      else  if constexpr( c == category::float64x4  ) return _mm256_cmp_pd(v,w,f);
      else  if constexpr( c == category::float32x4  ) return _mm_cmpneq_ps(v,w);
      else  if constexpr( c == category::float64x2  ) return _mm_cmpneq_pd(v,w);
      else  if constexpr(supports_xop)
      {
              if constexpr( c == category::uint64x2 ) return _mm_comneq_epu64(v,w);
        else  if constexpr( c == category::uint32x4 ) return _mm_comneq_epu32(v,w);
        else  if constexpr( c == category::uint16x8 ) return _mm_comneq_epu16(v,w);
        else  if constexpr( c == category::uint8x16 ) return _mm_comneq_epu8 (v,w);
        else  if constexpr( c == category::int64x2  ) return _mm_comneq_epi64(v,w);
        else  if constexpr( c == category::int32x4  ) return _mm_comneq_epi32(v,w);
        else  if constexpr( c == category::int16x8  ) return _mm_comneq_epi16(v,w);
        else  if constexpr( c == category::int8x16  ) return _mm_comneq_epi8 (v,w);
      }
      else                                            return !(v == w);
    }
  }

  template<real_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE auto self_neq(logical<wide<T,N,ABI>> v, logical<wide<T,N,ABI>> w) noexcept
  {
    if constexpr( !ABI::is_wide_logical )
    {
      return logical<wide<T,N,ABI>>{ v.storage() ^ w.storage() };
    }
    else
    {
      return bit_cast( v.bits() ^ w.bits(), as(v));
    }
  }

  //================================================================================================
  template<real_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE as_logical_t<wide<T, N, ABI>> self_less(wide<T,N,ABI> v, wide<T,N,ABI> w) noexcept
  {
    constexpr auto c = categorize<wide<T, N, ABI>>();
    constexpr auto f = to_integer(cmp_flt::lt_oq);

    if constexpr( current_api >= avx512 )
    {
            if constexpr( c == category::float32x16 ) return mask16{_mm512_cmp_ps_mask(v, w, f) };
      else  if constexpr( c == category::float32x8  ) return mask8 {_mm256_cmp_ps_mask(v, w, f) };
      else  if constexpr( c == category::float32x4  ) return mask8 {_mm_cmp_ps_mask   (v, w, f) };
      else  if constexpr( c == category::float64x8  ) return mask8 {_mm512_cmp_pd_mask(v, w, f) };
      else  if constexpr( c == category::float64x4  ) return mask8 {_mm256_cmp_pd_mask(v, w, f) };
      else  if constexpr( c == category::float64x2  ) return mask8 {_mm_cmp_pd_mask   (v, w, f) };
      else  if constexpr( c == category::uint64x8   ) return mask8 {_mm512_cmplt_epu64_mask(v,w)};
      else  if constexpr( c == category::uint64x4   ) return mask8 {_mm256_cmplt_epu64_mask(v,w)};
      else  if constexpr( c == category::uint64x2   ) return mask8 {_mm_cmplt_epu64_mask   (v,w)};
      else  if constexpr( c == category::uint32x16  ) return mask16{_mm512_cmplt_epu32_mask(v,w)};
      else  if constexpr( c == category::uint32x8   ) return mask8 {_mm256_cmplt_epu32_mask(v,w)};
      else  if constexpr( c == category::uint32x4   ) return mask8 {_mm_cmplt_epu32_mask   (v,w)};
      else  if constexpr( c == category::uint16x32  ) return mask32{_mm512_cmplt_epu16_mask(v,w)};
      else  if constexpr( c == category::uint16x16  ) return mask16{_mm256_cmplt_epu16_mask(v,w)};
      else  if constexpr( c == category::uint16x8   ) return mask8 {_mm_cmplt_epu16_mask    (v,w)};
      else  if constexpr( c == category::uint8x64   ) return mask64{_mm512_cmplt_epu8_mask (v,w)};
      else  if constexpr( c == category::uint8x32   ) return mask32{_mm256_cmplt_epu8_mask (v,w)};
      else  if constexpr( c == category::uint8x16   ) return mask16{_mm_cmplt_epu8_mask    (v,w)};
      else  if constexpr( c == category::int64x8    ) return mask8 {_mm512_cmplt_epi64_mask(v,w)};
      else  if constexpr( c == category::int64x4    ) return mask8 {_mm256_cmplt_epi64_mask(v,w)};
      else  if constexpr( c == category::int64x2    ) return mask8 {_mm_cmplt_epi64_mask   (v,w)};
      else  if constexpr( c == category::int32x16   ) return mask16{_mm512_cmplt_epi32_mask(v,w)};
      else  if constexpr( c == category::int32x8    ) return mask8 {_mm256_cmplt_epi32_mask(v,w)};
      else  if constexpr( c == category::int32x4    ) return mask8 {_mm_cmplt_epi32_mask   (v,w)};
      else  if constexpr( c == category::int16x32   ) return mask32{_mm512_cmplt_epi16_mask(v,w)};
      else  if constexpr( c == category::int16x16   ) return mask16{_mm256_cmplt_epi16_mask(v,w)};
      else  if constexpr( c == category::int16x8    ) return mask8 {_mm_cmplt_epi16_mask   (v,w)};
      else  if constexpr( c == category::int8x64    ) return mask64{_mm512_cmplt_epi8_mask (v,w)};
      else  if constexpr( c == category::int8x32    ) return mask32{_mm256_cmplt_epi8_mask (v,w)};
      else  if constexpr( c == category::int8x16    ) return mask16{_mm_cmplt_epi8_mask    (v,w)};
    }
    else
    {
            if constexpr( c == category::float32x8  ) return _mm256_cmp_ps(v,w,f);
      else  if constexpr( c == category::float64x4  ) return _mm256_cmp_pd(v,w,f);
      else  if constexpr( c == category::float32x4  ) return _mm_cmplt_ps(v,w);
      else  if constexpr( c == category::float64x2  ) return _mm_cmplt_pd(v,w);
      else  if constexpr(supports_xop)
      {
              if constexpr( c == category::uint64x2 ) return _mm_comlt_epu64(v,w);
        else  if constexpr( c == category::uint32x4 ) return _mm_comlt_epu32(v,w);
        else  if constexpr( c == category::uint16x8 ) return _mm_comlt_epu16(v,w);
        else  if constexpr( c == category::uint8x16 ) return _mm_comlt_epu8 (v,w);
        else  if constexpr( c == category::int64x2  ) return _mm_comlt_epi64(v,w);
        else  if constexpr( c == category::int32x4  ) return _mm_comlt_epi32(v,w);
        else  if constexpr( c == category::int16x8  ) return _mm_comlt_epi16(v,w);
        else  if constexpr( c == category::int8x16  ) return _mm_comlt_epi8 (v,w);
      }
      else
      {
        constexpr auto use_avx2 = current_api >= avx2;
        constexpr auto lt       = []<typename E>(E e, E f) { return as_logical_t<E>(e < f); };

        [[maybe_unused]]  auto unsigned_cmp = [](auto v, auto w)
        {
          using l_t = logical<wide<T, N, ABI>>;
          auto const sm = signmask(as_<as_integer_t<wide<T, N, ABI>, signed>>());
          return bit_cast( (bit_cast(v,as(sm))-sm) < (bit_cast(w,as(sm))-sm),as_<l_t>{});
        };

              if constexpr(use_avx2 && c == category::int64x4  )  return _mm256_cmpgt_epi64(w,v);
        else  if constexpr(use_avx2 && c == category::uint64x4 )  return unsigned_cmp(v,w);
        else  if constexpr(use_avx2 && c == category::int32x8  )  return _mm256_cmpgt_epi32(w,v);
        else  if constexpr(use_avx2 && c == category::uint32x8 )  return unsigned_cmp(v,w);
        else  if constexpr(use_avx2 && c == category::int16x16 )  return _mm256_cmpgt_epi16(w,v);
        else  if constexpr(use_avx2 && c == category::uint16x16)  return unsigned_cmp(v,w);
        else  if constexpr(use_avx2 && c == category::int8x32  )  return _mm256_cmpgt_epi8 (w,v);
        else  if constexpr(use_avx2 && c == category::uint8x32 )  return unsigned_cmp(v,w);
        else  if constexpr( c == category::int64x2  )             return map(lt, v, w);
        else  if constexpr( c == category::int32x4  )             return _mm_cmplt_epi32(v,w);
        else  if constexpr( c == category::int16x8  )             return _mm_cmplt_epi16(v,w);
        else  if constexpr( c == category::int8x16  )             return _mm_cmplt_epi8 (v,w);
        else  if constexpr( c == category::uint64x2 )             return map(lt,v,w);
        else  if constexpr( c == category::uint32x4 )             return unsigned_cmp(v,w);
        else  if constexpr( c == category::uint16x8 )             return unsigned_cmp(v,w);
        else  if constexpr( c == category::uint8x16 )             return unsigned_cmp(v,w);
        else                                                      return aggregate(lt,v,w);
      }
    }
  }

  //================================================================================================
  template<real_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE as_logical_t<wide<T, N, ABI>> self_greater(wide<T,N,ABI> v, wide<T,N,ABI> w) noexcept
  {
    constexpr auto c = categorize<wide<T, N, ABI>>();
    constexpr auto f = to_integer(cmp_flt::gt_oq);

    if constexpr( current_api >= avx512 )
    {
            if constexpr( c == category::float32x16 ) return mask16{_mm512_cmp_ps_mask(v, w, f) };
      else  if constexpr( c == category::float32x8  ) return mask8 {_mm256_cmp_ps_mask(v, w, f) };
      else  if constexpr( c == category::float32x4  ) return mask8 {_mm_cmp_ps_mask   (v, w, f) };
      else  if constexpr( c == category::float64x8  ) return mask8 {_mm512_cmp_pd_mask(v, w, f) };
      else  if constexpr( c == category::float64x4  ) return mask8 {_mm256_cmp_pd_mask(v, w, f) };
      else  if constexpr( c == category::float64x2  ) return mask8 {_mm_cmp_pd_mask   (v, w, f) };
      else  if constexpr( c == category::uint64x8   ) return mask8 {_mm512_cmpgt_epu64_mask(v,w)};
      else  if constexpr( c == category::uint64x4   ) return mask8 {_mm256_cmpgt_epu64_mask(v,w)};
      else  if constexpr( c == category::uint64x2   ) return mask8 {_mm_cmpgt_epu64_mask   (v,w)};
      else  if constexpr( c == category::uint32x16  ) return mask16{_mm512_cmpgt_epu32_mask(v,w)};
      else  if constexpr( c == category::uint32x8   ) return mask8 {_mm256_cmpgt_epu32_mask(v,w)};
      else  if constexpr( c == category::uint32x4   ) return mask8 {_mm_cmpgt_epu32_mask   (v,w)};
      else  if constexpr( c == category::uint16x32  ) return mask32{_mm512_cmpgt_epu16_mask(v,w)};
      else  if constexpr( c == category::uint16x16  ) return mask16{_mm256_cmpgt_epu16_mask(v,w)};
      else  if constexpr( c == category::uint16x8   ) return mask8 {_mm_cmpgt_epu16_mask    (v,w)};
      else  if constexpr( c == category::uint8x64   ) return mask64{_mm512_cmpgt_epu8_mask (v,w)};
      else  if constexpr( c == category::uint8x32   ) return mask32{_mm256_cmpgt_epu8_mask (v,w)};
      else  if constexpr( c == category::uint8x16   ) return mask16{_mm_cmpgt_epu8_mask    (v,w)};
      else  if constexpr( c == category::int64x8    ) return mask8 {_mm512_cmpgt_epi64_mask(v,w)};
      else  if constexpr( c == category::int64x4    ) return mask8 {_mm256_cmpgt_epi64_mask(v,w)};
      else  if constexpr( c == category::int64x2    ) return mask8 {_mm_cmpgt_epi64_mask   (v,w)};
      else  if constexpr( c == category::int32x16   ) return mask16{_mm512_cmpgt_epi32_mask(v,w)};
      else  if constexpr( c == category::int32x8    ) return mask8 {_mm256_cmpgt_epi32_mask(v,w)};
      else  if constexpr( c == category::int32x4    ) return mask8 {_mm_cmpgt_epi32_mask   (v,w)};
      else  if constexpr( c == category::int16x32   ) return mask32{_mm512_cmpgt_epi16_mask(v,w)};
      else  if constexpr( c == category::int16x16   ) return mask16{_mm256_cmpgt_epi16_mask(v,w)};
      else  if constexpr( c == category::int16x8    ) return mask8 {_mm_cmpgt_epi16_mask   (v,w)};
      else  if constexpr( c == category::int8x64    ) return mask64{_mm512_cmpgt_epi8_mask (v,w)};
      else  if constexpr( c == category::int8x32    ) return mask32{_mm256_cmpgt_epi8_mask (v,w)};
      else  if constexpr( c == category::int8x16    ) return mask16{_mm_cmpgt_epi8_mask    (v,w)};
    }
    else
    {
            if constexpr( c == category::float32x8  ) return _mm256_cmp_ps(v,w,f);
      else  if constexpr( c == category::float64x4  ) return _mm256_cmp_pd(v,w,f);
      else  if constexpr( c == category::float32x4  ) return _mm_cmpgt_ps(v,w);
      else  if constexpr( c == category::float64x2  ) return _mm_cmpgt_pd(v,w);
      else  if constexpr(supports_xop)
      {
              if constexpr( c == category::uint64x2 ) return _mm_comgt_epu64(v,w);
        else  if constexpr( c == category::uint32x4 ) return _mm_comgt_epu32(v,w);
        else  if constexpr( c == category::uint16x8 ) return _mm_comgt_epu16(v,w);
        else  if constexpr( c == category::uint8x16 ) return _mm_comgt_epu8 (v,w);
        else  if constexpr( c == category::int64x2  ) return _mm_comgt_epi64(v,w);
        else  if constexpr( c == category::int32x4  ) return _mm_comgt_epi32(v,w);
        else  if constexpr( c == category::int16x8  ) return _mm_comgt_epi16(v,w);
        else  if constexpr( c == category::int8x16  ) return _mm_comgt_epi8 (v,w);
      }
      else
      {
        constexpr auto use_avx2 = current_api >= avx2;
        constexpr auto use_sse4 = current_api >= sse4_2;

        constexpr auto gt = []<typename E>(E e, E f) { return as_logical_t<E>(e > f); };

        [[maybe_unused]]  auto unsigned_cmp = [](auto v, auto w)
        {
          using l_t = logical<wide<T, N, ABI>>;
          auto const sm = signmask(as_<as_integer_t<wide<T, N, ABI>, signed>>());
          return bit_cast((bit_cast(v,as(sm))-sm) > (bit_cast(w,as(sm))-sm),as_<l_t>{});
        };

              if constexpr(use_avx2 && c == category::int64x4  )  return _mm256_cmpgt_epi64(v,w);
        else  if constexpr(use_avx2 && c == category::uint64x4 )  return unsigned_cmp(v,w);
        else  if constexpr(use_avx2 && c == category::int32x8  )  return _mm256_cmpgt_epi32(v,w);
        else  if constexpr(use_avx2 && c == category::uint32x8 )  return unsigned_cmp(v,w);
        else  if constexpr(use_avx2 && c == category::int16x16 )  return _mm256_cmpgt_epi16(v,w);
        else  if constexpr(use_avx2 && c == category::uint16x16)  return unsigned_cmp(v,w);
        else  if constexpr(use_avx2 && c == category::int8x32  )  return _mm256_cmpgt_epi8 (v,w);
        else  if constexpr(use_avx2 && c == category::uint8x32 )  return unsigned_cmp(v,w);
        else  if constexpr(use_sse4 && c == category::int64x2  )  return _mm_cmpgt_epi64(v,w);
        else  if constexpr( c == category::int64x2  )             return map(gt, v, w);
        else  if constexpr( c == category::int32x4  )             return _mm_cmpgt_epi32(v,w);
        else  if constexpr( c == category::int16x8  )             return _mm_cmpgt_epi16(v,w);
        else  if constexpr( c == category::int8x16  )             return _mm_cmpgt_epi8 (v,w);
        else  if constexpr( c == category::uint64x2 )             return unsigned_cmp(v,w);
        else  if constexpr( c == category::uint32x4 )             return unsigned_cmp(v,w);
        else  if constexpr( c == category::uint16x8 )             return unsigned_cmp(v,w);
        else  if constexpr( c == category::uint8x16 )             return unsigned_cmp(v,w);
        else                                                      return aggregate(gt,v,w);
      }
    }
  }

  //================================================================================================
  template<real_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE as_logical_t<wide<T, N, ABI>> self_geq(wide<T,N,ABI> v, wide<T,N,ABI> w) noexcept
  {
    constexpr auto c = categorize<wide<T, N, ABI>>();
    constexpr auto f = to_integer(cmp_flt::ge_oq);

    if constexpr( current_api >= avx512 )
    {
            if constexpr( c == category::float32x16 ) return mask16{_mm512_cmp_ps_mask(v, w, f) };
      else  if constexpr( c == category::float32x8  ) return mask8 {_mm256_cmp_ps_mask(v, w, f) };
      else  if constexpr( c == category::float32x4  ) return mask8 {_mm_cmp_ps_mask   (v, w, f) };
      else  if constexpr( c == category::float64x8  ) return mask8 {_mm512_cmp_pd_mask(v, w, f) };
      else  if constexpr( c == category::float64x4  ) return mask8 {_mm256_cmp_pd_mask(v, w, f) };
      else  if constexpr( c == category::float64x2  ) return mask8 {_mm_cmp_pd_mask   (v, w, f) };
      else  if constexpr( c == category::uint64x8   ) return mask8 {_mm512_cmpge_epu64_mask(v,w)};
      else  if constexpr( c == category::uint64x4   ) return mask8 {_mm256_cmpge_epu64_mask(v,w)};
      else  if constexpr( c == category::uint64x2   ) return mask8 {_mm_cmpge_epu64_mask   (v,w)};
      else  if constexpr( c == category::uint32x16  ) return mask16{_mm512_cmpge_epu32_mask(v,w)};
      else  if constexpr( c == category::uint32x8   ) return mask8 {_mm256_cmpge_epu32_mask(v,w)};
      else  if constexpr( c == category::uint32x4   ) return mask8 {_mm_cmpge_epu32_mask   (v,w)};
      else  if constexpr( c == category::uint16x32  ) return mask32{_mm512_cmpge_epu16_mask(v,w)};
      else  if constexpr( c == category::uint16x16  ) return mask16{_mm256_cmpge_epu16_mask(v,w)};
      else  if constexpr( c == category::uint16x8   ) return mask8 {_mm_cmpge_epu16_mask    (v,w)};
      else  if constexpr( c == category::uint8x64   ) return mask64{_mm512_cmpge_epu8_mask (v,w)};
      else  if constexpr( c == category::uint8x32   ) return mask32{_mm256_cmpge_epu8_mask (v,w)};
      else  if constexpr( c == category::uint8x16   ) return mask16{_mm_cmpge_epu8_mask    (v,w)};
      else  if constexpr( c == category::int64x8    ) return mask8 {_mm512_cmpge_epi64_mask(v,w)};
      else  if constexpr( c == category::int64x4    ) return mask8 {_mm256_cmpge_epi64_mask(v,w)};
      else  if constexpr( c == category::int64x2    ) return mask8 {_mm_cmpge_epi64_mask   (v,w)};
      else  if constexpr( c == category::int32x16   ) return mask16{_mm512_cmpge_epi32_mask(v,w)};
      else  if constexpr( c == category::int32x8    ) return mask8 {_mm256_cmpge_epi32_mask(v,w)};
      else  if constexpr( c == category::int32x4    ) return mask8 {_mm_cmpge_epi32_mask   (v,w)};
      else  if constexpr( c == category::int16x32   ) return mask32{_mm512_cmpge_epi16_mask(v,w)};
      else  if constexpr( c == category::int16x16   ) return mask16{_mm256_cmpge_epi16_mask(v,w)};
      else  if constexpr( c == category::int16x8    ) return mask8 {_mm_cmpge_epi16_mask   (v,w)};
      else  if constexpr( c == category::int8x64    ) return mask64{_mm512_cmpge_epi8_mask (v,w)};
      else  if constexpr( c == category::int8x32    ) return mask32{_mm256_cmpge_epi8_mask (v,w)};
      else  if constexpr( c == category::int8x16    ) return mask16{_mm_cmpge_epi8_mask    (v,w)};
    }
    else
    {
            if constexpr( c == category::float32x8  ) return _mm256_cmp_ps(v,w,f);
      else  if constexpr( c == category::float64x4  ) return _mm256_cmp_pd(v,w,f);
      else  if constexpr( c == category::float32x4  ) return _mm_cmpge_ps(v,w);
      else  if constexpr( c == category::float64x2  ) return _mm_cmpge_pd(v,w);
      else  if constexpr(supports_xop)
      {
              if constexpr( c == category::uint64x2 ) return _mm_comge_epu64(v,w);
        else  if constexpr( c == category::uint32x4 ) return _mm_comge_epu32(v,w);
        else  if constexpr( c == category::uint16x8 ) return _mm_comge_epu16(v,w);
        else  if constexpr( c == category::uint8x16 ) return _mm_comge_epu8 (v,w);
        else  if constexpr( c == category::int64x2  ) return _mm_comge_epi64(v,w);
        else  if constexpr( c == category::int32x4  ) return _mm_comge_epi32(v,w);
        else  if constexpr( c == category::int16x8  ) return _mm_comge_epi16(v,w);
        else  if constexpr( c == category::int8x16  ) return _mm_comge_epi8 (v,w);
      }
      else                                            return !(v < w);
    }
  }

  //================================================================================================
  template<real_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE as_logical_t<wide<T, N, ABI>> self_leq(wide<T,N,ABI> v, wide<T,N,ABI> w) noexcept
  {
    constexpr auto c = categorize<wide<T, N, ABI>>();
    constexpr auto f = to_integer(cmp_flt::le_oq);

    if constexpr( current_api >= avx512 )
    {
            if constexpr( c == category::float32x16 ) return mask16{_mm512_cmp_ps_mask(v, w, f) };
      else  if constexpr( c == category::float32x8  ) return mask8 {_mm256_cmp_ps_mask(v, w, f) };
      else  if constexpr( c == category::float32x4  ) return mask8 {_mm_cmp_ps_mask   (v, w, f) };
      else  if constexpr( c == category::float64x8  ) return mask8 {_mm512_cmp_pd_mask(v, w, f) };
      else  if constexpr( c == category::float64x4  ) return mask8 {_mm256_cmp_pd_mask(v, w, f) };
      else  if constexpr( c == category::float64x2  ) return mask8 {_mm_cmp_pd_mask   (v, w, f) };
      else  if constexpr( c == category::uint64x8   ) return mask8 {_mm512_cmple_epu64_mask(v,w)};
      else  if constexpr( c == category::uint64x4   ) return mask8 {_mm256_cmple_epu64_mask(v,w)};
      else  if constexpr( c == category::uint64x2   ) return mask8 {_mm_cmple_epu64_mask   (v,w)};
      else  if constexpr( c == category::uint32x16  ) return mask16{_mm512_cmple_epu32_mask(v,w)};
      else  if constexpr( c == category::uint32x8   ) return mask8 {_mm256_cmple_epu32_mask(v,w)};
      else  if constexpr( c == category::uint32x4   ) return mask8 {_mm_cmple_epu32_mask   (v,w)};
      else  if constexpr( c == category::uint16x32  ) return mask32{_mm512_cmple_epu16_mask(v,w)};
      else  if constexpr( c == category::uint16x16  ) return mask16{_mm256_cmple_epu16_mask(v,w)};
      else  if constexpr( c == category::uint16x8   ) return mask8 {_mm_cmple_epu16_mask    (v,w)};
      else  if constexpr( c == category::uint8x64   ) return mask64{_mm512_cmple_epu8_mask (v,w)};
      else  if constexpr( c == category::uint8x32   ) return mask32{_mm256_cmple_epu8_mask (v,w)};
      else  if constexpr( c == category::uint8x16   ) return mask16{_mm_cmple_epu8_mask    (v,w)};
      else  if constexpr( c == category::int64x8    ) return mask8 {_mm512_cmple_epi64_mask(v,w)};
      else  if constexpr( c == category::int64x4    ) return mask8 {_mm256_cmple_epi64_mask(v,w)};
      else  if constexpr( c == category::int64x2    ) return mask8 {_mm_cmple_epi64_mask   (v,w)};
      else  if constexpr( c == category::int32x16   ) return mask16{_mm512_cmple_epi32_mask(v,w)};
      else  if constexpr( c == category::int32x8    ) return mask8 {_mm256_cmple_epi32_mask(v,w)};
      else  if constexpr( c == category::int32x4    ) return mask8 {_mm_cmple_epi32_mask   (v,w)};
      else  if constexpr( c == category::int16x32   ) return mask32{_mm512_cmple_epi16_mask(v,w)};
      else  if constexpr( c == category::int16x16   ) return mask16{_mm256_cmple_epi16_mask(v,w)};
      else  if constexpr( c == category::int16x8    ) return mask8 {_mm_cmple_epi16_mask   (v,w)};
      else  if constexpr( c == category::int8x64    ) return mask64{_mm512_cmple_epi8_mask (v,w)};
      else  if constexpr( c == category::int8x32    ) return mask32{_mm256_cmple_epi8_mask (v,w)};
      else  if constexpr( c == category::int8x16    ) return mask16{_mm_cmple_epi8_mask    (v,w)};
    }
    else
    {
            if constexpr( c == category::float32x8  ) return _mm256_cmp_ps(v,w,f);
      else  if constexpr( c == category::float64x4  ) return _mm256_cmp_pd(v,w,f);
      else  if constexpr( c == category::float32x4  ) return _mm_cmple_ps(v,w);
      else  if constexpr( c == category::float64x2  ) return _mm_cmple_pd(v,w);
      else  if constexpr(supports_xop)
      {
              if constexpr( c == category::uint64x2 ) return _mm_comle_epu64(v,w);
        else  if constexpr( c == category::uint32x4 ) return _mm_comle_epu32(v,w);
        else  if constexpr( c == category::uint16x8 ) return _mm_comle_epu16(v,w);
        else  if constexpr( c == category::uint8x16 ) return _mm_comle_epu8 (v,w);
        else  if constexpr( c == category::int64x2  ) return _mm_comle_epi64(v,w);
        else  if constexpr( c == category::int32x4  ) return _mm_comle_epi32(v,w);
        else  if constexpr( c == category::int16x8  ) return _mm_comle_epi16(v,w);
        else  if constexpr( c == category::int8x16  ) return _mm_comle_epi8 (v,w);
      }
      else                                            return !(v > w);
    }
  }
}
