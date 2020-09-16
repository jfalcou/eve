//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // 128 bits if_else
  template<real_scalar_value T, typename U, typename N>
  EVE_FORCEINLINE wide<U, N, sse_> if_else_(EVE_SUPPORTS(sse4_1_),
                                            logical<wide<T, N, sse_>> const &v0,
                                            wide<U, N, sse_> const &v1,
                                            wide<U, N, sse_> const &v2) noexcept
  {
    if constexpr(std::is_same_v<U, float>)        return _mm_blendv_ps(v2, v1, bit_cast(bit_mask(v0),as(v2)));
    else if constexpr(std::is_same_v<U, double>)  return _mm_blendv_pd(v2, v1, bit_cast(bit_mask(v0),as(v2)));
    else                                          return _mm_blendv_epi8(v2, v1, bit_cast(bit_mask(v0),as(v2)));
  }

  template<real_scalar_value T, typename U, typename N>
  EVE_FORCEINLINE wide<U, N, sse_> if_else_(EVE_SUPPORTS(sse4_1_),
                                            wide<T, N, sse_> const &v0,
                                            wide<U, N, sse_> const &v1,
                                            wide<U, N, sse_> const &v2) noexcept
  {
    return if_else(is_nez(v0), v1, v2);
  }

  template<real_scalar_value T, typename U, typename N>
  EVE_FORCEINLINE auto if_else_(EVE_SUPPORTS(sse4_1_),
                                logical<wide<T, N, sse_>> const &v0,
                                logical<wide<U, N, sse_>> const &v1,
                                logical<wide<U, N, sse_>> const &v2) noexcept
  {
    return bit_cast(if_else(v0, v1.mask(), v2.mask()), as(v2));
  }

  template<real_scalar_value T, typename U, typename N>
  EVE_FORCEINLINE logical<wide<U, N, sse_>> if_else_(EVE_SUPPORTS(sse4_1_),
                                            wide<T, N, sse_> const &v0,
                                            logical<wide<U, N, sse_>> const &v1,
                                            logical<wide<U, N, sse_>> const &v2) noexcept
  {
    return if_else(is_nez(v0), v1, v2);
  }

  //------------------------------------------------------------------------------------------------
  // 256 bits if_else
  template<real_scalar_value T, typename U, typename N>
  EVE_FORCEINLINE wide<U, N, avx_> if_else_(EVE_SUPPORTS(avx_),
                                            logical<wide<T, N, avx_>> const &v0,
                                            wide<U, N, avx_> const &v1,
                                            wide<U, N, avx_> const &v2) noexcept
  {
         if constexpr(std::is_same_v<U, float>)  return _mm256_blendv_ps(v2, v1,  bit_cast(v0.bits(),as(v2)));
    else if constexpr(std::is_same_v<U, double>) return _mm256_blendv_pd(v2, v1,  bit_cast(v0.bits(),as(v2)));
    else if constexpr(std::is_integral_v<U>)
    {
      if constexpr(current_api >= avx2)
      {
        using a_t = wide<as_integer_t<T>, N>;
        return _mm256_blendv_epi8(v2, v1, bit_cast(v0.bits(),as_<a_t>()));
      }
      else
      {
        if constexpr(std::is_integral_v<U> && sizeof(U) <= 2)      return aggregate(if_else, v0, v1, v2);
        else if constexpr(std::is_integral_v<U> && sizeof(U) >= 4)
        {
          using f_t = wide<as_floating_point_t<U>, N, avx_>;
          return bit_cast( if_else( v0, bit_cast(v1,as_<f_t>()), bit_cast(v2,as_<f_t>())), as(v2));
        }
      }
    }
  }

  template<real_scalar_value T, typename U, typename N>
  EVE_FORCEINLINE wide<U, N, avx_> if_else_(EVE_SUPPORTS(avx_),
                                            wide<T, N, avx_> const &v0,
                                            wide<U, N, avx_> const &v1,
                                            wide<U, N, avx_> const &v2) noexcept
  {
    return if_else(is_nez(v0), v1, v2);
  }

  template<real_scalar_value T, typename U, typename N>
  EVE_FORCEINLINE auto if_else_(EVE_SUPPORTS(avx_),
                                            logical<wide<T, N, avx_>> const &v0,
                                            logical<wide<U, N, avx_>> const &v1,
                                            logical<wide<U, N, avx_>> const &v2) noexcept
  {
    return bit_cast(if_else(v0, v1.mask(), v2.mask()), as(v2));
  }

  template<real_scalar_value T, typename U, typename N>
  EVE_FORCEINLINE auto if_else_(EVE_SUPPORTS(avx_),
                                            wide<T, N, avx_> const &v0,
                                            logical<wide<U, N, avx_>> const &v1,
                                            logical<wide<U, N, avx_>> const &v2) noexcept
  {
    return bit_cast(if_else(is_nez(v0), v1.mask(), v2.mask()), as(v2));
  }

}
