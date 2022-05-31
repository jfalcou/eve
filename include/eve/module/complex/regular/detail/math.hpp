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
#include <eve/module/complex/regular/conj.hpp>
#include <eve/module/complex/regular/i.hpp>

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

  template<typename Z, integral_value N>
  EVE_FORCEINLINE auto complex_binary_dispatch( eve::tag::ldexp_
                                              , Z const& z1
                                              , N n
                                              ) noexcept
  {
    return as_wide_as_t<Z,N>(ldexp(real(z1), n), ldexp(imag(z1), n));
  }

  EVE_FORCEINLINE auto complex_unary_dispatch(eve::tag::sqr_abs_, auto const& z) noexcept
  {
    auto [zr, zi] = z;
    return sum_of_prod(zr, zr, zi, zi);
  }
}
