//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/as_register.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/function/simd/x86/flags.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/forward.hpp>
#include <eve/traits/as_floating_point.hpp>

namespace eve::detail
{
//================================================================================================
template<typename T, typename U, typename N>
EVE_FORCEINLINE auto
self_logand(sse2_ const&, logical<wide<T, N>> v, logical<wide<U, N>> w) noexcept
requires(x86_abi<abi_t<T, N>> || x86_abi<abi_t<U, N>>)
{
  if constexpr( !use_is_wide_logical<abi_t<T, N>>::value )
  {
    using abi_t     = typename logical<wide<T,N>>::abi_type;
    using abi_u     = typename logical<wide<U,N>>::abi_type;
    using storage_t = typename logical<wide<T, N>>::storage_type;
    using m_t       = std::conditional_t< is_aggregated_v<abi_t>
                                        , typename logical<wide<U, N>>::storage_type
                                        , storage_t
                                        >;
    using u_t       = typename m_t::type;

    // We need to know which side is not aggregated to safely bit_cast its contents
    auto cvt = [](auto a, auto b)
    {
      storage_t dst;
      if constexpr( is_aggregated_v<abi_t> )
      {
        u_t them = bit_cast(a.storage(),as<u_t>()) & b.storage().value;
        dst = bit_cast(them,as<storage_t>());
      }
      else if constexpr( is_aggregated_v<abi_u> )
      {
        dst.value = a.storage().value & bit_cast(b.storage(),as<u_t>());
      }
      else
      {
        dst.value = a.storage().value & b.storage().value;
      }
      return dst;
    };

    return logical<wide<T, N>>(cvt(v,w));
  }
  else
  {
    return self_logand(cpu_ {}, v, w);
  }
}

//================================================================================================
template<typename T, typename U, typename N>
EVE_FORCEINLINE auto
self_logor(sse2_ const&, logical<wide<T, N>> v, logical<wide<U, N>> w) noexcept
requires(x86_abi<abi_t<T, N>> || x86_abi<abi_t<U, N>>)
{
  if constexpr( !use_is_wide_logical<abi_t<T, N>>::value )
  {
    using abi_t     = typename logical<wide<T,N>>::abi_type;
    using abi_u     = typename logical<wide<U,N>>::abi_type;
    using storage_t = typename logical<wide<T, N>>::storage_type;
    using m_t       = std::conditional_t< is_aggregated_v<abi_t>
                                        , typename logical<wide<U, N>>::storage_type
                                        , storage_t
                                        >;
    using u_t       = typename m_t::type;

    // We need to know which side is not aggregated to safely bit_cast its contents
    auto cvt = [](auto a, auto b)
    {
      storage_t dst;
      if constexpr( is_aggregated_v<abi_t> )
      {
        u_t them = bit_cast(a.storage(),as<u_t>()) | b.storage().value;
        dst = bit_cast(them,as<storage_t>());
      }
      else if constexpr( is_aggregated_v<abi_u> )
      {
        dst.value = a.storage().value | bit_cast(b.storage(),as<u_t>());
      }
      else
      {
        dst.value = a.storage().value | b.storage().value;
      }
      return dst;
    };

    return logical<wide<T, N>>(cvt(v,w));
  }
  else
  {
    return self_logor(cpu_ {}, v, w);
  }
}

//================================================================================================
template<real_value T, typename N>
EVE_FORCEINLINE auto
self_lognot(logical<wide<T, N>> v) noexcept requires x86_abi<abi_t<T, N>>
{
  if constexpr( !abi_t<T, N>::is_wide_logical )
  {
    using l_t = logical<wide<T, N>>;
    return l_t {~v.storage()};
  }
  else { return bit_cast(~v.bits(), as(v)); }
}

//================================================================================================
template<real_value T, typename N>
EVE_FORCEINLINE as_logical_t<wide<T, N>>
                self_eq(wide<T, N> v, wide<T, N> w) noexcept requires x86_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  constexpr auto f = to_integer(cmp_flt::eq_oq);

