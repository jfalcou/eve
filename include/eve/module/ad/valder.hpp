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
#include <eve/module/ad/regular/ad.hpp>
#include <eve/module/ad/regular/traits.hpp>
#include <eve/product_type.hpp>
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
  //! **Required header:** `#include <eve/module/complex.hpp>`
  //!
  //! eve::valder is structure representing pair of function value,  function derivative
  //! and mean to be used in conjunction with eve::wide.
  //!
  //! @tparam Type  Underlying floating point type
  //================================================================================================
  template<floating_scalar_value Type>
  struct valder : struct_support<valder<Type>, Type, Type>
  {
    using eve_disable_ordering = void;
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
    decltype(auto) tagged_dispatch( eve::tag::val_, like<valder> auto&& z )
    {
      return get<0>(EVE_FWD(z));
    }

    /// Retrieve the imaginary part of the current valder number
    EVE_FORCEINLINE friend
    decltype(auto) tagged_dispatch( eve::tag::der_, like<valder> auto&& z )
    {
      return get<1>(EVE_FWD(z));
    }

    //==============================================================================================
    // predicates
    //==============================================================================================

    template<typename Func>  static EVE_FORCEINLINE auto predicates(Func const & f, like < valder> auto const & z)
    {
      return f(eve::val(z));
    }

    template<typename Func, typename Z1, typename Z2>  static
    EVE_FORCEINLINE auto predicates( Func const & f
                                   , Z1  const & z1
                                   , Z2  const & z2)
      requires (is_valder_v<Z1> || is_valder_v<Z2>)
    {
      return f(val(z1), val(z2));
    }

    template<typename Func, typename Z1, typename... Zs>  static
    EVE_FORCEINLINE auto predicates( Func const & f
                                   , Z1 const & z1
                                   , Zs const & ... zs)
      requires is_valder_v<Z1> || (is_valder_v<Zs> ||  ...)
    {
      return f(val(z1), val(zs)...);
    }

//    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_equal_, auto const& z1, auto const& z2) noexcept  {return binary(is_equal , z1, z2);}


    //==============================================================================================
    //is_equal
    //==============================================================================================
//     template<like<valder> Z1, like<valder> Z2>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_equal_, Z1 const& z1, Z2 const& z2)
//     { return is_equal(val(z1), val(z2)); }

//     template<like<valder> Z1, typename Z2>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_equal_, Z1 const& z1, Z2 const& z2)
//     { return is_equal(val(z1), val(z2)); }

//     template<typename Z1, like<valder> Z2>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_equal_
//                                                , Z1 const& z1, Z2 const& z2)
//     { return is_equal(val(z1), val(z2)); }

//     template<like<valder> Z1, like<valder> Z2>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_equal_, numeric_type const &
//                                                , Z1 const& z1, Z2 const& z2)
//     { return predicates(is_equal, z1, z2); }

//     template<typename Z1, like<valder> Z2>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_equal_, numeric_type const &
//                                                , Z1 const& z1, Z2 const& z2)
//     { return predicates(numeric(is_equal), z1, z2); }

    //==============================================================================================
    //is_not_equal
    //==============================================================================================
    template<like<valder> Z1, typename Z2>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_not_equal_
                                               , Z1 const& z1, Z2 const& z2)
    { return predicates(is_not_equal, z1, z2); }

    template<typename Z1, like<valder> Z2>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_not_equal_
                                               , Z1 const& z1, Z2 const& z2)
    { return is_not_equal(val(z1), val(z2)); }

    template<like<valder> Z1, like<valder> Z2>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_not_equal_
                                               , Z1 const& z1, Z2 const& z2)
    { return predicates(is_not_equal, z1, z2); }

    template<typename Z1, like<valder> Z2>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_not_equal_, numeric_type const &
                                               , Z1 const& z1, Z2 const& z2)
    { return predicates(numeric(is_not_equal), z1, z2); }

    template<like<valder> Z1, typename Z2>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_not_equal_, numeric_type const &
                                               , Z1 const& z1, Z2 const& z2)
    { return predicates(numeric(is_not_equal), z1, z2); }

    template<like<valder> Z1, like<valder> Z2>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_not_equal_, numeric_type const &
                                               , Z1 const& z1, Z2 const& z2)
    { return predicates(numeric(is_not_equal), z1, z2); }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_less_
                                               , Z const& z1
                                               , Z const& z2) noexcept
    {
      return is_less(val(z1), val(z2));
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_less_equal_
                                               , Z const& z1
                                               , Z const& z2) noexcept
    {
      return is_less_equal_(val(z1), val(z2));
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_greater_
                                               , Z const& z1
                                               , Z const& z2) noexcept
    {
      return is_greater(val(z1), val(z2));
    }

    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::is_greater_equal_
                                               , Z const& z1
                                               , Z const& z2) noexcept
    {
      return is_greater_equal_(val(z1), val(z2));
    }

    //==============================================================================================
    //  Operators
    //==============================================================================================
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // add/sub
    ////////////////////////////////////////////////////////////////////////////////////////////////

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

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // multiplies
    ////////////////////////////////////////////////////////////////////////////////////////////////


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

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // divide
    ////////////////////////////////////////////////////////////////////////////////////////////////

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
    //  Unary functions
    //==============================================================================================


    template<typename Func, like < valder > Z>  static EVE_FORCEINLINE auto unary(Func const & f, Z const & z)
    {
      auto [v, d] = z;
      return Z{f(v), diff(f)(v)*d};
    }

    //==============================================================================================
    //  Binary functions
    //==============================================================================================

    template<typename Func, typename Z1, typename Z2>  static EVE_FORCEINLINE auto binary(Func const & f, Z1 const & z1, Z2 const & z2 )
      requires ((is_valder_v<Z1>)  || (is_valder_v<Z2>))
    {
      using v_t = decltype(f(val(z1), val(z2)));
      using r_t = eve::as_valder_t<v_t>;
      auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
      auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
      return r_t{f(v1, v2), sum_of_prod(diff_1st(f)(v1, v2), d1, diff_2nd(f)(v1, v2), d2)};
    }

    //==============================================================================================
    //  ternary functions
    //==============================================================================================

    template<typename Func, typename Z1, typename Z2, typename Z3>  static
    EVE_FORCEINLINE auto binary(Func const & f, Z1 const & z1, Z2 const & z2, Z3 const & z3 )
      requires ((is_valder_v<Z1>)  || (is_valder_v<Z2>) || (is_valder_v<Z3>))
    {
      using v_t = decltype(f(val(z1), val(z2), val(z3)));
      using r_t = eve::as_valder_t<v_t>;
      auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
      auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
      auto v3 = v_t(val(z3)); auto d3 = v_t(der(z3));
      r_t d = sum_of_prod(diff_1st(f)(v1, v2, v3), d1, diff_2nd(f)(v1, v2, v3), d2);
      return r_t{f(v1, v2, v3), fam(d, diff_3rd(f)(v1, v2, v3), d3)};
    }

    //unary functions
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::abs_,    like<valder> auto const& z) noexcept {return unary(abs,    z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::acos_,   like<valder> auto const& z) noexcept {return unary(acos,   z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::acosd_,  like<valder> auto const& z) noexcept {return unary(acosd,  z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::acosh_,  like<valder> auto const& z) noexcept {return unary(acosh,  z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::acospi_, like<valder> auto const& z) noexcept {return unary(acospi, z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::acot_,   like<valder> auto const& z) noexcept {return unary(acot,   z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::acotd_,  like<valder> auto const& z) noexcept {return unary(acotd,  z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::acoth_,  like<valder> auto const& z) noexcept {return unary(acoth,  z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::acotpi_, like<valder> auto const& z) noexcept {return unary(acotpi, z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::acsc_,   like<valder> auto const& z) noexcept {return unary(acsc,   z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::acscd_,  like<valder> auto const& z) noexcept {return unary(acscd,  z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::acsch_,  like<valder> auto const& z) noexcept {return unary(acsch,  z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::acscpi_, like<valder> auto const& z) noexcept {return unary(acscpi, z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::asec_,   like<valder> auto const& z) noexcept {return unary(asec,   z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::asecd_,  like<valder> auto const& z) noexcept {return unary(asecd,  z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::asech_,  like<valder> auto const& z) noexcept {return unary(asech,  z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::asecpi_, like<valder> auto const& z) noexcept {return unary(asecpi, z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::asin_,   like<valder> auto const& z) noexcept {return unary(asin,   z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::asind_,  like<valder> auto const& z) noexcept {return unary(asind,  z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::asinh_,  like<valder> auto const& z) noexcept {return unary(asinh,  z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::asinpi_, like<valder> auto const& z) noexcept {return unary(asinpi, z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::atan_,   like<valder> auto const& z) noexcept {return unary(atan,   z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::atand_,  like<valder> auto const& z) noexcept {return unary(atand,  z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::atanh_,  like<valder> auto const& z) noexcept {return unary(atanh,  z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::atanpi_, like<valder> auto const& z) noexcept {return unary(atanpi, z);}
   //cbrt optimized
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::ceil_,   like<valder> auto const& z) noexcept {return unary(ceil,   z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::cos_,    like<valder> auto const& z) noexcept {return unary(cos,    z);} // cos     to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::cosd_,   like<valder> auto const& z) noexcept {return unary(cosd,   z);} // cosd    to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::cosh_,   like<valder> auto const& z) noexcept {return unary(cosh,   z);} // cosh    to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::cospi_,  like<valder> auto const& z) noexcept {return unary(cospi,  z);} // cospi   to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::cot_,    like<valder> auto const& z) noexcept {return unary(cot,    z);} // cot     to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::cotd_,   like<valder> auto const& z) noexcept {return unary(cotd,   z);} // cotd    to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::coth_,   like<valder> auto const& z) noexcept {return unary(coth,   z);} // coth    to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::cotpi_,  like<valder> auto const& z) noexcept {return unary(cotpi,  z);} // cotpi   to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::csc_,    like<valder> auto const& z) noexcept {return unary(csc,    z);} // csc     to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::cscd_,   like<valder> auto const& z) noexcept {return unary(cscd,   z);} // cscd    to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::csch_,   like<valder> auto const& z) noexcept {return unary(csch,   z);} // csch    to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::cscpi_,  like<valder> auto const& z) noexcept {return unary(cscpi,  z);} // cscpi   to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::dec_,    like<valder> auto const& z) noexcept {return unary(dec,    z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::floor_,  like<valder> auto const& z) noexcept {return unary(floor,  z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::frac_,   like<valder> auto const& z) noexcept {return unary(frac,   z);}
    // if_else to be treted specially
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::inc_,    like<valder> auto const& z) noexcept {return unary(inc,    z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::log_,    like<valder> auto const& z) noexcept {return unary(log,    z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::log10_,  like<valder> auto const& z) noexcept {return unary(log10,  z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::log1p_,  like<valder> auto const& z) noexcept {return unary(log1p,  z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::log2_,   like<valder> auto const& z) noexcept {return unary(log2,   z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::minus_,  like<valder> auto const& z) noexcept {return unary(minus,  z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::oneminus_,like<valder> auto const& z) noexcept {return unary(oneminus,z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::plus_,   like<valder> auto const& z) noexcept {return unary(plus,   z);}
//    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::rec_,    like<valder> auto const& z) noexcept {return unary(rec,    z);} //rec to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::round_,  like<valder> auto const& z) noexcept {return unary(round,  z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::rsqrt_,  like<valder> auto const& z) noexcept {return unary(rsqrt,  z);} // rsqrt  to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::sec_,    like<valder> auto const& z) noexcept {return unary(sec,    z);} // sec     to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::secd_,   like<valder> auto const& z) noexcept {return unary(secd,   z);} // secd    to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::sech_,   like<valder> auto const& z) noexcept {return unary(sech,   z);} // sech    to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::secpi_,  like<valder> auto const& z) noexcept {return unary(secpi,  z);} // secpi   to optimize

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::sign_,   like<valder> auto const& z) noexcept {return unary(sign,   z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::signnz_, like<valder> auto const& z) noexcept {return unary(signnz, z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::sin_,    like<valder> auto const& z) noexcept {return unary(sin,    z);} // sin     to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::sind_,   like<valder> auto const& z) noexcept {return unary(sind,   z);} // sind    to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::sinh_,   like<valder> auto const& z) noexcept {return unary(sinh,   z);} // sinh    to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::sinpi_,  like<valder> auto const& z) noexcept {return unary(sinpi,  z);} // sinpi   to optimize


    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::sqr_,    like<valder> auto const& z) noexcept {return unary(sqr,    z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::sqrt_,   like<valder> auto const& z) noexcept {return unary(sqrt,   z);} // sqrt  to optimize
//    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::sqrt1pm1_,   like<valder> auto const& z) noexcept {return unary(sqrt1pm1,   z);} // sqrt1pm1  to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::tan_,    like<valder> auto const& z) noexcept {return unary(tan,    z);} // tan     to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::tand_,   like<valder> auto const& z) noexcept {return unary(tand,   z);} // tand    to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::tanh_,   like<valder> auto const& z) noexcept {return unary(tanh,   z);} // tanh    to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::tanpi_,  like<valder> auto const& z) noexcept {return unary(tanpi,  z);} // tanpi   to optimize
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::trunc_,  like<valder> auto const& z) noexcept {return unary(trunc,  z);} // tanpi   to optimize


    //binary functions
     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::atan2_,   auto const& z1, auto const& z2) noexcept  {return binary(atan2 , z1, z2);}
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::average_, auto const& z1, auto const& z2) noexcept  {return binary(average, z1, z2);}
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::copysign_, auto const& z1,  auto const& z2) noexcept {return binary(copysign, z1, z2);}
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::dist_,   auto const& z1, auto const& z2) noexcept  {return binary(dist, z1, z2);}
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::div_,    auto const& z1, auto const& z2) noexcept  {return binary(div,  z1, z2);}
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::exp_,    auto const& z1, auto const& z2) noexcept  {return binary(exp,  z1, z2);}     // exp   to optimize
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::exp2_,   auto const& z1, auto const& z2) noexcept  {return binary(exp2,  z1, z2);}    // exp2   to optimize
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::exp10_,  auto const& z1, auto const& z2) noexcept  {return binary(exp10,  z1, z2);}   // exp10   to optimize
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::expm1_,  auto const& z1, auto const& z2) noexcept  {return binary(expm1,  z1, z2);}   // expm1   to optimize
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::fam_, auto const& z1, auto const& z2, auto const& z3) noexcept {return ternary(fam, z1, z2, z3);}
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::fanm_, auto const& z1, auto const& z2, auto const& z3) noexcept {return ternary(fanm, z1, z2, z3);}
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::fma_, auto const& z1, auto const& z2, auto const& z3) noexcept {return ternary(fma, z1, z2, z3);}
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::fms_, auto const& z1, auto const& z2, auto const& z3) noexcept {return ternary(fms, z1, z2, z3);}
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::fnma_, auto const& z1, auto const& z2, auto const& z3) noexcept {return ternary(fnma, z1, z2, z3);}
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::fnms_, auto const& z1, auto const& z2, auto const& z3) noexcept {return ternary(fnms, z1, z2, z3);}
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::fsm_, auto const& z1, auto const& z2, auto const& z3) noexcept {return ternary(fsm, z1, z2, z3);}
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::fsnm_, auto const& z1, auto const& z2, auto const& z3) noexcept {return ternary(fsnm, z1, z2, z3);}
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::hypot_,  auto const& z1, auto const& z2) noexcept  {return binary(hypot, z1, z2);}
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::max_,    like<valder> auto const& z1, like<valder> auto const& z2) noexcept {return binary(max,       z1, z2);}
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::maxmag_, auto const& z1, auto const& z2) noexcept {return binary(maxmag,    z1, z2);}
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::min_,    auto const& z1, auto const& z2) noexcept {return binary(min,       z1, z2);}
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::minmag_, auto const& z1, auto const& z2) noexcept {return binary(minmag,    z1, z2);}




// is_equal.hpp
// is_eqz.hpp
// is_finite.hpp
// is_greater_equal.hpp
// is_greater.hpp
// is_imag.hpp
// is_inf.hpp
// is_not_finite.hpp
// is_less_equal.hpp
// is_less.hpp
// is_nan.hpp
// is_not_equal.hpp
// is_real.hpp
// ldexp.hpp


// maxnummag.hpp

// minmag.hpp
// minmod.hpp
// minnummag.hpp
// minus.hpp
// multiplies.hpp
// nearbyint.hpp
// plus.hpp
// pow_abs.hpp
// pow.hpp



    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::cbrt_, Z const& z) noexcept
    {
      auto [v, d] = z;
      auto cb = cbrt(v);
      return Z{cb, rec(3*sqr(cb))*d};
    }

    ///////////////////////////////////////////////////////////////////
    //clamp
    ///////////////////////////////////////////////////////////////////
    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::clamp_
                                                , Z const& z1
                                                , Z const& z2
                                                , Z const& z3
                                                ) noexcept
    {
      auto [v1, d1] = z1;
      auto [v2, d2] = z2;
      auto [v3, d3] = z3;
      auto d = diff_1st(clamp)(v1, v2, v3)*d1
        + diff_2nd(clamp)(v1, v2, v3)*d2
        + diff_3rd(clamp)(v1, v2, v3)*d3;
      return Z{clamp(v1, v2, v3), d};
    }

    ///////////////////////////////////////////////////////////////////
    //copysign
    ///////////////////////////////////////////////////////////////////
    template<like<valder> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::copysign_
                                                , Z const& z1
                                                , Z const& z2
                                                , Z const& z3
                                                ) noexcept
    {
      auto [v1, d1] = z1;
      auto [v2, d2] = z2;
      auto [v3, d3] = z3;
      auto d = diff_1st(copysign)(v1, v2, v3)*d1
        + diff_2nd(copysign)(v1, v2, v3)*d2;
      return Z{copysign(v1, v2, v3), d};
  }



//     template<like<valder> Z>
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::sqr_
//                                                 , Z const& z
//                                                 ) noexcept
//     {
//       auto [v, d] = z;
//       return Z{sqr(v), 2*v*d};
//     }



//     template<like<valder> Z>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sqrt_
//                                                , Z const& z ) noexcept
//     {
//       auto [v, d] = z;
//       auto sqrtv = sqrt(v);
//       return Z{sqrtv, -d/(2*sqrtv)};
//     }

//     //==============================================================================================
//     // trigo
//     //==============================================================================================

//     //==============================================================================================
//     //  exponential
//     //==============================================================================================
//     template<like<valder> Z>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::log_, Z const& z ) noexcept
//     {
//       auto [v, d] = z;
//       return Z{log(v), if_else(is_gtz(v), d*rec(v), allbits)};
//     }

//     template<like<valder> Z>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::log10_, Z const& z ) noexcept
//     {
//       auto [v, d] = z;
//       return Z{log10(v), d*if_else(is_gtz(v), rec(v)*invlog_10(as(v)), allbits)};
//     }

//     template<like<valder> Z>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::exp_, Z const& z ) noexcept
//     {
//        auto [v, d] = z;
//        auto e = exp(v);
//       return Z{e, e*d};

//     }

//     template<like<valder> Z>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::expm1_, Z const& z ) noexcept
//     {
//        auto [v, d] = z;
//        auto e = expm1(v);
//        return Z{e, inc(e)*d};

//     }

//     template<like<valder> Z>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::exp2_, Z const& z ) noexcept
//     {
//       auto [v, d] = z;
//       auto e = exp2(v);
//       return Z{e, e*log_2(as(v))*d};
//     }

//     template<like<valder> Z>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::exp10_, Z const& z ) noexcept
//     {
//       auto [v, d] = z;
//       auto e = exp10(v);
//       return Z{e, e*log_10(as(v))*d};
//     }

//     //==============================================================================================
//     //  Binary functions
//     //==============================================================================================

//     template < typename T >
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::ulpdist_
//                                                 , like<valder> auto const& z1
//                                                 , like<valder> auto const& z2
//                                                 ) noexcept
//     {
//       return eve::max( eve::ulpdist(val(z1), z2.val())
//                      , eve::ulpdist(der(z1), z2.der()));
//     }

//     template<like<valder> Z>
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::pow_
//                                                  , Z const & a
//                                                  , Z const & b
//                                                  ) noexcept
//     {
//       auto [v1, d1] = a;
//       auto [v2, d2] = b;
//       auto  puv = pow(v1, v2);
//       return Z{puv, puv*sum_of_prod(v2/v1), d1, log(v1), d2};
//     }

//     template<like<valder> Z, floating_real_value T>
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::pow_
//                                                 , Z const & a0
//                                                 , T const & a1
//                                                 ) noexcept
//     {
//       auto [v1, d1] = a;
//       return Z{ };
//     }

//     template<like<valder> Z, floating_real_value T>
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::pow_
//                                                 , T const & a0
//                                                 , Z const & a1
//                                                 ) noexcept
//     {
//       return if_else(is_eqz(a0)&&is_eqz(a1), one, exp(a1*cmplx(log)(a0)));
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::dist_
//                                                 , like<valder> auto  const & z1
//                                                 , like<valder> auto  const & z2
//                                                 ) noexcept
//     {
//       return abs(z1-z2);
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::acosh_
//                                                 , like<valder> auto  const & z
//                                                 ) noexcept
//     {
//       // acosh(a0) = +/-i acos(a0)
//       // Choosing the sign of multiplier to give nt2::val(acosh(a0)) >= 0
//       // we have compatibility with C99.
//       auto res = eve::acos(z);
//       return if_else(is_lez(der(res)),  mul_i(res), mul_mi(res));
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::acos_
//                                                 , like<valder> auto  const & z
//                                                 ) noexcept
//     {
//       return eve::detail::internal_acos(z);
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::cosh_
//                                                 , like<valder> auto  const & z
//                                                 ) noexcept
//     {
//       // We use cosh(z) = i cos(-i z);
//       // Note that C99 defines this the other way around (which is
//       // to say cos is specified in terms of cosh), this is consistent
//       // with C99 though:
//       return  mul_i(cos(mul_mi(z)));
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::cos_
//                                                 , like<valder> auto  const & z
//                                                 ) noexcept
//     {
//       return eve::detail::internal_cos(z);
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::cos_
//                                                 , like<valder> auto  const & z
//                                                 ) noexcept
//     {
//       // C99 definition here; cos(z) = -i cosh(iz):
//       return mul_mi(eve::cosh(mul_i(z)));
//     }

//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::cosh_
//                                                 , like<valder> auto  const & z
//                                                 ) noexcept
//     {
//       return eve::detail::internal_cosh(z);
//     }

 };

  //================================================================================================
  //! @}
  //================================================================================================
}
