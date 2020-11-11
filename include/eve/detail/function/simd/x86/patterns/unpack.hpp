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

#include <eve/detail/function/patterns/unpack.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/swizzle.hpp>
#include <eve/traits/element_type.hpp>

namespace eve::detail
{
  template<typename Wide, typename Target, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(sse2_), unpack_match const&
                                  , as_<Target> , Pattern const&, Wide const& r
                                  )
  {
    using e_t = element_type_t<Wide>;

    // Type-agnostic bit-shifting
    [[maybe_unused]] constexpr auto shifter = []<typename N>(auto v, N const&)
    {
      if constexpr( N::value != 0)
      {
        auto bits         = (__m128i)(v.storage());
        auto shifted_bits = _mm_bsrli_si128(bits, N::value);
        Wide that = (typename Wide::storage_type)(shifted_bits);
        return that;
      }
      else
      {
        return v;
      }
    };

    // Type-agnostic unpacklo
    [[maybe_unused]]  constexpr auto unpack_lo = [](auto v, auto w) -> Target
    {
      if constexpr( sizeof(e_t) == 4 )
      {
        if constexpr( std::is_floating_point_v<e_t> ) return _mm_unpacklo_ps (v,w);
        else                                          return _mm_unpacklo_epi32 (v,w);
      }
      else if constexpr( sizeof(e_t) == 2 ) return _mm_unpacklo_epi16(v,w);
      else if constexpr( sizeof(e_t) == 1 ) return _mm_unpacklo_epi8(v,w);
    };

    // Type-agnostic unpackhi
    [[maybe_unused]]  constexpr auto unpack_hi = [](auto v, auto w) -> Target
    {
      if constexpr( sizeof(e_t) == 4 )
      {
        if constexpr( std::is_floating_point_v<e_t> ) return _mm_unpackhi_ps (v,w);
        else                                          return _mm_unpackhi_epi32 (v,w);
      }
      else if constexpr( sizeof(e_t) == 2 ) return _mm_unpackhi_epi16(v,w);
      else if constexpr( sizeof(e_t) == 1 ) return _mm_unpackhi_epi8(v,w);
    };

    constexpr Pattern p{};

    constexpr auto p0     = p(0,Wide::static_size);
    constexpr auto p1     = p(1,Wide::static_size);

    // ---- Variants of unpacklo
    if constexpr( unpack_match::is_low(p, as_<Wide>()) )
    {
      constexpr auto shift  = p0 == -1 ? p1 : p0;

      constexpr std::integral_constant<std::size_t, sizeof(e_t)*shift> shifting = {};
      auto sr = shifter(r, shifting );

            if constexpr( p0 == -1) return unpack_lo(Target(0),sr);
      else  if constexpr( p1 == -1) return unpack_lo(sr,Target(0));
      else                          return unpack_lo(sr,sr);
    }
    else
    {
      constexpr auto shift  = (p0 == -1 ? p1 : p0) - Wide::static_size/2;

      constexpr std::integral_constant<std::size_t, sizeof(e_t)*shift> shifting = {};
      auto sr = shifter(r, shifting );

            if constexpr( p0 == -1) return unpack_hi(Target(0),sr);
      else  if constexpr( p1 == -1) return unpack_hi(sr,Target(0));
      else                          return unpack_hi(sr,sr);
    }
  }
}
