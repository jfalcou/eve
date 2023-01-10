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
#include <eve/module/dd/regular/ddlo.hpp>
#include <eve/module/dd/regular/ddhi.hpp>
#include <eve/module/dd/detail/predicates.hpp>

namespace eve::detail
{
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


  //================================================================================================
  //  trivial extension of some real unary functions
  //================================================================================================
  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::ceil_, Z const& z) noexcept
  {
    return Z{ceil(ddhi(z)), ceil(ddlo(z))};
  }
  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::floor_, Z const& z) noexcept
  {
    return Z {floor(ddhi(z)), floor(ddlo(z))};
  }
  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::nearest_, Z const& z) noexcept
  {
    return Z {nearest(ddhi(z)), nearest(ddlo(z))};
  }
  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::trunc_, Z const& z) noexcept
  {
    return Z {trunc(ddhi(z)), trunc(ddlo(z))};
  }
  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::frac_, Z const& z) noexcept
  {
    return z-trunc(z);
  }
  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::minus_, Z const& z) noexcept
  {
    return -z;
  }

  //================================================================================================
  //  trivial extension of some real binary functions
  //================================================================================================
  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  dd_binary_dispatch(eve::tag::maxabs_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return max(abs(z1), abs(z2));
  }
  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  dd_binary_dispatch(eve::tag::minabs_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return min(abs(z1), abs(z2));
  }
  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  dd_binary_dispatch(eve::tag::dist_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return abs(z1 - z2);
  }

  //================================================================================================
  //  trivial extension of some real ternary functions
  //================================================================================================
  template<typename Z1, typename Z2, ordered_value T>
  EVE_FORCEINLINE auto
  dd_ternary_dispatch(eve::tag::lerp_, Z1 const& z1, Z2 const& z2, T const& t) noexcept
  {
    using z_t = decltype(z1 + z2);
    return z_t {lerp(ddhi(z1), ddhi(z2), t), lerp(ddlo(z1), ddlo(z2), t)};
  }

  //================================================================================================
  //  Unary functions
  //================================================================================================

  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::abs_, auto const& z) noexcept
  {
    return if_else(is_ltz(ddhi(z)), -z, z);
  }

//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::arg_, auto const& z) noexcept
//   {
//     return if_else(is_ltz(ddhi(z)), zero, pi(as(z))));;
//   }

  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::conj_, Z const& z) noexcept
  {
    return z;
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::dec_, Z const& z) noexcept
  {
    return Z {dec(ddhi(z)), ddlo(z)};
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::inc_, Z const& z) noexcept
  {
    return Z {inc(ddhi(z)), ddlo(z)};
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::oneminus_, Z const& z) noexcept
  {
    return one(as(z))-z;
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::sqr_, Z const& a) noexcept
  {
    auto [ahi, alo] = a;
    auto[p1, p2] = two_sqr(ahi);
    p2 += 2.0 * ahi * alo;
    p2 += alo * alo;
    auto [ s1, s2] = quick_two_add(p1, p2);
    return Z{s1, s2};
  }

  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::sqr_abs_, auto const& z) noexcept
  {
    return sqr(z);
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::sign_, Z const& z) noexcept
  {
    return Z{sign(ddhi(z))};
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
  dd_binary_dispatch(eve::tag::average_, auto const& z1, auto const& z2) noexcept
  {
    using z_t = decltype(z1 + z2);
    return z_t {eve::average(ddhi(z1), ddhi(z2)), eve::average(ddlo(z1), ddlo(z2))};
  }

  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  dd_binary_dispatch(eve::tag::negate_, Z1 const& z1, Z2 const& z2) noexcept
  {
    using r_t = decltype(z1*z2);
    if constexpr(is_dd_v<Z2>)
      return r_t(z1 * sign(ddhi(z2)));
    else
      return z1 * sign(z2);
  }

  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  dd_binary_dispatch(eve::tag::negatenz_, Z1 const& z1, Z2 const& z2) noexcept
  {
    using r_t = decltype(z1*z2);
    return if_else(eve::is_eqz(z2), r_t(sign(z1)), sign(z1)*z2);
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
// //   dd_real Fma( dd_real const& a, dd_real const& b, dd_real const& c )
// //   {
// //     double p0, p1, p2, p3;
// //     qd_mul(a, b, p);
// //     qd_add(p, c, p);
// //     p[0] = qd::two_sum(p[0], p[1] + p[2] + p[3], p[1]);
// //     return dd_real(p[0], p[1]);
// //   }
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
