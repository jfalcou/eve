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
#include <eve/module/dd/regular/dd.hpp>
#include <eve/product_type.hpp>
#include <eve/detail/abi.hpp>
#include <dd>
#include <iostream>
#include <iomanip>

namespace eve
{
  //================================================================================================
  //! @addtogroup simd_types
  //! @{
  //================================================================================================
  //! @brief SIMD-compatible representation of double_double numbers
  //!
  //! **Required header:** `#include <eve/module/dd.hpp>`
  //!
  //! eve::dd is structure representing dd number and mean to be used in conjunction with
  //! eve::wide.
  //!
  //! @tparam Type  Underlying floating point type
  //================================================================================================
  template<floating_scalar_value Type>
  struct dd : struct_support<dd<Type>, Type, Type>
  {
    using eve_disable_ordering = void;
    using parent = struct_support<dd<Type>, Type, Type>;

    /// Underlying type
    using value_type = Type;

    /// Default constructor
    EVE_FORCEINLINE dd(Type r = 0, Type i = 0)  noexcept : parent{r,i} {}

    //==============================================================================================
    friend std::ostream& operator<<(std::ostream& os, like<dd> auto const& z)
    {
      return os << std::setprecision(20) << real(z) << std::showpos << null2(z) << "i" << std::noshowpos;
    }

    //==============================================================================================
    //  Real/Null2 parts as functions
    //==============================================================================================

    /// Retrieve the real part of the current dd number
    EVE_FORCEINLINE friend
    decltype(auto) tagged_dispatch( eve::tag::real_, like<dd> auto&& z )
    {
      return get<0>(EVE_FWD(z));
    }

    /// Retrieve the null2inary part of the current dd number
    EVE_FORCEINLINE friend
    decltype(auto) tagged_dispatch( eve::tag::null2_, like<dd> auto&& z )
    {
      return get<1>(EVE_FWD(z));
    }

    //==============================================================================================
    // predicates
    //==============================================================================================

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_equal_
                                               , Z const& z1
                                               , Z const& z2) noexcept
    {
      auto [z1r, z1i] = z1;
      auto [z2r, z2i] = z2;
      return is_equal(z1r, z2r) && is_equal(z1i, z2i);
    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_equal_
                                               , numeric_type const &
                                               , Z const& z1
                                               , Z const& z2) noexcept
    {
      auto [z1r, z1i] = z1;
      auto [z2r, z2i] = z2;
      return numeric(is_equal)(z1r, z2r) && numeric(is_equal)(z1i, z2i);
    }

