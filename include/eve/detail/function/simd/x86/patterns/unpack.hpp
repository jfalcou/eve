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

#include <eve/detail/implementation.hpp>
#include <eve/detail/swizzle.hpp>
#include <eve/traits/element_type.hpp>

namespace eve::detail
{
  //================================================================================================
  // Pattern based on UNPACKHI/UNPACKLO with partial zeroing
  //================================================================================================
  struct unpack_match
  {
    template<typename Wide, typename Pattern>
    static constexpr auto is_low(Pattern const& p, as_<Wide> const&)  noexcept
    {
      auto p0 = p(0,Wide::static_size);
      auto p1 = p(1,Wide::static_size);
      auto s = Wide::static_size/2;

      return p0 == -1 ? (p1<s) : (p0<s);
    }

    template<typename Wide, std::ptrdiff_t... I>
    static constexpr auto check(pattern_<I...> const&, as_<Wide> const&)  noexcept
    {
      constexpr pattern_<I...> p{};

      /*
        32 bits case has a more optimal shuffleps for missing cases
        16 bits case has a more optimal shuffle16 for missing cases
        8  bits case requires the most variants
      */
      // check for 32 bits unpacks
      constexpr bool  u32 =   sizeof(element_type_t<Wide>) == 4
                      &&  (   p.is_similar(pattern< 2, 2, 3, 3>)
                          ||  p.is_similar(pattern< 2,-1, 3,-1>)
                          ||  p.is_similar(pattern<-1, 2,-1, 3>)
                          ||  p.is_similar(pattern< 1, 1, 2, 2>)
                          ||  p.is_similar(pattern< 1,-1, 2,-1>)
                          ||  p.is_similar(pattern<-1, 1,-1, 2>)
                          ||  p.is_similar(pattern< 0, 0, 1, 1>)
                          ||  p.is_similar(pattern< 0,-1, 1,-1>)
                          ||  p.is_similar(pattern<-1, 0,-1, 1>)
                          );

      // check for 16 bits unpacks
      constexpr bool  u16 =   sizeof(element_type_t<Wide>) == 2
                      &&  (   p.is_similar(pattern< 4, 4, 5, 5, 6, 6, 7, 7>)
                          ||  p.is_similar(pattern< 4,-1, 5,-1, 6,-1, 7,-1>)
                          ||  p.is_similar(pattern<-1, 4,-1, 5,-1, 6,-1, 7>)
                          ||  p.is_similar(pattern< 3, 3, 4, 4, 5, 5, 6, 6>)
                          ||  p.is_similar(pattern<-1, 3,-1, 4,-1, 5,-1, 6>)
                          ||  p.is_similar(pattern< 3,-1, 4,-1, 5,-1, 6,-1>)
                          ||  p.is_similar(pattern< 1, 1, 2, 2, 3, 3, 4, 4>)
                          ||  p.is_similar(pattern<-1, 1,-1, 2,-1, 3,-1, 4>)
                          ||  p.is_similar(pattern< 1,-1, 2,-1, 3,-1, 4,-1>)
                          ||  p.is_similar(pattern< 0, 0, 1, 1, 2, 2, 3, 3>)
                          ||  p.is_similar(pattern< 0,-1, 1,-1, 2,-1, 3,-1>)
                          ||  p.is_similar(pattern<-1, 0,-1, 1,-1, 2,-1, 3>)
                          );

      // check for 8 bits unpacks
      constexpr bool  u8  =   sizeof(element_type_t<Wide>) == 1
                      &&  (   p.is_similar(pattern< 8, 8, 9, 9,10,10,11,11,12,12,13,13,14,14,15,15>)
                          ||  p.is_similar(pattern< 8,-1, 9,-1,10,-1,11,-1,12,-1,13,-1,14,-1,15,-1>)
                          ||  p.is_similar(pattern<-1, 8,-1, 9,-1,10,-1,11,-1,12,-1,13,-1,14,-1,15>)
                          ||  p.is_similar(pattern< 7, 7, 8, 8, 9, 9,10,10,11,11,12,12,13,13,14,14>)
                          ||  p.is_similar(pattern< 7,-1, 8,-1, 9,-1,10,-1,11,-1,12,-1,13,-1,14,-1>)
                          ||  p.is_similar(pattern<-1, 7,-1, 8,-1, 9,-1,10,-1,11,-1,12,-1,13,-1,14>)
                          ||  p.is_similar(pattern< 6, 6, 7, 7, 8, 8, 9, 9,10,10,11,11,12,12,13,13>)
                          ||  p.is_similar(pattern< 6,-1, 7,-1, 8,-1, 9,-1,10,-1,11,-1,12,-1,13,-1>)
                          ||  p.is_similar(pattern<-1, 6,-1, 7,-1, 8,-1, 9,-1,10,-1,11,-1,12,-1,13>)
                          ||  p.is_similar(pattern< 5, 5, 6, 6, 7, 7, 8, 8, 9, 9,10,10,11,11,12,12>)
                          ||  p.is_similar(pattern< 5,-1, 6,-1, 7,-1, 8,-1, 9,-1,10,-1,11,-1,12,-1>)
                          ||  p.is_similar(pattern<-1, 5,-1, 6,-1, 7,-1, 8,-1, 9,-1,10,-1,11,-1,12>)
                          ||  p.is_similar(pattern< 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9,10,10,11,11>)
                          ||  p.is_similar(pattern< 4,-1, 5,-1, 6,-1, 7,-1, 8,-1, 9,-1,10,-1,11,-1>)
                          ||  p.is_similar(pattern<-1, 4,-1, 5,-1, 6,-1, 7,-1, 8,-1, 9,-1,10,-1,11>)
                          ||  p.is_similar(pattern< 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9,10,10>)
                          ||  p.is_similar(pattern< 3,-1, 4,-1, 5,-1, 6,-1, 7,-1, 8,-1, 9,-1,10,-1>)
                          ||  p.is_similar(pattern<-1, 3,-1, 4,-1, 5,-1, 6,-1, 7,-1, 8,-1, 9,-1,10>)
                          ||  p.is_similar(pattern< 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9>)
                          ||  p.is_similar(pattern< 2,-1, 3,-1, 4,-1, 5,-1, 6,-1, 7,-1, 8,-1, 9,-1>)
                          ||  p.is_similar(pattern<-1, 2,-1, 3,-1, 4,-1, 5,-1, 6,-1, 7,-1, 8,-1, 9>)
                          ||  p.is_similar(pattern< 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8>)
                          ||  p.is_similar(pattern< 1,-1, 2,-1, 3,-1, 4,-1, 5,-1, 6,-1, 7,-1, 8,-1>)
                          ||  p.is_similar(pattern<-1, 1,-1, 2,-1, 3,-1, 4,-1, 5,-1, 6,-1, 7,-1, 8>)
                          ||  p.is_similar(pattern< 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7>)
                          ||  p.is_similar(pattern< 0,-1, 1,-1, 2,-1, 3,-1, 4,-1, 5,-1, 6,-1, 7,-1>)
                          ||  p.is_similar(pattern<-1, 0,-1, 1,-1, 2,-1, 3,-1, 4,-1, 5,-1, 6,-1, 7>)
                          ||  p.is_similar(pattern< 9, 9,10,10,11,11,12,12>)
                          ||  p.is_similar(pattern< 9,-1,10,-1,11,-1,12,-1>)
                          ||  p.is_similar(pattern<-1, 9,-1,10,-1,11,-1,12>)
                          ||  p.is_similar(pattern<10,10,11,11,12,12,13,13>)
                          ||  p.is_similar(pattern<10,-1,11,-1,12,-1,13,-1>)
                          ||  p.is_similar(pattern<-1,10,-1,11,-1,12,-1,13>)
                          ||  p.is_similar(pattern<11,11,12,12,13,13,14,14>)
                          ||  p.is_similar(pattern<11,-1,12,-1,13,-1,14,-1>)
                          ||  p.is_similar(pattern<-1,11,-1,12,-1,13,-1,14>)
                          ||  p.is_similar(pattern<12,12,13,13,14,14,15,15>)
                          ||  p.is_similar(pattern<12,-1,13,-1,14,-1,15,-1>)
                          ||  p.is_similar(pattern<-1,12,-1,13,-1,14,-1,15>)
                          ||  p.is_similar(pattern<13,13,14,14>)
                          ||  p.is_similar(pattern<13,-1,14,-1>)
                          ||  p.is_similar(pattern<-1,13,-1,14>)
                          ||  p.is_similar(pattern<14,14,15,15>)
                          ||  p.is_similar(pattern<14,-1,15,-1>)
                          ||  p.is_similar(pattern<-1,14,-1,15>)
                          ||  p.is_similar(pattern<15,15>)
                          ||  p.is_similar(pattern<15,-1>)
                          ||  p.is_similar(pattern<-1,15>)
                          );

      return u32 || u16 || u8;
    }
  };

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
        return bit_cast ( _mm_unpacklo_ps ( bit_cast(v, as_<wide<float,cardinal_t<Wide>>>() )
                                          , bit_cast(w, as_<wide<float,cardinal_t<Wide>>>() )
                                          )
                        , as_<Target>()
                        );
      }
      else if constexpr( sizeof(e_t) == 2 ) return _mm_unpacklo_epi16(v,w);
      else if constexpr( sizeof(e_t) == 1 ) return _mm_unpacklo_epi8(v,w);
    };

    // Type-agnostic unpackhi
    [[maybe_unused]]  constexpr auto unpack_hi = [](auto v, auto w) -> Target
    {
      if constexpr( sizeof(e_t) == 4 )
      {
        return bit_cast ( _mm_unpackhi_ps ( bit_cast(v, as_<wide<float,cardinal_t<Wide>>>() )
                                          , bit_cast(w, as_<wide<float,cardinal_t<Wide>>>() )
                                          )
                        , as_<Target>()
                        );
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
