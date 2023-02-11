//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/doublereal/regular/high.hpp>
#include <eve/module/doublereal/regular/low.hpp>

namespace eve::detail
{
  //================================================================================================
  // Unary predicates
  //================================================================================================
  EVE_FORCEINLINE auto doublereal_unary_dispatch(tag::is_denormal_, auto const& z) noexcept
  {
    return is_denormal(high(z));
  }

  EVE_FORCEINLINE auto doublereal_unary_dispatch( tag::is_finite_, auto const& z ) noexcept
  {
    return is_finite(high(z));
  }

  EVE_FORCEINLINE auto doublereal_unary_dispatch( tag::is_flint_, auto const& z ) noexcept
  {
    return trunc(z) == z;
  }

  EVE_FORCEINLINE auto doublereal_unary_dispatch( tag::is_eqz_, auto const& z ) noexcept
  {
    return is_eqz(high(z));
  }

  EVE_FORCEINLINE auto doublereal_unary_dispatch( tag::is_even_, auto const& z ) noexcept
  {
    return 2*trunc(z/2) == z;
  }

  EVE_FORCEINLINE auto doublereal_unary_dispatch( tag::is_gez_, auto const& z ) noexcept
  {
    return is_gez(high(z));
  }

  EVE_FORCEINLINE auto doublereal_unary_dispatch( tag::is_gtz_, auto const& z ) noexcept
  {
    return is_gtz(high(z));
  }

  EVE_FORCEINLINE auto doublereal_unary_dispatch( tag::is_lez_, auto const& z ) noexcept
  {
    return is_lez(high(z));
  }

  EVE_FORCEINLINE auto doublereal_unary_dispatch( tag::is_ltz_, auto const& z ) noexcept
  {
    return is_ltz(high(z));
  }

  EVE_FORCEINLINE auto doublereal_unary_dispatch( tag::is_negative_, auto const& z ) noexcept
  {
    return is_negative(high(z));
  }

  EVE_FORCEINLINE auto doublereal_unary_dispatch( tag::is_nez_, auto const& z ) noexcept
  {
    return is_nez(high(z));
  }

  EVE_FORCEINLINE auto doublereal_unary_dispatch( tag::is_ngez_, auto const& z ) noexcept
  {
    return is_ngez(high(z));
  }

  EVE_FORCEINLINE auto doublereal_unary_dispatch( tag::is_ngtz_, auto const& z ) noexcept
  {
    return is_ngtz(high(z));
  }

  EVE_FORCEINLINE auto doublereal_unary_dispatch( tag::is_nlez_, auto const& z ) noexcept
  {
    return is_nlez(high(z));
  }

  EVE_FORCEINLINE auto doublereal_unary_dispatch( tag::is_nltz_, auto const& z ) noexcept
  {
    return is_nltz(high(z));
  }

  EVE_FORCEINLINE auto doublereal_unary_dispatch( tag::is_not_denormal_, auto const& z ) noexcept
  {
    return is_not_denormal(high(z));
  }

  EVE_FORCEINLINE auto doublereal_unary_dispatch( tag::is_not_finite_, auto const& z ) noexcept
  {
    return is_not_finite(high(z));
  }

  EVE_FORCEINLINE auto doublereal_unary_dispatch( tag::is_infinite_, auto const& z ) noexcept
  {
    return is_infinite(high(z));
  }

  EVE_FORCEINLINE auto doublereal_unary_dispatch( tag::is_nan_, auto const& z ) noexcept
  {
    return is_nan(high(z))||is_nan(low(z));;
  }

  EVE_FORCEINLINE auto doublereal_unary_dispatch( tag::is_not_flint_, auto const& z ) noexcept
  {
    return z != trunc(z);
  }

  EVE_FORCEINLINE auto doublereal_unary_dispatch( tag::is_not_nan_, auto const& z ) noexcept
  {
     return is_not_nan(high(z))&&is_not_nan(low(z));
  }

  EVE_FORCEINLINE auto doublereal_unary_dispatch( tag::is_odd_, auto const& z ) noexcept
  {
    return (z != inc(z)) && is_even(inc(z));
  }

  EVE_FORCEINLINE auto doublereal_unary_dispatch( tag::is_positive_, auto const& z ) noexcept
  {
    return is_positive(high(z));
  }

  EVE_FORCEINLINE auto doublereal_unary_dispatch( tag::is_pow2_, auto const& z ) noexcept
  {
    return is_pow2(high(z)) && is_eqz(low(z));
  }
  //==============================================================================================
  //  binary is_equal, is_not_equal
  //==============================================================================================
  EVE_FORCEINLINE auto doublereal_binary_dispatch(eve::tag::is_equal_
                                              , auto const& z1, auto const& z2) noexcept
  {
    return (is_equal)(high(z1), high(z2)) && (is_equal)(low(z1), low(z2));
  }

  EVE_FORCEINLINE auto doublereal_binary_dispatch(eve::tag::is_equal_, eve::numeric_type const &
                                              , auto const& z1, auto const& z2) noexcept
  {
    return numeric(is_equal)(high(z1), high(z2)) && numeric(is_equal)(low(z1), low(z2));
  }

  EVE_FORCEINLINE auto doublereal_binary_dispatch(eve::tag::is_not_equal_, eve::numeric_type const &
                                              , auto const& z1, auto const& z2) noexcept
  {
    return numeric(is_not_equal)(high(z1), high(z2)) || numeric(is_not_equal)(low(z1), low(z2));
  }
}
