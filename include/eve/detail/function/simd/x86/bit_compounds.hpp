//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/function/bit_cast.hpp>

#include <concepts>

namespace eve::detail
{
  //================================================================================================
  // <<=
  //================================================================================================
  template<integral_real_scalar_value T, typename N, integral_real_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shr(wide<T,N>& v, U s) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c          = categorize<wide<T, N>>();
    constexpr bool is_avx2    = current_api >= avx2;
    constexpr bool is_avx512  = current_api >= avx512;

          if constexpr(              c == category::int64x8  ) v = _mm512_srai_epi64(v,s);
    else  if constexpr(              c == category::int32x16 ) v = _mm512_srai_epi32(v,s);
    else  if constexpr(              c == category::int16x32 ) v = _mm512_srai_epi16(v,s);
    else  if constexpr(              c == category::uint64x8 ) v = _mm512_srli_epi64(v,s);
    else  if constexpr(              c == category::uint32x16) v = _mm512_srli_epi32(v,s);
    else  if constexpr(              c == category::uint16x32) v = _mm512_srli_epi16(v,s);
    else  if constexpr( is_avx2   && c == category::int32x8  ) v = _mm256_srai_epi32(v,s);
    else  if constexpr( is_avx2   && c == category::int16x16 ) v = _mm256_srai_epi16(v,s);
    else  if constexpr( is_avx2   && c == category::uint64x4 ) v = _mm256_srli_epi64(v,s);
    else  if constexpr( is_avx2   && c == category::uint32x8 ) v = _mm256_srli_epi32(v,s);
    else  if constexpr( is_avx2   && c == category::uint16x16) v = _mm256_srli_epi16(v,s);
    else  if constexpr( is_avx512 && c == category::int64x2  ) v = _mm_srai_epi64(v,s);
    else  if constexpr(              c == category::int32x4  ) v = _mm_srai_epi32(v,s);
    else  if constexpr(              c == category::int16x8  ) v = _mm_srai_epi16(v,s);
    else  if constexpr(              c == category::uint64x2 ) v = _mm_srli_epi64(v,s);
    else  if constexpr(              c == category::uint32x4 ) v = _mm_srli_epi32(v,s);
    else  if constexpr(              c == category::uint16x8 ) v = _mm_srli_epi16(v,s);
    else
    {
      v = map( []<typename V>(V const& a, auto b) { return static_cast<V>(a >> b); }, v, s);
    }

