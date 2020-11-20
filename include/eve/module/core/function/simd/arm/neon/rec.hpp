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

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> rec_(EVE_SUPPORTS(neon128_)
                                      , raw_type const &
                                      , wide<T, N, ABI> const& v) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();
    
    
         if constexpr( cat == category::float32x2) return vrecpe_f32(v);
    else if constexpr( cat == category::float32x4) return vrecpe_f32(v);
#  if defined(__aarch64__)
    else if constexpr( cat == category::float64x1) return vrecpe_f64(v);
    else if constexpr( cat == category::float64x2) return vrecpeq_f64(v);
#  endif
    else                                           return map(ceil, v);
  }
  
  template<floating_real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> rec_(EVE_SUPPORTS(neon128_),
                                       wide<T, N, ABI> const &v0) noexcept
  {
      // estimate 1/x with an extra NR step for full precision
      auto a = refine_rec(v0, raw(rec)(v0));
      return refine_rec(v0, a);
  }

  
// #include <eve/detail/implementation.hpp>
// #include <eve/function/refine_rec.hpp>
// #include <eve/function/raw.hpp>
// #include <eve/concept/value.hpp>

// namespace eve::detail
// {
//   template<floating_real_scalar_value T, typename N>
//   EVE_FORCEINLINE wide<T, N, arm_64_>
//                   rec_(EVE_SUPPORTS(neon128_), raw_type const &, wide<T, N, arm_64_> const &v0) noexcept
//   {
// #if defined(__aarch64__)
//     if constexpr(std::is_same_v<T, double>) { return vrecpe_f64(v0); }
// #endif

//     if constexpr(std::is_same_v<T, float>) { return vrecpe_f32(v0); }
//   }

//   template<floating_real_scalar_value T, typename N>
//   EVE_FORCEINLINE wide<T, N, arm_128_>
//                   rec_(EVE_SUPPORTS(neon128_), raw_type const &, wide<T, N, arm_128_> const &v0) noexcept
//   {
// #if defined(__aarch64__)
//     if constexpr(std::is_same_v<T, double>) { return vrecpeq_f64(v0); }
// #endif

//     if constexpr(std::is_same_v<T, float>) { return vrecpeq_f32(v0); }
//   }

//   template<floating_real_scalar_value T, typename N>
//   EVE_FORCEINLINE wide<T, N, arm_64_> rec_(EVE_SUPPORTS(neon128_),
//                                            wide<T, N, arm_64_> const &v0) noexcept
//   {
// #if defined(__aarch64__)
//     if constexpr(std::is_same_v<T, double>) { return wide<T, N, arm_64_>{T{1} / v0[ 0 ]}; }
// #endif

//     if constexpr(std::is_same_v<T, float>)
//     {
//       // estimate 1/x with an extra NR step for full precision
//       auto a = refine_rec(v0, raw(rec)(v0));
//       return refine_rec(v0, a);
//     }
//   }

//   template<floating_real_scalar_value T, typename N>
//   EVE_FORCEINLINE wide<T, N, arm_128_> rec_(EVE_SUPPORTS(neon128_),
//                                             wide<T, N, arm_128_> const &v0) noexcept
//   {
//       // estimate 1/x with an extra NR step for full precision
//       auto a = refine_rec(v0, raw(rec)(v0));
//       return refine_rec(v0, a);
//   }
// }

