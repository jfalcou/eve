//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/vectorized.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/reduce.hpp>
#include <eve/function/splat.hpp>
#include <eve/function/splat.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, typename ABI, typename Callable>
  EVE_FORCEINLINE auto reduce_( EVE_SUPPORTS(cpu_), splat_type const&
                              , wide<T,N,ABI> v, Callable f
                              ) noexcept
  {
    return splat(detail::basic_reduce)(v,f);
  }

  template<real_scalar_value T, typename N, typename ABI, typename Callable>
  EVE_FORCEINLINE auto reduce_(EVE_SUPPORTS(cpu_), wide<T,N,ABI> v, Callable f) noexcept
  {
    return detail::basic_reduce(v,f);
  }
}
