//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::detail
{
// {
//         if constexpr(c_o == category::int8x16 ) return _mm_packs_epi16(v,v);
//   else  if constexpr(c_o == category::uint8x16) return _mm_packus_epi16(v,v);
// }

/////////////////////////////////////////////////////////////////////////////////////
// saturated conversions
//////////////////////////////////////////////////////////////////////////////////////
//====================================================================================
// 128 bits <-> 128 bits
template<arithmetic_scalar_value In, typename N, arithmetic_scalar_value Out>
EVE_FORCEINLINE wide<Out, N>
                convert_(EVE_SUPPORTS(sse2_),
                         saturated_type const                &sat_,
                         wide<In, N> const                   &v0,
                         as<Out> const                       &tgt) noexcept
{
  // Idempotent call
  if constexpr( std::is_same_v<In, Out> ) return v0;

  if constexpr( std::is_same_v<In, int16_t> && std::is_same_v<Out, int8_t> && (N::value <= 16) )
  {
    if constexpr( N::value == 16 )
    {
      auto [low, high] = v0.slice();
      return _mm_packs_epi16(low, high);
    }
    else if constexpr( N::value == 8 )
    {
      wide<Out, fixed<2 *N::value>> tmp = _mm_packs_epi16(v0, v0);
      auto [low, hi]                    = tmp.slice();
      return low;
    }
    else if constexpr( N::value <= 8 ) { return convert_(EVE_RETARGET(cpu_), sat_, v0, tgt); }
  }
  else if constexpr( std::is_same_v<In,
                                    int32_t> && std::is_same_v<Out, int16_t> && (N::value <= 8) )
  {
    if constexpr( N::value == 8 )
    {
      auto [low, high] = v0.slice();
      return _mm_packs_epi32(low, high);
    }
    else if constexpr( N::value == 4 )
    {
      wide<Out, fixed<2 *N::value>> tmp = _mm_packs_epi16(v0, v0);
      auto [low, hi]                    = tmp.slice();
      return low;
    }
    else if constexpr( N::value <= 4 ) { return convert_(EVE_RETARGET(cpu_), sat_, v0, tgt); }
  }
  else if constexpr( std::is_same_v<In,
                                    int16_t> && std::is_same_v<Out, uint8_t> && (N::value <= 16) )
  {
    if constexpr( N::value == 16 )
    {
      auto [low, high] = v0.slice();
      return _mm_packus_epi16(low, high);
    }
    else if constexpr( N::value == 8 )
    {
      wide<Out, fixed<2 *N::value>> tmp = _mm_packus_epi16(v0, v0);
      auto [low, hi]                    = tmp.slice();
      return low;
    }
    else if constexpr( N::value <= 8 ) { return convert_(EVE_RETARGET(cpu_), sat_, v0, tgt); }
  }
  else { return convert_(EVE_RETARGET(cpu_), sat_, v0, tgt); }
}

//================================================================================================
// 256 bits <-> 256 bits
template<arithmetic_scalar_value In, typename N, arithmetic_scalar_value Out>
EVE_FORCEINLINE wide<Out, N>
                convert_(EVE_SUPPORTS(avx2_),
                         saturated_type const                &sat_,
                         wide<In, N> const                   &v0,
                         as<Out> const                       &tgt) noexcept
{
  // Idempotent call
  if constexpr( std::is_same_v<In, Out> ) return v0;

  if constexpr( std::is_same_v<In, int16_t> && std::is_same_v<Out, int8_t> && (N::value <= 32) )
  {
    if constexpr( N::value == 32 )
    {
      auto [low, high] = v0.slice();
      return _mm256_packs_epi16(low, high);
    }
    else if constexpr( N::value == 16 )
    {
      wide<Out, fixed<2 *N::value>> tmp = _mm256_packs_epi16(v0, v0);
      auto [low, high]                  = tmp.slice();
      return low;
    }
    else if constexpr( N::value <= 8 ) { return convert_(EVE_RETARGET(sse2_), sat_, v0, tgt); }
  }
  else if constexpr( std::is_same_v<In,
                                    int32_t> && std::is_same_v<Out, int16_t> && (N::value <= 16) )
  {
    if constexpr( N::value == 16 )
    {
      auto [low, high] = v0.slice();
      return _mm256_packs_epi32(low, high);
    }
    else if constexpr( N::value == 8 )
    {
      wide<Out, fixed<2 *N::value>> tmp = _mm256_packs_epi32(v0, v0);
      auto [low, hi]                    = tmp.slice();
      return low;
    }
    else if constexpr( N::value <= 4 ) { return convert_(EVE_RETARGET(sse2_), sat_, v0, tgt); }
  }
  else if constexpr( std::is_same_v<In,
                                    int16_t> && std::is_same_v<Out, uint8_t> && (N::value <= 32) )
  {
    if constexpr( N::value == 32 )
    {
      auto [low, high] = v0.slice();
      return _mm256_packus_epi16(low, high);
    }
    else if constexpr( N::value == 16 )
    {
      wide<Out, fixed<2 *N::value>> tmp = _mm256_packus_epi16(v0, v0);
      auto [low, hi]                    = tmp.slice();
      return low;
    }
    else if constexpr( N::value <= 16 ) { return convert_(EVE_RETARGET(sse2_), sat_, v0, tgt); }
  }
  else if constexpr( std::is_same_v<In,
                                    int32_t> && std::is_same_v<Out, uint16_t> && (N::value <= 16) )
  {
    if constexpr( N::value == 16 )
    {
      auto [low, high] = v0.slice();
      return _mm256_packus_epi32(low, high);
    }
    else if constexpr( N::value == 8 )
    {
      wide<Out, fixed<2 *N::value>> tmp = _mm256_packus_epi32(v0, v0);
      auto [low, hi]                    = tmp.slice();
      return low;
    }
    else if constexpr( N::value <= 4 ) { return convert_(EVE_RETARGET(sse2_), sat_, v0, tgt); }
  }
  else { return convert_(EVE_RETARGET(cpu_), sat_, v0, tgt); }
}
}
