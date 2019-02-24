//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX2_SHL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX2_SHL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/architecture.hpp>
#include <eve/forward.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_or.hpp>
#include <eve/detail/assert_utils.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename I>
  EVE_FORCEINLINE wide<T, N, avx_>
                  shl_(EVE_SUPPORTS(avx2_), wide<T, N, avx_> const &a0, I a1) noexcept
  {
    using t_t = wide<T, N, avx_>;
    assert(assert_good_shift<t_t>(a1) && "shl avx2: a shift is out of range");
    if constexpr(std::is_floating_point_v<T>)
    {
      using i_t = wide<detail::as_integer_t<T>, N>;
      using t_t = wide<T, N, avx_>;
      return bitwise_cast<t_t>(shl(bitwise_cast<i_t>(a0), a1));
    }
    if constexpr(std::is_integral_v<T>)
    {
      if constexpr(sizeof(T) == 1)
      {
        using gen_t     = wide<std::uint16_t, fixed<N::value / 2>>;
        t_t const Mask1 = bitwise_cast<t_t>( gen_t(0x00ff));
        t_t const Mask2 = bitwise_cast<t_t>( gen_t(0xff00));
        t_t tmp  = bitwise_and(a0, Mask1);
        t_t       tmp1  = _mm256_slli_epi16(tmp, a1);
        tmp1 = bitwise_and(tmp1, Mask1);
        tmp = bitwise_and(a0, Mask2);
        t_t tmp3        = _mm256_slli_epi16(tmp, int(a1));
        return bitwise_or(tmp1, bitwise_and(tmp3, Mask2));
      }
      if constexpr(sizeof(T) == 2) return _mm256_slli_epi16(a0, a1);
      if constexpr(sizeof(T) == 4) return _mm256_slli_epi32(a0, a1);        
      if constexpr(sizeof(T) == 8) return _mm256_slli_epi64(a0, a1);
    }
  }

  template<typename T, typename N, typename I>
  EVE_FORCEINLINE wide<T, N, avx_>
                  shl_(EVE_SUPPORTS(avx2_)
                      , wide<T, N, avx_> const &a0
                      , wide<I, N, avx_> const &a1) noexcept
  {
    using t_t = wide<T, N, avx_>;
    assert(assert_good_shift<t_t>(a1) && "shl avx2: a shift is out of range");
    if constexpr(std::is_floating_point_v<T>)
    {
      using i_t = wide<detail::as_integer_t<T>, N>;
      using t_t = wide<T, N, avx_>;
      return bitwise_cast<t_t>(shl(bitwise_cast<i_t>(a0), a1));
    }
    if constexpr(std::is_integral_v<T>)
    {
      if constexpr(sizeof(T) <= 2) return map(eve::shl, a0, a1);
      if constexpr(sizeof(T) == 4) return _mm256_sllv_epi32(a0, a1);        
      if constexpr(sizeof(T) == 8) return _mm256_sllv_epi64(a0, a1);
    }
    
  }

}

#endif
