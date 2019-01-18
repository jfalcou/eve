//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_X86_SSE2_COMBINE_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_X86_SSE2_COMBINE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/arch/limits.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // double
  template<typename N>
  EVE_FORCEINLINE auto combine( sse2_ const&
                              , pack<double,N,sse_> const& l, pack<double,N,sse_> const& h
                              ) noexcept
  {
    using that_t = pack<double,typename N::combined_type>;

    if constexpr(N::value == 2)
      return that_t( typename that_t::storage_type{l,h} );
    else
      return that_t{_mm_shuffle_pd(l,h,0x20)};
  }

  // -----------------------------------------------------------------------------------------------
  // float
  template<typename N>
  EVE_FORCEINLINE auto combine( sse2_ const&
                              , pack<float,N,sse_> const& l, pack<float,N,sse_> const& h
                              ) noexcept
  {
    using that_t = pack<float,typename N::combined_type>;

    if constexpr(N::value == 4) return that_t( typename that_t::storage_type{l,h} );
    if constexpr(N::value == 2) return that_t{_mm_shuffle_ps(l,h,0x44)};

    if constexpr(N::value == 1)
    {
      that_t that = l.storage();
      that[1] = h[0];
      return that;
    }
  }

  // -----------------------------------------------------------------------------------------------
  // integers
  template< typename T, typename N>
  EVE_FORCEINLINE auto  combine ( sse2_ const&
                                , pack<T,N,sse_> const& l, pack<T,N,sse_> const& h
                                ) noexcept
                        requires( pack<T,typename N::combined_type>, Integral<T>)

  {
    using that_t = pack<T,typename N::combined_type>;
    constexpr auto sz = that_t::static_size;

    if constexpr      (sz*sizeof(T) ==  2*limits<sse2_>::bytes)
      return that_t( typename that_t::storage_type{l,h} );

    else if constexpr (sz*sizeof(T) ==  limits<sse2_>::bytes)
      return that_t ( _mm_castps_si128 ( _mm_shuffle_ps ( _mm_castsi128_ps(l.storage())
                                                        , _mm_castsi128_ps(h.storage())
                                                        , 0x44
                                                        )
                                      )
                    );

    else if constexpr (2*sz*sizeof(T) ==  limits<sse2_>::bytes)
      return that_t( _mm_shuffle_epi32( _mm_castps_si128
                                        ( _mm_shuffle_ps( _mm_castsi128_ps(l.storage())
                                                        , _mm_castsi128_ps(h.storage())
                                                        , 0x44
                                                        )
                                        )
                                      , 0x88
                                      )
                  );

    else if constexpr (sz == 4)
      return that_t(l[0],l[1],h[0],h[1]);

    else if constexpr (sz == 2)
      return that_t(l[0],h[0]);
  }

  // -----------------------------------------------------------------------------------------------
  // logicals
  template<typename T, typename N>
  EVE_FORCEINLINE
  typename pack<logical<T>, typename N::combined_type>::storage_type
  combine(sse2_ const&, pack<logical<T>,N,sse_> const& l, pack<logical<T>,N,sse_> const& h) noexcept
  {
    using that_t = pack<logical<T>,typename N::combined_type>;
    return that_t( typename that_t::storage_type{l,h} );
  }
}

#endif
