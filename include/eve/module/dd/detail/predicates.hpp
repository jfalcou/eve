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
  EVE_FORCEINLINE auto dd_unary_dispatch(tag::is_denormal_, auto const& z) noexcept
  {
    return is_denormal(ddhi(z));
  }

  EVE_FORCEINLINE auto dd_unary_dispatch(tag::is_not_denormal_, auto const& z) noexcept
  {
    return is_not_denormal(ddhi(z));
  }

  EVE_FORCEINLINE auto dd_unary_dispatch( tag::is_finite_, auto const& z ) noexcept
  {
    return is_finite(ddhi(z));
  }

  EVE_FORCEINLINE auto dd_unary_dispatch( tag::is_eqz_, auto const& z ) noexcept
  {
    return is_eqz(ddhi(z));
  }

  EVE_FORCEINLINE auto dd_unary_dispatch( tag::is_nez_, auto const& z ) noexcept
  {
    return is_nez(ddhi(z));
  }

  EVE_FORCEINLINE auto dd_unary_dispatch( tag::is_not_finite_, auto const& z ) noexcept
  {
    return is_not_finite(ddhi(z));
  }

  EVE_FORCEINLINE auto dd_unary_dispatch( tag::is_infinite_, auto const& z ) noexcept
  {
    return is_infinite(ddhi(z));
  }

  EVE_FORCEINLINE auto dd_unary_dispatch( tag::is_nan_, auto const& z ) noexcept
  {
    return is_nan(ddhi(z));
  }

  EVE_FORCEINLINE auto dd_unary_dispatch( tag::is_not_nan_, auto const& z ) noexcept
  {
    return is_not_nan(ddhi(z));
  }

  //==============================================================================================
  //  binary is_equal, is_not_equal
  //==============================================================================================
  EVE_FORCEINLINE auto dd_binary_dispatch(eve::tag::is_equal_, eve::numeric_type const &
                                              , auto const& z1, auto const& z2) noexcept
  {
    return numeric(is_equal)(ddhi(z1), ddhi(z2)) && numeric(is_equal)(ddlo(z1), ddlo(z2));
  }

  EVE_FORCEINLINE auto dd_binary_dispatch(eve::tag::is_not_equal_, eve::numeric_type const &
                                              , auto const& z1, auto const& z2) noexcept
  {
    return numeric(is_not_equal)(ddhi(z1), ddhi(z2)) || numeric(is_not_equal)(ddlo(z1), ddlo(z2));
  }

  EVE_FORCEINLINE auto dd_binary_dispatch(eve::tag::is_less_
                                              , auto const& z1, auto const& z2) noexcept
  {
    return is_less(ddhi(z1), ddhi(z2)) || (is_equal(ddhi(z1), ddhi(z2)) && is_less(ddlo(z1), ddlo(z2)));
  }
}
