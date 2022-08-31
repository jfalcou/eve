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
#include <iostream>

namespace eve
{
  namespace detail
  {
    template<typename Z>
    EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::erfcx_, Z const& z) noexcept
    {
      return faddeeva(i(as(z))*z);
    }
  }
}
