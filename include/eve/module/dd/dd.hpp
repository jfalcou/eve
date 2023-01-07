//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/vectorizable.hpp>
#include <eve/detail/abi.hpp>
#include <eve/product_type.hpp>
#include <eve/detail/abi.hpp>
#include <ostream>
#include <eve/module/complex/regular/ddlo.hpp>
#include <eve/module/complex/regular/ddhi.hpp>

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

    /// Base value type
    using value_type = Type;

    /// Base value type
    using underlying_type = underlying_type_t<Type>;

    /// Default constructor
              dd()               noexcept : parent{0,0} {}
    explicit  dd(Type r        ) noexcept : parent{r,0} {}
              dd(Type r, Type i) noexcept : parent{r,i} {}

    /// Stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, like<dd> auto const& r)
    {
      os << hi(r);
      auto l = lo(r);
      if(is_positive(i)) os << '+' << l; else os << '-' << -l;
    }

    //==============================================================================================
    // Operators
    //==============================================================================================
    // -----  Operator +
    EVE_FORCEINLINE friend auto operator+(like<dd> auto const& z) noexcept { return z; }

    template<like<dd> Z1, like<dd> Z2>
    EVE_FORCEINLINE friend auto& operator+=(Z1& self, Z2 const& o) noexcept
    {
      if constexpr(is_dd_v<Z2>) {
        auto [s1, s2] = two_add(ddlo(self), ddlo(o));
        x[0] = qd::two_sum(x[0], b.x[0], s2);
        if ( QD_ISFINITE( x[0] ) )
        {
          double t2, t1 = qd::two_sum( x[1], b.x[1], t2 );
          x[1] = qd::two_sum(s2, t1, t1);
          t1 += t2;
          qd::three_sum(x[0], x[1], t1);
        }
        else
        {
          x[1] = 0.0;
        }
      }
      else
      {
        if constexpr(same_as<float, underlying_type_t<Z2>>) 
      }
        return self;

    real(self) += real(o);
      if constexpr(is_dd_v<Z2>) imag(self) += imag(o);
      return self;
    }

    EVE_FORCEINLINE friend auto& operator+=(like<dd> auto& self, callable_i_ const&) noexcept
    {
      imag(self)++;
      return self;
    }

//     //==============================================================================================
//     // predicates
//     //==============================================================================================

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_equal_
//                                                , R const& r1
//                                                , R const& r2) noexcept
//     {
//       auto [r1r, r1i] = r1;
//       auto [r2r, r2i] = r2;
//       return is_equal(r1r, r2r) && is_equal(r1i, r2i);
//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_equal_
//                                                , numeric_type const &
//                                                , R const& r1
//                                                , R const& r2) noexcept
//     {
//       auto [r1r, r1i] = r1;
//       auto [r2r, r2i] = r2;
//       return numeric(is_equal)(r1r, r2r) && numeric(is_equal)(r1i, r2i);
//     }

//    template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_infinitesimal_, R const& r ) noexcept
//     {
//       return is_eqr(real(r));
//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_infinitesimal_, almost_type const &, R const& r ) noexcept
//     {
//       auto [rr, ir] = r;
//       return abs(rr) <= abs(r)*eps(as(rr));
//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_real_, R const& r ) noexcept
//     {
//       return is_eqr(null2(r));
//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_finite_, R const& r ) noexcept
//     {
//       return is_finite(null2(r)) && is_finite(real(r));
//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_eqr_, R const& r ) noexcept
//     {
//       return is_eqr(null2(r)) && is_eqr(real(r));
//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_ner_, R const& r ) noexcept
//     {
//       return is_ner(null2(r)) || is_ner(real(r));
//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_not_finite_, R const& r ) noexcept
//     {
//       return is_not_finite(null2(r)) || is_not_finite(real(r));
//     }

//      template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_infinite_, R const& r ) noexcept
//     {
//       return is_infinite(null2(r)) || is_infinite(real(r));
//     }

