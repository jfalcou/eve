//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_MINUS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_MINUS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve { namespace detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE pack<T,N,neon64_> minus_( EVE_SUPPORTS(neon128_)
                                          , pack<T,N,neon64_> const& v0
                                          , pack<T,N,neon64_> const& v1
                                          ) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

    #if defined(__aarch64__)
    if constexpr( std::is_same_v<T,double>          ) return vsub_f64(v0,v1);
    #endif
    if constexpr( std::is_same_v<T,float>           ) return vsub_f32(v0,v1);
    if constexpr( is_signed_int   && sizeof(T) == 8 ) return vsub_s64(v0,v1);
    if constexpr( is_signed_int   && sizeof(T) == 4 ) return vsub_s32(v0,v1);
    if constexpr( is_signed_int   && sizeof(T) == 2 ) return vsub_s16(v0,v1);
    if constexpr( is_signed_int   && sizeof(T) == 1 ) return vsub_s8 (v0,v1);
    if constexpr( is_unsigned_int && sizeof(T) == 8 ) return vsub_u64(v0,v1);
    if constexpr( is_unsigned_int && sizeof(T) == 4 ) return vsub_u32(v0,v1);
    if constexpr( is_unsigned_int && sizeof(T) == 2 ) return vsub_u16(v0,v1);
    if constexpr( is_unsigned_int && sizeof(T) == 1 ) return vsub_u8 (v0,v1);
  }

  template<typename T, typename N>
  EVE_FORCEINLINE pack<T,N,neon128_>  minus_( EVE_SUPPORTS(neon128_)
                                            , pack<T,N,neon128_> const& v0
                                            , pack<T,N,neon128_> const& v1
                                            ) noexcept
  {
    constexpr bool is_signed_int   = std::is_integral_v<T> && std::is_signed_v<T>;
    constexpr bool is_unsigned_int = std::is_integral_v<T> && std::is_unsigned_v<T>;

    #if defined(__aarch64__)
    if constexpr( std::is_same_v<T,double>          ) return vsubq_f64(v0,v1);
    #endif
    if constexpr( std::is_same_v<T,float>           ) return vsubq_f32(v0,v1);
    if constexpr( is_signed_int   && sizeof(T) == 8 ) return vsubq_s64(v0,v1);
    if constexpr( is_signed_int   && sizeof(T) == 4 ) return vsubq_s32(v0,v1);
    if constexpr( is_signed_int   && sizeof(T) == 2 ) return vsubq_s16(v0,v1);
    if constexpr( is_signed_int   && sizeof(T) == 1 ) return vsubq_s8 (v0,v1);
    if constexpr( is_unsigned_int && sizeof(T) == 8 ) return vsubq_u64(v0,v1);
    if constexpr( is_unsigned_int && sizeof(T) == 4 ) return vsubq_u32(v0,v1);
    if constexpr( is_unsigned_int && sizeof(T) == 2 ) return vsubq_u16(v0,v1);
    if constexpr( is_unsigned_int && sizeof(T) == 1 ) return vsubq_u8 (v0,v1);
  }
} }

#endif
