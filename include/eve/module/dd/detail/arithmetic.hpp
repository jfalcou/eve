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
  // operators as functions
  //================================================================================================
  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  dd_binary_dispatch(eve::tag::add_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return z1 + z2;
  }

  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  dd_binary_dispatch(eve::tag::sub_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return z1 - z2;
  }

  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  dd_binary_dispatch(eve::tag::mul_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return z1 * z2;
  }

  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  dd_binary_dispatch(eve::tag::div_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return z1 / z2;
  }


//   //================================================================================================
//   //  trivial extension of some high unary functions
//   //================================================================================================
//   template<typename Z>
//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::ceil_, Z const& z) noexcept
//   {
//     return Z {ceil(high(z)), ceil(low(z))};
//   }
//   template<typename Z>
//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::floor_, Z const& z) noexcept
//   {
//     return Z {floor(high(z)), floor(low(z))};
//   }
//   template<typename Z>
//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::nearest_, Z const& z) noexcept
//   {
//     return Z {nearest(high(z)), nearest(low(z))};
//   }
//   template<typename Z>
//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::trunc_, Z const& z) noexcept
//   {
//     return Z {trunc(high(z)), trunc(low(z))};
//   }
//   template<typename Z>
//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::frac_, Z const& z) noexcept
//   {
//     return Z {frac(high(z)), frac(low(z))};
//   }
//   template<typename Z>
//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::minus_, Z const& z) noexcept
//   {
//     return Z {minus(high(z)), minus(low(z))};
//   }

//   //================================================================================================
//   //  trivial extension of some high binary functions
//   //================================================================================================
//   template<typename Z1, typename Z2>
//   EVE_FORCEINLINE auto
//   dd_binary_dispatch(eve::tag::maxabs_, Z1 const& z1, Z2 const& z2) noexcept
//   {
//     return max(abs(z1), abs(z2));
//   }
//   template<typename Z1, typename Z2>
//   EVE_FORCEINLINE auto
//   dd_binary_dispatch(eve::tag::minabs_, Z1 const& z1, Z2 const& z2) noexcept
//   {
//     return min(abs(z1), abs(z2));
//   }
//   template<typename Z1, typename Z2>
//   EVE_FORCEINLINE auto
//   dd_binary_dispatch(eve::tag::dist_, Z1 const& z1, Z2 const& z2) noexcept
//   {
//     return abs(z1 - z2);
//   }

//   //================================================================================================
//   //  trivial extension of some high ternary functions
//   //================================================================================================
//   template<typename Z1, typename Z2, ordered_value T>
//   EVE_FORCEINLINE auto
//   dd_ternary_dispatch(eve::tag::lerp_, Z1 const& z1, Z2 const& z2, T const& t) noexcept
//   {
//     using z_t = decltype(z1 + z2);
//     return z_t {lerp(high(z1), high(z2), t), lerp(low(z1), low(z2), t)};
//   }

//   //================================================================================================
//   //  Unary functions
//   //================================================================================================
//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::abs_, pedantic_type const&, auto const& z) noexcept
//   {
//     return eve::pedantic(eve::hypot)(high(z), low(z));
//   }

//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::abs_, auto const& z) noexcept
//   {
//     return eve::hypot(high(z), low(z));
//   }

//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::arg_, auto const& z) noexcept
//   {
//     return eve::atan2(low(z), high(z));
//   }

//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::arg_, pedantic_type const&, auto const& z) noexcept
//   {
//     return eve::pedantic(eve::atan2)(low(z), high(z));
//   }

//   template<typename Z>
//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::conj_, Z const& z) noexcept
//   {
//     return Z {high(z), -low(z)};
//   }

//   template<typename Z>
//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::dec_, Z const& z) noexcept
//   {
//     return Z {dec(high(z)), low(z)};
//   }

//   template<typename Z>
//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::inc_, Z const& z) noexcept
//   {
//     return Z {inc(high(z)), low(z)};
//   }

//   template<typename Z>
//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::oneminus_, Z const& z) noexcept
//   {
//     return Z {oneminus(high(z)), -low(z)};
//   }
//   template<typename Z>
//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::proj_, Z const& z) noexcept
//   {
//     using real_t = as<as_real_t<Z>>;
//     return if_else(is_infinite(z), Z(inf(real_t {}), copysign(zero(real_t {}), low(z))), z);
//   }

//   template<typename Z>
//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::sqr_, Z const& z) noexcept
//   {
//     auto [zr, zi] = z;
//     return Z {fms(zr, zr, zi * zi), 2 * zr * zi};
//   }

//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::sqr_abs_, auto const& z) noexcept
//   {
//     auto [zr, zi] = z;
//     return fma(zr, zr, zi * zi);
//   }

//   template<typename Z>
//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::sqr_, eve::pedantic_type const&, Z const& z) noexcept
//   {
//     auto [zr, zi] = z;
//     return Z {diff_of_prod(zr, zr, zi, zi), 2 * zr * zi};
//   }

//   template<typename Z>
//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::sqr_, eve::numeric_type const&, Z const& z) noexcept
//   {
//     auto [zr, zi] = z;
//     return Z {(zr-zi)*(zi+zr), 2 * zr * zi};
//   }

//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::sqr_abs_, eve::pedantic_type const&, auto const& z) noexcept
//   {
//     auto [zr, zi] = z;
//     return sum_of_prod(zr, zr, zi, zi);
//   }

//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::sign_, auto const& z) noexcept
//   {
//     return if_else(is_eqz(z), zero, z / abs(z));
//     ;
//   }

//   template<typename Z>
//   EVE_FORCEINLINE auto dd_unary_dispatch(eve::tag::modf_, Z const& z) noexcept
//   {
//     auto t = trunc(z);
//     return kumi::tuple {z - t, t};
//   }

//   //================================================================================================
//   //  Binary functions
//   //================================================================================================
//   EVE_FORCEINLINE auto
//   dd_binary_dispatch(eve::tag::average_, auto const& z1, auto const& z2) noexcept
//   {
//     using z_t = decltype(z1 + z2);
//     return z_t {eve::average(high(z1), high(z2)), eve::average(low(z1), low(z2))};
//   }

//   EVE_FORCEINLINE auto
//   dd_binary_dispatch(eve::tag::negate_, auto const& z1, auto const& z2) noexcept
//   {
//     return z1 * sign(z2);
//   }

//   template<typename Z1, typename Z2>
//   EVE_FORCEINLINE auto
//   dd_binary_dispatch(eve::tag::negatenz_, Z1 const& z1, Z2 const& z2) noexcept
//   {
//     return if_else(eve::is_eqz(z2), to_dd(z1), z1 * sign(z2));
//   }

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
