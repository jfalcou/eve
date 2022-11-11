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
#include <eve/module/complex/regular/traits.hpp>
#include <eve/module/core/regular/conj.hpp>
#include <eve/module/complex/regular/proj.hpp>

namespace eve::detail
{
  //==============================================================================================
  //  trivial extension of some real unary functions
  //==============================================================================================
  template<typename Z> EVE_FORCEINLINE auto complex_unary_dispatch(eve::tag::ceil_,    Z const& z) noexcept { return Z{ceil(real(z)), ceil(imag(z))};       }
  template<typename Z> EVE_FORCEINLINE auto complex_unary_dispatch(eve::tag::floor_,   Z const& z) noexcept { return Z{floor(real(z)), floor(imag(z))};     }
  template<typename Z> EVE_FORCEINLINE auto complex_unary_dispatch(eve::tag::nearest_, Z const& z) noexcept { return Z{nearest(real(z)), nearest(imag(z))}; }
  template<typename Z> EVE_FORCEINLINE auto complex_unary_dispatch(eve::tag::trunc_,   Z const& z) noexcept { return Z{trunc(real(z)), trunc(imag(z))};     }
  template<typename Z> EVE_FORCEINLINE auto complex_unary_dispatch(eve::tag::frac_,    Z const& z) noexcept { return Z{frac(real(z)), frac(imag(z))};       }
  template<typename Z> EVE_FORCEINLINE auto complex_unary_dispatch(eve::tag::minus_,   Z const& z) noexcept { return Z{minus(real(z)), minus(imag(z))};     }

  //==============================================================================================
  //  trivial extension of some real binary functions
  //==============================================================================================
  template<typename Z1,  typename Z2>
  EVE_FORCEINLINE auto complex_binary_dispatch(eve::tag::maxabs_, Z1 const& z1, Z2 const& z2) noexcept { return max(abs(z1), abs(z2)); }
  template<typename Z1,  typename Z2>
  EVE_FORCEINLINE auto complex_binary_dispatch(eve::tag::minabs_, Z1 const& z1, Z2 const& z2) noexcept { return min(abs(z1), abs(z2)); }
  template<typename Z1,  typename Z2>
  EVE_FORCEINLINE auto complex_binary_dispatch(eve::tag::dist_,   Z1 const& z1, Z2 const& z2) noexcept { return abs(z1-z2); }

  //==============================================================================================
  //  trivial extension of some real ternary functions
  //==============================================================================================
  template<typename Z1,  typename Z2, real_value T>
  EVE_FORCEINLINE auto complex_ternary_dispatch(eve::tag::lerp_, Z1 const& z1, Z2 const& z2, T const& t) noexcept
  {
    using z_t = decltype(z1+z2);
    return z_t{lerp(real(z1), real(z2), t), lerp(imag(z1), imag(z2), t)};
  }

  //==============================================================================================
  //  Unary functions
  //==============================================================================================
  EVE_FORCEINLINE auto complex_unary_dispatch(eve::tag::abs_
                                             , pedantic_type const &, auto const& z) noexcept
  {
    return eve::pedantic(eve::hypot)(real(z), imag(z));
  }

  EVE_FORCEINLINE auto complex_unary_dispatch(eve::tag::abs_, auto const& z) noexcept
  {
    return eve::hypot(real(z), imag(z));
  }

  EVE_FORCEINLINE auto complex_unary_dispatch(eve::tag::arg_, auto const& z) noexcept
  {
    return eve::atan2(imag(z), real(z) );
  }

