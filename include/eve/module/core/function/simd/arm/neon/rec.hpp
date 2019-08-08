//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_REC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_REC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/refine_rec.hpp>
#include <eve/forward.hpp>
#include <eve/tags.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> rec_( EVE_SUPPORTS(neon128_),
                                            raw_type const & mode,
                                            wide<T, N, neon64_> const &v0
                                          ) noexcept
  {
#if defined(__aarch64__)
    if constexpr( std::is_same_v<T,double>)
    {
      return vrecpe_f64(v0);
    }
#endif

    if constexpr( std::is_same_v<T,float>)
    {
      return vrecpe_f32(v0);
    }
    else
    {
      return rec_(EVE_RETARGET(simd_), mode, v0);
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> rec_ ( EVE_SUPPORTS(neon128_),
                                              raw_type const& mode,
                                              wide<T, N, neon128_> const &v0
                                            ) noexcept
  {
#if defined(__aarch64__)
    if constexpr( std::is_same_v<T,double>)
    {
      return vrecpeq_f64(v0);
    }
#endif

    if constexpr( std::is_same_v<T,float>)
    {
      return vrecpeq_f32(v0);
    }
    else
    {
      return rec_(EVE_RETARGET(simd_), mode, v0);
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> rec_( EVE_SUPPORTS(neon128_),
                                            wide<T, N, neon64_> const &v0
                                          ) noexcept
  {
#if defined(__aarch64__)
    if constexpr( std::is_same_v<T,double>)
    {
      return wide<T, N, neon64_>{T{1}/v0[0]};
    }
#endif

    if constexpr( std::is_same_v<T,float>)
    {
      // estimate 1/x with an extra NR step for full precision
      auto a = refine_rec(v0, raw_(rec)(v0) );
      return refine_rec(v0, a );
    }
    else
    {
      return rec_(EVE_RETARGET(simd_), v0);
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> rec_( EVE_SUPPORTS(neon128_),
                                            wide<T, N, neon128_> const &v0
                                          ) noexcept
  {
    if constexpr( std::is_floating_point_v<T>)
    {
      // estimate 1/x with an extra NR step for full precision
      auto a = refine_rec(v0, raw_(rec)(v0) );
      return refine_rec(v0, a );
    }
    else
    {
      return rec_(EVE_RETARGET(simd_), v0);
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> rec_( EVE_SUPPORTS(neon128_),
                                            pedantic_type const & mode,
                                            wide<T, N, neon64_> const &v0
                                          ) noexcept
  {
    if constexpr( std::is_floating_point_v<T> )
    {
      return rec(v0);
    }
    else
    {
      return rec_(EVE_RETARGET(simd_), mode, v0);
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> rec_ ( EVE_SUPPORTS(neon128_),
                                              pedantic_type const & mode,
                                              wide<T, N, neon128_> const &v0
                                            ) noexcept
  {
    if constexpr( std::is_floating_point_v<T> )
    {
      return rec(v0);
    }
    else
    {
      return rec_(EVE_RETARGET(simd_), mode, v0);
    }
  }
}

#endif
