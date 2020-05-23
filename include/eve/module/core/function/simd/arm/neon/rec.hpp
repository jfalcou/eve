//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_REC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_REC_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/refine_rec.hpp>
#include <eve/function/raw.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_>
                  rec_(EVE_SUPPORTS(neon128_), raw_type const &mode, wide<T, N, neon64_> const &v0) noexcept
  {
#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) { return vrecpe_f64(v0); }
#endif

    if constexpr(std::is_same_v<T, float>) { return vrecpe_f32(v0); }
  }

  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_>
                  rec_(EVE_SUPPORTS(neon128_), raw_type const &mode, wide<T, N, neon128_> const &v0) noexcept
  {
#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) { return vrecpeq_f64(v0); }
#endif

    if constexpr(std::is_same_v<T, float>) { return vrecpeq_f32(v0); }
  }

  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> rec_(EVE_SUPPORTS(neon128_),
                                           wide<T, N, neon64_> const &v0) noexcept
  {
#if defined(__aarch64__)
    if constexpr(std::is_same_v<T, double>) { return wide<T, N, neon64_>{T{1} / v0[ 0 ]}; }
#endif

    if constexpr(std::is_same_v<T, float>)
    {
      // estimate 1/x with an extra NR step for full precision
      auto a = refine_rec(v0, raw_(rec)(v0));
      return refine_rec(v0, a);
    }
  }

  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> rec_(EVE_SUPPORTS(neon128_),
                                            wide<T, N, neon128_> const &v0) noexcept
  {
      // estimate 1/x with an extra NR step for full precision
      auto a = refine_rec(v0, raw_(rec)(v0));
      return refine_rec(v0, a);
  }

  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_>
                  rec_(EVE_SUPPORTS(neon128_), pedantic_type const &mode, wide<T, N, neon64_> const &v0) noexcept
  {
    return rec(v0);
  }

  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_>
                  rec_(EVE_SUPPORTS(neon128_), pedantic_type const &mode, wide<T, N, neon128_> const &v0) noexcept
  {
    return rec(v0);
  }
}

#endif
