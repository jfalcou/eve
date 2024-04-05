//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core.hpp>

namespace eve
{
  template<typename Options>
  struct newton_t : callable<newton_t, Options, pedantic_option>
  {
    template<floating_value X, value... Cs, value... Ns>
    EVE_FORCEINLINE constexpr common_value_t<X, Cs..., Ns...>
    operator()(X x, Cs... cs,  Ns... ns) const noexcept
    { return EVE_DISPATCH_CALL(x, cs..., ns...); }

    template<floating_value X, value... Cs, value... Ns>
    EVE_FORCEINLINE constexpr
    eve::common_value_t<X, Cs...,  Ns...>
    operator()(X x, kumi::tuple<Cs...> const & t1, kumi::tuple<Ns...> const & t2) const noexcept
    { return EVE_DISPATCH_CALL(x, t1, t2); }

    EVE_CALLABLE_OBJECT(newton_t, newton_);
  };

//================================================================================================
//! @addtogroup polynomial
//! @{
//!   @var newton
//!   @brief Implement the Newton scheme to evaluate polynomials.
//!
//!   If \f$(a_i)_{0\le i\le n-1}\f$ denotes the coefficients of the polynomial by decreasing
//!   power order,  and \f$(c_i)_{0\le i\le n-2}\f$ the nodes, the Newton scheme evaluates
//!   the polynom \f$p\f$ at \f$x\f$ using the following formula :
//!
//!   \f$ \displaystyle p(x) = (((a_0(x-c_0)+a_1)(x-c_1)+ ... )(x-c_{n-2}) + a_{n-1})\f$
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!     template< eve::floating_ordered_value T, kumi::tuple C, kumi::tuple N>
//!     T newton(T x, C c, N n) noexcept;                                      //1
//!     template< eve::floating_ordered_value T, value... CN>
//!     T newton(T x, CN.. cn) noexcept;                                       //2

//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_ordered_value).
//!     * `c` :  tuple  containing The coefficients by decreasing power order.
//!     * `n` :  tuple  containing The nodes by decreasing power order.
//!     * `cn`:  coefficients followed by nodes unless empty the total number of values
//!              is to be odd.If s is this number,  the (s+1)/2 first are the coefs and the others the nodes.
//!    **Return value**
//!
//!    The value of the polynom at  `x` is returned.
//!
//!    **Notes**
//!
//!      If the coefficients or nodes are simd values of cardinal N, this means you simultaneously
//!      compute the values of N polynomials.
//!        *  If x is scalar, the polynomials are all computed at the same point
//!        *  If x is simd, the nth polynomial is computed on the nth value of x
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/polynomial/regular/newton.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::pedantic
//!
//!      the expression `eve::newton[pedantic](...)`
//!      computes the result using `eve::fma[pedantic]` instead of `eve::fma` in
//!      internal computation.
//!
//!      This is intended to insure more accurate computations where needed. This has no cost (and is
//!      automatically done) if the system has hard wired fma but is very expansive if it is not the case.
//! @}
//================================================================================================
  inline constexpr auto newton = functor<newton_t>;

  namespace detail
  {
    template<typename X, typename ...Coefs, typename... Nodes, callable_options O >
    EVE_FORCEINLINE constexpr auto
    newton_(EVE_REQUIRES(cpu_), O const &o, X xx,  kumi::tuple<Coefs...> const& cs
           , kumi::tuple<Nodes...> const& ns)
    {
      EVE_ASSERT((kumi::size_v<decltype(cs)> == 0 && kumi::size_v<decltype(ns)> == 0)||
                 (kumi::size_v<decltype(cs)> ==  kumi::size_v<decltype(ns)>+1), "nodes and coefs have incompatible sizes");

      using r1_t  =  common_value_t<X, Coefs...>;
      using r2_t  =  common_value_t<X, Nodes...>;
      using r_t   = common_value_t<r1_t, r2_t>;
      if constexpr(kumi::size_v<decltype(cs)> == 0)
      {
        return zero(as<r_t>());
      }
      else if constexpr(kumi::size_v<decltype(cs)> == 1)
      {
        return r_t(get<0>(cs));
      }
      else
      {
        r_t that = r_t(get<0>(cs));
        auto ans = kumi::zip(kumi::pop_front(cs), ns);
        auto compute = [&](auto ... args){
          auto doit = [&](auto an){
            auto [a, n] = an;
            that =  fma[o](that, xx-n, a);
          };
          ((doit(args), ...));
          return that;
        };
        return kumi::apply(compute, ans);
      }
    }

    template<typename X, typename ...CsNs, callable_options O >
    EVE_FORCEINLINE constexpr auto
    newton_(EVE_REQUIRES(cpu_), O const &o, X xx, CsNs... cns)
    {
      using r_t = common_value_t<X, CsNs...>;
      auto x = r_t(xx);
      constexpr auto s   = sizeof...(cns);
      if constexpr(s == 0) The expression `eve::horner[pedantic](...)`
        return zero(as(xx));
      else
      {
        constexpr auto siz = (s+1)/2;
        using tt_t = kumi::result::generate_t<s, r_t>;
        using tc_t = kumi::result::generate_t<siz, r_t>;
        using tn_t = kumi::result::generate_t<siz-1, r_t>;
        tt_t tcn {r_t{cns}...};
        auto tc = kumi::extract(tcn, kumi::index<0>, kumi::index<siz>);
        auto tn = kumi::extract(tcn, kumi::index<siz>);
        return newton[o](x,tc,tn);
      }
    }
  }
}