  if constexpr( current_api >= avx512 )
  {
    if constexpr( c == category::float32x16 ) return mask16 {_mm512_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float32x8 ) return mask8 {_mm256_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float32x4 ) return mask8 {_mm_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float64x8 ) return mask8 {_mm512_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::float64x4 ) return mask8 {_mm256_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::float64x2 ) return mask8 {_mm_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::uint64x8 ) return mask8 {_mm512_cmpeq_epu64_mask(v, w)};
    else if constexpr( c == category::uint64x4 ) return mask8 {_mm256_cmpeq_epu64_mask(v, w)};
    else if constexpr( c == category::uint64x2 ) return mask8 {_mm_cmpeq_epu64_mask(v, w)};
    else if constexpr( c == category::uint32x16 ) return mask16 {_mm512_cmpeq_epu32_mask(v, w)};
    else if constexpr( c == category::uint32x8 ) return mask8 {_mm256_cmpeq_epu32_mask(v, w)};
    else if constexpr( c == category::uint32x4 ) return mask8 {_mm_cmpeq_epu32_mask(v, w)};
    else if constexpr( c == category::uint16x32 ) return mask32 {_mm512_cmpeq_epu16_mask(v, w)};
    else if constexpr( c == category::uint16x16 ) return mask16 {_mm256_cmpeq_epu16_mask(v, w)};
    else if constexpr( c == category::uint16x8 ) return mask8 {_mm_cmpeq_epu16_mask(v, w)};
    else if constexpr( c == category::uint8x64 ) return mask64 {_mm512_cmpeq_epu8_mask(v, w)};
    else if constexpr( c == category::uint8x32 ) return mask32 {_mm256_cmpeq_epu8_mask(v, w)};
    else if constexpr( c == category::uint8x16 ) return mask16 {_mm_cmpeq_epu8_mask(v, w)};
    else if constexpr( c == category::int64x8 ) return mask8 {_mm512_cmpeq_epi64_mask(v, w)};
    else if constexpr( c == category::int64x4 ) return mask8 {_mm256_cmpeq_epi64_mask(v, w)};
    else if constexpr( c == category::int64x2 ) return mask8 {_mm_cmpeq_epi64_mask(v, w)};
    else if constexpr( c == category::int32x16 ) return mask16 {_mm512_cmpeq_epi32_mask(v, w)};
    else if constexpr( c == category::int32x8 ) return mask8 {_mm256_cmpeq_epi32_mask(v, w)};
    else if constexpr( c == category::int32x4 ) return mask8 {_mm_cmpeq_epi32_mask(v, w)};
    else if constexpr( c == category::int16x32 ) return mask32 {_mm512_cmpeq_epi16_mask(v, w)};
    else if constexpr( c == category::int16x16 ) return mask16 {_mm256_cmpeq_epi16_mask(v, w)};
    else if constexpr( c == category::int16x8 ) return mask8 {_mm_cmpeq_epi16_mask(v, w)};
    else if constexpr( c == category::int8x64 ) return mask64 {_mm512_cmpeq_epi8_mask(v, w)};
    else if constexpr( c == category::int8x32 ) return mask32 {_mm256_cmpeq_epi8_mask(v, w)};
    else if constexpr( c == category::int8x16 ) return mask16 {_mm_cmpeq_epi8_mask(v, w)};
  }
  else
  {
    constexpr auto f = to_integer(cmp_flt::eq_oq);

    if constexpr( c == category::float32x8 ) return _mm256_cmp_ps(v, w, f);
    else if constexpr( c == category::float64x4 ) return _mm256_cmp_pd(v, w, f);
    else if constexpr( c == category::float32x4 ) return _mm_cmpeq_ps(v, w);
    else if constexpr( c == category::float64x2 ) return _mm_cmpeq_pd(v, w);
    else
    {
      constexpr auto use_avx2 = current_api >= avx2;
      constexpr auto eq       = []<typename E>(E const      &e, E const      &f)
      { return as_logical_t<E>(e == f); };

      if constexpr( use_avx2 && c == category::int64x4 ) return _mm256_cmpeq_epi64(v, w);
      else if constexpr( use_avx2 && c == category::uint64x4 ) return _mm256_cmpeq_epi64(v, w);
      else if constexpr( use_avx2 && c == category::int32x8 ) return _mm256_cmpeq_epi32(v, w);
      else if constexpr( use_avx2 && c == category::uint32x8 ) return _mm256_cmpeq_epi32(v, w);
      else if constexpr( use_avx2 && c == category::int16x16 ) return _mm256_cmpeq_epi16(v, w);
      else if constexpr( use_avx2 && c == category::uint16x16 ) return _mm256_cmpeq_epi16(v, w);
      else if constexpr( use_avx2 && c == category::int8x32 ) return _mm256_cmpeq_epi8(v, w);
      else if constexpr( use_avx2 && c == category::uint8x32 ) return _mm256_cmpeq_epi8(v, w);
      else if constexpr( c == category::int64x2 )
      {
        if constexpr( N::value == 2 )
          return as_logical_t<wide<T, N>> {v.get(0) == w.get(0), v.get(1) == w.get(1)};
        else return as_logical_t<wide<T, N>> {v.get(0) == w.get(0)};
      }
      else if constexpr( c == category::int32x4 ) return _mm_cmpeq_epi32(v, w);
      else if constexpr( c == category::int16x8 ) return _mm_cmpeq_epi16(v, w);
      else if constexpr( c == category::int8x16 ) return _mm_cmpeq_epi8(v, w);
      else if constexpr( c == category::uint64x2 )
      {
        if constexpr( N::value == 2 )
          return as_logical_t<wide<T, N>> {v.get(0) == w.get(0), v.get(1) == w.get(1)};
        else return as_logical_t<wide<T, N>> {v.get(0) == w.get(0)};
      }
      else if constexpr( c == category::uint32x4 ) return _mm_cmpeq_epi32(v, w);
      else if constexpr( c == category::uint16x8 ) return _mm_cmpeq_epi16(v, w);
      else if constexpr( c == category::uint8x16 ) return _mm_cmpeq_epi8(v, w);
      else return aggregate(eq, v, w);
    }
  }
}

