//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/vectorizable.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/product_type.hpp>
#include <eve/module/ad/regular/traits.hpp>
#include <eve/module/ad/regular/is_derivable.hpp>
#include <eve/detail/abi.hpp>
#include <iostream>
#include <iomanip>

namespace eve
{
  //================================================================================================
  //! @addtogroup simd_types
  //! @{
  //================================================================================================
  //! @brief SIMD-compatible representation of valder numbers
  //!
  //! **Required header:** `#include <eve/module/ad.hpp>`
  //!
  //! eve::valder is structure representing pair of function value,  function derivative
  //! and mean to be used in conjunction with eve::wide.
  //!
  //! All eve functions can be called with a valder parameter in place of floating or complex parameters
  //! with a few restrictions and exceptions
  //!
  //!    - the derivative of piecewise derivable functions (as abs, trunc or frac) are undefined at non derivable points
  //!    - complex non meromorphic functions cannot be derived relative the complex arguments.  // TO BE DONE complex still not accepted
  //!    - functions with no sensible derivation properties as predicates or bit-related
  //!      are accepted but always act as if  the derivative was not present and return a function value. // TO BE COMPLETED
  //!      They can be used in tests.
  //!    - eve constants of valder<T> are constant of T // TO BE DONE eve constants still not accepted
  //!
  //! @tparam Type  Underlying floating point type
  //================================================================================================
  template<floating_scalar_value Type>
  struct valder : struct_support<valder<Type>, Type, Type>
  {
    //   using eve_disable_ordering = void;
    using parent = struct_support<valder<Type>, Type, Type>;

    /// Underlying type
    using value_type = Type;

    /// Default constructor
    EVE_FORCEINLINE valder(Type val = 0, Type der = 0)  noexcept : parent{val, der} {}


    //==============================================================================================
    friend std::ostream& operator<<(std::ostream& os, like<valder> auto const& z)
    {
      return os << std::setprecision(20) << "(" << val(z) << ", "<< der(z) << ")" << std::noshowpos;
    }

    //==============================================================================================
    //  val/der parts as functions
    //==============================================================================================

    /// Retrieve the value part of the current valder number
    EVE_FORCEINLINE friend
    decltype(auto) tagged_dispatch( eve::tag::val_, like<valder> auto& z ) noexcept
    {
      return get<0>(EVE_FWD(z));
    }

    EVE_FORCEINLINE friend
    decltype(auto) tagged_dispatch( eve::tag::val_, like<valder> auto const& z ) noexcept
    {
      return get<0>(EVE_FWD(z));
    }

    /// Retrieve the derivative part of the current valder number
    EVE_FORCEINLINE friend
    decltype(auto) tagged_dispatch( eve::tag::der_, like<valder> auto& z ) noexcept
    {
      return get<1>(EVE_FWD(z));
    }

    EVE_FORCEINLINE friend
    decltype(auto) tagged_dispatch( eve::tag::der_, like<valder> auto const& z ) noexcept
    {
      return get<1>(EVE_FWD(z));
    }

    // helpers
    //==============================================================================================
    // Compute non-derivable function
    //==============================================================================================
    template<typename Func, typename Z1, typename... Zs>
    static EVE_FORCEINLINE auto compute(Func f, Z1 const& z1, Zs const& ... zs)
    {
      return f(val(z1), val(zs)...);
    }

    //==============================================================================================
    //  Unary functions
    //==============================================================================================
    template<typename Func, like<valder> Z>
    static EVE_FORCEINLINE auto unary(Func f, Z const & z)
    {
      auto [v, d] = z;
      return Z{f(v), diff(f)(v)*d};
    }

    //==============================================================================================
    //  n_ary functions
    //==============================================================================================
    template<typename Func, typename V0, typename V1, typename... Vs>
    static EVE_FORCEINLINE auto n_ary(Func f, V0 const& z0, V1 const& z1, Vs const&... zs )
    {
      using v_t = decltype(f(val(z0),val(z1),val(zs)...));
      using r_t = eve::as_valder_t<v_t>;

      auto vs = kumi::make_tuple(v_t(val(z0)),v_t(val(z1)),v_t(val(zs))...);
      auto ds = kumi::make_tuple(v_t(der(zs))...);

      v_t d = sum_of_prod ( kumi::apply(diff_1st(f),vs), v_t(der(z0))
                          , kumi::apply(diff_2nd(f),vs), v_t(der(z1))
                          );

      [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        ((d = fam(d, kumi::apply(diff_nth<I+3>(f),vs), get<I>(ds))),...);
      }(std::index_sequence_for<Vs...>{});

      return r_t{ kumi::apply(f,vs), d};
    }

