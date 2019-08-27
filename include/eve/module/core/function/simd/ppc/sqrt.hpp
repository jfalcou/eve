//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_SQRT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_SQRT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_> sqrt_(EVE_SUPPORTS(vmx_), wide<T, N, ppc_> const &v0) noexcept
  {
    if constexpr( std::is_floating_point_v<T> )
    {
      if constexpr( current_api == vmx )
      {
        auto that = if_else(v0, v0 * rsqrt(v0), v0);
        if constexpr( platform::supports_invalids)
        {
          return if_else( v0 == Inf(as(v0)), v0, that);
        }
        else
        {
          return that;
        }
      }
      else
      {
        return vec_sqrt(v0.storage());
      }
    }
    else
    {
      return map(raw_(sqrt),v0);
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_> sqrt_( EVE_SUPPORTS(vmx_),
                                          raw_type const &,
                                          wide<T, N, ppc_> const &v0
                                        ) noexcept
  {
    if constexpr( std::is_floating_point_v<T> )
    {
      if constexpr( current_api == vmx )
      {
        return if_else(v0, v0 * raw_(rsqrt)(v0), eve::zero_);
      }
      else
      {
        return vec_sqrt(v0.storage());
      }
    }
    else
    {
      return map(raw_(sqrt),v0);
    }
  }
}

#endif