template<real_value T, typename N>
EVE_FORCEINLINE auto
self_eq(logical<wide<T, N>> v, logical<wide<T, N>> w) noexcept requires x86_abi<abi_t<T, N>>
{
  if constexpr( !abi_t<T, N>::is_wide_logical )
  {
    return logical<wide<T, N>> {~(v.storage() ^ w.storage())};
  }
  else
  {
    // AVX has a bad == for integers so we use XOR
    if constexpr( current_api == avx ) return bit_cast(~v.bits() ^ w.bits(), as(v));
    else return bit_cast(v.bits() == w.bits(), as(v));
  }
}

//================================================================================================
template<real_value T, typename N>
EVE_FORCEINLINE as_logical_t<wide<T, N>>
                self_neq(wide<T, N> v, wide<T, N> w) noexcept requires x86_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  constexpr auto f = to_integer(cmp_flt::neq_uq);

  if constexpr( current_api >= avx512 )
  {
    if constexpr( c == category::float32x16 ) return mask16 {_mm512_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float32x8 ) return mask8 {_mm256_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float32x4 ) return mask8 {_mm_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float64x8 ) return mask8 {_mm512_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::float64x4 ) return mask8 {_mm256_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::float64x2 ) return mask8 {_mm_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::uint64x8 ) return mask8 {_mm512_cmpneq_epu64_mask(v, w)};
    else if constexpr( c == category::uint64x4 ) return mask8 {_mm256_cmpneq_epu64_mask(v, w)};
    else if constexpr( c == category::uint64x2 ) return mask8 {_mm_cmpneq_epu64_mask(v, w)};
    else if constexpr( c == category::uint32x16 ) return mask16 {_mm512_cmpneq_epu32_mask(v, w)};
    else if constexpr( c == category::uint32x8 ) return mask8 {_mm256_cmpneq_epu32_mask(v, w)};
    else if constexpr( c == category::uint32x4 ) return mask8 {_mm_cmpneq_epu32_mask(v, w)};
    else if constexpr( c == category::uint16x32 ) return mask32 {_mm512_cmpneq_epu16_mask(v, w)};
    else if constexpr( c == category::uint16x16 ) return mask16 {_mm256_cmpneq_epu16_mask(v, w)};
    else if constexpr( c == category::uint16x8 ) return mask8 {_mm_cmpneq_epu16_mask(v, w)};
    else if constexpr( c == category::uint8x64 ) return mask64 {_mm512_cmpneq_epu8_mask(v, w)};
    else if constexpr( c == category::uint8x32 ) return mask32 {_mm256_cmpneq_epu8_mask(v, w)};
    else if constexpr( c == category::uint8x16 ) return mask16 {_mm_cmpneq_epu8_mask(v, w)};
    else if constexpr( c == category::int64x8 ) return mask8 {_mm512_cmpneq_epi64_mask(v, w)};
    else if constexpr( c == category::int64x4 ) return mask8 {_mm256_cmpneq_epi64_mask(v, w)};
    else if constexpr( c == category::int64x2 ) return mask8 {_mm_cmpneq_epi64_mask(v, w)};
    else if constexpr( c == category::int32x16 ) return mask16 {_mm512_cmpneq_epi32_mask(v, w)};
    else if constexpr( c == category::int32x8 ) return mask8 {_mm256_cmpneq_epi32_mask(v, w)};
    else if constexpr( c == category::int32x4 ) return mask8 {_mm_cmpneq_epi32_mask(v, w)};
    else if constexpr( c == category::int16x32 ) return mask32 {_mm512_cmpneq_epi16_mask(v, w)};
    else if constexpr( c == category::int16x16 ) return mask16 {_mm256_cmpneq_epi16_mask(v, w)};
    else if constexpr( c == category::int16x8 ) return mask8 {_mm_cmpneq_epi16_mask(v, w)};
    else if constexpr( c == category::int8x64 ) return mask64 {_mm512_cmpneq_epi8_mask(v, w)};
    else if constexpr( c == category::int8x32 ) return mask32 {_mm256_cmpneq_epi8_mask(v, w)};
    else if constexpr( c == category::int8x16 ) return mask16 {_mm_cmpneq_epi8_mask(v, w)};
  }
  else
  {
    if constexpr( c == category::float32x8 ) return _mm256_cmp_ps(v, w, f);
    else if constexpr( c == category::float64x4 ) return _mm256_cmp_pd(v, w, f);
    else if constexpr( c == category::float32x4 ) return _mm_cmpneq_ps(v, w);
    else if constexpr( c == category::float64x2 ) return _mm_cmpneq_pd(v, w);
    else return !(v == w);
  }
}

