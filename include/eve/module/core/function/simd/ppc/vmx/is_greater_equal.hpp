//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_VMX_IS_GREATER_EQUAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_VMX_IS_GREATER_EQUAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_less.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE auto is_greater_equal_( EVE_SUPPORTS(vmx_),
                                          wide<T, N, ppc_> const &v0, wide<T, N, ppc_> const &v1
                                        ) noexcept
  {
    using t_t = wide<T, N, ppc_>;
    if constexpr(std::is_floating_point_v<T>)
      return as_logical_t<t_t>(vec_cmpge(v0.storage(), v1.storage()));
    else
      return !eve::is_less(v0, v1);
  }
}

#endif