//    template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_nan_, R const& r ) noexcept
//     {
//       auto [rr, ir] = r;
//       return is_unordered(rr, ir);
//     }

//     //==============================================================================================
//     //  Operators
//     //==============================================================================================
//     ////////////////////////////////////////////////////////////////////////////////////////////////
//     // add/sub
//     ////////////////////////////////////////////////////////////////////////////////////////////////

//     EVE_FORCEINLINE friend auto& operator+= ( like<dd> auto& self
//                                             , like<dd> auto const& other
//                                             ) noexcept
//     {
//       real(self) += real(other);
//       null2(self) += null2(other);
//       return self;
//     }

//     EVE_FORCEINLINE friend auto& operator-= ( like<dd> auto& self
//                                             , like<dd> auto const& other
//                                             ) noexcept
//     {
//       real(self) -= real(other);
//       null2(self) -= null2(other);
//       return self;
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::sub_
//                                                 , like<dd> auto const & r1
//                                                 , like<dd> auto const & r2
//                                                 ) noexcept
//     {
//       return r1 -= r2;
//     }

//     template<like<dd> R, floating_real_value O>
//     EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::sub_
//                                                 , R const & self
//                                                 , O const & other
//                                                 ) noexcept
//     {
//       auto [a, b] = self;
//       return R{ a-other, b};
//     }

//     template<like<dd> R, floating_real_value O>
//     EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::sub_
//                                                 , O const & a0
//                                                 , R const & a1
//                                                 ) noexcept
//     {
//       auto [a, b] = a1;
//       return R{ a0-a, -b};
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::add_
//                                                 , like<dd> auto const & r1
//                                                 , like<dd> auto const & r2
//                                                 ) noexcept
//     {
//       return r1 += r2;
//     }

//     template<like<dd> R, floating_real_value O>
//     EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::add_
//                                                 , R const & self
//                                                 , O const &  other
//                                                 ) noexcept
//     {
//       auto [a, b] = self;
//       return R{ a+other, b};
//     }

//     template<like<dd> R, floating_real_value O>
//     EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::add_
//                                                 , O const & a0
//                                                 , R const & a1
//                                                 ) noexcept
//     {
//       auto [a, b] = a1;
//       return R{ a+a0, b};
//     }

//     template<like<dd> R> EVE_FORCEINLINE friend auto operator-(R const & r) noexcept
//     {
//       return R{-real(r), -null2(r)};
//     }

//     template<like<dd> R> EVE_FORCEINLINE friend auto operator+(R const &r) noexcept
//     {
//       return r;
//     }

//     ////////////////////////////////////////////////////////////////////////////////////////////////
//     // multiplies
//     ////////////////////////////////////////////////////////////////////////////////////////////////


//   EVE_FORCEINLINE friend auto& operator*= ( like<dd> auto  & self
//                                           , like<dd> auto  const & other
//                                           ) noexcept
//     {
//       using r_t = std::remove_reference_t<decltype(self)>;
//       auto [a, b] = self;
//       auto [c, d] = other;
//       auto ri = sum_of_prod(a, d, b, c);
//       return self = r_t(a*c, ri);
//     }

//     EVE_FORCEINLINE friend auto& operator*= ( like<dd> auto & self
//                                             , callable_ep_ const &
//                                             ) noexcept
//     {
//       auto [a, b] = self;
//       return self = {rero(as(a)), a};
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::mul_
//                                                 , like<dd> auto  r1
//                                                 , like<dd> auto const & r2
//                                                 ) noexcept
//     {
//       return r1 *= r2;
//     }

//    template < like<dd> R>
//    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::mul_
//                                                , raw_type const &
//                                                , R const & r1
//                                                , R const & r2
//                                                ) noexcept
//     {
//       auto [a, b] = r1;
//       auto [c, d] = r2;
//       return  R{a*c, sum_of_prod(a, d, b, c)};
//     }

//     template < like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::mul_
//                                                 , R const & r
//                                                 , callable_ep_ const &
//                                                 ) noexcept
//     {
//       return R{rero(as(real(r))), real(r)};
//     }