  EVE_FORCEINLINE auto complex_unary_dispatch(eve::tag::arg_
                                             , pedantic_type const &, auto const& z) noexcept
  {
    return eve::pedantic(eve::atan2)(imag(z), real(z) );
  }

  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::conj_, Z const& z ) noexcept
  {
    return Z{real(z), -imag(z)};
  }

  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::dec_, Z const& z ) noexcept
  {
    return Z{dec(real(z)), imag(z)};
  }

  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::inc_, Z const& z ) noexcept
  {
    return Z{inc(real(z)), imag(z)};
  }

  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::oneminus_, Z const& z ) noexcept
  {
    return Z{oneminus(real(z)), -imag(z)};
  }
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch(eve::tag::proj_, Z const& z) noexcept
  {
    using real_t = as< as_real_t<Z> >;
    return if_else(is_infinite(z), Z(inf(real_t{}), copysign(zero(real_t{}), imag(z))), z);
  }

  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch(eve::tag::sqr_, Z const& z) noexcept
  {
    auto [zr, zi] = z;
    return Z{fms(zr, zr, zi*zi), 2*zr*zi};
  }

  EVE_FORCEINLINE auto complex_unary_dispatch(eve::tag::sqr_abs_, auto const& z) noexcept
  {
    auto [zr, zi] = z;
    return fma(zr, zr, zi*zi);
  }

  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch(eve::tag::sqr_, eve::pedantic_type const &, Z const& z) noexcept
  {
    auto [zr, zi] = z;
    return Z{diff_of_prod(zr, zr, zi, zi), 2*zr*zi};
  }

  EVE_FORCEINLINE auto complex_unary_dispatch(eve::tag::sqr_abs_, eve::pedantic_type const &, auto const& z) noexcept
  {
    auto [zr, zi] = z;
    return sum_of_prod(zr, zr, zi, zi);
  }


  //==============================================================================================
  //  Binary functions
  //==============================================================================================

  EVE_FORCEINLINE auto complex_binary_dispatch( eve::tag::average_
                                              , auto const& z1, auto const& z2
                                              ) noexcept
  {
    using z_t = decltype(z1+z2);
    return z_t{eve::average(real(z1), real(z2)), eve::average(imag(z1), imag(z2))};
  }

  //==============================================================================================
  //  Ternary functions
  //==============================================================================================

  EVE_FORCEINLINE auto complex_ternary_dispatch( eve::tag::fam_
                                              , auto const& z1, auto const& z2, auto const& z3
                                              ) noexcept
  {
    return fma(z2, z3, z1);
  }

  EVE_FORCEINLINE auto complex_ternary_dispatch( eve::tag::fma_
                                              , auto const& z1, auto const& z2, auto const& z3
                                              ) noexcept
  {
    using z_t = decltype(z1*z2+z3);
    auto [rz1, iz1] = z_t(z1);
    auto [rz2, iz2] = z_t(z2);
    auto [rz3, iz3] = z_t(z3);
    return z_t{fma(rz1, rz2, fnma(iz1, iz2, rz3)), fma(iz1, rz2, fma(rz1, iz2, iz3))};
  }

  EVE_FORCEINLINE auto complex_ternary_dispatch( eve::tag::fms_
                                              , auto const& z1, auto const& z2, auto const& z3
                                              ) noexcept
  {
    using z_t = decltype(z1*z2+z3);
    auto [rz1, iz1] = z_t(z1);
    auto [rz2, iz2] = z_t(z2);
    auto [rz3, iz3] = z_t(z3);
    return z_t{fma(rz1, rz2, fnms(iz1, iz2, rz3)), fma(iz1, rz2, fms(rz1, iz2, iz3))};
  }

  EVE_FORCEINLINE auto complex_ternary_dispatch( eve::tag::fsm_
                                              , auto const& z1, auto const& z2, auto const& z3
                                              ) noexcept
  {
    return fms(z2, z3, z1);
  }

  EVE_FORCEINLINE auto complex_ternary_dispatch( eve::tag::fnma_
                                              , auto const& z1, auto const& z2, auto const& z3
                                              ) noexcept
  {
    return -fms(z1, z2, z3);
  }

  EVE_FORCEINLINE auto complex_ternary_dispatch( eve::tag::fnms_
                                              , auto const& z1, auto const& z2, auto const& z3
                                              ) noexcept
  {
    return -fma(z1, z2, z3);
  }

   EVE_FORCEINLINE auto complex_ternary_dispatch( eve::tag::fanm_
                                              , auto const& z1, auto const& z2, auto const& z3
                                              ) noexcept
  {
    return fnma(z2, z3, z1);
  }

  EVE_FORCEINLINE auto complex_ternary_dispatch( eve::tag::fsnm_
                                              , auto const& z1, auto const& z2, auto const& z3
                                              ) noexcept
  {
    return fnms(z2, z3, z1);
  }

  //===-------------------------------------------------------------------------------------------
  //=== modf
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::modf_
                                             , Z const& z) noexcept
  {
    auto t = trunc(z);
    return kumi::tuple{z - t, t};
  }


}
