//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_X86_SSE2_SLICE_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_X86_SSE2_SLICE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/arch/limits.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <cstddef>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Single slice
  template<typename N, typename Slice>
  EVE_FORCEINLINE auto slice( pack<double,N,sse_> const& a, Slice const& ) noexcept
                  requires(pack<double,typename N::split_type>,If<(N::value>1)>)
  {
    using that_t = pack<double,typename N::split_type>;

    if constexpr(Slice::value)
    {
      return that_t(_mm_shuffle_pd(a,a,0x01));
    }
    else
    {
      return that_t(a.storage());
    }
  }

  template<typename N, typename Slice>
  EVE_FORCEINLINE auto slice( pack<float,N,sse_> const& a, Slice const& ) noexcept
                  requires(pack<float,typename N::split_type>,If<(N::value>1)>)
  {
    using that_t = pack<float,typename N::split_type>;

    if constexpr(Slice::value)
    {
      if constexpr(N::value == 4) return that_t(_mm_shuffle_ps(a,a,0x0E));
      if constexpr(N::value == 2) return that_t(_mm_shuffle_ps(a,a,0x11));
    }
    else
    {
      return that_t(a.storage());
    }
  }

  template<typename T, typename N, typename Slice>
  EVE_FORCEINLINE auto slice( pack<T,N,sse_> const& a, Slice const& ) noexcept
                  requires( pack<T,typename N::split_type>
                          , If<(N::value>1)>, Integral<T>
                          )
  {
    using that_t = pack<T,typename N::split_type>;

    if constexpr(Slice::value)
    {
      constexpr auto bytes_size = N::value*sizeof(T);
      constexpr auto lims       = limits<eve::sse2_>::bytes;

      if constexpr(  N::value   == 2   )  return that_t(a[1]);
      if constexpr(  bytes_size == lims)  return that_t(_mm_shuffle_epi32(a,0xEE));
      if constexpr(2*bytes_size == lims)  return that_t(_mm_shuffle_epi32(a,0x01));
      else                                return that_t(_mm_shufflelo_epi16(a,0x01));
    }
    else
    {
      return that_t(a.storage());
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Both slice
  template<typename T, typename N>
  EVE_FORCEINLINE auto  slice( pack<T,N,sse_> const& a ) noexcept
                        requires(std::array<pack<T,typename N::split_type>,2>,If<(N::value>1)>)
  {
    std::array<pack<T,typename N::split_type>,2> that{slice(a,lower_), slice(a,upper_)};
    return that;
  }
}

#endif