template<real_value T, typename N>
EVE_FORCEINLINE auto
self_neq(logical<wide<T, N>> v, logical<wide<T, N>> w) noexcept requires x86_abi<abi_t<T, N>>
{
  if constexpr( !abi_t<T, N>::is_wide_logical )
  {
    return logical<wide<T, N>> {v.storage() ^ w.storage()};
  }
  else { return bit_cast(v.bits() ^ w.bits(), as(v)); }
}

//================================================================================================
template<real_value T, typename N>
EVE_FORCEINLINE as_logical_t<wide<T, N>>
                self_less(wide<T, N> v, wide<T, N> w) noexcept requires x86_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  constexpr auto f = to_integer(cmp_flt::lt_oq);

  if constexpr( current_api >= avx512 )
  {
    if constexpr( c == category::float32x16 ) return mask16 {_mm512_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float32x8 ) return mask8 {_mm256_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float32x4 ) return mask8 {_mm_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float64x8 ) return mask8 {_mm512_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::float64x4 ) return mask8 {_mm256_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::float64x2 ) return mask8 {_mm_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::uint64x8 ) return mask8 {_mm512_cmplt_epu64_mask(v, w)};
    else if constexpr( c == category::uint64x4 ) return mask8 {_mm256_cmplt_epu64_mask(v, w)};
    else if constexpr( c == category::uint64x2 ) return mask8 {_mm_cmplt_epu64_mask(v, w)};
    else if constexpr( c == category::uint32x16 ) return mask16 {_mm512_cmplt_epu32_mask(v, w)};
    else if constexpr( c == category::uint32x8 ) return mask8 {_mm256_cmplt_epu32_mask(v, w)};
    else if constexpr( c == category::uint32x4 ) return mask8 {_mm_cmplt_epu32_mask(v, w)};
    else if constexpr( c == category::uint16x32 ) return mask32 {_mm512_cmplt_epu16_mask(v, w)};
    else if constexpr( c == category::uint16x16 ) return mask16 {_mm256_cmplt_epu16_mask(v, w)};
    else if constexpr( c == category::uint16x8 ) return mask8 {_mm_cmplt_epu16_mask(v, w)};
    else if constexpr( c == category::uint8x64 ) return mask64 {_mm512_cmplt_epu8_mask(v, w)};
    else if constexpr( c == category::uint8x32 ) return mask32 {_mm256_cmplt_epu8_mask(v, w)};
    else if constexpr( c == category::uint8x16 ) return mask16 {_mm_cmplt_epu8_mask(v, w)};
    else if constexpr( c == category::int64x8 ) return mask8 {_mm512_cmplt_epi64_mask(v, w)};
    else if constexpr( c == category::int64x4 ) return mask8 {_mm256_cmplt_epi64_mask(v, w)};
    else if constexpr( c == category::int64x2 ) return mask8 {_mm_cmplt_epi64_mask(v, w)};
    else if constexpr( c == category::int32x16 ) return mask16 {_mm512_cmplt_epi32_mask(v, w)};
    else if constexpr( c == category::int32x8 ) return mask8 {_mm256_cmplt_epi32_mask(v, w)};
    else if constexpr( c == category::int32x4 ) return mask8 {_mm_cmplt_epi32_mask(v, w)};
    else if constexpr( c == category::int16x32 ) return mask32 {_mm512_cmplt_epi16_mask(v, w)};
    else if constexpr( c == category::int16x16 ) return mask16 {_mm256_cmplt_epi16_mask(v, w)};
    else if constexpr( c == category::int16x8 ) return mask8 {_mm_cmplt_epi16_mask(v, w)};
    else if constexpr( c == category::int8x64 ) return mask64 {_mm512_cmplt_epi8_mask(v, w)};
    else if constexpr( c == category::int8x32 ) return mask32 {_mm256_cmplt_epi8_mask(v, w)};
    else if constexpr( c == category::int8x16 ) return mask16 {_mm_cmplt_epi8_mask(v, w)};
  }
  else
  {
    if constexpr( c == category::float32x8 ) return _mm256_cmp_ps(v, w, f);
    else if constexpr( c == category::float64x4 ) return _mm256_cmp_pd(v, w, f);
    else if constexpr( c == category::float32x4 ) return _mm_cmplt_ps(v, w);
    else if constexpr( c == category::float64x2 ) return _mm_cmplt_pd(v, w);
    else
    {
      constexpr auto use_avx2 = current_api >= avx2;
      constexpr auto lt       = []<typename E>(E e, E f) { return as_logical_t<E>(e < f); };

      [[maybe_unused]] auto unsigned_cmp = [](auto v, auto w)
      {
        using l_t     = logical<wide<T, N>>;
        auto const sm = signmask(as<as_integer_t<wide<T, N>, signed>>());
        return bit_cast((bit_cast(v, as(sm)) - sm) < (bit_cast(w, as(sm)) - sm), as<l_t> {});
      };

      if constexpr( use_avx2 && c == category::int64x4 ) return _mm256_cmpgt_epi64(w, v);
      else if constexpr( use_avx2 && c == category::uint64x4 ) return unsigned_cmp(v, w);
      else if constexpr( use_avx2 && c == category::int32x8 ) return _mm256_cmpgt_epi32(w, v);
      else if constexpr( use_avx2 && c == category::uint32x8 ) return unsigned_cmp(v, w);
      else if constexpr( use_avx2 && c == category::int16x16 ) return _mm256_cmpgt_epi16(w, v);
      else if constexpr( use_avx2 && c == category::uint16x16 ) return unsigned_cmp(v, w);
      else if constexpr( use_avx2 && c == category::int8x32 ) return _mm256_cmpgt_epi8(w, v);
      else if constexpr( use_avx2 && c == category::uint8x32 ) return unsigned_cmp(v, w);
      else if constexpr( c == category::int64x2 ) return map(lt, v, w);
      else if constexpr( c == category::int32x4 ) return _mm_cmplt_epi32(v, w);
      else if constexpr( c == category::int16x8 ) return _mm_cmplt_epi16(v, w);
      else if constexpr( c == category::int8x16 ) return _mm_cmplt_epi8(v, w);
      else if constexpr( c == category::uint64x2 ) return map(lt, v, w);
      else if constexpr( c == category::uint32x4 ) return unsigned_cmp(v, w);
      else if constexpr( c == category::uint16x8 ) return unsigned_cmp(v, w);
      else if constexpr( c == category::uint8x16 ) return unsigned_cmp(v, w);
      else return aggregate(lt, v, w);
    }
  }
}

