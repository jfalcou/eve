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
#include <eve/module/quaternion/detail/arithmetic.hpp>
#include <eve/module/quaternion/detail/math.hpp>


namespace eve::detail
{
  //===-------------------------------------------------------------------------------------------
  //=== exp
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto quaternion_unary_dispatch( eve::tag::exp_
                                             , Z const& z) noexcept
  {
    auto p = eve::pure(z);
    auto az = eve::abs(p);
    auto r  = eve::exp(real(z));
    auto w = r*eve::sinc(az);
    return r*cos(az) + w*p;
  }


  //===-------------------------------------------------------------------------------------------
  //=== expm1
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto quaternion_unary_dispatch( eve::tag::expm1_
                                             , Z const& z) noexcept
  {
    return dec(exp(z));
  }

  //===-------------------------------------------------------------------------------------------
  //=== exp2
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto quaternion_unary_dispatch( eve::tag::exp2_
                                             , Z const& z) noexcept
  {
    using e_t = underlying_type_t<Z>;
    return exp(z*log_2(as<e_t>()));
  }

  //===-------------------------------------------------------------------------------------------
  //=== exp10
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto quaternion_unary_dispatch( eve::tag::exp10_
                                             , Z const& z) noexcept
  {
    using e_t = underlying_type_t<Z>;
    return exp(z*log_10(as<e_t>()));
  }


  //===-------------------------------------------------------------------------------------------
  //=== cosh
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto quaternion_unary_dispatch( eve::tag::cosh_
                                             , Z const& z
                                             ) noexcept
  {
    return eve::average(exp(z), exp(minus(z)));
  }

  //===-------------------------------------------------------------------------------------------
  //=== sinh
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto quaternion_unary_dispatch( eve::tag::sinh_
                                             , Z const& z
                                             ) noexcept
  {
    return average(exp(z), -exp(-z));
  }

  //===-------------------------------------------------------------------------------------------
  //=== tanh
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto quaternion_unary_dispatch( eve::tag::tanh_
                                             , Z const& z
                                             ) noexcept
  {
    auto ez = exp(z);
    auto emz= exp(-z);
    return (ez-emz)/(ez+emz);
  }

  //===-------------------------------------------------------------------------------------------
  //=== coth
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto quaternion_unary_dispatch( eve::tag::coth_
                                             , Z const& z
                                             ) noexcept
  {
    auto ez = exp(z);
    auto emz= exp(-z);
    return (ez+emz)/(ez-emz);
  }

  //===-------------------------------------------------------------------------------------------
  //=== cos
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto quaternion_unary_dispatch( eve::tag::cos_, Z const& z) noexcept
  {
    auto az = eve::abs(eve::pure(z));
    auto [s, c] = sincos(real(z));
    auto w = -s*sinhc(az);
    auto r = Z{c*cosh(az) , w*ipart(z),w*jpart(z), w*kpart(z)};
    return r;
  }

  //===-------------------------------------------------------------------------------------------
  //=== sin
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto quaternion_unary_dispatch( eve::tag::sin_
                                             , Z const& z) noexcept
  {
    auto az = eve::abs(eve::pure(z));
    auto [s, c] = sincos(real(z));
    auto  w = c*sinhc(az);
    auto r = Z{s*cosh(az) , w*ipart(z),w*jpart(z), w*kpart(z)};
    return r;
  }

  //===-------------------------------------------------------------------------------------------
  //=== sincos
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto quaternion_unary_dispatch( eve::tag::sincos_
                                             , Z const& z) noexcept
  {
    auto az = eve::abs(eve::pure(z));
    auto [s, c] = sincos(real(z));
    auto shc = sinhc(az);
    auto ch  = cosh(az);
    auto wc = c*shc;
    auto ws =-s*shc;
    auto sq = Z{s*ch , wc*ipart(z),wc*jpart(z), wc*kpart(z)};
    auto cq = Z{c*ch , ws*ipart(z),ws*jpart(z), ws*kpart(z)};
    return kumi::tuple{sq, cq};
  }

  //===-------------------------------------------------------------------------------------------
  //=== sinhcosh
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto quaternion_unary_dispatch( eve::tag::sinhcosh_
                                             , Z const& z) noexcept
  {
    auto ez = exp(z);
    auto emz= exp(-z);
    return kumi::tuple{average(ez, -emz), average(ez, emz)};
  }


  //===-------------------------------------------------------------------------------------------
  //=== tan
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto quaternion_unary_dispatch( eve::tag::tan_
                                             , Z const& z
                                             ) noexcept
  {
    auto [s, c] = sincos(z);
    return s/c;
  }


  //===-------------------------------------------------------------------------------------------
  //=== cot
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto quaternion_unary_dispatch( eve::tag::cot_
                                             , Z const& z
                                             ) noexcept
  {
    auto [s, c] = sincos(z);
    return c/s;
   }

  //===-------------------------------------------------------------------------------------------
  //=== log
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto quaternion_unary_dispatch( eve::tag::log_
                                                , Z const& q
                                                ) noexcept
  {
    auto aq = abs(q);
    auto v = pure(q);
    auto s = real(q);
    auto z = eve::log(aq)+(eve::acos(s/aq)/abs(v))*v;
    return if_else( is_eqz(z)
                  , Z(minf(as(aq)))
                  , if_else( is_real(z)
                           , to_quaternion(log(to_complex(real(z))))
                           , z
                           )
                  );
  }

  //===-------------------------------------------------------------------------------------------
  //=== log2
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto quaternion_unary_dispatch( eve::tag::log2_
                                                , Z const& q
                                                ) noexcept
  {
    using e_t = underlying_type_t<Z>;
    return log(q)*invlog_2(as<e_t>());
  }

