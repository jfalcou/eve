//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_ARM_NEON_COMBINE_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_ARM_NEON_COMBINE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/arch/limits.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE auto combine( neon128_ const&
                              , wide<T,N,neon128_> const& l, wide<T,N,neon128_> const& h
                              ) noexcept
  {
    using that_t = wide<T,typename N::combined_type>;
    return that_t( typename that_t::storage_type{l,h} );
  }

  template<typename T, typename N>
  EVE_FORCEINLINE auto combine( neon128_ const&
                              , wide<T,N,neon64_> const& l, wide<T,N,neon64_> const& h
                              ) noexcept
  {
    using that_t = wide<T,typename N::combined_type>;

    if constexpr(N::value*sizeof(T) == limits<eve::neon64_>::bytes)
    {
      constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
      constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

      #if defined(__aarch64__)
      if constexpr( std::is_same_v<T,double>          ) return vcombine_f64(l,h);
      #endif
      if constexpr( std::is_same_v<T,float>           ) return vcombine_f32(l,h);
      if constexpr( is_signed_int   && sizeof(T) == 8 ) return vcombine_s64(l,h);
      if constexpr( is_signed_int   && sizeof(T) == 4 ) return vcombine_s32(l,h);
      if constexpr( is_signed_int   && sizeof(T) == 2 ) return vcombine_s16(l,h);
      if constexpr( is_signed_int   && sizeof(T) == 1 ) return vcombine_s8 (l,h);
      if constexpr( is_unsigned_int && sizeof(T) == 8 ) return vcombine_u64(l,h);
      if constexpr( is_unsigned_int && sizeof(T) == 4 ) return vcombine_u32(l,h);
      if constexpr( is_unsigned_int && sizeof(T) == 2 ) return vcombine_u16(l,h);
      if constexpr( is_unsigned_int && sizeof(T) == 1 ) return vcombine_u8 (l,h);
    }
    else
    {
      auto mask = [&](auto... I)
      {
        uint8x8_t m = { static_cast<std::uint8_t>(I)...
                      , static_cast<std::uint8_t>(I+limits<eve::neon64_>::bytes)...
                      };
        return m;
      };

      uint8x8x2_t lh    = {{ (uint8x8_t)l.storage(), (uint8x8_t)h.storage() }};
      auto        that  = vtbl2_u8(lh, apply<(sizeof(T) * N::value)>(mask));

      return that_t( typename that_t::storage_type(that) );
    }
  }
}

#endif