    //==============================================================================================
    //  Operators
    //==============================================================================================

    //==============================================================================================
    // add/sub
    //==============================================================================================
    EVE_FORCEINLINE friend auto& operator+= ( like<valder> auto& self
                                            , like<valder> auto const& other
                                            ) noexcept
    {
      val(self) += val(other);
      der(self) += der(other);
      return self;
    }

    EVE_FORCEINLINE friend auto& operator-= ( like<valder> auto& self
                                            , like<valder> auto const& other
                                            ) noexcept
    {
      val(self) -= val(other);
      der(self) -= der(other);
      return self;
    }

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::sub_
                                                , like<valder> auto const & z1
                                                , like<valder> auto const & z2
                                                ) noexcept
    {
      return z1 -= z2;
    }

    template<like<valder> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::sub_
                                                , Z const & self
                                                , O const & other
                                                ) noexcept
    {
      auto [a, b] = self;
      return Z{ a-other, b};
    }

    template<like<valder> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::sub_
                                                , O const & a0
                                                , Z const & a1
                                                ) noexcept
    {
      auto [a, b] = a1;
      return Z{ a0-a, -b};
    }

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::add_
                                                , like<valder> auto const & z1
                                                , like<valder> auto const & z2
                                                ) noexcept
    {
      return z1 += z2;
    }

    template<like<valder> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::add_
                                                , Z const & self
                                                , O const &  other
                                                ) noexcept
    {
      auto [a, b] = self;
      return Z{ a+other, b};
    }

    template<like<valder> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::add_
                                                , O const & a0
                                                , Z const & a1
                                                ) noexcept
    {
      auto [a, b] = a1;
      return Z{ a+a0, b};
    }

    template<like<valder> Z> EVE_FORCEINLINE friend auto operator-(Z const & z) noexcept
    {
      return Z{-val(z), -der(z)};
    }

    template<like<valder> Z> EVE_FORCEINLINE friend auto operator+(Z const &z) noexcept
    {
      return z;
    }

    //==============================================================================================
    // multiplies
    //==============================================================================================
    EVE_FORCEINLINE friend auto& operator*= ( like<valder> auto  & self
                                            , like<valder> auto  const & other
                                            ) noexcept
    {
      using r_t = std::remove_reference_t<decltype(self)>;
      auto [v1, d1] = self;
      auto [v2, d2] = other;
      auto dr = sum_of_prod(v1, d2, v2, d1);
      auto vr = v1*v2;
      return self = r_t(vr, dr);
    }

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::mul_
                                                , like<valder> auto  z1
                                                , like<valder> auto const & z2
                                                ) noexcept
    {
      return z1 *= z2;
    }

    template<like<valder> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto& operator *= ( Z & self
                                             , O const & other
                                             ) noexcept
    {
      auto [a, b] = self;
      return self = Z{ a*other, b*other};
    }

    template<like<valder> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::mul_
                                                , Z const & a0
                                                , O const & a1
                                                ) noexcept
    {
      auto [a, b] = a0;
      return Z{ a*a1, b*a1};
    }

    template<like<valder> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::mul_
                                                , O const & a0
                                                , Z const & a1
                                                ) noexcept
    {
      auto [a, b] = a1;
      return Z{a*a0, b*a0};
    }

    template<like<valder> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto operator*( Z const & a0
                                         , O const & a1
                                         ) noexcept
    {
      return mul(a0, a1);
    }

    template<like<valder> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto  operator*( O const & a0
                                          , Z const & a1
                                          ) noexcept
    {
      return mul(a1, a0);
    }

    //==============================================================================================
    // divide
    //==============================================================================================

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto operator/= ( Z & self
                                           , like<valder> auto const& other
                                           ) noexcept
    {
      using r_t = std::remove_reference_t<decltype(self)>;
      auto [v1, d1] = self;
      auto [v2, d2] = other;
      auto dr = diff_of_prod(v2, d1, v1, d2)/sqr(v2);
      auto vr = v1/v2;
      return self = r_t(vr, dr);
    }

    template<like<valder> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::div_
                                                , Z const & a0
                                                , O const & a1
                                                ) noexcept
    {
      auto [a, b] = a0;
      return Z{a/a1, b/a1};
    }

    template<like<valder> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::div_
                                                , O const & a0
                                                , Z const & a1
                                                ) noexcept
    {
      auto [v1, d1] = a1;
      return Z{a0/v1, -a0*d1/sqr(v1)};
    }

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::div_
                                                , like<valder> auto a0
                                                , like<valder> auto const & a1
                                                ) noexcept
    {
      return a0 /= a1;
    }

    template<like<valder> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto operator/= ( Z & self
                                           , O const& other

                                           ) noexcept
    {
      auto [a, b] = self;
      return self = Z{ a/other, b/other};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::rec_, Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto inv = rec(v);
      return Z{inv, -sqr(inv)*d};
    }

    template<like<valder> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto operator/( Z const & a0
                                         , O const & a1
                                         ) noexcept
    {
      return div(a0, a1);
    }

    template<like<valder> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto  operator/( O const & a0
                                          , Z const & a1
                                          ) noexcept
    {
      return div(a0, a1);
    }

    //==============================================================================================
    // functions & constants
    //==============================================================================================
    template<typename Tag, like<valder> T>
    EVE_FORCEINLINE friend auto tagged_dispatch(Tag, as<T> const&) noexcept
    {
      return T{ detail::callable_object<Tag>{}(as<value_type>{}), -10.555};
    }

    template<typename Tag>
    EVE_FORCEINLINE friend auto tagged_dispatch(Tag, like<valder> auto const& v) noexcept
    requires( has_derivation_v<Tag> )
    {
      if constexpr(is_derivable_v<Tag>) return unary  ( detail::callable_object<Tag>{}, v);
      else                              return compute( detail::callable_object<Tag>{}, v);
    }

    template<typename Tag>
    EVE_FORCEINLINE friend auto tagged_dispatch (Tag, maybe<valder> auto const&... v) noexcept
    requires( has_derivation_v<Tag> )
    {
      if constexpr(is_derivable_v<Tag>) return n_ary  ( detail::callable_object<Tag>{}, v...);
      else                              return compute( detail::callable_object<Tag>{}, v...);
    }

    // lpnorm
    // max familly
    // min familly

    // specials cases
    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::exponent_, Z const& z) noexcept
    {
      return exponent(val(z));
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::mantissa_, Z const& z) noexcept
    {
      return Z{mantissa(val(z)), der(z)};
    }

    //==============================================================================================/////////////////////////
    //==  optimizations
    //==============================================================================================/////////////////////////
    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::cbrt_, Z const& z) noexcept
    {
      auto [v, d] = z;
      auto cb = cbrt(v);
      return Z{cb, rec(3*sqr(cb))*d};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::cos_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto [s, c]= sincos(v);
      return Z{c, -d*s};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::cosh_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto [s, c]= sinhcosh(v);
      return Z{c, d*s};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sqrt_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto sqrtv = sqrt(v);
      return Z{sqrtv, -d/(2*sqrtv)};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::exp_, Z const& z ) noexcept
    {
       auto [v, d] = z;
       auto e = exp(v);
      return Z{e, e*d};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::expm1_, Z const& z ) noexcept
    {
       auto [v, d] = z;
       auto e = expm1(v);
       return Z{e, inc(e)*d};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::exp2_, Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto e = exp2(v);
      return Z{e, e*log_2(as(v))*d};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::exp10_, Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto e = exp10(v);
      return Z{e, e*log_10(as(v))*d};
    }

    //==============================================================================================
    //  Binary functions
    //==============================================================================================

    template<like<valder> Z1, like<valder> Z2>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::atan2_
                                                , Z1 const & z1
                                                , Z2 const & z2
                                                ) noexcept
    {
      using v_t = decltype(f(val(z1), val(z2)));
      using r_t = eve::as_valder_t<v_t>;
      auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
      auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
      auto  invden = rec(sum_of_prod(v1, v1, v2, v2));
      return r_t{atan2(v1, v2), invden*sum_of_prod(v1, d2, v2, d1)};
    }

    template<like<valder> Z1, like<valder> Z2>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::atan2d_
                                                , Z1 const & z1
                                                , Z2 const & z2
                                                ) noexcept
    {
      using v_t = decltype(f(val(z1), val(z2)));
      using r_t = eve::as_valder_t<v_t>;
      auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
      auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
      auto  invden = rec(sum_of_prod(v1, v1, v2, v2));
      return r_t{atan2d(v1, v2), radindeg(invden*sum_of_prod(v1, d2, v2, d1))};
    }

    template<like<valder> Z1, like<valder> Z2>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::atan2pi_
                                                , Z1 const & z1
                                                , Z2 const & z2
                                                ) noexcept
    {
      using v_t = decltype(f(val(z1), val(z2)));
      using r_t = eve::as_valder_t<v_t>;
      auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
      auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
      auto  invden = rec(sum_of_prod(v1, v1, v2, v2));
      return r_t{atan2pi(v1, v2), radinpi(invden*sum_of_prod(v1, d2, v2, d1))};
    }

      template < typename T >
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::ulpdist_
                                                , maybe<valder> auto const& z1
                                                , maybe<valder> auto const& z2
                                                ) noexcept
    {
      return eve::max( eve::ulpdist(val(z1), val(z2))
                     , eve::ulpdist(der(z1), der(z2)));
    }

    template<like<valder> Z1, like<valder> Z2>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::pow_
                                                 , Z1 const & z1
                                                 , Z2 const & z2
                                                 ) noexcept
    {
      using v_t = decltype(f(val(z1), val(z2)));
      using r_t = eve::as_valder_t<v_t>;
      auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
      auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
      auto  puv = pow(v1, v2);
      return r_t{puv, puv*sum_of_prod(v2/v1, d1, log(v1), d2)};
    }

    template<like<valder> Z, floating_real_value T>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::pow_
                                                , Z const & z1
                                                , T const & z2
                                                ) noexcept
    {
      using v_t = decltype(f(val(z1), val(z2)));
      using r_t = eve::as_valder_t<v_t>;
      auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
      auto  p = pow(v1, z2);
      return r_t{p, p*(z2/v1)*d1};
    }


    template<like<valder> Z, floating_real_value T>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::pow_
                                                , T const & z1
                                                , Z const & z2
                                                ) noexcept
    {
      using v_t = decltype(f(val(z1), val(z2)));
      using r_t = eve::as_valder_t<v_t>;
      auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
      auto p = pow(z1, v2);
      return r_t{p, log(z1)*p*d2};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::cosd_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto [s, c]= sincos(v);
      return Z{c, -d*s*deginrad(as(v))};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::cospi_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto [s, c]= sincos(v);
      return Z{c, -d*s*pi(as(v))};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::csc_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto cs = csc(v);
      return Z{cs, -d*cs*cot(v)};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::cscd_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto cs = cscd(v);
      return Z{cs, -d*cs*cot(v)*deginrad(as(v))};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::csch_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto cs = csch(v);
      return Z{cs, -d*cs*coth(v)*deginrad(as(v))};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::cscpi_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto cs = cscpi(v);
      return Z{cs, -d*cs*coth(v)*pi(as(v))};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::rsqrt_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto rs = rsqrt(v);
      return Z{rs, d*mhalf(as(v))*rs*rec(v)};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sec_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto se = sec(v);
      return Z{se, d*se*tan(v)};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::secd_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto se = secd(v);
      return Z{se, d*se*tan(v)*deginrad(as(v))};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sech_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto se = sech(v);
      return Z{se, -d*se*tanh(v)*deginrad(as(v))};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::secpi_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto se = secpi(v);
      return Z{se, d*se*tanh(v)*pi(as(v))};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sin_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto [s, c]= sincos(v);
      return Z{s, -d*c};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sincos_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto [s, c]= sincos(v);
      return kumi::tuple{Z{s, -d*c}, Z{c, -d*s}};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sinpicospi_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto [s, c]= sinpicospi(v);
      auto fac = pi(as(v));
      return kumi::tuple{Z{s, -d*c*fac}, Z{c, -d*s*fac}};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sinpi_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto [s, c]= sinpicospi(v);
      return Z{s, -d*c*pi(as(v))};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sindcosd_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto [s, c]= sindcosd(v);
      auto fac = deginrad(as(v));
      return kumi::tuple{Z{s, -d*c*fac}, Z{c, -d*s*fac}};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sind_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto [s, c]= sindcosd(v);
      return Z{s, -d*c*deginrad(as(v))};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sinhcosh_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto [s, c]= sinhcosh(v);
      return kumi::tuple{Z{s, d*c}, Z{c, d*s}};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sinh_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto [s, c]= sinhcosh(v);
      return Z{s, -d*c};
    }

   template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::tan_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto t = tan(v);
      return Z{t, -d*inc(sqr(t))};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::tanpi_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto t = tanpi(v);
      return Z{t, -d*inc(sqr(t))*pi(as(v))};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::tand_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto t = tand(v);
      return Z{t, -d*inc(sqr(t))*deginrad(as(v))};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::tanh_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto t = tanh(v);
      return Z{t, dec(sqr(t))*d};
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::modf_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto [f, t] = modf(v);
      return kumi::tuple{Z{f, d}, Z{t}};
    }

 };

  //================================================================================================
  //! @}
  //================================================================================================
}
