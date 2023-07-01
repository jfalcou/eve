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
#include <eve/module/complex.hpp>
#include <eve/module/quaternion/regular/traits.hpp>

namespace eve::detail
{
  //================================================================================================
  // operators as functions
  //================================================================================================
  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  quaternion_binary_dispatch(eve::tag::add_, Z1 const& z1, Z2 const& z2) noexcept -> decltype(z1+z2)
  {
    return z1 + z2;
  }

  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  quaternion_binary_dispatch(eve::tag::sub_, Z1 const& z1, Z2 const& z2) noexcept -> decltype(z1+z2)
  {
    return z1 - z2;
  }

  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  quaternion_binary_dispatch(eve::tag::mul_, Z1 const& z1, Z2 const& z2) noexcept -> decltype(z1+z2)
  {
    return z1 * z2;
  }

  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  quaternion_binary_dispatch(eve::tag::div_, Z1 const& z1, Z2 const& z2) noexcept -> decltype(z1+z2)
  {
    return z1 / z2;
  }

  //================================================================================================
  //  trivial extension of some real unary functions
  //================================================================================================
  template<typename Z>
  EVE_FORCEINLINE auto
  quaternion_unary_dispatch(eve::tag::ceil_, Z const& z) noexcept
  {
    return Z {ceil(real(z)), ceil(ipart(z)), ceil(jpart(z)), ceil(kpart(z))};
  }
  template<typename Z>
  EVE_FORCEINLINE auto
  quaternion_unary_dispatch(eve::tag::floor_, Z const& z) noexcept
  {
    return Z {floor(real(z)), floor(ipart(z)), floor(jpart(z)), floor(kpart(z))};
  }
  template<typename Z>
  EVE_FORCEINLINE auto
  quaternion_unary_dispatch(eve::tag::nearest_, Z const& z) noexcept
  {
    return Z {nearest(real(z)), nearest(ipart(z)), nearest(jpart(z)), nearest(kpart(z))};
  }
  template<typename Z>
  EVE_FORCEINLINE auto
  quaternion_unary_dispatch(eve::tag::trunc_, Z const& z) noexcept
  {
    return Z {trunc(real(z)), trunc(ipart(z)), trunc(jpart(z)), trunc(kpart(z))};
  }
  template<typename Z>
  EVE_FORCEINLINE auto
  quaternion_unary_dispatch(eve::tag::frac_, Z const& z) noexcept
  {
    return Z {frac(real(z)), frac(ipart(z)), frac(jpart(z)), frac(kpart(z))};
  }
  template<typename Z>
  EVE_FORCEINLINE auto
  quaternion_unary_dispatch(eve::tag::minus_, Z const& z) noexcept
  {
    return Z {minus(real(z)), minus(ipart(z)), minus(jpart(z)), minus(kpart(z))};
  }

  //================================================================================================
  //  trivial extension of some real binary functions
  //================================================================================================
  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  quaternion_binary_dispatch(eve::tag::maxabs_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return max(abs(z1), abs(z2));
  }
  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  quaternion_binary_dispatch(eve::tag::minabs_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return min(abs(z1), abs(z2));
  }
  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  quaternion_binary_dispatch(eve::tag::dist_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return abs(z1 - z2);
  }

  //================================================================================================
  //  trivial extension of some real ternary functions
  //================================================================================================
  template<typename Z1, typename Z2, ordered_value T>
  EVE_FORCEINLINE auto
  quaternion_ternary_dispatch(eve::tag::lerp_, Z1 const& z1, Z2 const& z2, T const& t) noexcept
  {
    using z_t = decltype(z1 + z2);
    return z_t {lerp(real(z1), real(z2), t), lerp(ipart(z1), ipart(z2), t)
                , lerp(jpart(z1), jpart(z2), t), lerp(kpart(z1), kpart(z2), t)};
  }

