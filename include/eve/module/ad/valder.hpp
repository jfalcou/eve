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

    // helpers
    //==============================================================================================
    // predicates
    //==============================================================================================

    template<typename Func, typename Z1, typename... Zs>  static
    EVE_FORCEINLINE auto predicates( Func const & f
                                   , Z1 const & z1
                                   , Zs const & ... zs)
    {
      return f(val(z1), val(zs)...);
    }


    //==============================================================================================
    //  Unary functions
    //==============================================================================================


    template<typename Func, like<valder> Z>  static EVE_FORCEINLINE auto unary(Func const & f, Z const & z)
    {
      auto [v, d] = z;
      return Z{f(v), diff(f)(v)*d};
    }

    //==============================================================================================
    //  Binary functions
    //==============================================================================================
    template<typename Func, typename Z1, typename Z2>
    static EVE_FORCEINLINE auto binary(Func const & f, Z1 const & z1, Z2 const & z2 )
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
    EVE_FORCEINLINE auto ternary(Func const & f, Z1 const & z1, Z2 const & z2, Z3 const & z3 )
    {
      using v_t = decltype(f(val(z1), val(z2), val(z3)));
      using r_t = eve::as_valder_t<v_t>;
      auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
      auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
      auto v3 = v_t(val(z3)); auto d3 = v_t(der(z3));
      v_t d = sum_of_prod(diff_1st(f)(v1, v2, v3), d1, diff_2nd(f)(v1, v2, v3), d2);
      return r_t{f(v1, v2, v3), fam(d, diff_3rd(f)(v1, v2, v3), d3)};
    }

    //==============================================================================================
    //  n_ary functions
    //==============================================================================================
    template<typename Func, typename V0, typename V1, typename... Vs>
    static EVE_FORCEINLINE auto n_ary(Func const & f, V0 const& z0, V1 const& z1, Vs const&... zs )
    {
      using v_t = decltype(f(val(zs)...));
      using r_t = eve::as_valder_t<v_t>;

      auto vs = kumi::make_tuple(v_t(val(z0)),v_t(val(z1)),v_t(val(zs))...);
      auto ds = kumi::make_tuple(v_t(der(zs))...);

      r_t d = sum_of_prod( kumi::apply(diff_1st(f),vs), v_t(der(z0)), kumi::apply(diff_2nd(f),vs), v_t(der(z1)));

      [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        ((d = fam(d, kumi::apply(diff_nth<I+3>(f),vs), get<I>(ds))),...);
      }(std::index_sequence_for<Vs...>{});

      return r_t{ kumi::apply(f,vs), d};
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

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // functions
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::ceil_,   like<valder> auto const& z) noexcept {return unary(ceil,   z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::dec_,    like<valder> auto const& z) noexcept {return unary(dec,    z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::floor_,  like<valder> auto const& z) noexcept {return unary(floor,  z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::frac_,   like<valder> auto const& z) noexcept {return unary(frac,   z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::inc_,    like<valder> auto const& z) noexcept {return unary(inc,    z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::log_,    like<valder> auto const& z) noexcept {return unary(log,    z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::log_abs_,like<valder> auto const& z) noexcept {return unary(log_abs, z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::log10_,  like<valder> auto const& z) noexcept {return unary(log10,  z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::log1p_,  like<valder> auto const& z) noexcept {return unary(log1p,  z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::log2_,   like<valder> auto const& z) noexcept {return unary(log2,   z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::minus_,  like<valder> auto const& z) noexcept {return unary(minus,  z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::oneminus_,like<valder> auto const& z) noexcept {return unary(oneminus,z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::plus_,   like<valder> auto const& z) noexcept {return unary(plus,   z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::round_,  like<valder> auto const& z) noexcept {return unary(round,  z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::sign_,   like<valder> auto const& z) noexcept {return unary(sign,   z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::signnz_, like<valder> auto const& z) noexcept {return unary(signnz, z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::sqr_,    like<valder> auto const& z) noexcept {return unary(sqr,    z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::trunc_,  like<valder> auto const& z) noexcept {return unary(trunc,  z);}

    //binary functions
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::atan2_,    maybe<valder> auto const& z1, maybe<valder> auto const& z2) noexcept {return binary(atan2 , z1, z2); }
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::average_,  maybe<valder> auto const& z1, maybe<valder> auto const& z2) noexcept {return binary(average, z1, z2);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::copysign_, maybe<valder> auto const& z1, maybe<valder> auto const& z2) noexcept {return binary(copysign, z1, z2);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::dist_,     maybe<valder> auto const& z1, maybe<valder> auto const& z2) noexcept {return binary(dist, z1, z2);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::div_,      maybe<valder> auto const& z1, maybe<valder> auto const& z2) noexcept {return binary(div,  z1, z2);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::hypot_,    maybe<valder> auto const& z1, maybe<valder> auto const& z2) noexcept {return binary(hypot, z1, z2);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::max_,      maybe<valder> auto const& z1, maybe<valder> auto const& z2) noexcept {return binary(max,       z1, z2);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::maxmag_,   maybe<valder> auto const& z1, maybe<valder> auto const& z2) noexcept {return binary(maxmag,    z1, z2);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::min_,      maybe<valder> auto const& z1, maybe<valder> auto const& z2) noexcept {return binary(min,       z1, z2);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::minmag_,   maybe<valder> auto const& z1, maybe<valder> auto const& z2) noexcept {return binary(minmag,    z1, z2);}

    //ternary functions
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::clamp_,     maybe<valder> auto const& z1, maybe<valder> auto const& z2, maybe<valder> auto const& z3) noexcept {return ternary(clamp, z1, z2, z3);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::fam_,      maybe<valder> auto const& z1, maybe<valder> auto const& z2, maybe<valder> auto const& z3) noexcept {return ternary(fam, z1, z2, z3);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::fanm_,     maybe<valder> auto const& z1, maybe<valder> auto const& z2, maybe<valder> auto const& z3) noexcept {return ternary(fanm, z1, z2, z3);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::fma_,      maybe<valder> auto const& z1, maybe<valder> auto const& z2, maybe<valder> auto const& z3) noexcept {return ternary(fma, z1, z2, z3);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::fms_,      maybe<valder> auto const& z1, maybe<valder> auto const& z2, maybe<valder> auto const& z3) noexcept {return ternary(fms, z1, z2, z3);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::fnma_,     maybe<valder> auto const& z1, maybe<valder> auto const& z2, maybe<valder> auto const& z3) noexcept {return ternary(fnma, z1, z2, z3);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::fnms_,     maybe<valder> auto const& z1, maybe<valder> auto const& z2, maybe<valder> auto const& z3) noexcept {return ternary(fnms, z1, z2, z3);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::fsm_,      maybe<valder> auto const& z1, maybe<valder> auto const& z2, maybe<valder> auto const& z3) noexcept {return ternary(fsm, z1, z2, z3);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::fsnm_,     maybe<valder> auto const& z1, maybe<valder> auto const& z2, maybe<valder> auto const& z3) noexcept {return ternary(fsnm, z1, z2, z3);}

    //binary predicates
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_equal_,         maybe<valder> auto const& z1, maybe<valder> auto const& z2) noexcept {return predicates(is_equal, z1, z2);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_not_equal_,     maybe<valder> auto const& z1, maybe<valder> auto const& z2) noexcept {return predicates(is_not_equal, z1, z2);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_less_,          maybe<valder> auto const& z1, maybe<valder> auto const& z2) noexcept {return predicates(is_less, z1, z2);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_less_equal_,    maybe<valder> auto const& z1, maybe<valder> auto const& z2) noexcept {return predicates(is_less_equal, z1, z2);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_greater_,       maybe<valder> auto const& z1, maybe<valder> auto const& z2) noexcept {return predicates(is_greater, z1, z2);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_greater_equal_, maybe<valder> auto const& z1, maybe<valder> auto const& z2) noexcept {return predicates(is_greater_equal, z1, z2);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_ordered_,       maybe<valder> auto const& z1, maybe<valder> auto const& z2) noexcept {return predicates(is_ordered, z1, z2);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_unordered_,     maybe<valder> auto const& z1, maybe<valder> auto const& z2) noexcept {return predicates(is_unordered, z1, z2);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_not_less_,          maybe<valder> auto const& z1, maybe<valder> auto const& z2) noexcept {return predicates(is_not_less, z1, z2);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_not_less_equal_,    maybe<valder> auto const& z1, maybe<valder> auto const& z2) noexcept {return predicates(is_not_less_equal, z1, z2);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_not_greater_,       maybe<valder> auto const& z1, maybe<valder> auto const& z2) noexcept {return predicates(is_not_greater, z1, z2);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_not_greater_equal_, maybe<valder> auto const& z1, maybe<valder> auto const& z2) noexcept {return predicates(is_not_greater_equal, z1, z2);}


    //unary predicates
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_eqz_,         like<valder> auto const& z) noexcept {return predicates(is_eqz, z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_even_,        like<valder> auto const& z) noexcept {return predicates(is_even, z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_nez_,         like<valder> auto const& z) noexcept {return predicates(is_nez, z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_infinite_,    like<valder> auto const& z) noexcept {return predicates(is_infinite, z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_finite_,      like<valder> auto const& z) noexcept {return predicates(is_finite, z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_lez_,         like<valder> auto const& z) noexcept {return predicates(is_lez, z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_ltz_,         like<valder> auto const& z) noexcept {return predicates(is_ltz, z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_gez_,         like<valder> auto const& z) noexcept {return predicates(is_gez, z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_gtz_,         like<valder> auto const& z) noexcept {return predicates(is_gtz, z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_nlez_,        like<valder> auto const& z) noexcept {return predicates(is_nlez, z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_nltz_,        like<valder> auto const& z) noexcept {return predicates(is_nltz, z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_ngez_,        like<valder> auto const& z) noexcept {return predicates(is_ngez, z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_ngtz_,        like<valder> auto const& z) noexcept {return predicates(is_ngtz, z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_not_finite_,  like<valder> auto const& z) noexcept {return predicates(is_not_finite, z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_nan_,         like<valder> auto const& z) noexcept {return predicates(is_nan, z);}
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::is_odd_,         like<valder> auto const& z) noexcept {return predicates(is_odd, z);}

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
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sinpi_
                                               , Z const& z ) noexcept
    {
      auto [v, d] = z;
      auto [s, c]= sinpicospi(v);
      return Z{s, -d*c*pi(as(v))};
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
 };

  //================================================================================================
  //! @}
  //================================================================================================
}
