//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/complex.hpp>
#include <eve/module/complex/regular/traits.hpp>
#include <eve/module/complex/regular/faddeeva.hpp>

namespace eve
{
  namespace detail
  {
    template<typename Z>
    EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::erfcx_, Z const& z) noexcept
    {
      auto realz = is_real(z);
      if (eve::all(realz))
        return Z{erfcx(real(z)), 0};
      else  if (eve::none(realz))
        return faddeeva(callable_i_{}*z);
      else
        return if_else(realz, Z{erfcx(real(z)), 0}, faddeeva(callable_i_{}*z));
    }
  }
}
