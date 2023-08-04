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
#include <eve/module/core.hpp>
#include <eve/module/complex/regular/proj.hpp>

namespace eve::detail
{
  //================================================================================================
  // operators as functions
  //================================================================================================
  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  complex_binary_dispatch(eve::tag::add_, Z1 const& z1, Z2 const& z2) noexcept -> decltype(z1+z2)
  {
    return z1 + z2;
  }

  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  complex_binary_dispatch(eve::tag::sub_, Z1 const& z1, Z2 const& z2) noexcept -> decltype(z1+z2)
  {
    return z1 - z2;
  }

  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  complex_binary_dispatch(eve::tag::mul_, Z1 const& z1, Z2 const& z2) noexcept -> decltype(z1+z2)
  {
    return z1 * z2;
  }

  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  complex_binary_dispatch(eve::tag::div_, Z1 const& z1, Z2 const& z2) noexcept -> decltype(z1+z2)
  {
    return z1 / z2;
  }

  //================================================================================================
  // operators as pedantic functions
  //================================================================================================
  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  complex_binary_dispatch(eve::tag::mul_, pedantic_type const&, Z1 const& z1, Z2 const& z2) noexcept
  {
    using v_t = decltype(real(z1) * real(z2));
    using r_t = eve::as_complex_t<v_t>;

    r_t r;
    auto a = real(z1);
    auto b = imag(z1);

    auto c = real(z2);
    auto d = imag(z2);

    if constexpr( !is_complex_v<Z1> || !is_complex_v<Z1> ) { r = z1 * z2; }
    else
    {
      auto rr = pedantic(diff_of_prod)(a, c, b, d);
      auto ri = pedantic(sum_of_prod)(a, d, b, c);
      r       = r_t(rr, ri);
    }
    auto test = is_finite(r);
    if( eve::all(test) ) return r;
    auto cur = logical_andnot(is_real(z1), test);
    if( eve::any(cur) )
    {
      r    = if_else(cur, a * z2, r);
      test = logical_or(test, cur);
      if( eve::all(test) ) return r;
    }
    cur = eve::logical_andnot(is_imag(z1), test);
    if( eve::any(cur) )
    {
      r    = if_else(cur, b * z2 * eve::i, r);
      test = logical_or(test, cur);
      if( eve::all(test) ) return r;
    }
    cur = eve::logical_andnot(is_real(z2), test);
    if( eve::any(cur) )
    {
      r    = if_else(cur, c * z1, r);
      test = logical_or(test, cur);
      if( eve::all(test) ) return r;
    }
    cur = eve::logical_andnot(is_imag(z2), test);
    if( eve::any(cur) )
    {
      r    = if_else(cur, d * z1 * eve::i, r);
      test = logical_or(test, cur);
      if( eve::all(test) ) return r;
    }
    return r;
  }

  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  complex_binary_dispatch(eve::tag::div_, pedantic_type const&, Z1 const& z1, Z2 const& z2) noexcept
  {
    using v_t = decltype(real(z1) / real(z2));
    using r_t = eve::as_complex_t<v_t>;
    if constexpr( !is_complex_v<Z2> )
    {
      auto iz2 = pedantic(rec)(z2);
      return pedantic(mul)(z1, iz2);
    }
    else
    {
      auto rr = eve::abs(real(z1));
      auto ii = eve::abs(imag(z1));
      auto e  = -if_else((rr < ii), exponent(ii), exponent(rr));
      auto zz2(eve::ldexp(z2, e));
      auto denom = sqr_abs(zz2);
      r_t  r     = pedantic(mul)(z1, conj(zz2));
      r /= denom;
      r = if_else(is_not_infinite(denom), r, zero);
      return ldexp(r, e);
    }
  }

  //================================================================================================
  //  trivial extension of some real unary functions
  //================================================================================================
  template<typename Z>
  EVE_FORCEINLINE auto
  complex_unary_dispatch(eve::tag::ceil_, Z const& z) noexcept
  {
    return Z {ceil(real(z)), ceil(imag(z))};
  }
  template<typename Z>
  EVE_FORCEINLINE auto
  complex_unary_dispatch(eve::tag::floor_, Z const& z) noexcept
  {
    return Z {floor(real(z)), floor(imag(z))};
  }
  template<typename Z>
  EVE_FORCEINLINE auto
  complex_unary_dispatch(eve::tag::nearest_, Z const& z) noexcept
  {
    return Z {nearest(real(z)), nearest(imag(z))};
  }
  template<typename Z>
  EVE_FORCEINLINE auto
  complex_unary_dispatch(eve::tag::trunc_, Z const& z) noexcept
  {
    return Z {trunc(real(z)), trunc(imag(z))};
  }
  template<typename Z>
  EVE_FORCEINLINE auto
  complex_unary_dispatch(eve::tag::frac_, Z const& z) noexcept
  {
    return Z {frac(real(z)), frac(imag(z))};
  }
  template<typename Z>
  EVE_FORCEINLINE auto
  complex_unary_dispatch(eve::tag::minus_, Z const& z) noexcept
  {
    return Z {minus(real(z)), minus(imag(z))};
  }