//     template < like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::mul_
//                                                 , callable_ep_ const &
//                                                 , R const & r
//                                                 ) noexcept
//     {
//       return R{rero(as(real(r))),real(r)};
//     }

//     template<like<dd> R, floating_real_value O>
//     EVE_FORCEINLINE friend auto& operator *= ( R & self
//                                              , O const & other
//                                              ) noexcept
//     {
//       auto [a, b] = self;
//       return self = R{ a*other, b*other};
//     }

//     template<like<dd> R, floating_real_value O>
//     EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::mul_
//                                                 , R const & a0
//                                                 , O const & a1
//                                                 ) noexcept
//     {
//       auto [a, b] = a0;
//       return R{ a*a1, b*a1};
//     }

//     template<like<dd> R, floating_real_value O>
//     EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::mul_
//                                                 , O const & a0
//                                                 , R const & a1
//                                                 ) noexcept
//     {
//       auto [a, b] = a1;
//       return R{a*a0, b*a0};
//     }

//     template<like<dd> R, floating_real_value O>
//     EVE_FORCEINLINE friend auto operator*( R const & a0
//                                          , O const & a1
//                                          ) noexcept
//     {
//       return mul(a0, a1);
//     }

//     template<like<dd> R, floating_real_value O>
//     EVE_FORCEINLINE friend auto  operator*( O const & a0
//                                           , R const & a1
//                                           ) noexcept
//     {
//       return mul(a1, a0);
//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto operator*( R const & r
//                                          , callable_ep_ const &
//                                          ) noexcept
//     {
//       return R{rero(as(real(r))), real(r)};
//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto  operator*( callable_ep_ const &
//                                           , R const & r
//                                           ) noexcept
//     {
//       return R{rero(as(real(r))), real(r)};
//     }

