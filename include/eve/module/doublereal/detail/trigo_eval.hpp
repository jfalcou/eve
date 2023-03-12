//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/doublereal/detail/trigo_base.hpp>

namespace eve::detail
{

  template<typename Z>
  EVE_FORCEINLINE auto
  doublereal_binary_dispatch(eve::tag::sin_eval_, Z const& zz, Z const& z) noexcept
  {
    auto [S, C] = internal::SC<Z>();
    return z  +  z * (zz * horner( zz, S));

  }

  template<typename Z>
  EVE_FORCEINLINE auto
  doublereal_unary_dispatch(eve::tag::cos_eval_, Z const& zz) noexcept
  {
    auto [S, C] = internal::SC<Z>();
    return oneminus(zz*half(as(zz))-zz*zz*horner(zz, C));

  }

  template<typename Z>
  EVE_FORCEINLINE auto
  doublereal_unary_dispatch(eve::tag::tancot_eval_, Z const& z) noexcept
  {
//     auto [P, Q] = internal::tan_PQ<Z>();
//     auto zz =  sqr(z);
//     return z +z*(zz*horner(zz, P)/horner(zz, Q));
    auto [s, c] = sincos(z);
    return s/c;

  }
}
