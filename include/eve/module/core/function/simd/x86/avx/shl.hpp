//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_SHL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX_SHL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
#if defined(EVE_SUPPORTS_XOP)
  template<typename T, typename N, typename I>
  EVE_FORCEINLINE auto shl_(EVE_SUPPORTS(avx_)
                           , wide<T, N, sse_> const &a0
                           , wide<I, N, sse_> const &a1) noexcept
  requires(wide<T, N, sse_>, Integral<T>, Integral<I>)
  {
    using t_t = wide<T, N, sse_>;
    EVE_ASSERT(detail::assert_good_shift<t_t>(a1),
               "[eve::shl xop sse] - At least one of " << a1 << "elements is out of the range [0, "
                                                   << sizeof(T) * 8 << "[.");

      if constexpr(sizeof(T) == 1) return t_t(_mm_shl_epi8 (a0, a1));
      if constexpr(sizeof(T) == 2) return t_t(_mm_shl_epi16(a0, a1));
      if constexpr(sizeof(T) == 4) return t_t(_mm_shl_epi32(a0, a1));
      if constexpr(sizeof(T) == 8) return t_t(_mm_shl_epi64(a0, a1));
  }
#endif

  template<typename T, typename N, typename I>
  EVE_FORCEINLINE auto shl_(EVE_SUPPORTS(avx_), wide<T, N, avx_> const &a0, I a1) noexcept
  {
    return aggregate(eve::shl,a0,a1);
  }
}

#endif
