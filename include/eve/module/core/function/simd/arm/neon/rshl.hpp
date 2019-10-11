//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_RSHL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_RSHL_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/function/simd/arm/neon/detail/shift.hpp>
#include <eve/forward.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename I>
  EVE_FORCEINLINE auto rshl_(EVE_SUPPORTS(neon128_),
                             wide<T, N, neon64_> const &v0,
                             wide<I, N, neon64_> const &v1) noexcept requires(wide<T, N, neon64_>,
                                                                              Integral<I>,
                                                                              Integral<T>)
  {
    return neon_shifter(v0, v1);
  }

  template<typename T, typename N, typename I>
  EVE_FORCEINLINE auto rshl_(EVE_SUPPORTS(neon128_),
                             wide<T, N, neon64_> const &v0,
                             I v1) noexcept requires(wide<T, N, neon64_>, Integral<I>, Integral<T>)
  {
    using i_t = wide<as_integer_t<T, signed>, N>;
    return eve::rshl(v0, i_t(v1));
  }

  template<typename T, typename N, typename I>
  EVE_FORCEINLINE auto rshl_(EVE_SUPPORTS(neon128_),
                             wide<T, N, neon128_> const &v0,
                             wide<I, N, neon128_> const &v1) noexcept requires(wide<T, N, neon128_>,
                                                                               Integral<I>,
                                                                               Integral<T>)
  {
    return neon_shifter(v0, v1);
  }

  template<typename T, typename N, typename I>
  EVE_FORCEINLINE auto rshl_(EVE_SUPPORTS(neon128_),
                             wide<T, N, neon128_> const &v0,
                             I v1) noexcept requires(wide<T, N, neon128_>, Integral<I>, Integral<T>)
  {
    using i_t = wide<as_integer_t<T, signed>, N>;
    return eve::rshl(v0, i_t(v1));
  }
}

#endif
