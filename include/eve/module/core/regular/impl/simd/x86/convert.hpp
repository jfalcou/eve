//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/interleave_shuffle.hpp>
#include <type_traits>

namespace eve::detail
{
//================================================================================================
// convert: logical -> logical
//================================================================================================
template<signed_integral_scalar_value T, typename N, signed_integral_scalar_value U>
EVE_FORCEINLINE logical<wide<U, N>>
convert_impl(EVE_SUPPORTS(sse2_), logical<wide<T, N>> v, as<logical<U>> const& tgt) noexcept
{
  using enum category;
  using out_t         = logical<wide<U, N>>;
  constexpr auto c_in = categorize<wide<T, N>>();

  //==============================================================================================
  // For non-wide logical, we only have to convert kmask
  if constexpr( !abi_t<T,N>::is_wide_logical )
  {
    using s_t = typename out_t::storage_type;
    return out_t(s_t {static_cast<typename s_t::type>(v.storage().value)});
  }
  //==============================================================================================
  // Common cases for 32/64->8, 64->16
  // The sizeof(U)/sizeof(T) > 2 case is handled by the generic implementation
  else if constexpr( sizeof(T) / sizeof(U) > 2 )
  {
    return convert(convert(v, as<logical<downgrade_t<as_integer_t<T, signed>>>> {}), tgt);
  }
  //==============================================================================================
  // Common cases for 8->16, 16->32, 32->64
  else if constexpr( sizeof(U) / sizeof(T) == 2 )
  {
    return bit_cast(interleave_shuffle(v, v), as<out_t> {});
  }
  //==============================================================================================
  // 16 bits cases
  else if constexpr( c_in == int16x8 && sizeof(U) == 1 ) return _mm_packs_epi16(v, v);
  else if constexpr( c_in == int16x16 && sizeof(U) == 1 )
    return _mm_packs_epi16(v.slice(lower_), v.slice(upper_));
  //==============================================================================================
  // 32 bits cases
  else if constexpr( c_in == int32x4 && sizeof(U) == 2 ) return _mm_packs_epi32(v, v);
  else if constexpr( c_in == int32x8 && sizeof(U) == 2 )
    return _mm_packs_epi32(v.slice(lower_), v.slice(upper_));
  //==============================================================================================
  // All other cases go to the generic implementation
  else return convert_impl(EVE_RETARGET(cpu_), v, tgt);
}

//================================================================================================
// convert: float64 -> U
//================================================================================================
template<typename N, arithmetic_scalar_value U>
EVE_FORCEINLINE wide<U, N>
                convert_impl(EVE_SUPPORTS(sse2_), wide<double, N> v, as<U> const &tgt) noexcept
{
  using enum category;
  constexpr auto c_i  = categorize<wide<double, N>>();
  constexpr auto c_o  = categorize<wide<U, N>>();
  constexpr auto a512 = current_api >= avx512;
  using t_t           = as<upgrade_t<as_integer_t<U, signed>>>;

  if constexpr( c_i == float64x2 && c_o == float32x4 ) return _mm_cvtpd_ps(v);
  else if constexpr( c_i == float64x4 && c_o == float32x4 ) return _mm256_cvtpd_ps(v);
  else if constexpr( c_i == float64x8 && c_o == float32x8 ) return _mm512_cvtpd_ps(v);
  else if constexpr( c_i == float64x2 && c_o == int64x2 && a512 ) return _mm_cvttpd_epi64(v);
  else if constexpr( c_i == float64x4 && c_o == int64x4 && a512 ) return _mm256_cvttpd_epi64(v);
  else if constexpr( c_i == float64x8 && c_o == int64x8 ) return _mm512_cvttpd_epi64(v);
  else if constexpr( c_i == float64x2 && c_o == uint64x2 && a512 ) return _mm_cvttpd_epu64(v);
  else if constexpr( c_i == float64x4 && c_o == uint64x4 && a512 ) return _mm256_cvttpd_epu64(v);
  else if constexpr( c_i == float64x8 && c_o == uint64x8 ) return _mm512_cvttpd_epu64(v);
  else if constexpr( c_i == float64x2 && c_o == int32x4 ) return _mm_cvttpd_epi32(v);
  else if constexpr( c_i == float64x4 && c_o == int32x4 ) return _mm256_cvttpd_epi32(v);
  else if constexpr( c_i == float64x8 && c_o == int32x8 ) return _mm512_cvttpd_epi32(v);
  else if constexpr( c_i == float64x2 && c_o == uint32x4 && a512 ) return _mm_cvttpd_epu32(v);
  else if constexpr( c_i == float64x8 && c_o == uint32x8 ) return _mm512_cvttpd_epu32(v);
  else if constexpr( sizeof(U) <= 2 ) return convert(convert(v, t_t {}), tgt);
  else return convert_impl(EVE_RETARGET(cpu_), v, tgt);
}

//================================================================================================
// convert: float32 -> U
//================================================================================================
template<typename N, arithmetic_scalar_value U>
EVE_FORCEINLINE wide<U, N>
                convert_impl(EVE_SUPPORTS(sse2_), wide<float, N> v, as<U> const &tgt) noexcept
{
  using enum category;
  constexpr auto c_i  = categorize<wide<float, N>>();
  constexpr auto c_o  = categorize<wide<U, N>>();
  constexpr bool a512 = current_api >= avx512;

  using i32_t = as<std::int32_t>;

  if constexpr( c_i == float32x4 && c_o == float64x2 ) return _mm_cvtps_pd(v);
  else if constexpr( c_i == float32x4 && c_o == float64x4 ) return _mm256_cvtps_pd(v);
  else if constexpr( c_i == float32x8 && c_o == float64x8 ) return _mm512_cvtps_pd(v);
  else if constexpr( c_i == float32x4 && c_o == int64x2 && a512 ) return _mm_cvttps_epi64(v);
  else if constexpr( c_i == float32x4 && c_o == int64x4 && a512 ) return _mm256_cvttps_epi64(v);
  else if constexpr( c_i == float32x8 && c_o == int64x8 && a512 ) return _mm512_cvttps_epi64(v);
  else if constexpr( c_i == float32x4 && c_o == uint64x2 && a512 ) return _mm_cvttps_epu64(v);
  else if constexpr( c_i == float32x4 && c_o == uint64x4 && a512 ) return _mm256_cvttps_epu64(v);
  else if constexpr( c_i == float32x8 && c_o == uint64x8 && a512 ) return _mm512_cvttps_epu64(v);
  else if constexpr( c_i == float32x4 && c_o == int32x4 ) return _mm_cvttps_epi32(v);
  else if constexpr( c_i == float32x8 && c_o == int32x8 ) return _mm256_cvttps_epi32(v);
  else if constexpr( c_i == float32x16 && c_o == int32x16 ) return _mm512_cvttps_epi32(v);
  else if constexpr( c_i == float32x4 && c_o == uint32x4 && a512 ) return _mm_cvttps_epu32(v);
  else if constexpr( c_i == float32x8 && c_o == uint32x8 && a512 ) return _mm256_cvttps_epu32(v);
  else if constexpr( c_i == float32x16 && c_o == uint32x16 ) return _mm512_cvttps_epu32(v);
  else if constexpr( sizeof(U) <= 2 ) return convert(convert(v, i32_t {}), tgt);
  else return convert_impl(EVE_RETARGET(cpu_), v, tgt);
}

//================================================================================================
// convert: (u)int64 -> U
//================================================================================================
template<integral_scalar_value T, typename N, arithmetic_scalar_value U>
EVE_FORCEINLINE wide<U, N>
                convert_impl(EVE_SUPPORTS(sse2_), wide<T, N> const &v, as<U> const &tgt) noexcept
    requires(sizeof(T) == 8)
{
  using enum category;
  constexpr auto c_i    = categorize<wide<T, N>>();
  constexpr auto c_o    = categorize<wide<U, N>>();
  constexpr auto a512   = current_api >= avx512;
  constexpr auto aavx2  = current_api >= avx2;
  constexpr auto mi64x4 = match(c_i, int64x4, uint64x4);
  constexpr auto mi64x8 = match(c_i, int64x8, uint64x8);
  constexpr auto mo32x4 = match(c_o, int32x4, uint32x4);

  if constexpr( c_i == int64x2 && c_o == float64x2 && a512 ) return _mm_cvtepi64_pd(v);
  else if constexpr( c_i == uint64x2 && c_o == float64x2 && a512 ) return _mm_cvtepu64_pd(v);
  else if constexpr( c_i == int64x2 && c_o == float32x4 && a512 ) return _mm_cvtepi64_ps(v);
  else if constexpr( c_i == uint64x2 && c_o == float32x4 && a512 ) return _mm_cvtepu64_ps(v);
  else if constexpr( N {} <= 2 && c_o == int16x8 && a512 ) return _mm_cvtepi64_epi16(v);
  else if constexpr( N {} <= 2 && c_o == uint16x8 && a512 ) return _mm_cvtepi64_epi16(v);
  else if constexpr( N {} <= 2 && c_o == int8x16 && a512 ) return _mm_cvtepi64_epi8(v);
  else if constexpr( N {} <= 2 && c_o == uint8x16 && a512 ) return _mm_cvtepi64_epi8(v);
  else if constexpr( N {} <= 2 && mo32x4 && a512 ) return _mm_cvtepi64_epi32(v);
  else if constexpr( N {} <= 2 && mo32x4 ) return convert_integers_shuffle(v, tgt);
  else if constexpr( N {} <= 2 && (match(c_o,integer_)) )
    return convert(convert(v, as<upgrade_t<U>> {}), tgt);
  else if constexpr( N {} <= 2 ) return convert_impl(EVE_RETARGET(cpu_), v, tgt);
  else if constexpr( c_i == int64x4 && c_o == float64x4 && a512 ) return _mm256_cvtepi64_pd(v);
  else if constexpr( c_i == uint64x4 && c_o == float64x4 && a512 ) return _mm256_cvtepu64_pd(v);
  else if constexpr( c_i == int64x4 && c_o == float32x4 && a512 ) return _mm256_cvtepi64_ps(v);
  else if constexpr( c_i == uint64x4 && c_o == float32x4 && a512 ) return _mm256_cvtepu64_ps(v);
  else if constexpr( c_i == int64x4 && c_o == float32x4 && a512 ) return _mm256_cvtepi64_ps(v);
  else if constexpr( c_i == uint64x4 && c_o == float32x4 && a512 ) return _mm256_cvtepu64_ps(v);
  else if constexpr( mi64x4 && c_o == int32x4 && a512 ) return _mm256_cvtepi64_epi32(v);
  else if constexpr( mi64x4 && c_o == uint32x4 && a512 ) return _mm256_cvtepi64_epi32(v);
  else if constexpr( mi64x4 && c_o == int16x8 && a512 ) return _mm256_cvtepi64_epi16(v);
  else if constexpr( mi64x4 && c_o == uint16x8 && a512 ) return _mm256_cvtepi64_epi16(v);
  else if constexpr( mi64x4 && c_o == int8x16 && a512 ) return _mm256_cvtepi64_epi8(v);
  else if constexpr( mi64x4 && c_o == uint8x16 && a512 ) return _mm256_cvtepi64_epi8(v);
  else if constexpr( mi64x4 && sizeof(U) <= 2 )
    return convert(convert(v, as<upgrade_t<U>> {}), tgt);
  else if constexpr( mi64x4 && mo32x4 && aavx2 )
  {
    auto const p = _mm256_permutevar8x32_epi32(v, _mm256_set_epi32(7, 5, 3, 1, 6, 4, 2, 0));
#ifdef __clang__
    // clang understands better the semantic of permutevar8x32 + extractf128
    // than permutevar8x32 + castsi256_si128. We can see this by
    // looking at the LLVM IR generated by these sequences: https://godbolt.org/z/K4dnTWPWo
    // With extractf128, we can see that clang understands that we are
    // truncating a vector of <4 x i64> to a vector of <4 x i32>. With
    // castsi256_si128, it generates a bunch of shuffles (which are still
    // semantically equivalent). Nevertheless, with only this code, we see
    // that the codegen in the end is the same.
    //
    // But interesting optimizations can then occur on more complex code,
    // like this one: https://godbolt.org/z/45sor8Ta1. In this case, we are
    // truncating and then zero-extending our vector, which can be optimized
    // as a simple mask operation (only keeping the low 32 bits of each
    // 64-bit packed number). By looking at the generated LLVM IR, we can see
    // that LLVM successfully manages to understand & optimize this if we use
    // extractf128, whereas it is not the case with castsi256_si128! The
    // codegen also looks far better, and only use 1-latency cycle
    // instructions.
    return _mm256_extractf128_si256(p, 0);
#else
    return _mm256_castsi256_si128(p);
#endif
  }
  else if constexpr( mi64x4 && mo32x4 ) return convert_slice(v, tgt);
  else if constexpr( mi64x4 ) return convert_impl(EVE_RETARGET(cpu_), v, tgt);
  else if constexpr( c_i == int64x8 && c_o == float64x8 ) return _mm512_cvtepi64_pd(v);
  else if constexpr( c_i == uint64x8 && c_o == float64x8 ) return _mm512_cvtepu64_pd(v);
  else if constexpr( c_i == int64x8 && c_o == float32x8 ) return _mm512_cvtepi64_ps(v);
  else if constexpr( c_i == uint64x8 && c_o == float32x8 ) return _mm512_cvtepu64_ps(v);
  else if constexpr( mi64x8 && sizeof(U) == 4 ) return _mm512_cvtepi64_epi32(v);
  else if constexpr( mi64x8 && sizeof(U) == 2 ) return _mm512_cvtepi64_epi16(v);
  else if constexpr( mi64x8 && sizeof(U) == 1 ) return _mm512_cvtepi64_epi8(v);
  else if( (sizeof(U) == 1) && (N::value >= 4) )
    return convert(convert(v, as<upgrade_t<U>> {}), tgt);
  else return convert_impl(EVE_RETARGET(cpu_), v, tgt);
}

//================================================================================================
// convert: (u)int32 -> U
//================================================================================================
template<integral_scalar_value T, typename N, arithmetic_scalar_value U>
EVE_FORCEINLINE wide<U, N>
                convert_impl(EVE_SUPPORTS(sse2_), wide<T, N> const &v, as<U> const &tgt) noexcept
    requires(sizeof(T) == 4)
{
  using enum category;
  constexpr auto c_i   = categorize<wide<T, N>>();
  constexpr auto c_o   = categorize<wide<U, N>>();
  constexpr bool a512  = current_api >= avx512;
  constexpr bool aavx2 = current_api >= avx2;
  constexpr bool asse4 = current_api >= sse4_1;

  //==============================================================================================
  // (u)int32 -> float(32/64)
  //==============================================================================================
  if constexpr( c_i == int32x4 && c_o == float64x2 ) return _mm_cvtepi32_pd(v);
  else if constexpr( c_i == int32x4 && c_o == float64x4 ) return _mm256_cvtepi32_pd(v);
  else if constexpr( c_i == uint32x4 && c_o == float64x4 && a512 ) return _mm256_cvtepu32_pd(v);
  else if constexpr( c_i == uint32x4 && c_o == float64x4 ) return convert_slice(v, tgt);
  else if constexpr( c_i == uint32x8 && c_o == float64x8 ) return _mm512_cvtepu32_pd(v);
  else if constexpr( c_i == int32x4 && c_o == float32x4 ) return _mm_cvtepi32_ps(v);
  else if constexpr( c_i == int32x8 && c_o == float32x8 ) return _mm256_cvtepi32_ps(v);
  else if constexpr( c_i == uint32x8 && c_o == float32x8 ) return convert_slice(v, tgt);
  else if constexpr( c_i == int32x16 && c_o == float32x16 ) return _mm512_cvtepi32_ps(v);
  else if constexpr( c_i == uint32x16 && c_o == float32x16 ) return _mm512_cvtepu32_ps(v);
  else if constexpr( c_i == uint32x4 && match(c_o,float_) )
  {
    // From https://stackoverflow.com/a/40766669/737268
    auto y = convert(bit_cast(v >> 1, as<wide<std::int32_t, N>> {}), tgt);
    auto x = convert(bit_cast(v, as<wide<std::int32_t, N>> {}) & 1, tgt);
    return x + y + y;
  }
  //==============================================================================================
  // (u)int32 -> (u)int*
  //==============================================================================================
  else if constexpr( c_i == int32x4 && match(c_o, int64x4, uint64x4) && aavx2 )
    return _mm256_cvtepi32_epi64(v);
  else if constexpr( c_i == uint32x4 && match(c_o, int64x4, uint64x4) && aavx2 )
    return _mm256_cvtepu32_epi64(v);
  else if constexpr( c_i == int32x4 && match(c_o, int64x2, uint64x2) && asse4 )
    return _mm_cvtepi32_epi64(v);
  else if constexpr( c_i == uint32x4 && match(c_o, int64x2, uint64x2) && asse4 )
    return _mm_cvtepu32_epi64(v);
  else if constexpr( c_i == int32x8 && match(c_o, int64x8, uint64x8) && a512 )
    return _mm512_cvtepi32_epi64(v);
  else if constexpr( c_i == uint32x8 && match(c_o, int64x8, uint64x8) && a512 )
    return _mm512_cvtepu32_epi64(v);
  else if constexpr( N {} <= 2 && std::is_signed_v<T>   && sizeof(U) == 8)
    return _mm_unpacklo_epi32(v, _mm_srai_epi32(v,31));
  else if constexpr( N {} <= 2 && std::is_unsigned_v<T> && sizeof(U) == 8)
    return _mm_unpacklo_epi32(v, zero(as(v)));
  else if constexpr( N {} <= 4 && sizeof(U) == 2 && a512 ) return _mm_cvtepi32_epi16(v);
  else if constexpr( N {} <= 2 && sizeof(U) == 2 ) return _mm_shufflelo_epi16(v, 8);
  else if constexpr( N {} == 8 && sizeof(U) == 2 && a512 ) return _mm256_cvtepi32_epi16(v);
  else if constexpr( N {} <= 4 && sizeof(U) == 1 && a512 ) return _mm_cvtepi32_epi8(v);
  else if constexpr( N {} <= 4 && sizeof(U) == 1 )
    return convert(convert(v, as<upgrade_t<U>> {}), tgt);
  else if constexpr( N {} == 8 && sizeof(U) == 1 && a512 ) return _mm256_cvtepi32_epi8(v);
  else if constexpr( N {} == 16 && sizeof(U) == 2 && a512 ) return _mm512_cvtepi32_epi16(v);
  else if constexpr( N {} == 16 && sizeof(U) == 1 && a512 ) return _mm512_cvtepi32_epi8(v);
  else return convert_slice(v, tgt);
}

//================================================================================================
// convert: (u)int16 -> U
//================================================================================================
template<integral_scalar_value T, typename N, arithmetic_scalar_value U>
EVE_FORCEINLINE wide<U, N>
                convert_impl(EVE_SUPPORTS(sse2_), wide<T, N> const &v, as<U> const &tgt) noexcept
    requires(sizeof(T) == 2)
{
  using enum category;
  constexpr auto c_i     = categorize<wide<T, N>>();
  constexpr auto c_o     = categorize<wide<U, N>>();
  constexpr auto a512    = current_api >= avx512;
  constexpr auto aavx2   = current_api >= avx2;
  constexpr auto a41     = current_api >= sse4_1;
  constexpr auto as3     = current_api >= ssse3;
  constexpr auto mi16x8  = match(c_i, int16x8, uint16x8);
  constexpr auto mi16x16 = match(c_i, int16x16, uint16x16);
  constexpr auto mi16x32 = match(c_i, int16x32, uint16x32);
  constexpr auto mo8x16  = match(c_o, int8x16, uint8x16);
  constexpr auto mo32x4  = match(c_o, int32x4, uint32x4);
  constexpr auto mo32x8  = match(c_o, int32x8, uint32x8);
  constexpr auto mo32x16 = match(c_o, int32x16, uint32x16);
  constexpr auto mo64x2  = match(c_o, int64x2, uint64x2);
  constexpr auto mo64x4  = match(c_o, int64x4, uint64x4);
  constexpr auto mo64x8  = match(c_o, int64x8, uint64x8);

  if constexpr( mi16x8 && mo8x16 && a512 ) return _mm_cvtepi16_epi8(v);
  else if constexpr( mi16x8 && mo8x16 && as3 ) return convert_integers_shuffle(v, tgt);
  else if constexpr( mi16x8 && mo8x16 ) return map(convert, v, tgt);
  else if constexpr( c_i == int16x8 && mo32x4 && a41 ) return _mm_cvtepi16_epi32(v);
  else if constexpr( c_i == uint16x8 && mo32x4 && a41 ) return _mm_cvtepu16_epi32(v);
  else if constexpr( c_i == int16x8 && mo32x8 && aavx2 ) return _mm256_cvtepi16_epi32(v);
  else if constexpr( c_i == uint16x8 && mo32x8 && aavx2 ) return _mm256_cvtepu16_epi32(v);
  else if constexpr( c_i == int16x8 && mo32x4  ) return _mm_unpacklo_epi16(v, _mm_srai_epi16(v,15));
  else if constexpr( c_i == uint16x8 && mo32x4 ) return _mm_unpacklo_epi16(v, zero(as(v)));
  else if constexpr( c_i == int16x8 && mo64x2 && a41 ) return _mm_cvtepi16_epi64(v);
  else if constexpr( c_i == uint16x8 && mo64x2 && a41 ) return _mm_cvtepu16_epi64(v);
  else if constexpr( c_i == int16x8 && mo64x4 && aavx2 ) return _mm256_cvtepi16_epi64(v);
  else if constexpr( c_i == uint16x8 && mo64x4 && aavx2 ) return _mm256_cvtepu16_epi64(v);
  else if constexpr( c_i == int16x8 && mo64x8 && a512 ) return _mm512_cvtepi16_epi64(v);
  else if constexpr( c_i == uint16x8 && mo64x8 && a512 ) return _mm512_cvtepu16_epi64(v);
  else if constexpr( c_i == int16x8 && c_o == float64x8 && a512 )
    return convert(convert(v, as<std::int64_t> {}), tgt);
  else if constexpr( c_i == uint16x8 && c_o == float64x8 && a512 )
    return convert(convert(v, as<std::int64_t> {}), tgt);
  else if constexpr( mi16x8 && std::is_floating_point_v<U> )
    return convert(convert(v, as<upgrade_t<T>> {}), tgt);
  else if constexpr( mi16x8 && sizeof(U) == 8 ) return convert_integers_chain(v, tgt);
  else if constexpr( mi16x8 && (sizeof(U) >= 4) && N::value == 8 ) return convert_slice(v, tgt);
  else if constexpr( mi16x16 && match(c_o, float_) )
    return convert(convert(v, as<upgrade_t<T>> {}), tgt);
  else if constexpr( mi16x16 && mo8x16 && a512 ) return _mm256_cvtepi16_epi8(v);
  else if constexpr( c_i == int16x16 && mo32x16 ) return _mm512_cvtepi16_epi32(v);
  else if constexpr( c_i == uint16x16 && mo32x16 ) return _mm512_cvtepu16_epi32(v);
  else if constexpr( mi16x16 ) return convert_slice(v, tgt);
  else if constexpr( mi16x32 && sizeof(U) == 1 ) return _mm512_cvtepi16_epi8(v);
  else if constexpr( mi16x32 ) return convert_slice(v, tgt);
  else return convert_impl(EVE_RETARGET(cpu_), v, tgt);
}

//================================================================================================
// convert: (u)int8 -> U
//================================================================================================
template<integral_scalar_value T, typename N, arithmetic_scalar_value U>
EVE_FORCEINLINE wide<U, N>
                convert_impl(EVE_SUPPORTS(sse2_), wide<T, N> const& v, as<U> const& tgt) noexcept
    requires(sizeof(T) == 1)
{
  using enum category;
  constexpr auto c_i     = categorize<wide<T, N>>();
  constexpr auto c_o     = categorize<wide<U, N>>();
  constexpr auto aavx2   = current_api >= avx2;
  constexpr auto a41     = current_api >= sse4_1;
  constexpr auto mi8x16  = match(c_i, int8x16, uint8x16);
  constexpr auto mo16x8  = match(c_o, int16x8, uint16x8);
  constexpr auto mo16x16 = match(c_o, int16x16, uint16x16);
  constexpr auto mo32x4  = match(c_o, int32x4, uint32x4);
  constexpr auto mo32x8  = match(c_o, int32x8, uint32x8);
  constexpr auto mo32x16 = match(c_o, int32x16, uint32x16);
  constexpr auto mo64x2  = match(c_o, int64x2, uint64x2);
  constexpr auto mo64x4  = match(c_o, int64x4, uint64x4);
  constexpr auto mo64x8  = match(c_o, int64x8, uint64x8);

  using d_t = as<downgrade_t<U>>;
  using t_t =
      std::conditional_t<std::is_signed_v<T>, as_integer_t<U, signed>, as_integer_t<U, unsigned>>;

  if constexpr( match(c_o, float_) ) return convert(convert(v, as<t_t> {}), tgt);
  else if constexpr( c_i == int8x16 && mo16x8 && a41 ) return _mm_cvtepi8_epi16(v);
  else if constexpr( c_i == int8x16 && mo16x16 && aavx2 ) return _mm256_cvtepi8_epi16(v);
  else if constexpr( c_i == uint8x16 && mo16x8 && a41 ) return _mm_cvtepu8_epi16(v);
  else if constexpr( c_i == uint8x16 && mo16x16 && aavx2 ) return _mm256_cvtepu8_epi16(v);
  else if constexpr( c_i == int8x16 && mo32x4 && a41 ) return _mm_cvtepi8_epi32(v);
  else if constexpr( c_i == int8x16 && mo32x8 && aavx2 ) return _mm256_cvtepi8_epi32(v);
  else if constexpr( c_i == int8x16 && mo32x16 ) return _mm512_cvtepi8_epi32(v);
  else if constexpr( c_i == uint8x16 && mo32x4 && a41 ) return _mm_cvtepu8_epi32(v);
  else if constexpr( c_i == uint8x16 && mo32x8 && aavx2 ) return _mm256_cvtepu8_epi32(v);
  else if constexpr( c_i == uint8x16 && mo32x16 ) return _mm512_cvtepu8_epi32(v);
  else if constexpr( c_i == int8x16 && mo64x2 && a41 ) return _mm_cvtepi8_epi64(v);
  else if constexpr( c_i == int8x16 && mo64x4 && aavx2 ) return _mm256_cvtepi8_epi64(v);
  else if constexpr( c_i == int8x16 && mo64x8 ) return _mm512_cvtepi8_epi64(v);
  else if constexpr( c_i == int8x16 && mo16x8 ) return _mm_srai_epi16(_mm_unpacklo_epi8(v, v),8);
  else if constexpr( c_i == int8x16 && mo32x4 )
  {
    auto w = _mm_unpacklo_epi8(v,v);
    return _mm_srai_epi32(_mm_unpacklo_epi16(w,w),24);
  }
  else if constexpr( c_i == uint8x16 && mo64x2 && a41 ) return _mm_cvtepu8_epi64(v);
  else if constexpr( c_i == uint8x16 && mo64x4 && aavx2 ) return _mm256_cvtepu8_epi64(v);
  else if constexpr( c_i == uint8x16 && mo64x8 ) return _mm512_cvtepu8_epi64(v);
  else if constexpr( c_i == uint8x16 && mo16x8 ) return _mm_unpacklo_epi8(v, zero(as(v)));
  else if constexpr( c_i == uint8x16 && mo32x4 ) return convert(convert(v, d_t {}), tgt);
  else if constexpr( mi8x16 && mo64x2 ) return convert(convert(v, d_t {}), tgt);
  else if constexpr( mi8x16 && mo64x4 ) return convert(convert(v, d_t {}), tgt);
  else if constexpr( mi8x16 && (sizeof(U) * N {} >= 16) ) return convert_slice(v, tgt);
  else if constexpr( mi8x16 ) return convert_impl(EVE_RETARGET(cpu_), v, tgt);
  else return convert_slice(v, tgt);
}
}