//================================================================================================
template<real_value T, typename N>
EVE_FORCEINLINE as_logical_t<wide<T, N>>
                self_greater(wide<T, N> v, wide<T, N> w) noexcept requires x86_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  constexpr auto f = to_integer(cmp_flt::gt_oq);

  if constexpr( current_api >= avx512 )
  {
    if constexpr( c == category::float32x16 ) return mask16 {_mm512_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float32x8 ) return mask8 {_mm256_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float32x4 ) return mask8 {_mm_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float64x8 ) return mask8 {_mm512_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::float64x4 ) return mask8 {_mm256_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::float64x2 ) return mask8 {_mm_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::uint64x8 ) return mask8 {_mm512_cmpgt_epu64_mask(v, w)};
    else if constexpr( c == category::uint64x4 ) return mask8 {_mm256_cmpgt_epu64_mask(v, w)};
    else if constexpr( c == category::uint64x2 ) return mask8 {_mm_cmpgt_epu64_mask(v, w)};
    else if constexpr( c == category::uint32x16 ) return mask16 {_mm512_cmpgt_epu32_mask(v, w)};
    else if constexpr( c == category::uint32x8 ) return mask8 {_mm256_cmpgt_epu32_mask(v, w)};
    else if constexpr( c == category::uint32x4 ) return mask8 {_mm_cmpgt_epu32_mask(v, w)};
    else if constexpr( c == category::uint16x32 ) return mask32 {_mm512_cmpgt_epu16_mask(v, w)};
    else if constexpr( c == category::uint16x16 ) return mask16 {_mm256_cmpgt_epu16_mask(v, w)};
    else if constexpr( c == category::uint16x8 ) return mask8 {_mm_cmpgt_epu16_mask(v, w)};
    else if constexpr( c == category::uint8x64 ) return mask64 {_mm512_cmpgt_epu8_mask(v, w)};
    else if constexpr( c == category::uint8x32 ) return mask32 {_mm256_cmpgt_epu8_mask(v, w)};
    else if constexpr( c == category::uint8x16 ) return mask16 {_mm_cmpgt_epu8_mask(v, w)};
    else if constexpr( c == category::int64x8 ) return mask8 {_mm512_cmpgt_epi64_mask(v, w)};
    else if constexpr( c == category::int64x4 ) return mask8 {_mm256_cmpgt_epi64_mask(v, w)};
    else if constexpr( c == category::int64x2 ) return mask8 {_mm_cmpgt_epi64_mask(v, w)};
    else if constexpr( c == category::int32x16 ) return mask16 {_mm512_cmpgt_epi32_mask(v, w)};
    else if constexpr( c == category::int32x8 ) return mask8 {_mm256_cmpgt_epi32_mask(v, w)};
    else if constexpr( c == category::int32x4 ) return mask8 {_mm_cmpgt_epi32_mask(v, w)};
    else if constexpr( c == category::int16x32 ) return mask32 {_mm512_cmpgt_epi16_mask(v, w)};
    else if constexpr( c == category::int16x16 ) return mask16 {_mm256_cmpgt_epi16_mask(v, w)};
    else if constexpr( c == category::int16x8 ) return mask8 {_mm_cmpgt_epi16_mask(v, w)};
    else if constexpr( c == category::int8x64 ) return mask64 {_mm512_cmpgt_epi8_mask(v, w)};
    else if constexpr( c == category::int8x32 ) return mask32 {_mm256_cmpgt_epi8_mask(v, w)};
    else if constexpr( c == category::int8x16 ) return mask16 {_mm_cmpgt_epi8_mask(v, w)};
  }
  else
  {
    if constexpr( c == category::float32x8 ) return _mm256_cmp_ps(v, w, f);
    else if constexpr( c == category::float64x4 ) return _mm256_cmp_pd(v, w, f);
    else if constexpr( c == category::float32x4 ) return _mm_cmpgt_ps(v, w);
    else if constexpr( c == category::float64x2 ) return _mm_cmpgt_pd(v, w);
    else
    {
      constexpr auto use_avx2 = current_api >= avx2;
      constexpr auto use_sse4 = current_api >= sse4_2;

      constexpr auto gt = []<typename E>(E e, E f) { return as_logical_t<E>(e > f); };

      [[maybe_unused]] auto unsigned_cmp = [](auto v, auto w)
      {
        using l_t     = logical<wide<T, N>>;
        auto const sm = signmask(as<as_integer_t<wide<T, N>, signed>>());
        return bit_cast((bit_cast(v, as(sm)) - sm) > (bit_cast(w, as(sm)) - sm), as<l_t> {});
      };

      if constexpr( use_avx2 && c == category::int64x4 ) return _mm256_cmpgt_epi64(v, w);
      else if constexpr( use_avx2 && c == category::uint64x4 ) return unsigned_cmp(v, w);
      else if constexpr( use_avx2 && c == category::int32x8 ) return _mm256_cmpgt_epi32(v, w);
      else if constexpr( use_avx2 && c == category::uint32x8 ) return unsigned_cmp(v, w);
      else if constexpr( use_avx2 && c == category::int16x16 ) return _mm256_cmpgt_epi16(v, w);
      else if constexpr( use_avx2 && c == category::uint16x16 ) return unsigned_cmp(v, w);
      else if constexpr( use_avx2 && c == category::int8x32 ) return _mm256_cmpgt_epi8(v, w);
      else if constexpr( use_avx2 && c == category::uint8x32 ) return unsigned_cmp(v, w);
      else if constexpr( use_sse4 && c == category::int64x2 ) return _mm_cmpgt_epi64(v, w);
      else if constexpr( c == category::int64x2 ) return map(gt, v, w);
      else if constexpr( c == category::int32x4 ) return _mm_cmpgt_epi32(v, w);
      else if constexpr( c == category::int16x8 ) return _mm_cmpgt_epi16(v, w);
      else if constexpr( c == category::int8x16 ) return _mm_cmpgt_epi8(v, w);
      else if constexpr( c == category::uint64x2 ) return unsigned_cmp(v, w);
      else if constexpr( c == category::uint32x4 ) return unsigned_cmp(v, w);
      else if constexpr( c == category::uint16x8 ) return unsigned_cmp(v, w);
      else if constexpr( c == category::uint8x16 ) return unsigned_cmp(v, w);
      else return aggregate(gt, v, w);
    }
  }
}

