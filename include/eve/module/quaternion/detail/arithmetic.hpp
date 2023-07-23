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
    return if_else(is_eqz(z), zero, z / pedantic(abs)(z));
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

  //================================================================================================
  //  dot product
  //================================================================================================
  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  quaternion_binary_dispatch(eve::tag::dot_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return sum_of_prod(real(z1), real(z2), ipart(z1), ipart(z2))+
      sum_of_prod(jpart(z1), jpart(z2), kpart(z1), kpart(z2));
  }

  //================================================================================================
  //  rotate vector
  //================================================================================================
  template<typename Z1, ordered_value T, bool normalize>
  EVE_FORCEINLINE auto
  quaternion_nary_dispatch(eve::tag::rot_vec_
                            , Z1 q
                            , std::span<T, 3> const & v
                            , nor<normalize>) noexcept
  {
    using e_t = std::decay_t<decltype(real(q))>;
    using v_t = decltype(T()+e_t());
    if constexpr (!normalize) EVE_ASSERT(eve::all(pedantic(is_unit)(q)), "some quaternions are not unitary");
    std::array<v_t, 3> w, wp;
    using a_t = decltype(abs(q));
    a_t fac(2);
    if constexpr(normalize) fac *= rec(sqr_abs(q));
    auto [r, i, j, k] = q;
    w[0] = fma(r, v[0], diff_of_prod(j, v[2], k, v[1]));
    w[1] = fma(r, v[1], diff_of_prod(k, v[0], i, v[2]));
    w[2] = fma(r, v[2], diff_of_prod(i, v[1], j, v[0]));

    wp[0] = fam(v[0], fac, diff_of_prod(j, w[2], k, w[1]));
    wp[1] = fam(v[1], fac, diff_of_prod(k, w[0], i, w[2]));
    wp[2] = fam(v[2], fac, diff_of_prod(i, w[1], j, w[0]));
    return wp;
  }

  template<typename Z1, ordered_value T>
  EVE_FORCEINLINE auto
  quaternion_nary_dispatch(eve::tag::rot_vec_
                            , Z1 q
                            , std::span<T, 3> const & v) noexcept
  {
    return rot_vec(q, v, Normalize);
  }

  //================================================================================================
  // axis
  //================================================================================================
  template<typename Z1>
  EVE_FORCEINLINE auto
  quaternion_unary_dispatch(eve::tag::axis_
                          , const Z1 & q) noexcept
  {
    using e_t = std::decay_t<decltype(real(q))>;
    auto invn = rec(abs(pure(q)));
    invn = if_else(is_nan(invn), zero, invn);
    std::array<e_t, 3> v{ipart(q)*invn, jpart(q)*invn, kpart(q)*invn};
    return v;
  }

  //================================================================================================
  // angle
  //================================================================================================
  template<typename Z1>
  EVE_FORCEINLINE auto
  quaternion_unary_dispatch(eve::tag::angle_
                          , const Z1 &q) noexcept
  {
    return 2*pedantic(atan2)(abs(pure(q)), real(q));
  }

  //================================================================================================
  // to_rotation_matrix
  //================================================================================================
  template<typename Z, bool normalize>
  EVE_FORCEINLINE auto
  quaternion_nary_dispatch(eve::tag::to_rotation_matrix_
                           , Z const & q , nor<normalize> const &) noexcept
  {
    if constexpr (!normalize) EVE_ASSERT(eve::all(pedantic(is_unit)(q)), "some quaternions are not unitary");
    else return to_rotation_matrix(q/abs(q), Assume_normalized);

    auto q0 = real(q);
    auto q1 = ipart(q);
    auto q2 = jpart(q);
    auto q3 = kpart(q);

    // First row of the rotation matrix
    auto r00 = 2 * (sqr(q0) + sqr(q1)) - 1;
    auto r01 = 2 * (q1 * q2 - q0 * q3);
    auto r02 = 2 * (q1 * q3 + q0 * q2);

    // Second row of the rotation matrix
    auto r10 = 2 * (q1 * q2 + q0 * q3);
    auto r11 = 2 * (sqr(q0) + sqr(q2)) - 1;
    auto r12 = 2 * (q2 * q3 - q0 * q1);

    // Third row of the rotation matrix
    auto r20 = 2 * (q1 * q3 - q0 * q2);
    auto r21 = 2 * (q2 * q3 + q0 * q1);
    auto r22 = 2 * (sqr(q0) + sqr(q3)) - 1;

    // 3x3 rotation matrix
    using e_t = std::decay_t<decltype(q0)>;
    using l_t = std::array<e_t, 3>;
    using m_t = std::array< l_t, 3>;
    std::array<e_t, 3> l1{r00, r01, r02};
    std::array<e_t, 3> l2{r10, r11, r12};
    std::array<e_t, 3> l3{r20, r21, r22};
    return m_t{l1, l2, l3};
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  quaternion_unary_dispatch(eve::tag::to_rotation_matrix_
                           , Z const & q) noexcept
  {
    return to_rotation_matrix(q, Normalize);
  }
}
