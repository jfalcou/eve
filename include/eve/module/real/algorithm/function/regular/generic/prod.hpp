//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/reduce.hpp>
#include <eve/function/mul.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, typename ABI>
  EVE_FORCEINLINE auto prod_ ( EVE_SUPPORTS(cpu_)
                                , splat_type const&, wide<T,N,ABI> const &v
                                ) noexcept
  {
    return splat(reduce)(v, eve::mul);
  }

  template<real_scalar_value T>
  EVE_FORCEINLINE auto prod_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  {
    return v;
  }

  template<real_scalar_value T, typename N, typename ABI>
  EVE_FORCEINLINE auto prod_(EVE_SUPPORTS(cpu_), wide<T,N,ABI> const &v) noexcept
  {
    return reduce(v, eve::mul);
  }
}