//================================================================================================
template<real_value T, typename N>
EVE_FORCEINLINE as_logical_t<wide<T, N>>
                self_geq(wide<T, N> v, wide<T, N> w) noexcept requires x86_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  constexpr auto f = to_integer(cmp_flt::ge_oq);

  if constexpr( current_api >= avx512 )
  {
    if constexpr( c == category::float32x16 ) return mask16 {_mm512_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float32x8 ) return mask8 {_mm256_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float32x4 ) return mask8 {_mm_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float64x8 ) return mask8 {_mm512_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::float64x4 ) return mask8 {_mm256_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::float64x2 ) return mask8 {_mm_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::uint64x8 ) return mask8 {_mm512_cmpge_epu64_mask(v, w)};
    else if constexpr( c == category::uint64x4 ) return mask8 {_mm256_cmpge_epu64_mask(v, w)};
    else if constexpr( c == category::uint64x2 ) return mask8 {_mm_cmpge_epu64_mask(v, w)};
    else if constexpr( c == category::uint32x16 ) return mask16 {_mm512_cmpge_epu32_mask(v, w)};
    else if constexpr( c == category::uint32x8 ) return mask8 {_mm256_cmpge_epu32_mask(v, w)};
    else if constexpr( c == category::uint32x4 ) return mask8 {_mm_cmpge_epu32_mask(v, w)};
    else if constexpr( c == category::uint16x32 ) return mask32 {_mm512_cmpge_epu16_mask(v, w)};
    else if constexpr( c == category::uint16x16 ) return mask16 {_mm256_cmpge_epu16_mask(v, w)};
    else if constexpr( c == category::uint16x8 ) return mask8 {_mm_cmpge_epu16_mask(v, w)};
    else if constexpr( c == category::uint8x64 ) return mask64 {_mm512_cmpge_epu8_mask(v, w)};
    else if constexpr( c == category::uint8x32 ) return mask32 {_mm256_cmpge_epu8_mask(v, w)};
    else if constexpr( c == category::uint8x16 ) return mask16 {_mm_cmpge_epu8_mask(v, w)};
    else if constexpr( c == category::int64x8 ) return mask8 {_mm512_cmpge_epi64_mask(v, w)};
    else if constexpr( c == category::int64x4 ) return mask8 {_mm256_cmpge_epi64_mask(v, w)};
    else if constexpr( c == category::int64x2 ) return mask8 {_mm_cmpge_epi64_mask(v, w)};
    else if constexpr( c == category::int32x16 ) return mask16 {_mm512_cmpge_epi32_mask(v, w)};
    else if constexpr( c == category::int32x8 ) return mask8 {_mm256_cmpge_epi32_mask(v, w)};
    else if constexpr( c == category::int32x4 ) return mask8 {_mm_cmpge_epi32_mask(v, w)};
    else if constexpr( c == category::int16x32 ) return mask32 {_mm512_cmpge_epi16_mask(v, w)};
    else if constexpr( c == category::int16x16 ) return mask16 {_mm256_cmpge_epi16_mask(v, w)};
    else if constexpr( c == category::int16x8 ) return mask8 {_mm_cmpge_epi16_mask(v, w)};
    else if constexpr( c == category::int8x64 ) return mask64 {_mm512_cmpge_epi8_mask(v, w)};
    else if constexpr( c == category::int8x32 ) return mask32 {_mm256_cmpge_epi8_mask(v, w)};
    else if constexpr( c == category::int8x16 ) return mask16 {_mm_cmpge_epi8_mask(v, w)};
  }
  else
  {
    if constexpr( c == category::float32x8 ) return _mm256_cmp_ps(v, w, f);
    else if constexpr( c == category::float64x4 ) return _mm256_cmp_pd(v, w, f);
    else if constexpr( c == category::float32x4 ) return _mm_cmpge_ps(v, w);
    else if constexpr( c == category::float64x2 ) return _mm_cmpge_pd(v, w);
    else return !(v < w);
  }
}

