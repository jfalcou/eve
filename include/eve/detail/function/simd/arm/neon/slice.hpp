//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_ARM_NEON_SLICE_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_ARM_NEON_SLICE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <cstddef>

namespace eve { namespace detail
{
  template<typename T, typename N, typename Slice>
  EVE_FORCEINLINE pack<T,typename N::split_type>
  slice( pack<T,N,neon128_> const& a, Slice const& ) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

    if constexpr(Slice::value)
    {
      #if defined(__aarch64__)
      if constexpr( std::is_same_v<T,double>          ) return vget_high_f64(a);
      #endif
      if constexpr( std::is_same_v<T,float>           ) return vget_high_f32(a);
      if constexpr( is_signed_int   && sizeof(T) == 8 ) return vget_high_s64(a);
      if constexpr( is_signed_int   && sizeof(T) == 4 ) return vget_high_s32(a);
      if constexpr( is_signed_int   && sizeof(T) == 2 ) return vget_high_s16(a);
      if constexpr( is_signed_int   && sizeof(T) == 1 ) return vget_high_s8 (a);
      if constexpr( is_unsigned_int && sizeof(T) == 8 ) return vget_high_u64(a);
      if constexpr( is_unsigned_int && sizeof(T) == 4 ) return vget_high_u32(a);
      if constexpr( is_unsigned_int && sizeof(T) == 2 ) return vget_high_u16(a);
      if constexpr( is_unsigned_int && sizeof(T) == 1 ) return vget_high_u8 (a);
    }
    else
    {
      #if defined(__aarch64__)
      if constexpr( std::is_same_v<T,double>          ) return vget_low_f64(a);
      #endif
      if constexpr( std::is_same_v<T,float>           ) return vget_low_f32(a);
      if constexpr( is_signed_int   && sizeof(T) == 8 ) return vget_low_s64(a);
      if constexpr( is_signed_int   && sizeof(T) == 4 ) return vget_low_s32(a);
      if constexpr( is_signed_int   && sizeof(T) == 2 ) return vget_low_s16(a);
      if constexpr( is_signed_int   && sizeof(T) == 1 ) return vget_low_s8 (a);
      if constexpr( is_unsigned_int && sizeof(T) == 8 ) return vget_low_u64(a);
      if constexpr( is_unsigned_int && sizeof(T) == 4 ) return vget_low_u32(a);
      if constexpr( is_unsigned_int && sizeof(T) == 2 ) return vget_low_u16(a);
      if constexpr( is_unsigned_int && sizeof(T) == 1 ) return vget_low_u8 (a);
    }
  }

  template<typename T, typename N, typename Slice>
  EVE_FORCEINLINE auto  slice( pack<T,N,neon64_> const& a, Slice const& ) noexcept
                        requires( pack<T,typename N::split_type>, If<(N::value>1)>)
  {
    using type = pack<T,typename N::split_type>;
    if constexpr(Slice::value)
    {
      auto select = [](auto const& v, auto size)
      {
        auto mask = [&](auto... I)
        {
          auto offset = (sizeof(T) * size)/2;
          uint8x8_t m ={ static_cast<std::uint8_t>(offset + I%offset)...};
          return m;
        };

        return vtbl1_u8((uint8x8_t)(v.storage()), apply<8>(mask));
      };

      return type((typename type::storage_type)(select(a,N{})));
    }
    else
    {
      return type(a.storage());
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE auto slice( pack<T,N,neon128_> const& a ) noexcept
  {
    std::array<pack<T,typename N::split_type>,2> that{ slice(a,lower_), slice(a,upper_)};
    return that;
  }

  template<typename T, typename N>
  EVE_FORCEINLINE auto slice( pack<T,N,neon64_> const& a ) noexcept
  {
    std::array<pack<T,typename N::split_type>,2> that{ slice(a,lower_), slice(a,upper_)};
    return that;
  }
} }

#endif