  //===-------------------------------------------------------------------------------------------
  //=== log10
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  EVE_FORCEINLINE auto quaternion_unary_dispatch( eve::tag::log10_
                                                , Z const& q
                                                ) noexcept
  {
    using e_t = underlying_type_t<Z>;
    return log(q)*invlog_10(as<e_t>());
  }

  //===-------------------------------------------------------------------------------------------
  //=== rec
  //===-------------------------------------------------------------------------------------------

  template<typename Z>
  EVE_FORCEINLINE auto quaternion_unary_dispatch( eve::tag::rec_
                                            , Z const& z ) noexcept
  {
    return conj(z)*rec(sqr_abs(z));
  }

  //==============================================================================================
  //  Binary functions :
  //==============================================================================================

  template<typename Z1, typename ...Z2>
  EVE_FORCEINLINE auto quaternion_nary_dispatch( eve::tag::hypot_
                                            , Z1 const& z1, Z2 const&... z2
                                            ) noexcept
  {
    return hypot(real(z1), ipart(z1), jpart(z1), kpart(z1), real(z2)..., ipart(z2)..., jpart(z2)..., kpart(z2)...);
  }

  template<decorator D, typename Z1, typename ...Z2>
  EVE_FORCEINLINE auto quaternion_nary_dispatch( eve::tag::hypot_
                                            , D const & d
                                            , Z1 const& z1, Z2 const&... z2
                                            ) noexcept
  {
    return d(hypot)(real(z1), ipart(z1), jpart(z1), kpart(z1), real(z2)..., ipart(z2)..., jpart(z2)..., kpart(z2)...);
  }

  template<ordered_value P, typename Z1, typename ...Z2>
  EVE_FORCEINLINE auto quaternion_nary_dispatch( eve::tag::lpnorm_
                                            , P const & p, Z1 const& z1, Z2 const&... z2
                                            ) noexcept
  {
    return lpnorm(p, abs(z1), abs(z2)...);
  }

  template<decorator D, ordered_value P, typename Z1, typename ...Z2>
  EVE_FORCEINLINE auto quaternion_nary_dispatch( eve::tag::lpnorm_
                                            , D const & d
                                            , P const & p, Z1 const& z1, Z2 const&... z2
                                            ) noexcept
  {
    return d(lpnorm)(p, abs(z1), abs(z2)...);
  }

  template<typename Z, int II,  int JJ,  int KK>
  EVE_FORCEINLINE auto quaternion_nary_dispatch( eve::tag::to_euler_
                                               , Z const& q
                                               , axis<II>
                                               , axis<JJ>
                                               , axis<KK>
                                               , bool extrinsic
                                               ) noexcept
  {
    int I = II;
    int J = JJ;
    int K = KK;
    using e_t =  std::remove_reference_t<decltype(real(Z()))>;
    std::array<e_t, 4> aq{get<0>(q), get<1>(q), get<2>(q), get<3>(q)};
    EVE_ASSERT(eve::all(is_nez(q)), "some quaternion are null");
    EVE_ASSERT(I != J && J != K, "Expected consecutive axes to be different");
    bool is_proper = I == K; //Proper Euler angles else Tait-Bryan
    if (!extrinsic) std::swap(I, K);
    K = 6-I-J;
    int sign = (I-J)*(J-K)*(K-I)/2; // even (+1) permutation or odd (-1);
    auto a = aq[0];
    auto b = aq[I];
    auto c = aq[J];
    auto d = aq[K]*sign;
    if (!is_proper)
    {
      a -= aq[J];
      b += aq[K]*sign;
      c += aq[0];
      d -= aq[I];
    }
    auto a2pb2 = sqr(a)+sqr(b);
    auto n2 = a2pb2+sqr(c)+sqr(d);
    auto theta1 = acos(dec(2*a2pb2/n2));
    auto eps = 1e-7;
    auto pi  = eve::pi(as<e_t>());
    auto twopi = eve::two_pi(as<e_t>());
    auto mpi = -pi;
    auto is_safe1 = abs(theta1) >= eps;
    auto is_safe2 = abs(theta1 - pi) >= eps;
    auto is_safe = is_safe1 && is_safe2;

    auto hp = atan2(b, a);
    auto hm = atan2(-d, c);

    auto theta0 = hp + hm;
    auto theta2 = hp - hm;

    if (!extrinsic)
    {
      theta0 = if_else(!is_safe, zero, theta0);
      theta2 = if_else(!is_safe1, 2*hp, theta2);
      theta2 = if_else(!is_safe2, -2*hm, theta2);
    }
    else
    {
      theta2 = if_else(!is_safe, zero, theta2);
      theta0 = if_else(!is_safe1, 2*hp, theta0);
      theta0 = if_else(!is_safe2, 2*hm, theta0);
    }
    theta0 += if_else(theta0 < mpi, twopi, zero);
    theta0 -= if_else(theta0 >  pi, twopi, zero);
    theta1 += if_else(theta1 < mpi, twopi, zero);
    theta1 -= if_else(theta1 >  pi, twopi, zero);
    theta2 += if_else(theta2 < mpi, twopi, zero);
    theta2 -= if_else(theta2 >  pi, twopi, zero);

    // for Tait-Bryan thetas
    if(!is_proper)
    {
      theta2 *= sign;
      theta1 -= pi / 2;
    }
    if (!extrinsic) std::swap(theta0, theta2);

    return kumi::tuple{theta0, theta1, theta2};
  }

}