  //================================================================================================
  //  trivial extension of some real binary functions
  //================================================================================================
  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  complex_binary_dispatch(eve::tag::maxabs_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return max(abs(z1), abs(z2));
  }
  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  complex_binary_dispatch(eve::tag::minabs_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return min(abs(z1), abs(z2));
  }
  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  complex_binary_dispatch(eve::tag::dist_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return abs(z1 - z2);
  }

  //================================================================================================
  //  trivial extension of some real ternary functions
  //================================================================================================
  template<typename Z1, typename Z2, ordered_value T>
  EVE_FORCEINLINE auto
  complex_ternary_dispatch(eve::tag::lerp_, Z1 const& z1, Z2 const& z2, T const& t) noexcept
  {
    using z_t = decltype(z1 + z2);
    return z_t {lerp(real(z1), real(z2), t), lerp(imag(z1), imag(z2), t)};
  }


  //================================================================================================
  //  Unary functions
  //================================================================================================
  EVE_FORCEINLINE auto
  complex_unary_dispatch(eve::tag::abs_, pedantic_type const&, auto const& z) noexcept
  {
    return eve::pedantic(eve::hypot)(real(z), imag(z));
  }

  EVE_FORCEINLINE auto
  complex_unary_dispatch(eve::tag::abs_, auto const& z) noexcept
  {
    return eve::hypot(real(z), imag(z));
  }

  EVE_FORCEINLINE auto
  complex_unary_dispatch(eve::tag::arg_, auto const& z) noexcept
  {
    return eve::atan2(imag(z), real(z));
  }

