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
  EVE_FORCEINLINE auto quaternion_unary_dispatch(tag::is_denormal_, auto const& z) noexcept
  {
    return is_denormal(real(z)) || is_denormal(ipart(z)) || is_denormal(jpart(z)) || is_denormal(kpart(z));
  }

  EVE_FORCEINLINE auto quaternion_unary_dispatch(tag::is_not_denormal_, auto const& z) noexcept
  {
    return is_not_denormal(real(z)) && is_not_denormal(ipart(z)) && is_not_denormal(jpart(z)) && is_not_denormal(kpart(z));
  }

//   EVE_FORCEINLINE auto quaternion_unary_dispatch(tag::is_pure_, auto const& z) noexcept
//   {
//     return is_eqz(real(z));
//   }

  EVE_FORCEINLINE auto quaternion_unary_dispatch(tag::is_real_, auto const& z) noexcept
  {
    return is_eqz(pure(z));
  }

  EVE_FORCEINLINE auto quaternion_unary_dispatch( tag::is_finite_, auto const& z ) noexcept
  {
    return  is_finite(real(z)) && is_finite(ipart(z)) && is_finite(jpart(z)) && is_finite(kpart(z));
  }

  EVE_FORCEINLINE auto quaternion_unary_dispatch( tag::is_eqz_, auto const& z ) noexcept
  {
    return is_eqz(real(z)) && is_eqz(ipart(z)) && is_eqz(jpart(z)) && is_eqz(kpart(z));
  }

  EVE_FORCEINLINE auto quaternion_unary_dispatch( tag::is_nez_, auto const& z ) noexcept
  {
    return is_nez(real(z))|| is_nez(ipart(z)) || is_nez(jpart(z)) || is_nez(kpart(z));
  }

  EVE_FORCEINLINE auto quaternion_unary_dispatch( tag::is_not_finite_, auto const& z ) noexcept
  {
    return is_not_finite(real(z))|| is_not_finite(ipart(z)) || is_not_finite(jpart(z)) || is_not_finite(kpart(z));
  }

  EVE_FORCEINLINE auto quaternion_unary_dispatch( tag::is_infinite_, auto const& z ) noexcept
  {
    return is_infinite(real(z))|| is_infinite(ipart(z)) || is_infinite(jpart(z)) || is_infinite(kpart(z));
  }

  EVE_FORCEINLINE auto quaternion_unary_dispatch( tag::is_nan_, auto const& z ) noexcept
  {
    auto [rz, iz, jz, kz] = z;
    return is_unordered(rz, iz)||is_unordered(jz, kz);
  }

  EVE_FORCEINLINE auto quaternion_unary_dispatch( tag::is_not_nan_, auto const& z ) noexcept
  {
    auto [rz, iz, jz, kz] = z;
    return is_ordered(rz, iz) && is_ordered(jz, kz);
  }

  //==============================================================================================
  //  binary is_equal, is_not_equal
  //==============================================================================================
  EVE_FORCEINLINE auto quaternion_binary_dispatch(eve::tag::is_equal_, eve::numeric_type const &
                                              , auto const& z1, auto const& z2) noexcept
  {
    return numeric(is_equal)(real(z1), real(z2)) && numeric(is_equal)(ipart(z1), ipart(z2))
      && numeric(is_equal)(jpart(z1), jpart(z2)) && numeric(is_equal)(kpart(z1), kpart(z2));
  }

  EVE_FORCEINLINE auto quaternion_binary_dispatch(eve::tag::is_not_equal_, eve::numeric_type const &
                                              , auto const& z1, auto const& z2) noexcept
  {
   return numeric(is_not_equal)(real(z1), real(z2)) || numeric(is_not_equal)(ipart(z1), ipart(z2))
      || numeric(is_not_equal)(jpart(z1), jpart(z2)) || numeric(is_not_equal)(kpart(z1), kpart(z2));
  }
}
