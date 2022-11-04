//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
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

  EVE_FORCEINLINE auto complex_unary_dispatch( tag::is_not_nan_, auto const& z ) noexcept
  {
    auto [rz, iz] = z;
    return is_ordered(rz, iz);
  }

  //==============================================================================================
  //  binary is_equal, is_not_equal
  //==============================================================================================
  template<typename Z1,  typename Z2>
  EVE_FORCEINLINE auto complex_binary_dispatch(eve::tag::is_equal_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return (real(z1) == real(z2)) && (imag(z1) == imag(z2));
 }

  template<typename Z1,  typename Z2>
  EVE_FORCEINLINE auto complex_binary_dispatch(eve::tag::is_not_equal_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return (real(z1) != real(z2)) || (imag(z1) != imag(z2));
  }

  EVE_FORCEINLINE auto complex_binary_dispatch(eve::tag::is_equal_, eve::numeric_type const &
                                              , auto const& z1, auto const& z2) noexcept
  {
    return numeric(is_equal)(real(z1), real(z2)) && numeric(is_equal)(imag(z1), imag(z2));
  }

  EVE_FORCEINLINE auto complex_binary_dispatch(eve::tag::is_not_equal_, eve::numeric_type const &
                                              , auto const& z1, auto const& z2) noexcept
  {
    return numeric(is_not_equal)(real(z1), real(z2)) || numeric(is_not_equal)(imag(z1), imag(z2));
  }
}
