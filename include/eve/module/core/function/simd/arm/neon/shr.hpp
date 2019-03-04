//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_SHR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_SHR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/forward.hpp>
#include <eve/function/unary_minus.hpp>
#include <eve/function/shl.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename I>
  EVE_FORCEINLINE auto shr_ ( EVE_SUPPORTS(neon128_),
                              wide<T, N, neon64_> const &v0,
                              wide<I, N, neon64_> const &v1) noexcept
  requires(wide<T, N, neon64_>, Integral<I>, Integral<T>)
  {
    EVE_ASSERT( (detail::assert_good_shift<wide<T, N, neon64_>>(v1)),
               "[eve::shr neon64] - At least one of " << v1 << "elements is out of the range [0, "
                                                       << sizeof(T) * 8 << "[.");
    return eve::shl(v0,-v1);
  }

  template<typename T, typename N, typename I>
  EVE_FORCEINLINE auto shr_(EVE_SUPPORTS(neon128_),wide<T, N, neon64_> const &v0,I v1) noexcept
  requires(wide<T, N, neon64_>, Integral<I>, Integral<T>)
  {
    using i_t = wide<as_integer_t<T,signed>,N>;
    return eve::shr(v0,i_t(v1));
  }

  template<typename T, typename N, typename I>
  EVE_FORCEINLINE auto shr_( EVE_SUPPORTS(neon128_),
                             wide<T, N, neon128_> const &v0,
                             wide<I, N, neon128_> const &v1) noexcept
  requires(wide<T, N, neon128_>, Integral<I>, Integral<T>)
  {
    EVE_ASSERT( (detail::assert_good_shift<wide<T, N, neon128_>>(v1)),
               "[eve::shr neon128] - At least one of " << v1 << "elements is out of the range [0, "
                                                       << sizeof(T) * 8 << "[.");
    return eve::shl(v0,-v1);
  }

  template<typename T, typename N, typename I>
  EVE_FORCEINLINE auto shr_(EVE_SUPPORTS(neon128_),wide<T, N, neon128_> const &v0,I v1) noexcept
  requires(wide<T, N, neon128_>, Integral<I>, Integral<T>)
  {
    using i_t = wide<as_integer_t<T,signed>,N>;
    return eve::shr(v0,i_t(v1));
  }
}

#endif
