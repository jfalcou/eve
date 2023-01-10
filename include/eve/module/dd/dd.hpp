//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/abi.hpp>
#include <eve/traits/product_type.hpp>
#include <eve/module/dd/detail/predicates.hpp>
#include <eve/module/dd/detail/arithmetic.hpp>
#include <ostream>
#include <eve/module/dd/regular/ddlo.hpp>
#include <eve/module/dd/regular/ddhi.hpp>
#include <eve/module/dd/regular/traits.hpp>
#include <iostream>
#include <tts/tts.hpp>

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
  struct dd;

  template<typename Type>
  struct supports_ordering<dd<Type>> : std::true_type
  {};

  template<floating_scalar_value Type>
  struct dd : struct_support<dd<Type>, Type, Type>
  {
    using parent = struct_support<dd<Type>, Type, Type>;

    /// Base value type
    using value_type = Type;

    /// Base value type
    using underlying_type = underlying_type_t<Type>;

    /// Default constructor
              dd()               noexcept : parent{0,0} {}
    explicit  dd(Type r        ) noexcept : parent{r,0} {}
              dd(Type r, Type i) noexcept : parent{r,0}
    {
      std::cout << "icitte1 " << std::endl;
      *this += i;
    }

    template < ordered_value T>
    dd(T t)
    requires(!std::same_as<T, underlying_type> && scalar_value<T>)
    {
      using u_t =  underlying_type;
      u_t h(t);
      auto self = two_add(h, u_t(t-T(h)));
      get<0>(*this) = get<0>(self);
      get<1>(*this) = get<1>(self);
    }
    /// Stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, like<dd> auto const& r)
    {
      auto h = ddhi(r);
      auto l = ddlo(r);
      os << '(' << h << ')';
      if(is_positive(l)) os << "+(" << l << ')'; else os << "-(" << -l << ')';
      return os;
    }

    //==============================================================================================
    // Operators
    //==============================================================================================
    // -----  Operator +=
    EVE_FORCEINLINE friend auto operator+(like<dd> auto const& z) noexcept { return z; }

    template<like<dd> Z1, like<dd> Z2>
    EVE_FORCEINLINE friend auto& operator+=(Z1& self, Z2 const& o) noexcept
    {
//        std::cout << "icitte2 " << std::endl;
//        std::cout << tts::typename_<eve::element_type_t<Z2>> << std::endl;
      if constexpr(is_dd_v<eve::element_type_t<Z2>>)
      {
//        std::cout << "icitte3 " << std::endl;
        auto & [x0, x1] = self;
        auto   [z0, s2] = two_add(x0, ddhi(o));
        x0 = z0;
        auto finitex0 = is_finite(x0);
        if (eve::none(finitex0)) x1 = zero(as(x1));
        else
        {
          auto [t1, t2] = two_add( x1, ddlo(o));
          auto [t3, t4] = two_add(s2, t1);
          x1 = t3;
          t4 += t2;
          three_add(x0, x1, t4);
          x1 = if_else(finitex0, x1, zero);
        }
        return self;
      }
      else if constexpr(std::same_as<underlying_type_t<Z1>, underlying_type_t<Z2>>)
      {
//        std::cout << "icitte4 " << std::endl;
        auto & [x0, x1] = self;
        auto   [z0, s2] = two_add(x0, as_real_t<Z1>(o));
        x0 = z0;
        auto finitex0 = is_finite(x0);
        if (eve::none(finitex0)) x1 = zero(as(x1));
        else
        {
          auto finitex0 = is_finite(x0);
          auto  [z1, s3] = two_add(x1, s2);
          x1 = z1;
          three_add(x0, x1, s3);
          x1 = if_else(finitex0, x1, zero);
        }
//        std::cout << "icitte4 " << self << std::endl;
        return self;
      }
      else // Z1 is always scalar here
      {
        using u_t = underlying_type_t<Z1>;
        u_t h(o);
        Z1 oo(h, o-Z2(h));
        return  self += oo;
      }
    }

    // -----  Operator -=
    template<like<dd> Z>
    EVE_FORCEINLINE friend auto operator-(Z const& z) noexcept
    {
      return Z{-get<0>(z), -get<1>(z)};
    }

    template<like<dd> Z1, like<dd> Z2>
    EVE_FORCEINLINE friend auto& operator-=(Z1& self, Z2 const& o) noexcept
    {
      return self += -o;
    }

    // -----  Operator *=
    template<like<dd> Z1, like<dd> Z2>
    EVE_FORCEINLINE friend auto& operator*=(Z1& self, Z2 const& o) noexcept
    {
      if constexpr(is_dd_v<Z2>)
      {
        auto & [x0, x1] = self;
        auto [ohi, olo] = o;
        auto [p0, p1] = two_prod(x0, ohi);
        auto finitex0 = is_finite(x0);
        if (eve::none(finitex0)){
          x0 = p0;
          x1 = zero(as(x1));
          return self;
        }
        else
        {
          auto [p2, p4] = two_prod(x0, olo);
          auto [p3, p5] = two_prod(x1, ohi);
          auto p6 = x1*olo;
          three_add(p1, p2, p3);
          p2 += p4 + p5 + p6;
          three_add(p0, p1, p2);
          x0 = p0;
          x1 = p1;
          return self;
        }
      }
      else if constexpr(std::same_as<underlying_type_t<Z1>, underlying_type_t<Z2>>)
      {
        auto & [x0, x1] = self;
        auto [p0, p1] = two_prod(x0, o);
        x0 = p0;
        auto finitex0 = is_finite(x0);
        x1*= o;
        three_add(x0, x1, p1);
        x1 = if_else(finitex0, x1, zero);
        return self;
      }
      else // Z1 is always scalar here
      {
        using u_t = underlying_type_t<Z1>;
        u_t h(o);
        Z1 oo(h, o-Z2(h));
        return  self *= oo;
      }
    }

    template<like<dd> Z1, like<dd> Z2>
    EVE_FORCEINLINE friend auto& operator/=(Z1& self, Z2 const& o) noexcept
    {
      if constexpr(is_dd_v<Z2>)
      {
        auto & [x0, x1] = self;
        auto [ohi, olo] = o;
        auto q1 = x0 / ohi;  /* approximate quotient */
        Z1 r = self - o*q1;
        auto [rhi, rlo] = r;
        auto q2 = rhi/ohi;
        r -= o*q2;
        auto q3 = rhi/ohi;
        auto [q4, q5] = quick_two_add(q1, q2);
        r = Z1(q4, q5) + q3;
        return self = Z1(r);
      }
      else if constexpr(std::same_as<underlying_type_t<Z1>, underlying_type_t<Z2>>)
      {
        auto & [x0, x1] = self;
        auto q1 = x0 / o;  /* approximate quotient */
        Z1 r = self - o*q1;
        auto [rhi, rlo] = r;
        auto q2 = rhi/o;
        r -= o*q2;
        auto q3 = rhi/o;
        auto [q4, q5] = quick_two_add(q1, q2);
        r = Z1(q4, q5) + q3;
        return self = Z1(r);
        //        return self /= Z1(o);
      }
      else // Z1 is always scalar here
      {
        using u_t = underlying_type_t<Z1>;
        u_t h(o);
        Z1 oo(h, o-Z2(h));
        return  self /= oo;
      }
    }

    // -----  Operator <
    template<like<dd> Z1, like<dd> Z2>
    EVE_FORCEINLINE friend auto operator < (Z1 const& a, Z2 const& b) noexcept
    {
      if constexpr(is_dd_v<Z1> && is_dd_v<Z2>)
      {
        auto  [ahi, alo] = a;
        auto  [bhi, blo] = b;
        return (ahi < bhi) || ( (ahi == bhi) && (alo < blo) );
      }
      else
      {
        using r_t = decltype(a+b);
        return r_t(a) < r_t(b);
      }
    }

    //==============================================================================================
    // Functions support
    //==============================================================================================
    template<typename Tag, like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch(Tag const& tag, Z const& z) noexcept
        -> decltype(detail::dd_unary_dispatch(tag, z))
    {
      return detail::dd_unary_dispatch(tag, z);
    }

    template<typename Tag, decorator D, like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch(Tag const& tag, D const& d, Z const& z) noexcept
        -> decltype(detail::dd_unary_dispatch(tag, d, z))
    {
      return detail::dd_unary_dispatch(tag, d, z);
    }

    //==============================================================================================
    // Utilities
    //==============================================================================================
    template <typename U>
    EVE_FORCEINLINE static void three_add( U &a
                                         , U &b
                                         , U &c) noexcept
    {
      if constexpr( has_native_abi_v<U> )
      {
        auto [t1, t2] = two_add(a, b);
        auto z = two_add(c, t1);
        a = get<0>(z);
        z = two_add(t2, get<1>(z));
        b = get<0>(z);
        c = get<1>(z);

      }
      else return apply_over2(three_add, a, b);
    }

 //    EVE_FORCEINLINE static auto  qd_mul( dd const &a
//                                        , dd const &b) noexcept
//     {
//       auto [ahi,  alo] = a;
//       auto [bhi,  blo] = b;
//       auto [p0, p1] = two_prod(ahi, bhi);
//       auto finitep0 = is_finite(p0);
//       auto [p2, p4] = two_prod(ahi, blo);
//       auto [p3, p5] = two_prod(alo, bhi);
//       auto [p6, p7] = two_prod(alo, blo);
//       three_add(p1, p2, p3);
//       three_add(p4, p5, p6);
//       tie(p2, p4) = two_add(p2, p4);
//       three_add(p3, p4, p5);
//       tie(p3, p7) = two_add(p3, p7);
//       p4 += p6+p7;
//       renorm(p0, p1, p2, p3, p4);
//       return kumi::make_tuple(p0, p1, p2, p3);
//     }


    // quad-double = double-double * double-double
  //
 //  void qd_mul(dd_real const& a, dd_real const& b, double* p)
//   {
//     double p4, p5, p6, p7;

//     //  powers of e - 0, 1, 1, 1, 2, 2, 2, 3
//     p[0] = qd::two_prod(a._hi(), b._hi(), p[1]);
//     if (QD_ISFINITE(p[0]))
//     {
//       p[2] = qd::two_prod(a._hi(), b._lo(), p4);
//       p[3] = qd::two_prod(a._lo(), b._hi(), p5);
//       p6 = qd::two_prod(a._lo(), b._lo(), p7);

//       //  powers of e - 0, 1, 2, 3, 2, 2, 2, 3
//       qd::three_sum(p[1], p[2], p[3]);

//       //  powers of e - 0, 1, 2, 3, 2, 3, 4, 3
//       qd::three_sum(p4, p5, p6);

//       //  powers of e - 0, 1, 2, 3, 3, 3, 4, 3
//       p[2] = qd::two_sum(p[2], p4, p4);

//       //  powers of e - 0, 1, 2, 3, 4, 5, 4, 3
//       qd::three_sum(p[3], p4, p5);

//       //  powers of e - 0, 1, 2, 3, 4, 5, 4, 4
//       p[3] = qd::two_sum(p[3], p7, p7);

//       p4 += (p6 + p7);

//       qd::renorm(p[0], p[1], p[2], p[3], p4);
//     }
//     else
//     {
//       p[1] = p[2] = p[3] = 0.0;
//     }
//   }



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