//     ////////////////////////////////////////////////////////////////////////////////////////////////
//     // divide
//     ////////////////////////////////////////////////////////////////////////////////////////////////

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto operator/= ( R & self
//                                            , like<dd> auto const& other
//                                            ) noexcept
//     {
//       auto [a, b] = self;
//       auto [c, d] = other;
//       auto r =  R{a/c, diff_of_prod(b, c, a, d)/sqr(c)};
//     }

//     template<like<dd> R, floating_real_value O>
//     EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::div_
//                                                 , R const & a0
//                                                 , O const & a1
//                                                 ) noexcept
//     {
//       auto [a, b] = a0;
//       return R{a/a1, b/a1};
//     }

//     template<like<dd> R, floating_real_value O>
//     EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::div_
//                                                 , O const & a0
//                                                 , R const & a1
//                                                 ) noexcept
//     {
//       return mul(rec(a1), a0);
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::div_
//                                                 , like<dd> auto a0
//                                                 , like<dd> auto const & a1
//                                                 ) noexcept
//     {

//       return a0 /= a1;
//     }

//     template<like<dd> R, floating_real_value O>
//     EVE_FORCEINLINE friend auto operator/= ( R & self
//                                            , O const& other
//                                            ) noexcept
//     {
//       auto [a, b] = self;
//       return self = R{ a/other, b/other};
//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::rec_, R const& r ) noexcept
//     {
//       auto [a, b] = r;
//       auto c = rec(a);
//       return R{c, -b*sqr(c)};
//     }

//     template<like<dd> R, floating_real_value O>
//     EVE_FORCEINLINE friend auto operator/( R const & a0
//                                          , O const & a1
//                                          ) noexcept
//     {
//       return div(a0, a1);
//     }

//     template<like<dd> R, floating_real_value O>
//     EVE_FORCEINLINE friend auto  operator/( O const & a0
//                                           , R const & a1
//                                           ) noexcept
//     {
//       return div(a0, a1);
//     }

//     //==============================================================================================
//     //  Unary functions
//     //==============================================================================================
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::abs_
//                                                 , like<dd> auto const& r
//                                                 ) noexcept
//     {
//       auto rr = real(r);
//       return R{abs(rr), sign(rr)};
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::sqr_abs_
//                                                 , like<dd> auto const& r
//                                                 ) noexcept
//     {
//       auto rr = real(r);
//       return R{sqr(rr), 2*rr};

//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::sqr_
//                                                 , R const& r
//                                                 ) noexcept
//     {
//       auto rr = real(r);
//       return R{sqr(rr), 2*rr};
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::arg_
//                                                 , like<dd> auto const& r
//                                                 ) noexcept
//     {
//       auto [a, b] = self;
//       return b/abs(a);
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::conj_
//                                                 , like<dd> auto const& r
//                                                 ) noexcept
//     {
//       auto [a, b] = self;
//       return self = {a, -b};
//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::mul_ep_, R const& r ) noexcept
//     {
//       auto r = real(self);
//       return self = {rero(as(r)), r};
//     }


//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::mul_mep_, R const& r ) noexcept
//     {
//       auto r = real(self);
//       return self = {rero(as(r)), -r};
//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sqrt_
//                                                , R const& r ) noexcept
//     {
//       auto [a, b] = self;
//       return self = {sqrt(a), b*rsqrt(a)/2};
//     }


//     //==============================================================================================
//     // trigo
//     //==============================================================================================
//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::cosh_, R const& r ) noexcept
//     {
//       auto [a, b] = r;
//       auto [s, c] = sinhcosh(a);
//       return R(c, s*b);
//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::cos_, R const& r ) noexcept
//     {
//       auto [a, b] = r;
//       auto [s, c] = sincos(a);
//       return R(c, -s*b);
//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sinh_, R const& r ) noexcept
//     {
//       auto [a, b] = r;
//       auto [s, c] = sinhcosh(a);
//       return R(s, c*b);
//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sin_, R const& r ) noexcept
//     {
//       auto [a, b] = r;
//       auto [s, c] = sincos(a);
//       return R(s, c*b);
//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::tan_, R const& r ) noexcept
//     {
//       auto [a, b] = r;
//       auto t = tan(a);
//       return R(t, fma(t, t, one(as(t))*b);
//     }


//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::tanpi_
//                                                , R const& r ) noexcept
//     {
//       auto [v, d] = r;
//       auto t = tanpi(v);
//       return R{t, d*inc(sqr(t))*pi(as(v))};
//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::tand_
//                                                , R const& r ) noexcept
//     {
//       auto [v, d] = r;
//       auto t = tand(v);
//       return R{t, deginrad(d)*inc(sqr(t))};
//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::tanh_, R const& r ) noexcept
//     {
//       auto [a, b] = r;
//       auto t = tanh(a);
//       return R(t, fnma(t, t, one(as(t))*b);
//     }

//     //==============================================================================================
//     //  exponential
//     //==============================================================================================
//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::exp_, R const& r ) noexcept
//     {
//        auto [v, d] = r;
//        auto e = exp(v);
//       return R{e, e*d};
//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::exp2_, R const& r ) noexcept
//     {
//       auto [v, d] = r;
//       auto e = exp2(v);
//       return R{e, e*log_2(as(v))*d};
//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::exp10_, R const& r ) noexcept
//     {
//       auto [v, d] = r;
//       auto e = exp10(v);
//       return R{e, e*log_10(as(v))*d};
//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::log_, R const& r ) noexcept
//     {
//       auto [v, d] = r;
//       auto l = log(v);
//       return R{l, d*if_else(v >= 0, rec(v), allbits)};

//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::log2_, R const& r ) noexcept
//     {
//       auto [v, d] = r;
//       auto l = log2(v);
//       return R{l, d*if_else(v >= 0, rec(v)*invlog_2(as(v)), allbits)};
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::log10_, R const& r ) noexcept
//     {
//       auto [v, d] = r;
//       auto l = log10(v);
//       return R{l, d*if_else(v >= 0, rec(v)*invlog_10(as(v)), allbits)};
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::log_abs_, R const& r ) noexcept
//     {
//       auto [v, d] = r;
//       auto l = log_abs(v);
//       return R{l, d*rec(v)};
//     }