  template<typename Z1, typename Z2, ordered_value T>
  EVE_FORCEINLINE auto
  quaternion_ternary_dispatch(eve::tag::slerp_, Z1 const& z1, Z2  z2, T const& t) noexcept
  {
    std::cout << "z1 " << z1              << std::endl;
    std::cout << "z2 " << z2              << std::endl;
    EVE_ASSERT(eve::all(is_unit(z1)&&is_unit(z2)), "a parameter is not unitary");
    auto ct = fma(real(z1), real(z2), fma(ipart(z1), ipart(z2), fma(jpart(z1), jpart(z2), kpart(z1)*kpart(z2))));
    std::cout << "ct " << ct << std::endl;
//     auto is_not_sp = is_ltz(ct);
//     z2 = if_else(is_not_sp, -z2, z2);
//     ct = if_else(is_not_sp, -ct, ct);
//     ct = clamp(ct, mone(as(ct)), one(as(ct)));
    auto theta = acos(ct);
    auto invs = csc(theta);
//     auto res = ( (invs*sin(t*theta))*z1+(invs*sin(dec(t)*theta))*z2 );
//    auto [s, c] = sincos(t*theta);
//     auto pipo = sign(z1*c+(z1-z2*ct)*s);
//     std::cout << "norm " << sqr_abs(pipo-res) << std::endl;
//     std::cout << "pipo " << pipo              << std::endl;
//     std::cout << "res  " << res               << std::endl;
//    return if_else(abs(ct-1) < 3*eps(as(ct)), z1, res);
    auto z1m1z2 = rec(z1)*z2;
    auto p =  pure(z1m1z2)*invs;
    auto [s, c] = sincos(theta*t);

    return z1*(c+s*p);
  }

  //================================================================================================
  //  Unary functions
  //================================================================================================
  EVE_FORCEINLINE auto
  quaternion_unary_dispatch(eve::tag::abs_, pedantic_type const&, auto const& z) noexcept
  {
    return eve::pedantic(eve::hypot)(real(z), ipart(z), jpart(z), kpart(z));
  }

  EVE_FORCEINLINE auto
  quaternion_unary_dispatch(eve::tag::abs_, auto const& z) noexcept
  {
    return eve::hypot(real(z), ipart(z), jpart(z), kpart(z));
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  quaternion_unary_dispatch(eve::tag::conj_, Z const& z) noexcept
  {
    return Z {real(z), -ipart(z), -jpart(z), -kpart(z)};
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  quaternion_unary_dispatch(eve::tag::dec_, Z  z) noexcept
  {
    real(z) = dec(real(z));
    return z;
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  quaternion_unary_dispatch(eve::tag::inc_, Z z) noexcept
  {
    real(z) = inc(real(z));
    return z;
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  quaternion_unary_dispatch(eve::tag::oneminus_, Z const& z) noexcept
  {
    return inc(minus(z));
  }


  template<typename Z>
  EVE_FORCEINLINE auto
  quaternion_unary_dispatch(eve::tag::sqr_, Z z) noexcept
  {
    auto [a, b, c, d] = z;
    real(z)  = a*a - b*b - c*c - d*d;
    ipart(z) = 2*a*b;
    jpart(z) = 2*a*c;
    kpart(z) = 2*a*d;
    return z;
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  quaternion_unary_dispatch(eve::tag::sqrt_, Z z) noexcept
  {
    auto r = abs(z);
    auto theta = acos(real(z)/r);
    auto u = sign(pure(z));
    auto [s, c] = sincos(theta*half(as(theta)));
    auto res = u*s;
    real(res) = c;
    res = if_else(is_eqz(r), zero(as(z))
                 , if_else(is_real(z), Z(sqrt(real(z))), res*sqrt(r)
                          )
                 );
    return res;
  }

  EVE_FORCEINLINE auto
  quaternion_unary_dispatch(eve::tag::sqr_abs_, auto const& z) noexcept
  {
    auto [a, b, c, d] = z;
    return fma(a, a, fma(b, b, fma(c, c, d*d)));
  }


  EVE_FORCEINLINE auto
  quaternion_unary_dispatch(eve::tag::sign_, auto const& z) noexcept
  {
    return if_else(is_eqz(z), zero, z / abs(z));
  }

  template<typename Z>
  EVE_FORCEINLINE auto quaternion_unary_dispatch(eve::tag::modf_, Z const& z) noexcept
  {
    auto t = trunc(z);
    return kumi::tuple {z - t, t};
  }

  //================================================================================================
  //  Binary functions
  //================================================================================================
  EVE_FORCEINLINE auto
  quaternion_binary_dispatch(eve::tag::average_, auto const& z1, auto const& z2) noexcept -> decltype(z1+z2)
  {
    using z_t = decltype(add(z1, z2));
    return z_t { eve::average(real(z1), real(z2))
        , eve::average(ipart(z1), ipart(z2))
        , eve::average(jpart(z1), jpart(z2))
        , eve::average(kpart(z1), kpart(z2))};
  }

  //================================================================================================
  //  relative distance
  //================================================================================================
   template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  quaternion_binary_dispatch(eve::tag::reldist_, Z1 const& z1, Z2 const& z2) noexcept -> decltype(abs(z1+z2))
  {
    using r_t = decltype(abs(z1+z2));
    return dist(z1, z2)/max(abs(z1), abs(z2), one(as<r_t>()));
  }
}
