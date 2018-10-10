//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_BITWISE_CAST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_BITWISE_CAST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/core/function/simd/detail/bitwise_cast.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve { namespace detail
{
  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE pack<Target,M,avx_> bitwise_cast_ ( EVE_SUPPORTS(avx_)
                                                    , pack<Source,N,avx_> const& v0
                                                    , as_<pack<Target,M,avx_>> const&
                                                    ) noexcept
  {
    // Idempotent call
    if constexpr( std::is_same_v<Source,Target> ) return v0;

    // bitwise_cast from float
    if constexpr( std::is_same_v<Source,float> )
    {
      if constexpr( std::is_same_v<Target,double> ) return _mm256_castps_pd(v0);
      if constexpr( std::is_integral_v<Target>     ) return _mm256_castps_si256(v0);
    }

    // bitwise_cast from double
    if constexpr( std::is_same_v<Source,double> )
    {
      if constexpr( std::is_same_v<Target,float>) return _mm256_castpd_ps(v0);
      if constexpr( std::is_integral_v<Target>   ) return _mm256_castpd_si256(v0);
    }

    // bitwise_cast from integer
    if constexpr( std::is_integral_v<Source> )
    {
      if constexpr( std::is_same_v<Target,float>  ) return _mm256_castsi256_ps(v0);
      if constexpr( std::is_same_v<Target,double> ) return _mm256_castsi256_pd(v0);
      if constexpr( std::is_integral_v<Target>     ) return v0.storage();
    }
  }

  // AVX supports logical bitwise casting
  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE pack<logical<Target>,M,avx_>
  bitwise_cast_ ( EVE_SUPPORTS(avx_)
                , pack<Source,N,avx_> const& v0, as_<pack<logical<Target>,M,avx_>> const& tgt
                ) noexcept
  {
    return a2l_isocast_(v0,tgt);
  }

  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE pack<Target,M,avx_>
  bitwise_cast_ ( EVE_SUPPORTS(avx_)
                , pack<logical<Source>,N,avx_> const& v0, as_<pack<Target,M,avx_>> const& tgt
                ) noexcept
  {
    return l2a_isocast_(v0,tgt);
  }

  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE pack<logical<Target>,M,avx_>
  bitwise_cast_ ( EVE_SUPPORTS(avx_)
                , pack<logical<Source>,N,avx_> const& v0
                , as_<pack<logical<Target>,M,avx_>> const& tgt
                ) noexcept
  {
    return l2l_isocast_(v0,tgt);
  }
} }

#endif
