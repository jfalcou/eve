//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE2_BITWISE_CAST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE2_BITWISE_CAST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve { namespace detail
{
  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE pack<Target,M,sse_> bitwise_cast_ ( EVE_SUPPORTS(sse2_)
                                                    , pack<Source,N,sse_> const& v0
                                                    , as_<pack<Target,M,sse_>> const&
                                                    ) noexcept
  {
    // Idempotent call
    if constexpr( std::is_same_v<Source,Target> ) return v0;

    // bitwise_cast from float
    if constexpr( std::is_same_v<Source,float> )
    {
      if constexpr( std::is_same_v<Target,double> ) return _mm_castps_pd(v0);
      if constexpr( std::is_integral_v<Target>     ) return _mm_castps_si128(v0);
    }

    // bitwise_cast from double
    if constexpr( std::is_same_v<Source,double> )
    {
      if constexpr( std::is_same_v<Target,float>) return _mm_castpd_ps(v0);
      if constexpr( std::is_integral_v<Target>   ) return _mm_castpd_si128(v0);
    }

    // bitwise_cast from integer
    if constexpr( std::is_integral_v<Source> )
    {
      if constexpr( std::is_same_v<Target,float>  ) return _mm_castsi128_ps(v0);
      if constexpr( std::is_same_v<Target,double> ) return _mm_castsi128_pd(v0);
      if constexpr( std::is_integral_v<Target>     ) return v0.storage();
    }
  }
} }

#endif
