//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_REC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_REC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/refine_rec.hpp>
#include <eve/function/bitwise_or.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/forward.hpp>
#include <eve/tags.hpp>

#if !defined(EVE_NO_INFINITIES)
#  include <eve/constant/mzero.hpp>
#  include <eve/function/bitwise_and.hpp>
#  include <eve/function/is_infinite.hpp>
#endif

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_>
                  rec_(EVE_SUPPORTS(vmx_), raw_type const &mode, wide<T, N, ppc_> const &v0) noexcept
  {
    if constexpr(std::is_floating_point_v<T>) { return vec_re(v0.storage()); }
    else
    {
      return rec_(EVE_RETARGET(cpu_), mode, v0);
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_> rec_(EVE_SUPPORTS(vmx_), wide<T, N, ppc_> const &v0) noexcept
  {
    if constexpr(std::is_same_v<double, T>)
    {
      auto estimate = refine_rec(v0, raw_(rec)(v0));
      return refine_rec(v0, estimate);
    }
    else if constexpr(std::is_same_v<float, T>)
    {
      return refine_rec(v0, raw_(rec)(v0));
    }
    else
    {
      return rec_(EVE_RETARGET(cpu_), v0);
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_>
                  rec_(EVE_SUPPORTS(vmx_), pedantic_type const &mode, wide<T, N, ppc_> const &v0) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      auto estimate = rec(v0);

      estimate = if_else(is_eqz(v0), bitwise_or(v0, Inf(as(v0))), estimate);

#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_REC_HPP_INCLUDED
      estimate = if_else(is_infinite(v0), bitwise_and(v0, Mzero(as(v0))), estimate);
#endif

      return estimate;
    }
    else
    {
      return rec_(EVE_RETARGET(cpu_), mode, v0);
    }
  }
}

#endif