   template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_infinitesimal_, Z const& z ) noexcept
    {
      return is_eqz(real(z));
    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_infinitesimal_, almost_type const &, Z const& z ) noexcept
    {
      auto [rz, iz] = z;
      return abs(rz) <= abs(z)*eps(as(rz));
    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_real_, Z const& z ) noexcept
    {
      return is_eqz(null2(z));
    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_finite_, Z const& z ) noexcept
    {
      return is_finite(null2(z)) && is_finite(real(z));
    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_eqz_, Z const& z ) noexcept
    {
      return is_eqz(null2(z)) && is_eqz(real(z));
    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_nez_, Z const& z ) noexcept
    {
      return is_nez(null2(z)) || is_nez(real(z));
    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_not_finite_, Z const& z ) noexcept
    {
      return is_not_finite(null2(z)) || is_not_finite(real(z));
    }

     template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_infinite_, Z const& z ) noexcept
    {
      return is_infinite(null2(z)) || is_infinite(real(z));
    }

   template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_nan_, Z const& z ) noexcept
    {
      auto [rz, iz] = z;
      return is_unordered(rz, iz);
    }

    //==============================================================================================
    //  Operators
    //==============================================================================================
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // add/sub
    ////////////////////////////////////////////////////////////////////////////////////////////////

    EVE_FORCEINLINE friend auto& operator+= ( like<dd> auto& self
                                            , like<dd> auto const& other
                                            ) noexcept
    {
      real(self) += real(other);
      null2(self) += null2(other);
      return self;
    }

    EVE_FORCEINLINE friend auto& operator-= ( like<dd> auto& self
                                            , like<dd> auto const& other
                                            ) noexcept
    {
      real(self) -= real(other);
      null2(self) -= null2(other);
      return self;
    }

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::sub_
                                                , like<dd> auto const & z1
                                                , like<dd> auto const & z2
                                                ) noexcept
    {
      return z1 -= z2;
    }

    template<like<dd> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::sub_
                                                , Z const & self
                                                , O const & other
                                                ) noexcept
    {
      auto [a, b] = self;
      return Z{ a-other, b};
    }

    template<like<dd> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::sub_
                                                , O const & a0
                                                , Z const & a1
                                                ) noexcept
    {
      auto [a, b] = a1;
      return Z{ a0-a, -b};
    }

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::add_
                                                , like<dd> auto const & z1
                                                , like<dd> auto const & z2
                                                ) noexcept
    {
      return z1 += z2;
    }

    template<like<dd> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::add_
                                                , Z const & self
                                                , O const &  other
                                                ) noexcept
    {
      auto [a, b] = self;
      return Z{ a+other, b};
    }

    template<like<dd> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::add_
                                                , O const & a0
                                                , Z const & a1
                                                ) noexcept
    {
      auto [a, b] = a1;
      return Z{ a+a0, b};
    }

    template<like<dd> Z> EVE_FORCEINLINE friend auto operator-(Z const & z) noexcept
    {
      return Z{-real(z), -null2(z)};
    }

    template<like<dd> Z> EVE_FORCEINLINE friend auto operator+(Z const &z) noexcept
    {
      return z;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // multiplies
    ////////////////////////////////////////////////////////////////////////////////////////////////


  EVE_FORCEINLINE friend auto& operator*= ( like<dd> auto  & self
                                          , like<dd> auto  const & other
                                          ) noexcept
    {
      using r_t = std::remove_reference_t<decltype(self)>;
      auto [a, b] = self;
      auto [c, d] = other;
      auto ri = sum_of_prod(a, d, b, c);
      return self = r_t(a*c, ri);
    }

    EVE_FORCEINLINE friend auto& operator*= ( like<dd> auto & self
                                            , callable_ep_ const &
                                            ) noexcept
    {
      auto [a, b] = self;
      return self = {zero(as(a)), a};
    }

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::mul_
                                                , like<dd> auto  z1
                                                , like<dd> auto const & z2
                                                ) noexcept
    {
      return z1 *= z2;
    }

   template < like<dd> Z>
   EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::mul_
                                               , raw_type const &
                                               , Z const & z1
                                               , Z const & z2
                                               ) noexcept
    {
      auto [a, b] = z1;
      auto [c, d] = z2;
      return  Z{a*c, sum_of_prod(a, d, b, c)};
    }

    template < like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::mul_
                                                , Z const & z
                                                , callable_ep_ const &
                                                ) noexcept
    {
      return Z{zero(as(real(z))), real(z)};
    }

    template < like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::mul_
                                                , callable_ep_ const &
                                                , Z const & z
                                                ) noexcept
    {
      return Z{zero(as(real(z))),real(z)};
    }

    template<like<dd> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto& operator *= ( Z & self
                                             , O const & other
                                             ) noexcept
    {
      auto [a, b] = self;
      return self = Z{ a*other, b*other};
    }

    template<like<dd> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::mul_
                                                , Z const & a0
                                                , O const & a1
                                                ) noexcept
    {
      auto [a, b] = a0;
      return Z{ a*a1, b*a1};
    }

    template<like<dd> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::mul_
                                                , O const & a0
                                                , Z const & a1
                                                ) noexcept
    {
      auto [a, b] = a1;
      return Z{a*a0, b*a0};
    }

    template<like<dd> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto operator*( Z const & a0
                                         , O const & a1
                                         ) noexcept
    {
      return mul(a0, a1);
    }

    template<like<dd> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto  operator*( O const & a0
                                          , Z const & a1
                                          ) noexcept
    {
      return mul(a1, a0);
    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto operator*( Z const & z
                                         , callable_ep_ const &
                                         ) noexcept
    {
      return Z{zero(as(real(z))), real(z)};
    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto  operator*( callable_ep_ const &
                                          , Z const & z
                                          ) noexcept
    {
      return Z{zero(as(real(z))), real(z)};
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // divide
    ////////////////////////////////////////////////////////////////////////////////////////////////

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto operator/= ( Z & self
                                           , like<dd> auto const& other
                                           ) noexcept
    {
      auto [a, b] = self;
      auto [c, d] = other;
      auto r =  Z{a/c, diff_of_prod(b, c, a, d)/sqr(c)};
    }

    template<like<dd> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::div_
                                                , Z const & a0
                                                , O const & a1
                                                ) noexcept
    {
      auto [a, b] = a0;
      return Z{a/a1, b/a1};
    }

    template<like<dd> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::div_
                                                , O const & a0
                                                , Z const & a1
                                                ) noexcept
    {
      return mul(rec(a1), a0);
    }

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::div_
                                                , like<dd> auto a0
                                                , like<dd> auto const & a1
                                                ) noexcept
    {

      return a0 /= a1;
    }

    template<like<dd> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto operator/= ( Z & self
                                           , O const& other
                                           ) noexcept
    {
      auto [a, b] = self;
      return self = Z{ a/other, b/other};
    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::rec_, Z const& z ) noexcept
    {
      auto [a, b] = z;
      auto c = rec(a);
      return Z{c, -b*sqr(c)};
    }

    template<like<dd> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto operator/( Z const & a0
                                         , O const & a1
                                         ) noexcept
    {
      return div(a0, a1);
    }

    template<like<dd> Z, floating_real_value O>
    EVE_FORCEINLINE friend auto  operator/( O const & a0
                                          , Z const & a1
                                          ) noexcept
    {
      return div(a0, a1);
    }

    //==============================================================================================
    //  Unary functions
    //==============================================================================================
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::abs_
                                                , like<dd> auto const& z
                                                ) noexcept
    {
      auto rz = real(z);
      return Z{abs(rz), sign(rz)};
    }

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::sqr_abs_
                                                , like<dd> auto const& z
                                                ) noexcept
    {
      auto rz = real(z);
      return Z{sqr(rz), 2*rz};

    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::sqr_
                                                , Z const& z
                                                ) noexcept
    {
      auto rz = real(z);
      return Z{sqr(rz), 2*rz};
    }

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::arg_
                                                , like<dd> auto const& z
                                                ) noexcept
    {
      auto [a, b] = self;
      return b/abs(a);
    }

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::conj_
                                                , like<dd> auto const& z
                                                ) noexcept
    {
      auto [a, b] = self;
      return self = {a, -b};
    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::mul_ep_, Z const& z ) noexcept
    {
      auto r = real(self);
      return self = {zero(as(r)), r};
    }


    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::mul_mep_, Z const& z ) noexcept
    {
      auto r = real(self);
      return self = {zero(as(r)), -r};
    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sqrt_
                                               , Z const& z ) noexcept
    {
      auto [a, b] = self;
      return self = {sqrt(a), b*rsqrt(a)/2};
    }


    //==============================================================================================
    // trigo
    //==============================================================================================
    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::cosh_, Z const& z ) noexcept
    {
      auto [a, b] = z;
      auto [s, c] = sinhcosh(a);
      return Z(c, s*b);
    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::cos_, Z const& z ) noexcept
    {
      auto [a, b] = z;
      auto [s, c] = sincos(a);
      return Z(c, -s*b);
    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sinh_, Z const& z ) noexcept
    {
      auto [a, b] = z;
      auto [s, c] = sinhcosh(a);
      return Z(s, c*b);
    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sin_, Z const& z ) noexcept
    {
      auto [a, b] = z;
      auto [s, c] = sincos(a);
      return Z(s, c*b);
    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::tan_, Z const& z ) noexcept
    {
      auto [a, b] = z;
      auto t = tan(a);
      return Z(t, fma(t, t, one(as(t))*b);
    }


    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::tanpi_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto t = tanpi(v);
      return Z{t, d*inc(sqr(t))*pi(as(v))};
    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::tand_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto t = tand(v);
      return Z{t, deginrad(d)*inc(sqr(t))};
    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::tanh_, Z const& z ) noexcept
    {
      auto [a, b] = z;
      auto t = tanh(a);
      return Z(t, fnma(t, t, one(as(t))*b);
    }

    //==============================================================================================
    //  exponential
    //==============================================================================================
    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::exp_, Z const& z ) noexcept
    {
       auto [v, d] = z;
       auto e = exp(v);
      return Z{e, e*d};
    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::exp2_, Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto e = exp2(v);
      return Z{e, e*log_2(as(v))*d};
    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::exp10_, Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto e = exp10(v);
      return Z{e, e*log_10(as(v))*d};
    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::log_, Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto l = log(v);
      return Z{l, d*if_else(v >= 0, rec(v), allbits)};

    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::log2_, Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto l = log2(v);
      return Z{l, d*if_else(v >= 0, rec(v)*invlog_2(as(v)), allbits)};
    }

    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::log10_, Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto l = log10(v);
      return Z{l, d*if_else(v >= 0, rec(v)*invlog_10(as(v)), allbits)};
    }

    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::log_abs_, Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto l = log_abs(v);
      return Z{l, d*rec(v)};
    }

    //==============================================================================================
    //  Binary functions
    //==============================================================================================
    EVE_FORCEINLINE friend auto operator == ( like<dd> auto const & a
                                            , like<dd> auto const & b
                                            ) noexcept
    {
      return (real(a) == real(b)) &&  (null2(a) == null2(b));
    }

    EVE_FORCEINLINE friend auto operator != ( like<dd> auto const & a
                                            , like<dd> auto const & b
                                            ) noexcept
    {
      return (real(a) != real(b)) || (null2(a) != null2(b));
    }

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::ulpdist_
                                                , like<dd> auto const& z1
                                                , like<dd> auto const& z2
                                                ) noexcept
    {
      return eve::max( eve::ulpdist(real(z1), real(z2))
                     , eve::ulpdist(null2(z1), null2(z2)));
    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::ldexp_
                                                , Z const& z1
                                                , integral_value auto n
                                                ) noexcept
    {
      return Z{ldexp(real(z), n), ldexp(one(as(real(z))), n)*null2(z)};
    }

    template<like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::pow_
                                                 , Z const & a
                                                 , Z const & b
                                                 ) noexcept
    {
      auto [u, v] = b;
      auto labsa = log_abs(a);
      auto arga = arg(a);
      auto rz = exp(diff_of_prod(u, labsa, v, arga));
      auto iz = exp_i(sum_of_prod(u, arga, v, labsa));
      return if_else(is_eqz(a)&&is_eqz(b), one, mul(iz, rz));
    }

    template<like<dd> Z, floating_real_value T>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::pow_
                                                , Z const & a0
                                                , T const & a1
                                                ) noexcept
    {
      auto t = arg(a0);
      auto a = abs(a0);
      return if_else(is_eqz(a)&&is_eqz(a1), one, eve::pow(a, a1)*exp_i(t*a1));
    }

    template<like<dd> Z, floating_real_value T>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::pow_
                                                , T const & a0
                                                , Z const & a1
                                                ) noexcept
    {
      return if_else(is_eqz(a0)&&is_eqz(a1), one, exp(a1*cmplx(log)(a0)));
    }

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::dist_
                                                , like<dd> auto  const & z1
                                                , like<dd> auto  const & z2
                                                ) noexcept
    {
      return abs(z1-z2);
    }

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::acosh_
                                                , like<dd> auto  const & z
                                                ) noexcept
    {
      // acosh(a0) = +/-i acos(a0)
      // Choosing the sign of multiplier to give nt2::real(acosh(a0)) >= 0
      // we have compatibility with C99.
      auto res = eve::acos(z);
      return if_else(is_lez(null2(res)),  mul_i(res), mul_mi(res));
    }

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::acos_
                                                , like<dd> auto  const & z
                                                ) noexcept
    {
      return eve::detail::internal_acos(z);
    }

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::asinh_
                                                , like<dd> auto  const & z
                                                ) noexcept
    {
      // We use asinh(z) = i asin(-i z);
      // Note that C99 defines this the other way around (which is
      // to say asin is specified in terms of asinh), this is consistent
      // with C99 though:
      return  mul_i(asin(mul_mi(z)));
    }

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::asin_
                                                , like<dd> auto  const & z
                                                ) noexcept
    {
      return eve::detail::internal_asin(z);
    }

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::atan_
                                                , like<dd> auto  const & z
                                                ) noexcept
    {
      // C99 definition here; atan(z) = -i atanh(iz):
      return mul_mi(eve::atanh(mul_i(z)));
    }

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::atanh_
                                                , like<dd> auto  const & z
                                                ) noexcept
    {
      return eve::detail::internal_atanh(z);
    }

 };

  //================================================================================================
  //! @}
  //================================================================================================
}
