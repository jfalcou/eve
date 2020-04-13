//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_X86_LOOKUP_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_X86_LOOKUP_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/function/simd/lookup_helpers.hpp>
#include <eve/forward.hpp>

//TODO: later std::bit_cast
#include <eve/module/core/function/simd/x86/bit_cast.hpp>

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
            i1 = bit_cast(bit_cast(i1,as<wide<I,N,sse_>>())+offset<I>,as<t8_t>());

      t8_t const blocks = _mm_shuffle_epi8(bit_cast(a,as<t8_t>()),i1);
      return bit_cast( blocks, as(a));
    }
  }
}

#endif
