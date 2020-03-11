//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_RSQRT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_RSQRT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/function/is_denormal.hpp>
#include <eve/function/any.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // Raw version
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_>
                  rsqrt_(EVE_SUPPORTS(neon128_), raw_type const &, wide<T, N, neon64_> const &v0) noexcept
  {
    using that_t = wide<T, N, neon64_>;

    if constexpr(std::is_same_v<T, double> && supports_aarch64) { return that_t(vrsqrte_f64(v0)); }
    else if constexpr(std::is_same_v<T, float>)
    {
      return that_t(vrsqrte_f32(v0));
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::rsqrt] - Unsupported integral parameters");
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_>
                  rsqrt_(EVE_SUPPORTS(neon128_), raw_type const &, wide<T, N, neon128_> const &v0) noexcept
  {
    using that_t = wide<T, N, neon128_>;

    if constexpr(std::is_same_v<T, double> && supports_aarch64) { return that_t(vrsqrteq_f64(v0)); }
    else if constexpr(std::is_same_v<T, float>)
    {
      return that_t(vrsqrteq_f32(v0));
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::rsqrt] - Unsupported integral parameters");
    }
  }

  //------------------------------------------------------------------------------------------------
  // Basic version
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> rsqrt_(EVE_SUPPORTS(neon128_),
                                             wide<T, N, neon64_> const &v0) noexcept
  {
    using that_t = wide<T, N, neon64_>;
 
    if constexpr(std::is_same_v<T, double> && supports_aarch64)
    {
      that_t inv  = vrsqrte_f64(v0);
      inv         = vmul_f64(vrsqrts_f64(v0, inv * inv), inv);
      inv         = vmul_f64(vrsqrts_f64(v0, inv * inv), inv);
      return that_t(vmul_f64(vrsqrts_f64(v0, inv * inv), inv));
    }
    else if constexpr(std::is_same_v<T, float>)
    {
      that_t inv  = vrsqrte_f32(v0);
      inv         = vmul_f32(vrsqrts_f32(v0, inv * inv), inv);
      return that_t(vmul_f32(vrsqrts_f32(v0, inv * inv), inv));
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::rsqrt] - Unsupported integral parameters");
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> rsqrt_(EVE_SUPPORTS(neon128_),
                                             wide<T, N, neon128_> const &v0) noexcept
  {
    using that_t = wide<T, N, neon128_>;

    if constexpr(std::is_same_v<T, double> && supports_aarch64)
    {
      that_t inv  = vrsqrteq_f64(v0);
      inv         = vmulq_f64(vrsqrtsq_f64(v0, inv * inv), inv);
      inv         = vmulq_f64(vrsqrtsq_f64(v0, inv * inv), inv);
      return that_t(vmulq_f64(vrsqrtsq_f64(v0, inv * inv), inv));
    }
    else if constexpr(std::is_same_v<T, float>)
    {
      that_t inv  = vrsqrteq_f32(v0);
      inv         = vmulq_f32(vrsqrtsq_f32(v0, inv * inv), inv);
      return that_t(vmulq_f32(vrsqrtsq_f32(v0, inv * inv), inv));
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::rsqrt] - Unsupported integral parameters");
    }
  }

 
  //------------------------------------------------------------------------------------------------
  // Pedantic version
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> rsqrt_(EVE_SUPPORTS(neon128_),
                                             pedantic_type const &, 
                                             wide<T, N, neon64_> const &v00) noexcept
  {
    if (any(is_denormal(v00)))
    {              
      using that_t = wide<T, N, neon64_>;
      auto[v0, nn] =  pedantic_(eve::ifrexp)(v00);
      auto tst = is_odd(nn);
      nn  = dec[tst](nn);
      v0 = mul[tst](v0,2);
      auto inv = rsqrt(v0);
      return that_t(pedantic_(eve::ldexp)(inv, -nn/2));
    }
    else return rsqrt(v00);
  }
  
    
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> rsqrt_(EVE_SUPPORTS(neon128_),
                                             pedantic_type const &, 
                                             wide<T, N, neon128_> const &v00) noexcept
  {
    if (any(is_denormal(v00)))
    {              
      using that_t = wide<T, N, neon128_>;
      auto[v0, nn] =  pedantic_(eve::ifrexp)(v00);
      auto tst = is_odd(nn);
      nn  = dec[tst](nn);
      v0 = mul[tst](v0,2);
      auto inv = rsqrt(v0);
      return that_t(pedantic_(eve::ldexp)(inv, -nn/2));
    }
    else return rsqrt(v00);
  } 
}

#endif