    return v;
  }

  template<integral_real_scalar_value T, typename N, integral_real_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shr(wide<T,N>& v, wide<U,N> s) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c         = categorize<wide<T, N>>();
    constexpr bool is_avx2   = current_api >= avx2;
    constexpr bool is_avx512 = current_api >= avx512;

    [[maybe_unused]] auto shft = []<typename V>(V a, auto b)
    {
      auto[la,ha] = a.slice();
      auto[lb,hb] = b.slice();

      la >>= lb;
      ha >>= hb;

      return  V{la,ha};
    };

          if constexpr( is_avx512    && c == category::int64x2  ) v = _mm_srav_epi64(v, s);
    else  if constexpr( is_avx2      && c == category::int32x4  ) v = _mm_srav_epi32(v, s);
    else  if constexpr( is_avx512    && c == category::int16x8  ) v = _mm_srav_epi16(v, s);
    else  if constexpr( is_avx2      && c == category::uint64x2 ) v = _mm_srlv_epi64(v, s);
    else  if constexpr( is_avx2      && c == category::uint32x4 ) v = _mm_srlv_epi32(v, s);
    else  if constexpr( is_avx512    && c == category::uint16x8 ) v = _mm_srlv_epi16(v, s);
    else  if constexpr( is_avx512    && c == category::int64x4  ) v = _mm256_srav_epi64(v, s);
    else  if constexpr( is_avx2      && c == category::int32x8  ) v = _mm256_srav_epi32(v, s);
    else  if constexpr( is_avx512    && c == category::int16x16 ) v = _mm256_srav_epi16(v, s);
    else  if constexpr( is_avx2      && c == category::uint64x4 ) v = _mm256_srlv_epi64(v, s);
    else  if constexpr( is_avx2      && c == category::uint32x8 ) v = _mm256_srlv_epi32(v, s);
    else  if constexpr( is_avx512    && c == category::uint16x16) v = _mm256_srlv_epi16(v, s);
    else  if constexpr(                 c == category::int64x8  ) v = _mm512_srav_epi64(v, s);
    else  if constexpr(                 c == category::int32x16 ) v = _mm512_srav_epi32(v, s);
    else  if constexpr(                 c == category::int16x32 ) v = _mm512_srav_epi16(v, s);
    else  if constexpr(                 c == category::uint64x8 ) v = _mm512_srlv_epi64(v, s);
    else  if constexpr(                 c == category::uint32x16) v = _mm512_srlv_epi32(v, s);
    else  if constexpr(                 c == category::uint16x32) v = _mm512_srlv_epi16(v, s);
    else
    {
      v = map( []<typename V>(V a, auto b) { return static_cast<V>(a >> b); }, v, s);
    }

    return v;
  }

  //================================================================================================
  // <<=
  //================================================================================================
  template<integral_real_scalar_value T, typename N, integral_real_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shl(wide<T,N>& v, U s) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
    constexpr bool is_avx2 = current_api >= avx2;

    [[maybe_unused]] auto shft = [](auto a, auto b )
    {
      using i16_t = wide<std::uint16_t, fixed<N::value/2>>;

      i16_t const masklow(0xff);
      i16_t const maskhi (0xff00);
      auto const xx   =  bit_cast(a, as<i16_t>());
      auto const odd  = (xx << b) & masklow;
      auto const even = ((xx & maskhi) << b) & maskhi;

      return bit_cast(odd+even, as(a));
    };

          if constexpr( c == category::int64x8  ) v = _mm512_slli_epi64(v,s);
    else  if constexpr( c == category::int32x16 ) v = _mm512_slli_epi32(v,s);
    else  if constexpr( c == category::int16x32 ) v = _mm512_slli_epi16(v,s);
    else  if constexpr( c == category::uint64x8 ) v = _mm512_slli_epi64(v,s);
    else  if constexpr( c == category::uint32x16) v = _mm512_slli_epi32(v,s);
    else  if constexpr( c == category::uint16x32) v = _mm512_slli_epi16(v,s);
    else  if constexpr( c == category::int8x16  && N::value != 1) v = shft(v,s);
    else  if constexpr( c == category::uint8x16 && N::value != 1) v = shft(v,s);
    else  if constexpr( c == category::int64x2  ) v = _mm_slli_epi64(v,s);
    else  if constexpr( c == category::uint64x2 ) v = _mm_slli_epi64(v,s);
    else  if constexpr( c == category::int32x4  ) v = _mm_slli_epi32(v,s);
    else  if constexpr( c == category::uint32x4 ) v = _mm_slli_epi32(v,s);
    else  if constexpr( c == category::int16x8  ) v = _mm_slli_epi16(v,s);
    else  if constexpr( c == category::uint16x8 ) v = _mm_slli_epi16(v,s);
    else  if constexpr( sizeof(v) == 32 )
    {
      if constexpr( is_avx2 )
      {
              if constexpr( c == category::int64x4  ) v = _mm256_slli_epi64(v,s);
        else  if constexpr( c == category::int32x8  ) v = _mm256_slli_epi32(v,s);
        else  if constexpr( c == category::int16x16 ) v = _mm256_slli_epi16(v,s);
        else  if constexpr( c == category::int8x32  ) v = shft(v,s);
        else  if constexpr( c == category::uint64x4 ) v = _mm256_slli_epi64(v,s);
        else  if constexpr( c == category::uint32x8 ) v = _mm256_slli_epi32(v,s);
        else  if constexpr( c == category::uint16x16) v = _mm256_slli_epi16(v,s);
        else  if constexpr( c == category::uint8x32 ) v = shft(v,s);
      }
      else
      {
        auto[la,ha] = v.slice();
        la <<= s;
        ha <<= s;
        v = wide<T,N>{la,ha};
      }
    }
    else
    {
      v = map( []<typename V>(V a, auto b) { return static_cast<V>(a << b); }, v, s);
    }

    return v;
  }

  template<integral_real_scalar_value T, typename N, integral_real_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shl(wide<T,N>& v, wide<U,N> s) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
    constexpr bool is_avx2 = current_api >= avx2;

    [[maybe_unused]] auto shft = []<typename V>(V a, auto b)
    {
      auto[la,ha] = a.slice();
      auto[lb,hb] = b.slice();

      la <<= lb;
      ha <<= hb;

      return  V{la,ha};
    };

          if constexpr( is_avx2 && c == category::int64x4  ) v = _mm256_sllv_epi64(v, s);
    else  if constexpr( is_avx2 && c == category::int32x8  ) v = _mm256_sllv_epi32(v, s);
    else  if constexpr( is_avx2 && c == category::uint64x4 ) v = _mm256_sllv_epi64(v, s);
    else  if constexpr( is_avx2 && c == category::uint32x8 ) v = _mm256_sllv_epi32(v, s);
    else  if constexpr(            c == category::int64x8  ) v = _mm512_sllv_epi64(v, s);
    else  if constexpr(            c == category::int32x16 ) v = _mm512_sllv_epi32(v, s);
    else  if constexpr(            c == category::int16x32 ) v = _mm512_sllv_epi16(v, s);
    else  if constexpr(            c == category::uint64x8 ) v = _mm512_sllv_epi64(v, s);
    else  if constexpr(            c == category::uint32x16) v = _mm512_sllv_epi32(v, s);
    else  if constexpr(            c == category::uint16x32) v = _mm512_sllv_epi16(v, s);
    else
    {
      v = map( []<typename V>(V a, auto b) { return static_cast<V>(a << b); }, v, s);
    }

    return v;
  }

  //================================================================================================
  // &=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_bitand(wide<T, N> &self, U const &other) noexcept
  requires((sizeof(wide<T, N>) == sizeof(U)) || (sizeof(T) == sizeof(U))) && x86_abi<abi_t<T, N>>
  {
    using type = wide<T, N>;

    if constexpr( scalar_value<U> )
    {
      return self &= type{bit_cast(other, as<T> {})};
    }
    else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
    {
      const     auto bits = bit_cast(other, as<type> {});
      constexpr auto c    = categorize<type>();
      constexpr bool i    = match(c, category::integer_);

            if constexpr( c == category::float64x8        ) self = _mm512_and_pd(self, bits);
      else  if constexpr( c == category::float64x4        ) self = _mm256_and_pd(self, bits);
      else  if constexpr( c == category::float64x2        ) self = _mm_and_pd   (self, bits);
      else  if constexpr( c == category::float32x16       ) self = _mm512_and_ps(self, bits);
      else  if constexpr( c == category::float32x8        ) self = _mm256_and_ps(self, bits);
      else  if constexpr( c == category::float32x4        ) self = _mm_and_ps   (self, bits);
      else  if constexpr( i && std::same_as<abi_t<T, N>,x86_512_> ) self = _mm512_and_si512(self, bits);
      else  if constexpr( i && std::same_as<abi_t<T, N>,x86_256_> )
      {
        if constexpr  ( current_api >= avx2 ) self =  _mm256_and_si256(self, bits);
        else                                  self =  _mm256_castps_si256
                                                      ( _mm256_and_ps ( _mm256_castsi256_ps(self)
                                                                      , _mm256_castsi256_ps(bits)
                                                                      )
                                                      );
      }
      else  if constexpr  ( i && std::same_as<abi_t<T, N>,x86_128_> ) self = _mm_and_si128(self, bits);

      return self;
    }
  }

  //================================================================================================
  // |=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_bitor(wide<T, N> &self, U const &other) noexcept
      requires((sizeof(wide<T, N>) == sizeof(U)) || (sizeof(T) == sizeof(U))) && x86_abi<abi_t<T, N>>
  {
    using type = wide<T, N>;

    if constexpr( scalar_value<U> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as<T> {});
      return self_bitor(self, type {bit_other});
    }
    else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
    {
      auto bits = detail::bit_cast_(EVE_RETARGET(cpu_), other, as<type> {});
      constexpr auto c = categorize<type>();
      constexpr bool i = match(c, category::integer_);

            if constexpr  ( c == category::float64x8        ) self = _mm512_or_pd(self, bits);
      else  if constexpr  ( c == category::float64x4        ) self = _mm256_or_pd(self, bits);
      else  if constexpr  ( c == category::float64x2        ) self = _mm_or_pd   (self, bits);
      else  if constexpr  ( c == category::float32x16       ) self = _mm512_or_ps(self, bits);
      else  if constexpr  ( c == category::float32x8        ) self = _mm256_or_ps(self, bits);
      else  if constexpr  ( c == category::float32x4        ) self = _mm_or_ps   (self, bits);
      else  if constexpr  ( i && std::same_as<abi_t<T, N>,x86_512_> ) self = _mm512_or_si512(self, bits);
      else  if constexpr  ( i && std::same_as<abi_t<T, N>,x86_256_> )
      {
        if constexpr  ( current_api >= avx2 ) self =  _mm256_or_si256(self, bits);
        else                                  self =  _mm256_castps_si256
                                                      ( _mm256_or_ps ( _mm256_castsi256_ps(self)
                                                                      , _mm256_castsi256_ps(bits)
                                                                      )
                                                      );
      }
      else  if constexpr  ( i && std::same_as<abi_t<T, N>,x86_128_> ) self = _mm_or_si128(self, bits);

      return self;
    }
  }

  //================================================================================================
  // ^=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_bitxor(wide<T, N> &self, U const &other) noexcept
      requires((sizeof(wide<T, N>) == sizeof(U)) || (sizeof(T) == sizeof(U))) && x86_abi<abi_t<T, N>>
  {
    using type = wide<T, N>;

    if constexpr( scalar_value<U> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as<T> {});
      return self_bitxor(self, type {bit_other});
    }
    else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
    {
      auto bits = detail::bit_cast_(EVE_RETARGET(cpu_), other, as<type> {});
      constexpr auto c = categorize<type>();
      constexpr bool i = match(c, category::integer_);

            if constexpr  ( c == category::float64x8        ) self = _mm512_xor_pd(self, bits);
      else  if constexpr  ( c == category::float64x4        ) self = _mm256_xor_pd(self, bits);
      else  if constexpr  ( c == category::float64x2        ) self = _mm_xor_pd   (self, bits);
      else  if constexpr  ( c == category::float32x16       ) self = _mm512_xor_ps(self, bits);
      else  if constexpr  ( c == category::float32x8        ) self = _mm256_xor_ps(self, bits);
      else  if constexpr  ( c == category::float32x4        ) self = _mm_xor_ps   (self, bits);
      else  if constexpr  ( i && std::same_as<abi_t<T, N>,x86_512_> ) self = _mm512_xor_si512(self, bits);
      else  if constexpr  ( i && std::same_as<abi_t<T, N>,x86_256_> )
      {
        if constexpr  ( current_api >= avx2 ) self =  _mm256_xor_si256(self, bits);
        else                                  self =  _mm256_castps_si256
                                                      ( _mm256_xor_ps ( _mm256_castsi256_ps(self)
                                                                      , _mm256_castsi256_ps(bits)
                                                                      )
                                                      );
      }
      else  if constexpr  ( i && std::same_as<abi_t<T, N>,x86_128_> ) self = _mm_xor_si128(self, bits);

      return self;
    }
  }
}
