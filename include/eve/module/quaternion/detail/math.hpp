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
    auto az = eve::abs(eve::pure(z));
    auto r  = eve::exp(real(z));
    auto w = r*eve::sinc(az);
    return Z{r*cos(az), w*ipart(z), w*jpart(z), w*kpart(z)};
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

  template<int I,  int J,  int K, typename Z>
  EVE_FORCEINLINE auto quaternion_nary_dispatch( eve::tag::to_euler_
                                               , Z const& q
                                               , std::integral_constant<int, I>
                                               , std::integral_constant<int, J>
                                               , std::integral_constant<int, K>
                                            ) noexcept
  {
    EVE_ASSERT(eve::all(is_nez(q)), "some quaternion are null");
    using e_t =  std::remove_reference_t<decltype(real(Z()))>;
    static_assert(I != J && J != K);
    constexpr bool not_proper = I == K;
    constexpr int KK = 6-I-J;
    constexpr int sign = (I-J)*(J-KK)*(KK-I)/2; // even (+1) permutation or odd (-1);
    auto a = real(q);
    auto b = get<I>(q);
    auto c = get<J>(q);
    auto d = get<K>(q)*sign;
    if constexpr (not_proper)
    {
      a += get<J>(q);
      b += get<KK>(q)*sign;
      c += real(q);
      d -= get<I>(q);
    }
    auto a2pb2 = sqr(a)+sqr(b);
    e_t theta2 = acos(dec(2*(a2pb2/(a2pb2+sqr(c)+sqr(d)))));
    auto thetap = atan2(b, a);
    auto thetam = atan2(d, c);
    thetam = if_else(is_nan(thetam), zero, thetam);
    auto isz = almost(is_equal)(theta2, zero(as(theta2)));
    auto ispio2 = almost(is_equal)(theta2, pio_2(as(theta2)));
    e_t theta3 = if_else(isz, 2*thetap-thetam
                        , if_else(ispio2
                                 , 2*thetam+thetap
                                 , thetap+thetam
                                 )
                        );
    e_t theta1 = if_else(isz || ispio2, zero, thetap-thetam);
    if constexpr(not_proper)
    {
      theta3 *= sign;
      theta2 -= pio_2(as(theta2));
    }
    return kumi::tuple{theta1, theta2, theta3};
  }

}