//     //==============================================================================================
//     //  Binary functions
//     //==============================================================================================
//     EVE_FORCEINLINE friend auto operator == ( like<dd> auto const & a
//                                             , like<dd> auto const & b
//                                             ) noexcept
//     {
//       return (real(a) == real(b)) &&  (null2(a) == null2(b));
//     }

//     EVE_FORCEINLINE friend auto operator != ( like<dd> auto const & a
//                                             , like<dd> auto const & b
//                                             ) noexcept
//     {
//       return (real(a) != real(b)) || (null2(a) != null2(b));
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::ulpdist_
//                                                 , like<dd> auto const& r1
//                                                 , like<dd> auto const& r2
//                                                 ) noexcept
//     {
//       return eve::max( eve::ulpdist(real(r1), real(r2))
//                      , eve::ulpdist(null2(r1), null2(r2)));
//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::ldexp_
//                                                 , R const& r1
//                                                 , integral_value auto n
//                                                 ) noexcept
//     {
//       return R{ldexp(real(r), n), ldexp(one(as(real(r))), n)*null2(r)};
//     }

//     template<like<dd> R>
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::pow_
//                                                  , R const & a
//                                                  , R const & b
//                                                  ) noexcept
//     {
//       auto [u, v] = b;
//       auto labsa = log_abs(a);
//       auto arga = arg(a);
//       auto rr = exp(diff_of_prod(u, labsa, v, arga));
//       auto ir = exp_i(sum_of_prod(u, arga, v, labsa));
//       return if_else(is_eqr(a)&&is_eqr(b), one, mul(ir, rr));
//     }

//     template<like<dd> R, floating_real_value T>
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::pow_
//                                                 , R const & a0
//                                                 , T const & a1
//                                                 ) noexcept
//     {
//       auto t = arg(a0);
//       auto a = abs(a0);
//       return if_else(is_eqr(a)&&is_eqr(a1), one, eve::pow(a, a1)*exp_i(t*a1));
//     }

//     template<like<dd> R, floating_real_value T>
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::pow_
//                                                 , T const & a0
//                                                 , R const & a1
//                                                 ) noexcept
//     {
//       return if_else(is_eqr(a0)&&is_eqr(a1), one, exp(a1*cmplx(log)(a0)));
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::dist_
//                                                 , like<dd> auto  const & r1
//                                                 , like<dd> auto  const & r2
//                                                 ) noexcept
//     {
//       return abs(r1-r2);
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::acosh_
//                                                 , like<dd> auto  const & r
//                                                 ) noexcept
//     {
//       // acosh(a0) = +/-i acos(a0)
//       // Choosing the sign of multiplier to give nt2::real(acosh(a0)) >= 0
//       // we have compatibility with C99.
//       auto res = eve::acos(r);
//       return if_else(is_ler(null2(res)),  mul_i(res), mul_mi(res));
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::acos_
//                                                 , like<dd> auto  const & r
//                                                 ) noexcept
//     {
//       return eve::detail::internal_acos(r);
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::asinh_
//                                                 , like<dd> auto  const & r
//                                                 ) noexcept
//     {
//       // We use asinh(r) = i asin(-i r);
//       // Note that C99 defines this the other way around (which is
//       // to say asin is specified in terms of asinh), this is consistent
//       // with C99 though:
//       return  mul_i(asin(mul_mi(r)));
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::asin_
//                                                 , like<dd> auto  const & r
//                                                 ) noexcept
//     {
//       return eve::detail::internal_asin(r);
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::atan_
//                                                 , like<dd> auto  const & r
//                                                 ) noexcept
//     {
//       // C99 definition here; atan(r) = -i atanh(ir):
//       return mul_mi(eve::atanh(mul_i(r)));
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::atanh_
//                                                 , like<dd> auto  const & r
//                                                 ) noexcept
//     {
//       return eve::detail::internal_atanh(r);
//     }

 };

  //================================================================================================
  //! @}
  //================================================================================================
}
