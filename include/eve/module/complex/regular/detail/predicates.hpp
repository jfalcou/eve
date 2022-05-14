//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve::detail
{
  //================================================================================================
  // Unary predicates
  //================================================================================================
  EVE_FORCEINLINE auto complex_unary_dispatch(tag::is_imag_, auto const& z) noexcept
  {
    return is_eqz(real(z));
  }

  EVE_FORCEINLINE auto complex_unary_dispatch(tag::is_imag_, almost_type const&, auto const& z) noexcept
  {
    auto [rz, iz] = z;
    return abs(rz) <= abs(z)*eps(as(rz));
  }

  EVE_FORCEINLINE auto complex_unary_dispatch(tag::is_real_, auto const& z) noexcept
  {
    return is_eqz(imag(z));
  }

  EVE_FORCEINLINE auto complex_unary_dispatch(tag::is_real_, almost_type const&, auto const& z) noexcept
  {
    auto [rz, iz] = z;
    return abs(iz) <= abs(z)*eps(as(rz));
  }

  EVE_FORCEINLINE auto complex_unary_dispatch( tag::is_finite_, auto const& z ) noexcept
  {
    return is_finite(imag(z)) && is_finite(real(z));
  }

  EVE_FORCEINLINE auto complex_unary_dispatch( tag::is_eqz_, auto const& z ) noexcept
  {
    return is_eqz(imag(z)) && is_eqz(real(z));
  }

  EVE_FORCEINLINE auto complex_unary_dispatch( tag::is_nez_, auto const& z ) noexcept
  {
    return is_nez(imag(z)) || is_nez(real(z));
  }

  EVE_FORCEINLINE auto complex_unary_dispatch( tag::is_not_finite_, auto const& z ) noexcept
  {
    return is_not_finite(imag(z)) || is_not_finite(real(z));
  }

  EVE_FORCEINLINE auto complex_unary_dispatch( tag::is_infinite_, auto const& z ) noexcept
  {
    return is_infinite(imag(z)) || is_infinite(real(z));
  }

  EVE_FORCEINLINE auto complex_unary_dispatch( tag::is_nan_, auto const& z ) noexcept
  {
    auto [rz, iz] = z;
    return is_unordered(rz, iz);
  }
}
