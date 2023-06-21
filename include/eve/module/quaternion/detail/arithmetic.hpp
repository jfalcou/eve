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
// #include <eve/module/core/regular/conj.hpp>
// #include <eve/module/quaternion/regular/proj.hpp>

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

//   //================================================================================================
//   // operators as pedantic functions
//   //================================================================================================
//   template<typename Z1, typename Z2>
//   EVE_FORCEINLINE auto
//   quaternion_binary_dispatch(eve::tag::mul_, pedantic_type const&, Z1 const& z1, Z2 const& z2) noexcept
//   {
//     using v_t = decltype(real(z1) * real(z2));
//     using r_t = eve::as_quaternion_t<v_t>;

//     r_t r;
//     auto a = real(z1);
//     auto b = imag(z1);

//     auto c = real(z2);
//     auto d = imag(z2);

//     if constexpr( !is_quaternion_v<Z1> || !is_quaternion_v<Z1> ) { r = z1 * z2; }
//     else
//     {
//       auto rr = pedantic(diff_of_prod)(a, c, b, d);
//       auto ri = pedantic(sum_of_prod)(a, d, b, c);
//       r       = r_t(rr, ri);
//     }
//     auto test = is_finite(r);
//     if( eve::all(test) ) return r;
//     auto cur = logical_andnot(is_real(z1), test);
//     if( eve::any(cur) )
//     {
//       r    = if_else(cur, a * z2, r);
//       test = logical_or(test, cur);
//       if( eve::all(test) ) return r;
//     }
//     cur = eve::logical_andnot(is_imag(z1), test);
//     if( eve::any(cur) )
//     {
//       r    = if_else(cur, b * z2 * eve::i, r);
//       test = logical_or(test, cur);
//       if( eve::all(test) ) return r;
//     }
//     cur = eve::logical_andnot(is_real(z2), test);
//     if( eve::any(cur) )
//     {
//       r    = if_else(cur, c * z1, r);
//       test = logical_or(test, cur);
//       if( eve::all(test) ) return r;
//     }
//     cur = eve::logical_andnot(is_imag(z2), test);
//     if( eve::any(cur) )
//     {
//       r    = if_else(cur, d * z1 * eve::i, r);
//       test = logical_or(test, cur);
//       if( eve::all(test) ) return r;
//     }
//     return r;
//   }

//   template<typename Z1, typename Z2>
//   EVE_FORCEINLINE auto
//   quaternion_binary_dispatch(eve::tag::div_, pedantic_type const&, Z1 const& z1, Z2 const& z2) noexcept
//   {
//     using v_t = decltype(real(z1) / real(z2));
//     using r_t = eve::as_quaternion_t<v_t>;
//     if constexpr( !is_quaternion_v<Z2> )
//     {
//       auto iz2 = pedantic(rec)(z2);
//       return pedantic(mul)(z1, iz2);
//     }
//     else
//     {
//       auto rr = eve::abs(real(z1));
//       auto ii = eve::abs(imag(z1));
//       auto e  = -if_else((rr < ii), exponent(ii), exponent(rr));
//       auto zz2(eve::ldexp(z2, e));
//       auto denom = sqr_abs(zz2);
//       r_t  r     = pedantic(mul)(z1, conj(zz2));
//       r /= denom;
//       r = if_else(is_not_infinite(denom), r, zero);
//       return ldexp(r, e);
//     }
//   }

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
  quaternion_unary_dispatch(eve::tag::sqr_, Z const& z) noexcept
  {
    auto [a, b, c, d] = z;
    real(z)  = a*a - b*b - c*c - d*d;
    ipart(z) = 2*a*b;
    jpart(z) = 2*a*c;
    kpart(z) = 2*a*d;
    return z;
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

//   template<typename Z>
//   EVE_FORCEINLINE auto quaternion_unary_dispatch(eve::tag::modf_, Z const& z) noexcept
//   {
//     auto t = trunc(z);
//     return kumi::tuple {z - t, t};
//   }

  //================================================================================================
  //  Binary functions
  //================================================================================================
  EVE_FORCEINLINE auto
  quaternion_binary_dispatch(eve::tag::average_, auto const& z1, auto const& z2) noexcept
  {
    using z_t = decltype(z1 + z2);
    return z_t {eve::average(real(z1), real(z2)), eve::average(ipart(z1), ipart(z2))
        , eve::average(jpart(z1), jpart(z2)) , eve::average(kpart(z1), kpart(z2))};
  }
}
