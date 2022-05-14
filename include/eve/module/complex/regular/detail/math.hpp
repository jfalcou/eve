//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/complex/regular/traits.hpp>

namespace eve::detail
{
  EVE_FORCEINLINE auto complex_binary_dispatch( eve::tag::ulpdist_
                                              , auto const& z1, auto const& z2
                                              ) noexcept
  {
    return eve::max ( eve::ulpdist(real(z1), real(z2))
                    , eve::ulpdist(imag(z1), imag(z2))
                    );
  }
}