//================================================================================================
template<real_value T, typename N>
EVE_FORCEINLINE as_logical_t<wide<T, N>>
                self_leq(wide<T, N> v, wide<T, N> w) noexcept requires x86_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  constexpr auto f = to_integer(cmp_flt::le_oq);

  if constexpr( current_api >= avx512 )
  {
    if constexpr( c == category::float32x16 ) return mask16 {_mm512_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float32x8 ) return mask8 {_mm256_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float32x4 ) return mask8 {_mm_cmp_ps_mask(v, w, f)};
    else if constexpr( c == category::float64x8 ) return mask8 {_mm512_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::float64x4 ) return mask8 {_mm256_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::float64x2 ) return mask8 {_mm_cmp_pd_mask(v, w, f)};
    else if constexpr( c == category::uint64x8 ) return mask8 {_mm512_cmple_epu64_mask(v, w)};
    else if constexpr( c == category::uint64x4 ) return mask8 {_mm256_cmple_epu64_mask(v, w)};
    else if constexpr( c == category::uint64x2 ) return mask8 {_mm_cmple_epu64_mask(v, w)};
    else if constexpr( c == category::uint32x16 ) return mask16 {_mm512_cmple_epu32_mask(v, w)};
    else if constexpr( c == category::uint32x8 ) return mask8 {_mm256_cmple_epu32_mask(v, w)};
    else if constexpr( c == category::uint32x4 ) return mask8 {_mm_cmple_epu32_mask(v, w)};
    else if constexpr( c == category::uint16x32 ) return mask32 {_mm512_cmple_epu16_mask(v, w)};
    else if constexpr( c == category::uint16x16 ) return mask16 {_mm256_cmple_epu16_mask(v, w)};
    else if constexpr( c == category::uint16x8 ) return mask8 {_mm_cmple_epu16_mask(v, w)};
    else if constexpr( c == category::uint8x64 ) return mask64 {_mm512_cmple_epu8_mask(v, w)};
    else if constexpr( c == category::uint8x32 ) return mask32 {_mm256_cmple_epu8_mask(v, w)};
    else if constexpr( c == category::uint8x16 ) return mask16 {_mm_cmple_epu8_mask(v, w)};
    else if constexpr( c == category::int64x8 ) return mask8 {_mm512_cmple_epi64_mask(v, w)};
    else if constexpr( c == category::int64x4 ) return mask8 {_mm256_cmple_epi64_mask(v, w)};
    else if constexpr( c == category::int64x2 ) return mask8 {_mm_cmple_epi64_mask(v, w)};
    else if constexpr( c == category::int32x16 ) return mask16 {_mm512_cmple_epi32_mask(v, w)};
    else if constexpr( c == category::int32x8 ) return mask8 {_mm256_cmple_epi32_mask(v, w)};
    else if constexpr( c == category::int32x4 ) return mask8 {_mm_cmple_epi32_mask(v, w)};
    else if constexpr( c == category::int16x32 ) return mask32 {_mm512_cmple_epi16_mask(v, w)};
    else if constexpr( c == category::int16x16 ) return mask16 {_mm256_cmple_epi16_mask(v, w)};
    else if constexpr( c == category::int16x8 ) return mask8 {_mm_cmple_epi16_mask(v, w)};
    else if constexpr( c == category::int8x64 ) return mask64 {_mm512_cmple_epi8_mask(v, w)};
    else if constexpr( c == category::int8x32 ) return mask32 {_mm256_cmple_epi8_mask(v, w)};
    else if constexpr( c == category::int8x16 ) return mask16 {_mm_cmple_epi8_mask(v, w)};
  }
  else
  {
    if constexpr( c == category::float32x8 ) return _mm256_cmp_ps(v, w, f);
    else if constexpr( c == category::float64x4 ) return _mm256_cmp_pd(v, w, f);
    else if constexpr( c == category::float32x4 ) return _mm_cmple_ps(v, w);
    else if constexpr( c == category::float64x2 ) return _mm_cmple_pd(v, w);
    else return !(v > w);
  }
}
}
