//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_RSHL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_RSHL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/shl.hpp>
#include <eve/function/shr.hpp>
#include <eve/function/abs.hpp>
#include <eve/forward.hpp>
#include <type_traits>

#ifndef NDEBUG
#include <eve/constant/zero.hpp>
#include <eve/function/max.hpp>
#endif

namespace eve::detail
{
  template<typename T, typename U, typename N, typename ABI>
  EVE_FORCEINLINE auto
  rshl_(EVE_SUPPORTS(simd_), wide<T, N, ABI> const &v0, wide<U, N, ABI> const &v1) noexcept
  {
    EVE_ASSERT( detail::assert_good_shift<T>(eve::abs(v1)),
                "[ eve::rshl ] (SIMD) - At least a shift absolute value (" << v1
                << ") is out of range [0, " << sizeof(T) * 8 << "[."
              );

    if      constexpr(is_aggregated_v<ABI>)   return aggregate(eve::rshl, v0, v1);
    else if constexpr(is_emulated_v<ABI>)     return map(eve::rshl, v0, v1);
    else if constexpr(std::is_unsigned_v<U>)  return shl(v0, v1);
    else
    {
#ifndef NDEBUG
      return if_else(is_gtz(v1), shl(v0, max(Zero(as(v1)), v1)), shr(v0, max(Zero(as(v1)), -v1)));
#else
      return if_else(is_gtz(v1), shl(v0, v1), shr(v0, -v1));
#endif
    }
  }


  template<typename T, typename U, typename N, typename ABI>
  EVE_FORCEINLINE auto rshl_(EVE_SUPPORTS(simd_), wide<T, N, ABI> const &v0, U const &v1) noexcept
  requires( wide<T, N, ABI>, Vectorizable<U> )
  {
    EVE_ASSERT( detail::assert_good_shift<T>(eve::abs(v1)),
                "[ eve::rshl ] (SIMD) - At least a shift absolute value (" << v1
                << ") is out of range [0, " << sizeof(T) * 8 << "[."
              );

    if      constexpr(is_aggregated_v<ABI>)   return aggregate(eve::rshl, v0, v1);
    else if constexpr(is_emulated_v<ABI>)     return map(eve::rshl, v0, v1);
    else if constexpr(std::is_unsigned_v<U>)  return shl(v0, v1);
    else
    {
#ifndef NDEBUG
      return if_else(is_gtz(v1), shl(v0, max(Zero(as(v1)), v1)), shr(v0, max(Zero(as(v1)), -v1)));
#else
      return if_else(is_gtz(v1), shl(v0, v1), shr(v0, -v1));
#endif
    }
  }
}

#endif
