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
#include <eve/module/complex/regular/proj.hpp>

namespace eve::detail
{

  //==============================================================================================
  //  trivial extension of some real unary functions
  //==============================================================================================
  template<typename Z> EVE_FORCEINLINE auto complex_unary_dispatch(eve::tag::ceil_, Z const& z) noexcept { return Z{ceil(real(z)), ceil(imag(z))}; }
  template<typename Z> EVE_FORCEINLINE auto complex_unary_dispatch(eve::tag::floor_, Z const& z) noexcept { return Z{floor(real(z)), floor(imag(z))}; }
  template<typename Z> EVE_FORCEINLINE auto complex_unary_dispatch(eve::tag::nearest_, Z const& z) noexcept { return Z{nearest(real(z)), nearest(imag(z))}; }
  template<typename Z> EVE_FORCEINLINE auto complex_unary_dispatch(eve::tag::trunc_, Z const& z) noexcept { return Z{trunc(real(z)), trunc(imag(z))}; }
  template<typename Z> EVE_FORCEINLINE auto complex_unary_dispatch(eve::tag::frac_, Z const& z) noexcept { return Z{frac(real(z)), frac(imag(z))}; }

  //==============================================================================================
  //  trivial extension of some real binary functions
  //==============================================================================================
  template<typename Z1,  typename Z2>
  EVE_FORCEINLINE auto complex_binary_dispatch(eve::tag::maxabs_, Z1 const& z1, Z2 const& z2) noexcept { return max(abs(z1), abs(z2)); }
  template<typename Z1,  typename Z2>
  EVE_FORCEINLINE auto complex_binary_dispatch(eve::tag::minabs_, Z1 const& z1, Z2 const& z2) noexcept { return min(abs(z1), abs(z2)); }
  template<typename Z1,  typename Z2>
  EVE_FORCEINLINE auto complex_binary_dispatch(eve::tag::dist_, Z1 const& z1, Z2 const& z2) noexcept { return abs(z1-z2); }

  //==============================================================================================
  //  trivial extension of some real ternary functions
  //==============================================================================================
  template<typename Z1,  typename Z2, real_value Z3>
  EVE_FORCEINLINE auto complex_ternary_dispatch(eve::tag::lerp_, Z1 const& z1, Z2 const& z2, Z3 const& t) noexcept
  { return lerp(abs(z1), abs(z2), t); }

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
    return Z{diff_of_prod(zr, zr, zi, zi), 2*zr*zi};
  }

  EVE_FORCEINLINE auto complex_unary_dispatch(eve::tag::sqr_abs_, auto const& z) noexcept
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
}
