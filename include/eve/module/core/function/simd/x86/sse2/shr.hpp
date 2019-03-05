//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE2_SHR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE2_SHR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/architecture.hpp>
#include <eve/forward.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_or.hpp>
#include <eve/function/bitwise_ornot.hpp>
//TODO test if functions and bench are available
//#include <eve/function/if_else_allbits.hpp>
//#include <eve/function/is_ltz.hpp>
//#include <eve/constant/allbits.hpp>
#include <eve/assert.hpp>
#include <eve/detail/assert_utils.hpp>
#include <type_traits>
#include <cassert>

namespace eve ::detail
{
  template<typename T, typename N, typename I>
  EVE_FORCEINLINE auto shr_(EVE_SUPPORTS(sse2_)
                           , wide<T, N, sse_> const &a0, I a1) noexcept
  requires(wide<T, N, sse_>, Integral<T>, Integral<I>)
  {
    using t_t = wide<T, N, sse_>;
    EVE_ASSERT(detail::assert_good_shift<t_t>(a1),
               "[eve::shr sse2] -  At least one of " << a1 << "elements is out of the range [0, "
                                                     << sizeof(T) * 8 << "[.");
    if constexpr(std::is_unsigned_v<T>)
    {
      if constexpr(sizeof(T) == 1)
      {
        using int_t     = std::uint16_t;
        using gen_t     = wide<int_t, fixed<N::value / 2>>;
        t_t const Mask1 = bitwise_cast<t_t>(gen_t(0x00ff));
        t_t const Mask2 = bitwise_cast<t_t>(gen_t(0xff00));
        t_t tmp  = bitwise_and(a0, Mask1);
        t_t tmp1 = _mm_srli_epi16(tmp, int(a1));
        tmp1 = bitwise_and(tmp1, Mask1);
        tmp = bitwise_and(a0, Mask2);
        t_t tmp3 = _mm_srli_epi16(tmp, int(a1));
        return bitwise_or(tmp1, bitwise_and(tmp3, Mask2));
      }
      if constexpr(sizeof(T) == 2) { return _mm_srli_epi16(a0, a1); }
      if constexpr(sizeof(T) == 4) { return _mm_srli_epi32(a0, a1); }
      if constexpr(sizeof(T) == 8) { return _mm_srli_epi64(a0, a1); }
    }
    else
    {
      if constexpr(sizeof(T) == 1)
      {
        return map(eve::shr, a0, a1);
//           auto s = split(a0);
//           return bitwise_cast<A0>(group(shr(s[0], a1), shr(s[1], a1)));
      }
      if constexpr(sizeof(T) == 2) { return _mm_srai_epi16(a0, a1); }
      if constexpr(sizeof(T) == 4) { return _mm_srai_epi32(a0, a1); }
      if constexpr(sizeof(T) == 8)
      {
        return map(eve::shr, a0, a1);
//           t_t that = _mm_srli_epi64(a0, a1);
//           t_t mask = _mm_srli_epi64(Allbits<t_t>(), a1);
//           return bitwise_ornot(that, if_else_allbits(is_ltz(a0), mask));
      }
    }
  }

  template<typename T, typename N, typename I>
  EVE_FORCEINLINE auto shr_(EVE_SUPPORTS(sse2_)
                           , wide<T, N, sse_> const &a0
                           , wide<I, N, sse_> const &a1) noexcept
  requires(wide<T, N, sse_>, Integral<T>, Integral<I>)
  {
    EVE_ASSERT((detail::assert_good_shift<wide<T, N, sse_>>(a1)),
               "[eve::shr sse2] -  At least one of " << a1 << "elements is out of the range [0, "
                                                     << sizeof(T) * 8 << "[.");
    return map(eve::shr, a0, a1);
  }

}

#endif
