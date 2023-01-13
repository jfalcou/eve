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
#include <eve/module/dd/regular/traits.hpp>


namespace eve::detail
{

  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::rec_, Z const& z) noexcept
  {
    auto r = rec(high(z));
    Z x(r);
    x += r*(Z(1)-z*r);
    return x;
  }

  //================================================================================================
  //  trivial extension of some unary functions
  //================================================================================================
  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::ceil_, Z const& z) noexcept
  {
    auto rhi = ceil(high(z));
    auto already = rhi == high(z);
    auto rlo = if_else(already,  ceil(low(z)), zero);
    auto [hi, lo] = quick_two_add(rhi, rlo);
    return Z(hi, lo);
  }
 template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::floor_, Z const& z) noexcept
  {
    auto rhi = floor(high(z));
    auto already = rhi == high(z);
    auto rlo = if_else(already,  floor(low(z)), zero);
    auto [hi, lo] = quick_two_add(rhi, rlo);
    return Z(hi, lo);
  }
  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::nearest_, Z const& z) noexcept
  {
    auto f = floor(z);
    auto c = ceil(z);
    auto zmf = z-f;
    auto cmz = c-z;
    return if_else(zmf == cmz, if_else((f/2 == trunc(f/2)), f, c), if_else(zmf <  cmz, f, c));
    auto rhi = nearest(high(z));
    auto already = rhi == high(z);
    auto rlo = if_else(already,  nearest(low(z)), zero);
    auto [hi, lo] = quick_two_add(rhi, rlo);
    return Z(hi, lo);
  }
  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::trunc_, Z const& z) noexcept
  {
    return if_else(is_positive(high(z)), floor(z), ceil(z));
  }
  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::frac_, Z const& z) noexcept
  {
    return z-trunc(z);
  }


//   //================================================================================================
//   //  Unary functions
//   //================================================================================================


  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::sqr_, Z const& a) noexcept
  {
    auto [ahi, alo] = a;
    auto[p1, p2] = two_sqr(ahi);
    p2 += 2 * ahi * alo;
    p2 += sqr(alo);
    auto [ s1, s2] = quick_two_add(p1, p2);
    return Z{s1, s2};
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::sign_, Z const& z) noexcept
  {
    return Z(sign(high(z)));
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::signnz_, Z const& z) noexcept
  {
    return Z(signnz(high(z)));
  }

  template<typename Z>
  EVE_FORCEINLINE auto dd_unary_dispatch(eve::tag::modf_, Z const& z) noexcept
  {
    auto t = trunc(z);
    return kumi::tuple {z - t, t};
  }

  //================================================================================================
  //  Binary functions
  //================================================================================================

  EVE_FORCEINLINE auto
  dd_binary_dispatch(eve::tag::negate_, auto const& z1, auto const& z2) noexcept
  {
    return z1 * sign(high(z2));
  }

  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  dd_binary_dispatch(eve::tag::negatenz_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return z1 * signnz(high(z2));
  }

//   //================================================================================================
//   //  Ternary functions
//   //================================================================================================
//   EVE_FORCEINLINE auto
//   dd_ternary_dispatch(eve::tag::fam_, auto const& z1, auto const& z2, auto const& z3) noexcept
//   {
//     return fma(z2, z3, z1);
//   }

//   EVE_FORCEINLINE auto
//   dd_ternary_dispatch(eve::tag::fma_, auto const& z1, auto const& z2, auto const& z3) noexcept
//   {
//     using z_t       = decltype(z1 * z2 + z3);
//     auto [rz1, iz1] = z_t(z1);
//     auto [rz2, iz2] = z_t(z2);
//     auto [rz3, iz3] = z_t(z3);
//     return z_t {fma(rz1, rz2, fnma(iz1, iz2, rz3)), fma(iz1, rz2, fma(rz1, iz2, iz3))};
//   }

//   EVE_FORCEINLINE auto
//   dd_ternary_dispatch(eve::tag::fms_, auto const& z1, auto const& z2, auto const& z3) noexcept
//   {
//     using z_t       = decltype(z1 * z2 + z3);
//     auto [rz1, iz1] = z_t(z1);
//     auto [rz2, iz2] = z_t(z2);
//     auto [rz3, iz3] = z_t(z3);
//     return z_t {fma(rz1, rz2, fnms(iz1, iz2, rz3)), fma(iz1, rz2, fms(rz1, iz2, iz3))};
//   }

//   EVE_FORCEINLINE auto
//   dd_ternary_dispatch(eve::tag::fsm_, auto const& z1, auto const& z2, auto const& z3) noexcept
//   {
//     return fms(z2, z3, z1);
//   }

//   EVE_FORCEINLINE auto
//   dd_ternary_dispatch(eve::tag::fnma_, auto const& z1, auto const& z2, auto const& z3) noexcept
//   {
//     return -fms(z1, z2, z3);
//   }

//   EVE_FORCEINLINE auto
//   dd_ternary_dispatch(eve::tag::fnms_, auto const& z1, auto const& z2, auto const& z3) noexcept
//   {
//     return -fma(z1, z2, z3);
//   }

//   EVE_FORCEINLINE auto
//   dd_ternary_dispatch(eve::tag::fanm_, auto const& z1, auto const& z2, auto const& z3) noexcept
//   {
//     return fnma(z2, z3, z1);
//   }

//   EVE_FORCEINLINE auto
//   dd_ternary_dispatch(eve::tag::fsnm_, auto const& z1, auto const& z2, auto const& z3) noexcept
//   {
//     return fnms(z2, z3, z1);
//   }
}
