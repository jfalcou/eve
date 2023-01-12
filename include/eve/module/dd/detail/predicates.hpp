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
    return is_denormal(high(z)) || is_denormal(low(z));
  }

  EVE_FORCEINLINE auto dd_unary_dispatch(tag::is_not_denormal_, auto const& z) noexcept
  {
    return is_not_denormal(high(z)) && is_not_denormal(low(z));
  }

  EVE_FORCEINLINE auto dd_unary_dispatch( tag::is_finite_, auto const& z ) noexcept
  {
    return is_finite(low(z)) && is_finite(high(z));
  }

  EVE_FORCEINLINE auto dd_unary_dispatch( tag::is_eqz_, auto const& z ) noexcept
  {
    return is_eqz(low(z)) && is_eqz(high(z));
  }

  EVE_FORCEINLINE auto dd_unary_dispatch( tag::is_nez_, auto const& z ) noexcept
  {
    return is_nez(low(z)) || is_nez(high(z));
  }

  EVE_FORCEINLINE auto dd_unary_dispatch( tag::is_not_finite_, auto const& z ) noexcept
  {
    return is_not_finite(low(z)) || is_not_finite(high(z));
  }

  EVE_FORCEINLINE auto dd_unary_dispatch( tag::is_infinite_, auto const& z ) noexcept
  {
    return is_infinite(low(z)) || is_infinite(high(z));
  }

  EVE_FORCEINLINE auto dd_unary_dispatch( tag::is_nan_, auto const& z ) noexcept
  {
    auto [rz, iz] = z;
    return is_unordered(rz, iz);
  }

  EVE_FORCEINLINE auto dd_unary_dispatch( tag::is_not_nan_, auto const& z ) noexcept
  {
    auto [rz, iz] = z;
    return is_ordered(rz, iz);
  }

  //==============================================================================================
  //  binary is_equal, is_not_equal
  //==============================================================================================
  EVE_FORCEINLINE auto dd_binary_dispatch(eve::tag::is_equal_, eve::numeric_type const &
                                              , auto const& z1, auto const& z2) noexcept
  {
    return numeric(is_equal)(high(z1), high(z2)) && numeric(is_equal)(low(z1), low(z2));
  }

  EVE_FORCEINLINE auto dd_binary_dispatch(eve::tag::is_not_equal_, eve::numeric_type const &
                                              , auto const& z1, auto const& z2) noexcept
  {
    return numeric(is_not_equal)(high(z1), high(z2)) || numeric(is_not_equal)(low(z1), low(z2));
  }
}
