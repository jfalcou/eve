//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_IS_EQUAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_IS_EQUAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  is_equal_(EVE_SUPPORTS(vmx_), wide<T, N, ppc_> const &v0, wide<T, N, ppc_> const &v1) noexcept
  {
    using t_t = wide<T, N, ppc_>;
    return as_logical_t<t_t>(vec_cmpeq(v0.storage(), v1.storage()));
  }
}

#endif
