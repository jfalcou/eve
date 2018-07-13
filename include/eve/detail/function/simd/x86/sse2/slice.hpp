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

namespace eve { namespace detail
{
  // -----------------------------------------------------------------------------------------------
  // double
  template< typename N, typename Slice
          , typename = std::enable_if_t<(N::value>1)>
          >
  EVE_FORCEINLINE auto slice( pack<double,N,sse_> const& a, Slice const& ) noexcept
  {
    if constexpr(Slice::value)
      return pack<double,typename N::split_type>(_mm_shuffle_pd(a,a,0x01));
    else
      return pack<double,typename N::split_type>(a.storage());
  }

  // -----------------------------------------------------------------------------------------------
  // float
  template< typename N, typename Slice
          , typename = std::enable_if_t<(N::value>1)>
          >
  EVE_FORCEINLINE auto slice( pack<float,N,sse_> const& a, Slice const& ) noexcept
  {
    if constexpr(Slice::value)
    {
      auto select = [](auto const& v, auto const& size)
      {
        using size_ = std::decay_t<decltype(size)>;
        if constexpr(size_::value == 4) return _mm_shuffle_ps(v,v,0x0E);
        if constexpr(size_::value == 2) return _mm_shuffle_ps(v,v,0x11);
      };

      return pack<float,typename N::split_type>(select(a,N{}));
    }
    else
    {
      return pack<float,typename N::split_type>(a.storage());
    }
  }

  // -----------------------------------------------------------------------------------------------
  // integers
  template< typename T,typename N, typename Slice
          , typename = std::enable_if_t <   std::is_integral_v<T>
                                        &&  (N::value>1)
                                        >
          >
  EVE_FORCEINLINE auto slice( pack<T,N,sse_> const& a, Slice const& ) noexcept
  {
    if constexpr(Slice::value)
    {
      auto select = [](auto const& v)
      {
        using that_t = pack<T,typename N::split_type>;

        if constexpr(N::value == 2)
          return that_t(v[1]);
        if constexpr(N::value*sizeof(T) == limits<eve::sse2_>::bytes)
          return that_t(_mm_shuffle_epi32(v,0xEE));
        if constexpr(N::value*sizeof(T)*2 == limits<eve::sse2_>::bytes)
          return that_t(_mm_shuffle_epi32(v,0x01));
        else
          return that_t(_mm_shufflelo_epi16(v,0x01));
      };

      return pack<T,typename N::split_type>(select(a));
    }
    else
    {
      return pack<T,typename N::split_type>(a.storage());
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Both slice
  template< typename N, typename T
          , typename = std::enable_if_t<(N::value>1)>
          >
  EVE_FORCEINLINE auto slice( pack<T,N,sse_> const& a ) noexcept
  {
    std::array<pack<T,typename N::split_type>,2> that{slice(a,lower_), slice(a,upper_)};
    return that;
  }
} }

#endif
