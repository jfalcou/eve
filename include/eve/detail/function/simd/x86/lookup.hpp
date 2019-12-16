//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_X86_LOOKUP_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_X86_LOOKUP_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/if_else.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/detail/function/simd/lookup.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename I, typename N>
  EVE_FORCEINLINE wide<T,N,sse_> lookup_( EVE_SUPPORTS(ssse3_),
                                          wide<T,N,sse_> a, wide<I,N,sse_> idx
                                        ) noexcept
  {
    // TODO: We use sizeof as a discriminant but we could actually use shuffle
    // to extract the one byte for the lookup form bigger integer and put them inside
    // a proper wide<char> before indexing. This would make lookup usable with any
    // integer index on x86
    if constexpr(sizeof(I) == 1)
    {
      return _mm_shuffle_epi8(a, idx);
    }
    else
    {
      using t8_t = typename wide<T,N,sse_>::template rebind<std::uint8_t, fixed<16>>;

      t8_t  i1 = _mm_shuffle_epi8(idx<<shift<I>, t8_t{repeater<I>});
            i1 = bitwise_cast(bitwise_cast(i1,as<wide<I,N,sse_>>())+offset<I>,as<t8_t>());
      t8_t const blocks = _mm_shuffle_epi8(bitwise_cast(a,as<t8_t>()),i1);

      return bitwise_cast( blocks, as(a));
    }
  }

  template<typename T, typename I, typename N>
  EVE_FORCEINLINE wide<T,N,avx_> lookup_( EVE_SUPPORTS(avx_),
                                          wide<T,N,avx_> a, wide<I,N,avx_> idx
                                        ) noexcept
  {
    puts("XXXXX");
    // TODO: Find a way to benchmark this as we generate quite a bunch of operations
    // Is it better than the scalar unrolling ?
    auto[hx,lx] = a.slice();
    auto[hi,li] = idx.slice();

    constexpr auto sz = N::value/2;
    auto ch = hi<sz;
    auto cl = li<sz;

    auto hu = lookup(hx,if_else(ch , hi           , eve::allbits_ ));
    auto hv = lookup(lx,if_else(ch , eve::allbits_, hi-sz         ));
    auto lu = lookup(hx,if_else(cl , li           , eve::allbits_ ));
    auto lv = lookup(lx,if_else(cl , eve::allbits_, li-sz         ));

    return wide<T,N,avx_>(hu|hv,lu|lv);
  }
}

#endif
