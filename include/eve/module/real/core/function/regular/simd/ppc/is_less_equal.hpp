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

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/forward.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto is_less_equal_(EVE_SUPPORTS(vmx_),
                                      wide<T, N, ppc_> const &v0,
                                      wide<T, N, ppc_> const &v1) noexcept
  {
    using t_t = wide<T, N, ppc_>;
    if constexpr(std::is_floating_point_v<T>) return as_logical_t<t_t>(vec_cmple(v0.storage(), v1.storage()));
    else                                      return !eve::is_greater(v0, v1);
  }
}

