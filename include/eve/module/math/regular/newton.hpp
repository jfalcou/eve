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
    template<floating_value X, value... CsNs>
    requires(eve::same_lanes_or_scalar<X, CsNs...>)
    EVE_FORCEINLINE constexpr common_value_t<X, CsNs...>
    operator()(X x, CsNs... csns) const noexcept
    { return EVE_DISPATCH_CALL(x, csns...); }

    template<floating_value X, value... Cs, value... Ns>
    requires(eve::same_lanes_or_scalar<X, Cs..., Ns...>)
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
//!   If \f$(c_i)_{0\le i\le n-1}\f$ denotes the coefficients of the polynomial by decreasing
//!   power order,  and \f$(m_i)_{0\le i\le n-2}\f$ the nodes, the Newton scheme evaluates
//!   the polynom \f$p\f$ at \f$x\f$ using the following formula :
//!
//!   \f$\qquad\displaystyle p(x) = (((c_0(x-m_0)+c_1)(x-m_1)+ ... )(x-m_{n-2}) + c_{n-1})\f$
//!
//!   @groupheader{Header file}
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
//!      // Regular overloads
//!      constexpr auto horner(value auto x, value auto ... cmi)                       noexcept; // 1
//!      constexpr auto horner(value auto x, kumi::non_empty_product_type auto ci
//!                                          kumi::non_empty_product_type auto mi)     noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto newton[conditional_expr auto c](*any of the above overloads*/) noexcept; // 2
//!      constexpr auto newton[logical_value auto m](*any of the above overloads*/)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto horner[pedantic](/*any of the above overloads*/)               noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`:  [real floating argument](@ref eve::floating_ordered_value).
//!     * `ci`:  tuple  containing the coefficients by decreasing power order.
//!     * `cm`:  tuple  containing the nodes by decreasing power order.
//!     * `cmi...`: all the coefficients followed by all the nodes, both in decreasing power order.
//!                The total number of values is to be odd. If s is this number, the (s+1)/2 first
//!                are taken as the coefs and the others are the nodes
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!      1. The value of the polynom at  `x` is returned.
//!      2. same as the call with the elements of the tuples.
//!      3. [The operation is performed conditionnaly](@ref conditional).
//!      4. `fma[pedantic]` instead of `fma` is used in internal computations.
//!
//!   @note If the coefficients or nodes are simd values of cardinal N, this means you simultaneously
//!      compute the values of N polynomials.
//!        *  If x is scalar, the polynomials are all computed at the same point
//!        *  If x is simd, the nth polynomial is computed on the nth value of x
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/newton.cpp}
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
      if constexpr(s == 0)
        return zero(as(xx));
      else
      {
        EVE_ASSERT(s&1, "nodes and coefs have incompatible sizes");
        kumi::result::generate_t<s, r_t> tcn{r_t{cns}...};
        auto [tc, tn] = split(tcn, kumi::index<(s+1)/2>);
        return newton[o](x,tc,tn);
      }
    }
  }
}