  EVE_FORCEINLINE auto
  complex_unary_dispatch(eve::tag::arg_, pedantic_type const&, auto const& z) noexcept
  {
    return eve::pedantic(eve::atan2)(imag(z), real(z));
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  complex_unary_dispatch(eve::tag::conj_, Z const& z) noexcept
  {
    return Z {real(z), -imag(z)};
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  complex_unary_dispatch(eve::tag::dec_, Z const& z) noexcept
  {
    return Z {dec(real(z)), imag(z)};
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  complex_unary_dispatch(eve::tag::inc_, Z const& z) noexcept
  {
    return Z {inc(real(z)), imag(z)};
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  complex_unary_dispatch(eve::tag::oneminus_, Z const& z) noexcept
  {
    return Z {oneminus(real(z)), -imag(z)};
  }
  template<typename Z>
  EVE_FORCEINLINE auto
  complex_unary_dispatch(eve::tag::proj_, Z const& z) noexcept
  {
    using real_t = as<as_real_t<Z>>;
    return if_else(is_infinite(z), Z(inf(real_t {}), copysign(zero(real_t {}), imag(z))), z);
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  complex_unary_dispatch(eve::tag::sqr_, Z const& z) noexcept
  {
    auto [zr, zi] = z;
    return Z {fms(zr, zr, zi * zi), 2 * zr * zi};
  }

  EVE_FORCEINLINE auto
  complex_unary_dispatch(eve::tag::sqr_abs_, auto const& z) noexcept
  {
    auto [zr, zi] = z;
    return fma(zr, zr, zi * zi);
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  complex_unary_dispatch(eve::tag::sqr_, eve::pedantic_type const&, Z const& z) noexcept
  {
    auto [zr, zi] = z;
    return Z {diff_of_prod(zr, zr, zi, zi), 2 * zr * zi};
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  complex_unary_dispatch(eve::tag::sqr_, eve::numeric_type const&, Z const& z) noexcept
  {
    auto [zr, zi] = z;
    return Z {(zr-zi)*(zi+zr), 2 * zr * zi};
  }

  EVE_FORCEINLINE auto
  complex_unary_dispatch(eve::tag::sqr_abs_, eve::pedantic_type const&, auto const& z) noexcept
  {
    auto [zr, zi] = z;
    return sum_of_prod(zr, zr, zi, zi);
  }

  EVE_FORCEINLINE auto
  complex_unary_dispatch(eve::tag::sign_, auto const& z) noexcept
  {
    return if_else(is_eqz(z), zero, z / abs(z));
    ;
  }

  template<typename Z>
  EVE_FORCEINLINE auto complex_unary_dispatch(eve::tag::modf_, Z const& z) noexcept
  {
    auto t = trunc(z);
    return kumi::tuple {z - t, t};
  }

  //================================================================================================
  //  Binary functions
  //================================================================================================
  EVE_FORCEINLINE auto
  complex_binary_dispatch(eve::tag::average_, auto const& z1, auto const& z2) noexcept
  {
    using z_t = decltype(z1 + z2);
    return z_t {eve::average(real(z1), real(z2)), eve::average(imag(z1), imag(z2))};
  }

  EVE_FORCEINLINE auto
  complex_binary_dispatch(eve::tag::negate_, auto const& z1, auto const& z2) noexcept
  {
    return z1 * sign(z2);
  }

  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  complex_binary_dispatch(eve::tag::negatenz_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return if_else(eve::is_eqz(z2), to_complex(z1), z1 * sign(z2));
  }

  //================================================================================================
  //  Ternary functions
  //================================================================================================
  EVE_FORCEINLINE auto
  complex_ternary_dispatch(eve::tag::fam_, auto const& z1, auto const& z2, auto const& z3) noexcept
  {
    return fma(z2, z3, z1);
  }

  EVE_FORCEINLINE auto
  complex_ternary_dispatch(eve::tag::fma_, auto const& z1, auto const& z2, auto const& z3) noexcept
  {
    using z_t       = decltype(z1 * z2 + z3);
    auto [rz1, iz1] = z_t(z1);
    auto [rz2, iz2] = z_t(z2);
    auto [rz3, iz3] = z_t(z3);
    return z_t {fma(rz1, rz2, fnma(iz1, iz2, rz3)), fma(iz1, rz2, fma(rz1, iz2, iz3))};
  }

  EVE_FORCEINLINE auto
  complex_ternary_dispatch(eve::tag::fms_, auto const& z1, auto const& z2, auto const& z3) noexcept
  {
    using z_t       = decltype(z1 * z2 + z3);
    auto [rz1, iz1] = z_t(z1);
    auto [rz2, iz2] = z_t(z2);
    auto [rz3, iz3] = z_t(z3);
    return z_t {fma(rz1, rz2, fnms(iz1, iz2, rz3)), fma(iz1, rz2, fms(rz1, iz2, iz3))};
  }

  EVE_FORCEINLINE auto
  complex_ternary_dispatch(eve::tag::fsm_, auto const& z1, auto const& z2, auto const& z3) noexcept
  {
    return fms(z2, z3, z1);
  }

  EVE_FORCEINLINE auto
  complex_ternary_dispatch(eve::tag::fnma_, auto const& z1, auto const& z2, auto const& z3) noexcept
  {
    return -fms(z1, z2, z3);
  }

  EVE_FORCEINLINE auto
  complex_ternary_dispatch(eve::tag::fnms_, auto const& z1, auto const& z2, auto const& z3) noexcept
  {
    return -fma(z1, z2, z3);
  }

  EVE_FORCEINLINE auto
  complex_ternary_dispatch(eve::tag::fanm_, auto const& z1, auto const& z2, auto const& z3) noexcept
  {
    return fnma(z2, z3, z1);
  }

  EVE_FORCEINLINE auto
  complex_ternary_dispatch(eve::tag::fsnm_, auto const& z1, auto const& z2, auto const& z3) noexcept
  {
    return fnms(z2, z3, z1);
  }


  //================================================================================================
  //  trivial extension of some real tetrary functions
  //================================================================================================
  template<typename Z1, typename Z2, typename Z3, typename Z4>
  EVE_FORCEINLINE auto
  complex_nary_dispatch(eve::tag::sum_of_prod_, Z1 const& z1, Z2 const& z2, Z3 const& z3, Z4 const& z4) noexcept
  {
    return fma(z1, z2, z3*z4);
  }

  template<typename Z1, typename Z2, typename Z3, typename Z4>
  EVE_FORCEINLINE auto
  complex_nary_dispatch(eve::tag::diff_of_prod_, Z1 const& z1, Z2 const& z2, Z3 const& z3, Z4 const& z4) noexcept
  {
    return fms(z1, z2, z3*z4);
  }

  //================================================================================================
  //  relative distance
  //================================================================================================
   template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  complex_binary_dispatch(eve::tag::reldist_, Z1 const& z1, Z2 const& z2) noexcept -> decltype(abs(z1+z2))
  {
    using r_t = decltype(abs(z1+z2));
    return dist(z1, z2)/max(abs(z1), abs(z2), one(as<r_t>()));
  }

  //================================================================================================
  //  dot product
  //================================================================================================
  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  complex_binary_dispatch(eve::tag::dot_, Z1 const& z1, Z2 const& z2) noexcept
  {
    if constexpr(ordered_value<Z1>)
      return z1*real(z2);
    else if constexpr(ordered_value<Z2>)
        return z2*real(z1);
    else
      return real(z1)*real(z2)+ imag(z1)*imag(z2);
  }

}
